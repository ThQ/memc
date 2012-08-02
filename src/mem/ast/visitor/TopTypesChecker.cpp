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
      case node::Kind::FIELD:
      {
         assert (node->Parent()->isClassNode());
         visitField(node->Parent()->BoundSymbol(),
            static_cast<node::Field*>(node));
         return false;
      }
      case node::Kind::FUNCTION:
      {
         assert (node->Parent()->isFileNode());
         visitFuncDecl(node->Parent()->BoundSymbol(),
            static_cast<node::Func*>(node));
         return false;
      }
   }
   return true;
}

#if 0

void
TopTypesChecker::visitArray (st::Symbol* scope, node::Array* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);

   st::Symbol* arr_sym = BugType();

   if (n->TypeNode() != NULL)
   {
      visitTypeName(scope, n->TypeNode());
      ensureSymbolIsType(n->TypeNode(), n->TypeNode()->BoundSymbol());

      if (n->LengthNode() != NULL)
      {
         visitExpr(scope, n->LengthNode());
      }

      if (n->TypeNode()->hasBoundSymbol())
      {
         if (n->LengthNode() == NULL)
         {
            arr_sym = st::Util::getUnsizedArrayType(n->TypeNode()->ExprType());
         }
         else
         {
            // Array with size
            if (n->LengthNode()->isNumberNode())
            {
               arr_sym = st::Util::lookupArrayType(scope,
               n->TypeNode()->BoundSymbol()->Name(),
               static_cast<ast::node::Number*>(n->LengthNode())->getInt());
            }
            // Array without size
            else
            {
               arr_sym = st::Util::getUnsizedArrayType(static_cast<st::Type*>(n->TypeNode()->BoundSymbol()));
            }
         }
      }
   }
   else
   {
      assert(false);
   }

   n->setBoundSymbol(arr_sym);
   n->setExprType(static_cast<st::Type*>(arr_sym));

   DEBUG_ENSURE (n->hasBoundSymbol());
   DEBUG_ENSURE (n->hasExprType());
   DEBUG_ENSURE (n->TypeNode() != NULL);
   DEBUG_ENSURE (n->TypeNode()->hasBoundSymbol());
   DEBUG_ENSURE (n->TypeNode()->hasExprType());
}

void
TopTypesChecker::visitDot (st::Symbol* scope, node::Node* node)
{
   node::Node* left_node = node->getChild(0);
   node::Node* right_node = node->getChild(1);

   if (left_node->isFinalIdNode())
   {
      visitQualifiedName(scope, left_node);
   }
   else if (left_node->isDotNode())
   {
      visitDot(scope, left_node);
   }

   if (right_node->isIdNode())
   {
      visitQualifiedName(left_node->BoundSymbol(), right_node);
   }
   else
   {
      // FIXME
      DEBUG_PRINT("Not expr type in left expr of dot\n");
      assert(false);
   }

   node->setBoundSymbol(right_node->BoundSymbol());
   node->setExprType(right_node->BoundSymbol());
}
#endif

void
TopTypesChecker::visitField (st::Symbol* scope, node::Field* field)
{
   assert(scope!=NULL);
   assert(scope->isClassSymbol());
   assert(field!=NULL);

   node::Text* name_node = static_cast<node::Text*>(field->NameNode());
   node::Node* type_node = field->ValueNode();
   assert (name_node != NULL);
   assert (type_node != NULL);

   visitExpr(scope, type_node);

   if (type_node->hasExprType()
      && ensureSymbolIsType(type_node, type_node->ExprType()))
   {
      // TODO Ugly one here...
      if (!type_node->ExprType()->isClassSymbol() || !static_cast<st::Class*>(type_node->BoundSymbol())->isDependingOn(static_cast<st::Class*>(scope)))
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
      assert(false);
   }
}

void
TopTypesChecker::visitFuncDecl (st::Symbol* scope, node::Func* func_decl)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (func_decl != NULL);

   st::Func* func_sym = new st::Func();
   if (func_decl->hasMetadata())
   {
      func_sym->setMetadata(func_decl->Metadata());
   }
   else
   {
      func_sym->setMetadata(new Metadata());
   }
   func_sym->setName(func_decl->gValue());
   scope->addChild(func_sym);

   func_decl->setBoundSymbol(func_sym);

   if (func_decl->ReturnTypeNode() != NULL)
   {
      this->visitFuncReturnType (func_decl, func_sym);
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

   node::Text* ret_ty_node = static_cast<node::Text*>(
      func_node->ReturnTypeNode());

   visitExpr(func_sym, ret_ty_node);
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

#if 0
void
TopTypesChecker::visitQualifiedName (st::Symbol* scope, node::Node* node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (node != NULL);

   node::Text* name_node = static_cast<node::Text*>(node);
   st::Symbol* node_ty = st::Util::lookupSymbol(scope, name_node->gValue());

   name_node->setExprType(node_ty);
   name_node->setBoundSymbol(node_ty);

   if (!name_node->hasExprType())
   {
      name_node->setExprType(BugType());
      name_node->setBoundSymbol(BugType());

      log::SymbolNotFound* err = new log::SymbolNotFound();
      err->sSymbolName(name_node->gValue());
      err->sScopeName(scope->gQualifiedName());
      err->format();
      //err->setPosition(name_node->copyPosition());
      log(err);
   }

   DEBUG_ENSURE(name_node->hasExprType());
   DEBUG_ENSURE(name_node->hasBoundSymbol());
}

void
TopTypesChecker::visitTypeName (st::Symbol* scope, node::Node* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);

   switch (n->Kind())
   {
      case node::Kind::FINAL_ID:
         visitQualifiedName(scope, n);
         break;

      case node::Kind::ARRAY:
         visitArray(scope, static_cast<node::Array*>(n));
         break;

      case node::Kind::DOT:
         visitDot(scope, static_cast<node::Dot*>(n));
         break;

      case node::Kind::POINTER:
      {
         visitTypeName(scope, static_cast<node::Ptr*>(n)->TypeNode());

         st::Type* ty = static_cast<st::Type*>(static_cast<node::Ptr*>(n)->TypeNode()->BoundSymbol());
         assert(ty != NULL);

         n->setBoundSymbol(st::Util::lookupPointer(scope, ty));
         n->setExprType(n->BoundSymbol());
         break;
      }

      default:
         DEBUG_PRINTF("Unsupported node {Kind:%d, Name:%s}\n", n->Kind(),
            n->KindNameCstr());
         assert(false);
   }

   DEBUG_ENSURE (n->hasExprType());
}
#endif

} } }
