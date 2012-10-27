#include "mem/ast/visitor/TopTypesChecker.hpp"

namespace mem { namespace ast { namespace visitor {


TopTypesChecker::TopTypesChecker ()
{
   _name = "ast.TopTypesChecker";
}

bool
TopTypesChecker::visit (node::Node* node)
{
   if (node == NULL) return true;

   node::Node* parent = node->Parent();

   switch (node->Kind())
   {
      case node::MetaKind::CLASS:
      {
         assert (parent != NULL);
         visitClass(node->BoundSymbol(), node::cast<node::Class>(node));
         return false;
      }
      case node::MetaKind::ENUM:
      {
         assert (parent != NULL);
         assert (node::isa<node::File>(parent));
         visitEnumType(parent->BoundSymbol(), node::cast<node::EnumType>(node));
         return false;
      }
      case node::MetaKind::FIELD:
      {
         assert (parent != NULL);
         visitField(parent->Parent()->BoundSymbol(), node::cast<node::Field>(node));
         return false;
      }
      case node::MetaKind::FUNCTION:
      {
         assert (parent != NULL);
         assert(parent->hasBoundSymbol());
         visitFuncDecl(parent->BoundSymbol(), node::cast<node::Func>(node));
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
   DEBUG_REQUIRE (node::isa<node::Class>(clss));

   node::Node* parent_ty_node = clss->ParentTypeNode();
   if (parent_ty_node != NULL)
   {
      visitExpr(scope, parent_ty_node);
      st::Symbol* parent_cls = parent_ty_node->BoundSymbol();
      if (parent_cls != NULL && ensureClassType(parent_ty_node))
      {
         st::cast<st::Class>(clss->BoundSymbol())->setParentClass(st::cast<st::Class>(parent_cls));
      }
   }

   node::NodeList* members_n = clss->MembersNode();

   for (size_t i = 0; i < members_n->ChildCount(); ++i)
   {
      if (node::isa<node::Func>(members_n->getChild(i)))
      {
         visitFuncDecl(clss->BoundSymbol(), node::cast<node::Func>(members_n->getChild(i)));
      }
      else
      {
         visitField(clss->BoundSymbol(), node::cast<node::Field>(members_n->getChild(i)));
      }
   }
}

void
TopTypesChecker::visitEnumType (st::Symbol* scope, node::EnumType* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (node::isa<node::EnumType>(n));

   visitExpr(scope, n->ParentTypeNode());

   // Create the enumeration type
   st::EnumType* enum_ty = new st::EnumType();
   enum_ty->setName(n->Value());

   // Add the enum to the parent file node
   scope->addChild(enum_ty);

   n->setBoundSymbol(enum_ty);

   if (n->ChildCount() > 0)
   {
      node::VarDecl* var_n = NULL;
      node::NodeList* members_n = n->MembersNode();
      for (size_t i = 0; i < members_n->ChildCount(); ++i)
      {
         node::FinalId* field_type_n = new node::FinalId();
         field_type_n->setValue(n->ParentTypeNode()->Value());

         var_n = node::cast<node::VarDecl>(members_n->getChild(i));
         var_n->setTypeNode(field_type_n);

         visitVarDecl(enum_ty, var_n);
         if (var_n->ValueNode() != NULL)
         {
            ensureConstantExpr(var_n->ValueNode());
         }
         var_n->setExprType(enum_ty);
         //st::cast<st::Var>(var_n->BoundSymbol())->setConstantValue(st::cast<st::IntConstant>(var_n->ValueNode()->BoundSymbol()));
      }
      enum_ty->setType(st::cast<st::Type>(n->ParentTypeNode()->BoundSymbol()));

      // We have to go over all the enum fields again to replace their original
      // type (ex: int) by the enum ty.
      // FIXME : This should be done otherwise, how ?
      st::SymbolMapIterator i;
      st::Var* field = NULL;
      for (i = enum_ty->Children().begin(); i != enum_ty->Children().end(); ++i)
      {
         field = st::cast<st::Var>(i->second);
         field->setType(enum_ty);
         field->setIsGlobal(true);
         field->setIsConstant(true);
      }
   }
}

void
TopTypesChecker::visitField (st::Symbol* scope, node::Field* field)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (st::isa<st::Class>(scope) || st::isa<st::EnumType>(scope));
   DEBUG_REQUIRE (field != NULL);
   DEBUG_REQUIRE (node::isa<node::Field>(field));

   node::Node* name_node = field->NameNode();
   node::Node* type_node = field->TypeNode();
   assert (name_node != NULL);
   assert (type_node != NULL);

   visitExpr(scope, type_node);

   if (type_node->hasExprType() && type_node->hasBoundSymbol())
   {
      if (ensureSizedExprType(type_node))
      {
         // TODO Ugly one here...
         st::Type* ty = st::cast<st::Type>(type_node->BoundSymbol());
         //if (ty->isClassType())// || !class_ty->isDependingOn(static_cast<st::Class*>(scope)))
         //{
            st::Field* sym_field = new st::Field();
            sym_field->setName(name_node->Value());
            sym_field->setType(ty);
            scope->addChild(sym_field);

            name_node->setBoundSymbol(sym_field);
            field->setBoundSymbol(sym_field);
            field->setExprType(sym_field->Type());
            assert(sym_field->Type() != NULL);
#if 0
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
#endif
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
   DEBUG_REQUIRE (node::isa<node::Func>(func_decl));

   // ----------------------
   //  Declare the function
   // ----------------------
   st::Func* func_sym = new st::Func();
   func_sym->setName(func_decl->Value());
   func_sym->setHasBody(func_decl->BodyNode() != NULL);
   scope->addChild(func_sym);
   _symbols->registerFunction(func_sym);

   func_decl->setBoundSymbol(func_sym);
   func_decl->NameNode()->setBoundSymbol(func_sym);
   func_decl->NameNode()->setExprType(func_sym);

   visitFuncReturnType (func_decl, func_sym);

   // ---------------------------
   //  Visit function parameters
   // ---------------------------
   node::Node* func_params = func_decl->ParamsNode();
   if (func_params != NULL)
   {
      visitFuncParams(scope, func_params, func_sym);
   }

   // -----------------------
   //  Register the function
   // -----------------------
   node::File* file_node = ast::util::getFileNode(func_decl);
   assert (file_node != NULL);
   file_node->registerFunction(func_decl);

   // ---------------------------
   //  Declare the function type
   // ---------------------------
   st::TypeVector func_args;
   for (size_t i = 0; i < func_sym->ParamCount(); ++i)
   {
      func_args.push_back(func_sym->getParam(i)->Type());
   }
   st::FunctionType* func_ty = st::util::getFunctionType(_symbols->System(), func_args, func_sym->ReturnType());
   st::PointerType* functor_ty = st::util::getPointerType(func_ty);
   func_sym->setType(func_ty);
   func_ty->setFunctorType(functor_ty);

   // ----------------
   //  Ctor specifics
   // ----------------
   if (st::isa<st::Class>(scope) && func_sym->Name() == "$ctor")
   {
      st::Class* cls_ty = st::cast<st::Class>(scope);
      cls_ty->setDefaultCtor(func_sym);
   }

   // ------------------
   //  Overriding check
   // ------------------
   // Try to find a function with the same name in ancestors
   // FIXME This should be moved to another function
   if (st::isa<st::Class>(scope))
   {
      st::Symbol* shadowed_sym = st::util::lookupSymbol(st::cast<st::Class>(scope)->ParentClass(), func_decl->Value());

      if (shadowed_sym != NULL)
      {
         func_sym->setOverridenFunction(st::cast<st::Func>(shadowed_sym));

         if (st::isa<st::Func>(shadowed_sym))
         {
            log::OverridingFunction* err = new log::OverridingFunction();
            err->setFunction(func_sym);
            err->setOverridenFunction(shadowed_sym->Parent());
            err->format();
            log(err);

            if (func_sym->ReturnType() != st::cast<st::Func>(shadowed_sym)->ReturnType())
            {
               log::Message* err = new log::Error();
               err->formatMessage("Return type was defined as %s (not %s)",
                  st::cast<st::Func>(shadowed_sym)->ReturnType()->gQualifiedNameCstr(),
                  func_sym->ReturnType()->gQualifiedNameCstr());
               err->formatDescription("Overriding function `%s' is redefining the return type of function `%s'",
                  func_sym->gQualifiedNameCstr(),
                  st::cast<st::Func>(shadowed_sym)->gQualifiedNameCstr());
               log(err);
            }
         }

      }
   }
}

void
TopTypesChecker::visitFuncParams (st::Symbol* scope, node::Node* params_node,
   st::Func* func_sym)
{
   st::Arg* param_sym = NULL;
   node::VarDecl* param_node = NULL;
   node::Node* name_node = NULL;
   node::Node* type_node = NULL;

   for (size_t i = 0; i < params_node->ChildCount(); ++i)
   {
      param_node = node::cast<node::VarDecl>(params_node->getChild(i));
      name_node = param_node->NameNode();
      type_node = param_node->TypeNode();

      visitExpr(scope, type_node);

      if (type_node->hasExprType())
      {
         // Add parameter to function symbol parameters
         param_sym = func_sym->addParam(name_node->Value(),
            st::cast<st::Type>(type_node->ExprType()));

         // Add parameter to the symbol table of the block
         if (type_node->hasExprType()
            && ensureSizedExprType(type_node))
         {
            param_sym->setType(type_node->ExprType());
         }
         func_sym->addChild(param_sym);

         name_node->setBoundSymbol(param_sym);
         name_node->setExprType(param_sym->Type());
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
   DEBUG_REQUIRE (node::isa<node::Func>(func_node));
   DEBUG_REQUIRE (func_sym != NULL);
   DEBUG_REQUIRE (st::isa<st::Func>(func_sym));
   DEBUG_REQUIRE (func_node->ReturnTypeNode() != NULL);

   node::Node* ret_ty_node = func_node->ReturnTypeNode();

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
      func_sym->setReturnType(ret_ty_node->ExprType());
      func_node->setExprType(func_sym->ReturnType());

      assert(func_sym->ReturnType() != NULL);
      assert(func_node->hasExprType());
   }

   DEBUG_ENSURE (ret_ty_node->hasExprType());
   DEBUG_ENSURE (ret_ty_node->hasBoundSymbol());
}

} } }
