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
         class_scope = cls->_bound_type;
         this->visit_field(class_scope, static_cast<node::Field*>(node));
         return false;
      }
      case MEM_NODE_FUNCTION_DECLARATION:
      {
         class_scope = cls->_bound_type;
         this->visit_function_declaration(class_scope, static_cast<node::Function*>(node));
         return false;
      }
   }
   return true;
}

void
TopTypesChecker::visit_field (st::Symbol* scope, node::Field* field)
{
   assert(scope!=NULL);
   assert(field!=NULL);

   this->visit_qualified_name(scope, static_cast<node::Text*>(field->getChild(1)));

   if (field->getChild(1)->_exp_type != NULL)
   {
      st::Var* sym_field = new st::Var();
      sym_field->sName(static_cast<node::Text*>(field->getChild(0))->_value);
      sym_field->sType(static_cast<st::Class*>(field->getChild(1)->_exp_type));
      scope->addChild(sym_field);

      field->getChild(0)->_bound_type = sym_field;
      field->_bound_type = sym_field;
      field->_exp_type = sym_field->_type;
      assert (sym_field->_type != NULL);
   }
}

void
TopTypesChecker::visit_qualified_name (st::Symbol* scope, node::Text* name_node)
{
   //assert (scope != NULL);
   assert (name_node != NULL);

   //printf("VISITING QUALIFIED NAME [%s]...\n", name_node->_value.c_str());
   if (name_node->isType(MEM_NODE_FINAL_ID))
   {
      name_node->sExprType(st::Util::lookup_symbol(scope, name_node->_value));
      if (name_node->gExprType() == NULL)
      {
         log::Message* err = new log::Message(log::ERROR);
         err->formatMessage("Unknown symbol (%s) in scope (%s)",
            name_node->_value.c_str(),
            scope->gQualifiedNameCstr());
         err->sPosition(name_node->_position->copy());
         this->_logger->log(err);
      }
   }
   // @FIXME : Make this happen
   else
   {
      /*
      node::Text* sub_node = NULL;
      st::Symbol* node_expr_type = NULL;

      for (size_t i = 0 ; i < name_node->_child_count; ++i)
      {
      }
      */
   }
}

void
TopTypesChecker::visit_function_declaration (st::Symbol* scope, node::Function* func_decl)
{
   assert(scope != NULL);
   assert(func_decl != NULL);

   // Add the function to the symbol table
   st::Function* func_sym = st::Util::lookup_function(scope, func_decl->_value);
   if (func_sym == NULL)
   {
      func_sym = new st::Function();
      func_sym->sName(func_decl->_value);
      scope->addChild(func_sym);
   }
   assert (func_sym != NULL);

   //
   st::FunctionSignature* func_sign_sym = new st::FunctionSignature();
   func_sym->addChild(func_sign_sym);

   // Add {this} to the symbol table
   if (!func_decl->is_virtual())
   {
      st::Var* vthis = new st::Var();
      vthis->sName("this");
      vthis->sType(static_cast<st::Class*>(func_sym->_parent));
      func_sign_sym->addChild(vthis);
   }

   // Visit return type node
   if (func_decl->g_return_type_node() != NULL)
   {
      this->visit_qualified_name(func_sym->_parent, static_cast<node::Text*>(func_decl->g_return_type_node()));
      func_decl->sBoundSymbol(func_sign_sym);
      if (func_decl->g_return_type_node()->gExprType() != NULL)
      {
         // Return type differs from a previously defined function with
         // the same name (function overloading)
         if (func_sym->_return_type != NULL && func_decl->g_return_type_node()->gExprType() != func_sym->_return_type)
         {
            log::Message* err = new log::Message(log::ERROR);
            err->sMessage("When overloading functions, return type must be the same");
            err->formatDescription("Return type was defined as %s, but got %s instead.",
               func_sym->_return_type->gQualifiedNameCstr(),
               func_decl->g_return_type_node()->gExprType()->gQualifiedNameCstr());
            err->sPosition(func_decl->g_return_type_node()->_position->copy());
            this->_logger->log(err);
         }

         // @TODO Ouch, this is really ugly
         func_sym->_return_type = static_cast<st::Class*>(func_decl->g_return_type_node()->gExprType());
         func_decl->sExprType(func_sym->gReturnType());

         assert(func_sym->gReturnType() != NULL);
         assert(func_decl->gExprType() != NULL);
      }
   }
   else
   {
      // @TODO Set the return type to void
   }

   // Visit function parameters
   node::Node* func_params = func_decl->g_parameters_node();
   if (func_params != NULL)
   {
      st::Var* param_sym = NULL;
      node::Node* param_node = NULL;
      for (size_t i = 0; i < func_params->_child_count; ++i)
      {
         param_node = func_params->getChild(i);
         this->visit_func_param(scope, param_node);

         // Add parameter to the symbol table of the block
         param_sym = new st::Var();
         param_sym->sName(static_cast<node::Text*>(param_node->getChild(0))->_value);
         if (param_node->getChild(1)->gExprType() != NULL)
         {
            param_sym->sType(static_cast<st::Class*>(param_node->getChild(1)->gExprType()));
         }
         func_sign_sym->addChild(param_sym);

         param_node->getChild(0)->sBoundSymbol(param_sym);
         param_node->sBoundSymbol(param_sym);
         param_node->sExprType(param_sym->_type);

         // Add parameter to function symbol parameters
         func_sign_sym->_params.push_back(param_node->gExprType());
      }
   }
}

void
TopTypesChecker::visit_func_param(st::Symbol* scope, node::Node* param_node)
{
   this->visit_qualified_name(scope, static_cast<node::Text*>(param_node->getChild(1)));
}


} } }
