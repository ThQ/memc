#include "mem/ast/visitor/TopTypesChecker.hpp"

namespace mem { namespace ast { namespace visitor {


TopTypesChecker::TopTypesChecker ()
{
   _name = "ast.TopTypesChecker";
}

bool
TopTypesChecker::visit (node::Node* node)
{
   DEBUG_REQUIRE (node != NULL);

   node::Node* parent = node->Parent();

   switch (node->Kind())
   {
      case node::Kind::CLASS:
      {
         assert (parent != NULL);
         visitClass(node->BoundSymbol(), static_cast<node::Class*>(node));
         return true;
      }
      case node::Kind::ENUM:
      {
         assert (parent != NULL);
         assert (parent->isFileNode());
         visitEnum(parent->BoundSymbol(), static_cast<node::Enum*>(node));
         return false;
      }
      case node::Kind::FIELD:
      {
         assert (parent != NULL);
         assert (parent->isClassNode() || parent->isEnumNode());
         visitField(parent->BoundSymbol(), static_cast<node::Field*>(node));
         return false;
      }
      case node::Kind::FILE: break;
      case node::Kind::FUNCTION:
      {
         assert (parent != NULL);
         assert(parent->BoundSymbol() != NULL);
         visitFuncDecl(parent->BoundSymbol(), static_cast<node::Func*>(node));
         return false;
      }
      case node::Kind::ROOT: break;
      default:
         return false;
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
TopTypesChecker::visitEnum (st::Symbol* scope, node::Enum* n)
{

   st::EnumType* enum_ty = new st::EnumType();
   enum_ty->setName(n->gValue());
   scope->addChild(enum_ty);
   n->setBoundSymbol(enum_ty);

   if (n->ChildCount() > 0)
   {
      node::VarDecl* var_n = NULL;
      for (int i = 0; i < n->ChildCount(); ++i)
      {
         var_n = static_cast<node::VarDecl*>(n->getChild(i));
         visitVarDecl(enum_ty, var_n);
         ensureConstantExpr(var_n->ValueNode());
         var_n->setExprType(enum_ty);
         static_cast<st::Var*>(var_n->BoundSymbol())->setConstantValue(st::castToIntConstant(var_n->ValueNode()->BoundSymbol()));
      }
      enum_ty->setType(static_cast<node::VarDecl*>(n->getChild(0))->ValueNode()->ExprType());

      // We have to go over all the enum fields again to replace their original
      // type (ex: int) by the enum ty.
      st::SymbolMapIterator i;
      st::Var* field = NULL;
      for (i = enum_ty->Children().begin(); i != enum_ty->Children().end(); ++i)
      {
         field = st::castToVar(i->second);
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
   DEBUG_REQUIRE (scope->isClassType() || scope->isEnumType());
   DEBUG_REQUIRE (field != NULL);

   node::Text* name_node = static_cast<node::Text*>(field->NameNode());
   node::Node* type_node = field->TypeNode();
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

   // ----------------------
   //  Declare the function
   // ----------------------
   st::Func* func_sym = new st::Func();
   func_sym->setName(func_decl->gValue());
   func_sym->setHasBody(func_decl->BodyNode() != NULL);
   scope->addChild(func_sym);
   _symbols->registerFunction(func_sym);

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
   if (scope->isClassType() && func_sym->Name() == "$ctor")
   {
      st::Class* cls_ty = st::castToClassType(scope);
      cls_ty->setDefaultCtor(func_sym);
   }

   // ------------------
   //  Overriding check
   // ------------------
   // Try to find a function with the same name in ancestors
   if (scope->isClassType())
   {
      st::Symbol* shadowed_sym = st::util::lookupSymbol(st::castToClassType(scope)->ParentClass(), func_decl->gValue());

      if (shadowed_sym != NULL)
      {
         func_sym->setOverridenFunction(st::castToFunc(shadowed_sym));

         if (shadowed_sym->isFuncSymbol())
         {
            log::OverridingFunction* err = new log::OverridingFunction();
            err->sFunction(func_sym);
            err->sOverridenFunction(shadowed_sym->Parent());
            err->format();
            log(err);

            if (func_sym->ReturnType() != st::castToFunc(shadowed_sym)->ReturnType())
            {
               log::Message* err = new log::Error();
               err->formatMessage("Return type was defined as %s (not %s)",
                  static_cast<st::Func*>(shadowed_sym)->ReturnType()->gQualifiedNameCstr(),
                  func_sym->ReturnType()->gQualifiedNameCstr());
               err->formatDescription("Overriding function `%s' is redefining the return type of function `%s'",
                  func_sym->gQualifiedNameCstr(),
                  static_cast<st::Func*>(shadowed_sym)->gQualifiedNameCstr());
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
            st::castToType(type_node->ExprType()));

         // Add parameter to the symbol table of the block
         if (type_node->hasExprType()
            && ensureSizedExprType(type_node))
         {
            param_sym->setType(type_node->ExprType());
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
      func_sym->setReturnType(ret_ty_node->ExprType());
      func_node->setExprType(func_sym->ReturnType());

      assert(func_sym->ReturnType() != NULL);
      assert(func_node->hasExprType());
   }

   DEBUG_ENSURE (ret_ty_node->hasExprType());
   DEBUG_ENSURE (ret_ty_node->hasBoundSymbol());
}

} } }
