#include "mem/ast/visitor/TopTypesChecker.hpp"

namespace mem { namespace ast { namespace visitor {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

TopTypesChecker::TopTypesChecker ()
{
   _name = "ast.TopTypesChecker";
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
TopTypesChecker::visit (node::Node* node)
{
   if (node == NULL) return true;

   node::Node* parent = node->Parent();

   switch (node->Kind())
   {
      case node::MetaKind::CLASS:
      {
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
TopTypesChecker::visitClass (st::Symbol* scope, node::Class* nodeClass)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeClass != NULL);
   DEBUG_REQUIRE (node::isa<node::Class>(nodeClass));


   //------------------------------
   // Register parent class if any
   //------------------------------
   node::Node* nodeParentType = nodeClass->ParentTypeNode();

   if (nodeParentType != NULL)
   {
      visitExpr(scope, nodeParentType);
      st::Symbol* symParentClass = nodeParentType->BoundSymbol();
      if (symParentClass != NULL && ensureClassType(nodeParentType))
      {
         st::cast<st::Class>(nodeClass->BoundSymbol())->setParentClass(st::cast<st::Class>(symParentClass));
      }
   }

   // ---------------------
   //  Visit class members
   // ---------------------
   node::NodeList* nodeMembers = nodeClass->MembersNode();
   node::Node* nodeMember = NULL;

   for (size_t i = 0; i < nodeMembers->ChildCount(); ++i)
   {
      nodeMember = nodeMembers->getChild(i);

      if (node::isa<node::Func>(nodeMember))
      {
         visitFuncDecl(nodeClass->BoundSymbol(), node::cast<node::Func>(nodeMember));
      }
      else if (node::isa<node::Field>(nodeMember))
      {
         visitField(nodeClass->BoundSymbol(), node::cast<node::Field>(nodeMember));
      }
      else
      {
         assert(false);
      }
   }
}

void
TopTypesChecker::visitEnumType (st::Symbol* scope, node::EnumType* nodeEnum)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeEnum != NULL);
   DEBUG_REQUIRE (node::isa<node::EnumType>(nodeEnum));

   visitExpr(scope, nodeEnum->ParentTypeNode());

   // -----------------------------
   //  Create the enumeration type
   // -----------------------------
   st::EnumType* symEnum = new st::EnumType();
   symEnum->setName(nodeEnum->Value());
   symEnum->setType(st::cast<st::Type>(nodeEnum->ParentTypeNode()->BoundSymbol()));

   // Add the enum to the parent file node
   scope->addChild(symEnum);

   nodeEnum->setBoundSymbol(symEnum);

   if (nodeEnum->ChildCount() > 0)
   {
      visitEnumMembers(symEnum, nodeEnum->MembersNode());
   }
}

void
TopTypesChecker::visitEnumMembers (st::EnumType* symEnum, node::NodeList* nodeMembers)
{
   // ------------------
   //  Set fields' type
   // ------------------
   node::VarDecl* nodeField = NULL;

   for (size_t i = 0; i < nodeMembers->ChildCount(); ++i)
   {
      node::FinalId* nodeFieldType = new node::FinalId();
      nodeFieldType->setValue(symEnum->Name());

      nodeField = node::cast<node::VarDecl>(nodeMembers->getChild(i));
      nodeField->setTypeNode(nodeFieldType);
      //nodeField->setIsGlobal(true);
      //nodeField->setIsConstant(true);

      visitVarDecl(symEnum, nodeField);
      if (nodeField->ValueNode() != NULL)
      {
         ensureConstantExpr(nodeField->ValueNode());
      }
      nodeField->setExprType(symEnum);
   }
}


void
TopTypesChecker::visitField (st::Symbol* scope, node::Field* nodeField)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (st::isa<st::Class>(scope) || st::isa<st::EnumType>(scope));
   DEBUG_REQUIRE (nodeField != NULL);
   DEBUG_REQUIRE (node::isa<node::Field>(nodeField));

