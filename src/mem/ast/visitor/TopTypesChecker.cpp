#include "mem/ast/visitor/TopTypesChecker.hpp"

namespace mem { namespace ast { namespace visitor {


TopTypesChecker::TopTypesChecker ()
{
   this->_name = "TopTypesChecker";
}

bool
TopTypesChecker::visit (node::Node* node)
{
   assert(node != NULL);

   node::Class* cls = static_cast<node::Class*>(node->_parent);
   st::Symbol* class_scope = NULL;

   switch (node->_type)
   {
      case MEM_NODE_FIELD:
      {
         class_scope = cls->gBoundSymbol();
         this->visitField(class_scope, static_cast<node::Field*>(node));
         return false;
      }
      case MEM_NODE_FUNCTION_DECLARATION:
      {
         class_scope = cls->gBoundSymbol();
         this->visitFuncDecl(class_scope, static_cast<node::Func*>(node));
         return false;
      }
   }
   return true;
}

void
TopTypesChecker::visitField (st::Symbol* scope, node::Field* field)
{
   assert(scope!=NULL);
   assert(field!=NULL);

   node::Text* name_node = static_cast<node::Text*>(field->getChild(0));
   node::Node* type_node = field->getChild(1);

   this->visitQualifiedName(scope, name_node);

   if (type_node->hasExprType()
      && this->ensureSymbolIsType(type_node, type_node->gExprType()))
   {
      st::Var* sym_field = new st::Var();
      sym_field->sName(name_node->gValue());
      sym_field->sType(static_cast<st::Class*>(type_node->gExprType()));
      scope->addChild(sym_field);

      name_node->sBoundSymbol(sym_field);
      field->sBoundSymbol(sym_field);
      field->sExprType(sym_field->_type);
      assert (sym_field->_type != NULL);
   }
}

void
TopTypesChecker::visitQualifiedName (st::Symbol* scope, node::Text* name_node)
{
   assert (name_node != NULL);

   if (name_node->isType(MEM_NODE_FINAL_ID))
   {
      name_node->sExprType(st::Util::lookupSymbol(scope, name_node->gValue()));
      if (!name_node->hasExprType())
      {
         log::Message* err = new log::Error();
         err->formatMessage("Unknown symbol (%s) in scope (%s)",
            name_node->gValueCstr(),
            scope->gQualifiedNameCstr());
         err->sPosition(name_node->copyPosition());
         this->log(err);
      }
   }
}

void
TopTypesChecker::visitFuncDecl (st::Symbol* scope, node::Func* func_decl)
{
   assert(scope != NULL);
   assert(func_decl != NULL);

   // Lookup the function, or create it
   st::Func* func_sym = st::Util::lookupFunction(scope, func_decl->gValue());
   if (func_sym == NULL)
   {
      func_sym = new st::Func();
      func_sym->sName(func_decl->gValue());
      scope->addChild(func_sym);
   }
   assert (func_sym != NULL);

   //
   st::FunctionSignature* func_sign_sym = new st::FunctionSignature();
   func_sym->addChild(func_sign_sym);

   // Add {this} to the symbol table
   if (!func_decl->isVirtual())
   {
      st::Var* vthis = new st::Var();
      vthis->sName("this");
      vthis->sType(static_cast<st::Class*>(func_sym->_parent));
      func_sign_sym->addChild(vthis);
   }

   if (func_decl->gReturnTypeNode() != NULL)
   {
      this->visitFuncReturnType (func_decl, func_sym, func_sign_sym);
   }
   else
   {
      // @TODO Set the return type to void
   }

   // Visit function parameters
   node::Node* func_params = func_decl->gParamsNode();
   if (func_params != NULL)
   {
      this->visitFuncParams(scope, func_params, func_sign_sym);
   }

   // Try to find an overridden function
   st::Class* parent_cls = static_cast<st::Class*>(static_cast<st::Class*>(scope)->_parent_type);
   st::Func* older_func = NULL;
   st::FunctionSignature* overridden_func = NULL;
   std::map<std::string, st::Symbol*>::iterator i;

   while (parent_cls != NULL)
   {
      older_func = static_cast<st::Func*>(parent_cls->getChild(func_sym->gName()));
      if (older_func != NULL)
      {
         for (i=older_func->_children.begin() ; i != older_func->_children.end() ; ++i)
         {
            overridden_func = static_cast<st::FunctionSignature*>(i->second);
            if (func_sign_sym->canOverride(overridden_func))
            {
               func_sign_sym->sOverriddenFunc(overridden_func);
               break;
            }
         }
      }
      parent_cls = static_cast<st::Class*>(parent_cls->_parent_type);
   }
}

void
TopTypesChecker::visitFuncParams (st::Symbol* scope, node::Node* params_node,
   st::FunctionSignature* func_sign_sym)
{
   st::Var* param_sym = NULL;
   node::Node* param_node = NULL;
   node::Text* name_node = NULL;
   node::Text* type_node = NULL;

   for (size_t i = 0; i < params_node->gChildCount(); ++i)
   {
      param_node = params_node->getChild(i);
      name_node = static_cast<node::Text*>(param_node->getChild(0));
      type_node = static_cast<node::Text*>(param_node->getChild(1));

      this->visitQualifiedName(scope, type_node);

      // Add parameter to the symbol table of the block
      param_sym = new st::Var();
      param_sym->sName(name_node->gValue());
      if (type_node->hasExprType()
         && this->ensureSymbolIsType(type_node, type_node->gExprType()))
      {
         param_sym->sType(static_cast<st::Class*>(type_node->gExprType()));
      }
      func_sign_sym->addChild(param_sym);

      name_node->sBoundSymbol(param_sym);
      param_node->sBoundSymbol(param_sym);
      param_node->sExprType(param_sym->_type);

      // Add parameter to function symbol parameters
      func_sign_sym->_params.push_back(param_node->gExprType());
   }
}

void
TopTypesChecker::visitFuncReturnType (node::Func* func_node,
   st::Func* func_sym, st::FunctionSignature* func_sign_sym)
{
   node::Text* ret_ty_node = static_cast<node::Text*>(func_node->gReturnTypeNode());

   this->visitQualifiedName(func_sym->_parent, ret_ty_node);
   func_node->sBoundSymbol(func_sign_sym);

   if (func_node->gReturnTypeNode()->hasExprType()
      && this->ensureSymbolIsType(ret_ty_node, ret_ty_node->gExprType()))
   {
      if (func_sym->gReturnType() != NULL
         && ret_ty_node->gExprType() != func_sym->gReturnType())
      {
         // Return type differs from a previously defined function with
         // the same name (function overloading)
         log::Message* err = new log::Error();
         err->sMessage("When overloading functions, return type must be the same");
         err->formatDescription("Return type was defined as %s, but got %s instead.",
            func_sym->gReturnType()->gQualifiedNameCstr(),
            ret_ty_node->gExprType()->gQualifiedNameCstr());
         err->sPosition(ret_ty_node->copyPosition());
         this->log(err);
      }

      func_sym->sReturnType(static_cast<st::Class*>(ret_ty_node->gExprType()));
      func_node->sExprType(func_sym->gReturnType());

      assert(func_sym->gReturnType() != NULL);
      assert(func_node->hasExprType());
   }
}


} } }
