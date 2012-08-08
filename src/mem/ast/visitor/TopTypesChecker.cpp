#include "mem/ast/visitor/TopTypesChecker.hpp"

namespace mem { namespace ast { namespace visitor {


TopTypesChecker::TopTypesChecker ()
{
   _name = "ast.TopTypesChecker";
}

bool
TopTypesChecker::visit (node::Node* node)
{
   assert(node != NULL);

   switch (node->Kind())
   {
      case node::Kind::CLASS:
      {
         visitClass(node->BoundSymbol(), static_cast<node::Class*>(node));
         return true;
      }
      case node::Kind::FIELD:
      {
         assert (node->Parent()->isClassNode());
         visitField(node->Parent()->BoundSymbol(),
            static_cast<node::Field*>(node));
         return false;
      }
      case node::Kind::FUNCTION:
      {
         visitFuncDecl(node->Parent()->BoundSymbol(),
            static_cast<node::Func*>(node));
         return false;
      }
   }
   return true;
}

void
TopTypesChecker::visitClass (st::Symbol* scope, node::Class* clss)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (clss != NULL);

   node::Node* parent_ty_node = clss->gParentTypeNode();
   if (parent_ty_node != NULL)
   {
      visitExpr(scope, parent_ty_node);
      st::Symbol* parent_cls = parent_ty_node->BoundSymbol();
      if (parent_cls != NULL && ensureClassType(parent_ty_node))
      {
         static_cast<st::Class*>(clss->BoundSymbol())->setParentClass(static_cast<st::Class*>(parent_cls));
      }
   }
}

void
TopTypesChecker::visitField (st::Symbol* scope, node::Field* field)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (scope->isClassType());
   DEBUG_REQUIRE (field != NULL);

   node::Text* name_node = static_cast<node::Text*>(field->NameNode());
   node::Node* type_node = field->ValueNode();
   assert (name_node != NULL);
   assert (type_node != NULL);

   visitExpr(scope, type_node);

   if (type_node->hasExprType())
   {
      if (ensureSizedExprType(type_node))
      {
         // TODO Ugly one here...
         if (!type_node->ExprType()->isClassType() || !static_cast<st::Class*>(type_node->BoundSymbol())->isDependingOn(static_cast<st::Class*>(scope)))
         {
            st::Field* sym_field = new st::Field();
            sym_field->setName(name_node->gValue());
            sym_field->setType(type_node->ExprType());
            scope->addChild(sym_field);

            name_node->setBoundSymbol(sym_field);
            field->setBoundSymbol(sym_field);
            field->setExprType(sym_field->Type());
            assert(sym_field->Type() != NULL);

         }
         // Circular dependency
         else
         {
            log::CircularClassDependency* err = new log::CircularClassDependency();
            err->sBaseClassName(scope->gQualifiedName());
            err->sDepClassName(type_node->ExprType()->gQualifiedName());
            err->setPosition(field->copyPosition());
            err->format();
            log(err);
         }
      }
      else
      {
         type_node->setExprType(BugType());
         field->setExprType(BugType());
         field->setBoundSymbol(BugType());
      }
   }
   else
   {
      DEBUG_UNREACHABLE();
   }

   DEBUG_ENSURE (field->hasExprType());
   DEBUG_ENSURE (field->hasBoundSymbol());
}

void
TopTypesChecker::visitFuncDecl (st::Symbol* scope, node::Func* func_decl)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (func_decl != NULL);


   st::Func* func_sym = new st::Func();
   func_sym->setName(func_decl->gValue());
   func_sym->setHasBody(func_decl->BodyNode() != NULL);
   scope->addChild(func_sym);
   _symbols->registerFunction(func_sym);

   // Populate the function node linked list
   node::File* file_node = ast::util::getFileNode(func_decl);
   assert (file_node != NULL);
   file_node->registerFunction(func_decl);

   func_decl->setBoundSymbol(func_sym);

   if (func_decl->ReturnTypeNode() != NULL)
   {
      visitFuncReturnType (func_decl, func_sym);
   }
   else
   {
      // @TODO Set the return type to void
   }

   // Visit function parameters
   node::Node* func_params = func_decl->ParamsNode();
   if (func_params != NULL)
   {
      visitFuncParams(scope, func_params, func_sym);
   }

   // FIXME This should be the only thing to be done here, but while we are
   // catching on...
   st::TypeVector func_args;
   for (size_t i = 0; i < func_sym->ParamCount(); ++i)
   {
      func_args.push_back(func_sym->getParam(i)->Type());
   }
   st::FunctionType* func_ty = st::util::getFunctionType(_symbols->System(), func_args, func_sym->ReturnType());
   st::PointerType* functor_ty = st::util::getPointerType(func_ty);
   func_sym->setType(func_ty);
   func_ty->setFunctorType(functor_ty);
}

void
TopTypesChecker::visitFuncParams (st::Symbol* scope, node::Node* params_node,
   st::Func* func_sym)
{
   st::Arg* param_sym = NULL;
   node::Node* param_node = NULL;
   node::Text* name_node = NULL;
   node::Text* type_node = NULL;

   for (size_t i = 0; i < params_node->ChildCount(); ++i)
   {
      param_node = params_node->getChild(i);
      name_node = static_cast<node::Text*>(param_node->getChild(0));
      type_node = static_cast<node::Text*>(param_node->getChild(1));

      visitExpr(scope, type_node);

      if (type_node->hasExprType())
      {
         // Add parameter to function symbol parameters
         param_sym = func_sym->addParam(name_node->gValueCstr(),
            static_cast<st::Type*>(type_node->ExprType()));

         // Add parameter to the symbol table of the block
         if (type_node->hasExprType()
            && ensureSizedExprType(type_node))
         {
            param_sym->setType(static_cast<st::Class*>(type_node->ExprType()));
         }
         func_sym->addChild(param_sym);

         name_node->setBoundSymbol(param_sym);
         param_node->setBoundSymbol(param_sym);
         param_node->setExprType(param_sym->Type());
      }
   }
}

void
TopTypesChecker::visitFuncReturnType (node::Func* func_node,
   st::Func* func_sym)
{
   DEBUG_REQUIRE (func_node != NULL);
   DEBUG_REQUIRE (func_sym != NULL);
   DEBUG_REQUIRE (func_node->ReturnTypeNode() != NULL);

   node::Text* ret_ty_node = static_cast<node::Text*>(
      func_node->ReturnTypeNode());

   visitExpr(func_sym, ret_ty_node);
   assert (ret_ty_node != NULL);
   func_node->setBoundSymbol(func_sym);

   if (ret_ty_node->BoundSymbol()->Name() != "void")
   {
      ensureSizedExprType(ret_ty_node);
   }
   else
   {
      ensureSymbolIsType(ret_ty_node, ret_ty_node->BoundSymbol());
   }

   if (func_node->ReturnTypeNode()->hasExprType())
   {
      func_sym->setReturnType(static_cast<st::Class*>(ret_ty_node->ExprType()));
      func_node->setExprType(func_sym->ReturnType());

      assert(func_sym->ReturnType() != NULL);
      assert(func_node->hasExprType());
   }

   DEBUG_ENSURE (ret_ty_node->hasExprType());
   DEBUG_ENSURE (ret_ty_node->hasBoundSymbol());
}

} } }