   node::Node* nodeName = nodeField->NameNode();
   node::Node* nodeType = nodeField->TypeNode();

   visitExpr(scope, nodeType);

   if (nodeType->hasExprType() && nodeType->hasBoundSymbol())
   {
      if (ensureSizedExprType(nodeType))
      {
         st::Type* symFieldType = st::cast<st::Type>(nodeType->BoundSymbol());
         st::Field* symField = new st::Field();
         symField->setName(nodeName->Value());
         symField->setType(symFieldType);
         scope->addChild(symField);

         nodeName->setBoundSymbol(symField);
         nodeField->setBoundSymbol(symField);
         nodeField->setExprType(symField->Type());
      }
      else
      {
         nodeType->setExprType(BugType());
         nodeField->setExprType(BugType());
         nodeField->setBoundSymbol(BugType());
      }
   }
   else
   {
      DEBUG_UNREACHABLE();
   }

   DEBUG_ENSURE (nodeField->hasExprType());
   DEBUG_ENSURE (nodeField->hasBoundSymbol());
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

   DEBUG_PRINTF("Found function `%s %s' in `%s'\n",
      func_sym->gQualifiedName().c_str(),
      func_ty->Name().c_str(),
      scope->gQualifiedName().c_str());

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
TopTypesChecker::visitFuncParams (st::Symbol* scope, node::Node* nodeParams, st::Func* symFunc)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeParams != NULL);
   DEBUG_REQUIRE (symFunc != NULL);

   st::Arg* symParam = NULL;
   node::VarDecl* nodeParam = NULL;
   node::Node* nodeParamName = NULL;
   node::Node* nodeParamType = NULL;

   for (size_t i = 0; i < nodeParams->ChildCount(); ++i)
   {
      nodeParam = node::cast<node::VarDecl>(nodeParams->getChild(i));
      nodeParamName = nodeParam->NameNode();
      nodeParamType = nodeParam->TypeNode();

      visitExpr(scope, nodeParamType);

      if (nodeParamType->hasExprType())
      {
         // Add parameter to function symbol parameters
         symParam = symFunc->addParam(nodeParamName->Value(), st::cast<st::Type>(nodeParamType->ExprType()));

         // Add parameter to the symbol table of the block
         if (nodeParamType->hasExprType() && ensureSizedExprType(nodeParamType))
         {
            symParam->setType(nodeParamType->ExprType());
         }
         symFunc->addChild(symParam);

         nodeParamName->setBoundSymbol(symParam);
         nodeParamName->setExprType(symParam->Type());

         nodeParam->setBoundSymbol(symParam);
         nodeParam->setExprType(symParam->Type());
      }
   }
}

void
TopTypesChecker::visitFuncReturnType (node::Func* nodeFunc, st::Func* symFunc)
{
   DEBUG_REQUIRE (nodeFunc != NULL);
   DEBUG_REQUIRE (node::isa<node::Func>(nodeFunc));
   DEBUG_REQUIRE (nodeFunc->ReturnTypeNode() != NULL);
   DEBUG_REQUIRE (symFunc != NULL);
   DEBUG_REQUIRE (st::isa<st::Func>(symFunc));

   node::Node* nodeReturnType = nodeFunc->ReturnTypeNode();

   visitExpr(symFunc, nodeReturnType);
   nodeFunc->setBoundSymbol(symFunc);

   if (nodeReturnType->BoundSymbol()->Name() != "void")
   {
      ensureSizedExprType(nodeReturnType);
   }
   else
   {
      ensureSymbolIsType(nodeReturnType, nodeReturnType->BoundSymbol());
   }

   if (nodeReturnType->hasExprType())
   {
      symFunc->setReturnType(nodeReturnType->ExprType());
      nodeFunc->setExprType(symFunc->ReturnType());

      assert(symFunc->ReturnType() != NULL);
      assert(nodeFunc->hasExprType());
   }

   DEBUG_ENSURE (nodeReturnType->hasExprType());
   DEBUG_ENSURE (nodeReturnType->hasBoundSymbol());
}

} } }
