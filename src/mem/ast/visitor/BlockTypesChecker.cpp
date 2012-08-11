#include "mem/ast/visitor/BlockTypesChecker.hpp"


namespace mem { namespace ast { namespace visitor {



BlockTypesChecker::BlockTypesChecker ()
{
   _name = "ast.BlockTypesChecker";
}

void
BlockTypesChecker::checkCallParameters (st::Symbol* caller, st::FunctionType* func_sym, node::Node* params)
{
   DEBUG_REQUIRE (func_sym != NULL);

   int param_count = params != NULL ? params->ChildCount() : 0;

   if (params != NULL)
   {
      if (func_sym->ArgumentCount() == param_count)
      {
         // Each parameter node must have the same expr type as declared in its
         // function definition.
         for (size_t i = 0; i < params->ChildCount(); ++i)
         {
            checkAssignment(params->getChild(i), func_sym->getArgument(i));
         }
      }
      else
      {
         log::BadParameterCount* err = new log::BadParameterCount();
         err->sExpectedParamCount(func_sym->ArgumentCount());
         err->sParamCount(params->ChildCount());
         err->format();
         //err->setPosition(params->copyPosition());
         log(err);
      }
   }
}

st::Func*
BlockTypesChecker::chooseOverridenFunction (st::FunctionVector funcs, st::TypeVector param_tys)
{
   std::vector<int> scores;
   int max_score = 0;
   size_t best_func = 0;
   scores.resize(funcs.size());

   for (size_t func_idx = 0; func_idx < funcs.size(); ++func_idx)
   {
      scores[func_idx] = 0;
      for (size_t j = 0; j < funcs[func_idx]->ParamCount(); ++j)
      {
         if (funcs[func_idx]->getParam(j)->Type() == param_tys[j])
         {
            scores[func_idx] += (j == 0) ? 2 : 1;
         }
      }
      if (scores[func_idx] > max_score)
      {
         max_score = scores[func_idx];
         best_func = func_idx;
      }
   }

   return funcs[best_func];
}

bool
BlockTypesChecker::visit (node::Node* node)
{
   if (node->isFuncNode())
   {
      node::Func* func = static_cast<node::Func*>(node);

      if (func->BodyNode() != NULL)
      {
         visitBlock(node->BoundSymbol(), func->BodyNode());
      }
      return false;
   }
   return true;
}

void
BlockTypesChecker::visitAmpersand (st::Symbol* scope, node::Node* node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (node != NULL);

   visitExpr(scope, node->getChild(0));

   if (node->getChild(0)->ExprType() != NULL)
   {
      st::Type* ptr_base_ty = static_cast<st::Type*>(node->getChild(0)->ExprType());
      std::string base_ty_name = ptr_base_ty->Name();
      st::Type* amp_ty = st::util::lookupPointer(scope, ptr_base_ty);

      if (amp_ty != NULL)
      {
         node->setExprType(amp_ty);
      }
      else
      {
         logSymbolNotFound(scope, node->getChild(0), ptr_base_ty->gQualifiedName() + "*");
         node->setExprType(BugType());
      }

      // FIXME There should be more checks. For ex you should not be able to
      // do : &2
   }
   else
   {
      node->getChild(0)->setExprType(BugType());
   }

   DEBUG_ENSURE (node->hasExprType());
   DEBUG_ENSURE (node->getChild(0) != NULL);
   DEBUG_ENSURE (node->getChild(0)->hasExprType());
}

void
BlockTypesChecker::visitArithmeticOp (st::Symbol* scope, node::Node* node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (node != NULL);
   DEBUG_REQUIRE (node->getChild(0) != NULL);
   DEBUG_REQUIRE (node->getChild(1) != NULL);

   // Check left node
   node::Node* left_node = node->getChild(0);
   visitExpr(scope, left_node);

   // Check right node
   node::Node* right_node = node->getChild(1);
   visitExpr(scope, right_node);

   std::string op_name;
   switch (node->Kind())
   {
      case node::Kind::OP_BIT_AND: op_name = "band"; break;
      case node::Kind::OP_BIT_OR:  op_name = "bor"; break;
      case node::Kind::OP_XOR:     op_name = "xor"; break;
      case node::Kind::OP_LSHIFT:  op_name = "<<"; break;
      case node::Kind::OP_RSHIFT:  op_name = ">>"; break;
      case node::Kind::OP_PLUS:    op_name = "+"; break;
      case node::Kind::OP_MINUS:   op_name = "-"; break;
      case node::Kind::OP_MODULO:  op_name = "%"; break;
      case node::Kind::OP_MUL:     op_name = "*"; break;
      case node::Kind::OP_DIV:     op_name = "/"; break;

      default:
         DEBUG_PRINTF("Unsupported arithmetic operator (%s)",
            node->KindName().c_str());
         assert (false);
   }

   if (op_name.size() != 0)
   {
      st::Type* left_ty = left_node->ExprType();
      st::Type* right_ty = right_node->ExprType();
      st::Type* common_ty = st::util::getBiggestIntType(
         static_cast<st::IntType*>(left_ty),
         static_cast<st::IntType*>(right_ty));
      // FIXME Must check operand types
      node->setExprType(common_ty);
   }
   else
   {
      fs::position::Composite* pos = new fs::position::Composite();
      pos->addChild(left_node->copyPosition());
      pos->addChild(right_node->copyPosition());

      log::UnsupportedArithmeticOperation* err =
         new log::UnsupportedArithmeticOperation();
      err->sLeftTypeName(left_node->ExprType()->NameCstr());
      err->sOpName(op_name.c_str());
      err->sRightTypeName(right_node->ExprType()->NameCstr());
      err->format();
      err->setPosition(pos);
      log(err);
   }

   DEBUG_ENSURE(node->hasExprType());
   DEBUG_ENSURE(node->getChild(0)->hasExprType());
   DEBUG_ENSURE(node->getChild(1)->hasExprType());
}

void
BlockTypesChecker::visitArray (st::Symbol* scope, node::Array* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);

   st::Symbol* arr_sym = BugType();
   int arr_size = -1;
   node::Node* type_n = n->TypeNode();
   node::Node* length_n = n->LengthNode();
   st::Type* item_ty = NULL;

   // -----------
   //  Item type
   // -----------
   if (type_n != NULL)
   {
      visitExpr(scope, type_n);
      ensureSymbolIsType(type_n, type_n->BoundSymbol());
      item_ty = static_cast<st::Type*>(type_n->BoundSymbol());

      assert(item_ty->isAnyType());
   }

   // ------
   //  Size
   // ------
   if (length_n != NULL)
   {
      visitExpr(scope, length_n);
      if (length_n->isNumberNode()
         && length_n->hasBoundSymbol()
         && length_n->BoundSymbol()->isIntConstant())
      {
         st::IntConstant* i_const = static_cast<st::IntConstant*>(length_n->BoundSymbol());
         // FIXME This may break since it returns an int64_t
         arr_size = (int)i_const->getSignedValue();
      }
   }

   // ------------
   //  Array type
   // ------------
   if (item_ty != NULL)
   {
      // Unsized array
      if (arr_size == -1)
      {
         arr_sym = st::util::getUnsizedArrayType(item_ty);
      }
      // Sized array
      else
      {
         arr_sym = st::util::getSizedArrayType(item_ty, arr_size);
      }
   }

   n->setBoundSymbol(arr_sym);
   n->setExprType(static_cast<st::Type*>(arr_sym));

   DEBUG_ENSURE (n->hasBoundSymbol());
   DEBUG_ENSURE (n->hasExprType());
   DEBUG_ENSURE (type_n != NULL);
   DEBUG_ENSURE (type_n->hasBoundSymbol());
   DEBUG_ENSURE (type_n->hasExprType());
}

void
BlockTypesChecker::visitBracketOp (st::Symbol* scope, node::BracketOp* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);

   visitExpr (scope, n->ValueNode());
   visitExpr (scope, n->IndexNode());

   node::Node* value_node = n->ValueNode();
   node::Node* index_n = n->IndexNode();
   st::Type* value_ty = value_node->ExprType();

   if (value_ty != NULL)
   {
      if (value_ty->isPointerType())
      {
         value_ty = static_cast<st::PointerType*>(value_ty)->getNonPointerParent();
      }

      if (value_ty->isArrayType())
      {
         st::ArrayType* arr = static_cast<st::ArrayType*>(value_ty);
         n->setExprType(arr->ItemType());
      }
      else if (value_ty->isTupleType())
      {
         // FIXME Nothing super safe here...
         if (index_n->isNumberNode()
            && index_n->hasBoundSymbol()
            && index_n->BoundSymbol()->isIntConstant())
         {
            node::Number* index_nb_n = static_cast<node::Number*>(index_n);
            st::IntConstant* i_const = static_cast<st::IntConstant*>(index_nb_n->BoundSymbol());

            // FIXME This may break, it returns an int64_t
            int item_index = (int)i_const->getSignedValue();
            // FIXME No bound checking...
            n->setExprType(static_cast<st::TupleType*>(value_ty)->Subtypes()[item_index]);
         }
      }
      /*
      else if (value_ty->isPointerType())
      {
         st::Type* ptr_parent = static_cast<st::PointerType*>(value_ty)->PointedType();
         if (ptr_parent->isArrayType())
         {
            n->setExprType(static_cast<st::ArrayType*>(ptr_parent)->ItemType());
         }
         else
         {
            n->setExprType(ptr_parent);
         }
      }
      */
      else
      {
         log::Error* err = new log::Error();
         err->setPrimaryText("Subscripted value is not of array or tuple type (nor a pointer to those types)");
         _logger->log(err);
      }
   }
   if (!n->hasExprType())
   {
      n->setExprType(BugType());
   }

   DEBUG_ENSURE (n->hasExprType());
}

void
BlockTypesChecker::visitCastOperator (st::Symbol* scope, node::CastOp* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);

   visitExpr(scope, n->ValueNode());
   visitExpr(scope, n->TypeNode());

   if (n->TypeNode()->BoundSymbol() != NULL)
   {
      n->setExprType(n->TypeNode()->BoundSymbol());
   }
   else
   {
      n->setExprType(BugType());
   }

   if (ensureSizedExprType(n))
   {
      st::Type* src_ty = n->ValueNode()->ExprType();
      st::Type* dest_ty = static_cast<st::Type*>(n->TypeNode()->BoundSymbol());

      /*
      bool can_cast = false;

      // TODO We should be able to cast from a class type to another
      if (!src_ty->canCastTo(dest_ty))
      {
         log::InvalidCast* err = new log::InvalidCast();
         err->sSourceType(src_ty);
         err->sDestType(dest_ty);
         err->format();
         log(err);
      }
      */
   }


   DEBUG_ENSURE (n->hasExprType());
}

void
BlockTypesChecker::visitCompOp (st::Symbol* scope, node::BinaryOp* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->LeftNode() != NULL);
   DEBUG_REQUIRE (n->RightNode() != NULL);

   visitExpr(scope, n->LeftNode());
   visitExpr(scope, n->RightNode());

   // FIXME Must check that type is a primitive type
   if (n->LeftNode()->ExprType() == n->RightNode()->ExprType())
   {
      n->setExprType(_core_types->gBoolTy());
   }
   else
   {
      // FIXME Log an appropriate error
      DEBUG_PRINT("Not same type in both expressions of binary operator.\n");
      assert (false);
   }

   DEBUG_REQUIRE (n->hasExprType());
}

void
BlockTypesChecker::visitDeref (st::Symbol* scope, node::Node* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->getChild(0) != NULL);

   visitExpr(scope, n->getChild(0));
   node::Node* value_node = n->getChild(0);
   st::Type* value_ty = value_node != NULL ? value_node->ExprType() : NULL;

   if (value_ty != NULL)
   {
      if (value_ty->isPointerType())
      {
         n->setExprType(static_cast<st::PointerType*>(value_ty)->PointedType());
      }
      else
      {
         n->setExprType(BugType());

         log::DerefNonPointer* err = new log::DerefNonPointer();
         err->sTypeName(value_ty->Name());
         err->format();
         log(err);
      }
   }
}

void
BlockTypesChecker::visitLogicalExpr (st::Symbol* scope, node::Node* expr_node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (expr_node != NULL);
   DEBUG_REQUIRE (expr_node->getChild(0) != NULL);
   DEBUG_REQUIRE (expr_node->getChild(1) != NULL);

   if (expr_node->isAndNode() || expr_node->isOrNode())
   {
      visitExpr(scope, expr_node->getChild(0));
      visitExpr(scope, expr_node->getChild(1));

      ensureBoolExpr(expr_node->getChild(0));
      ensureBoolExpr(expr_node->getChild(1));

      expr_node->setExprType(_core_types->gBoolTy());
   }

   DEBUG_ENSURE (expr_node->hasExprType());
}

void
BlockTypesChecker::visitCall (st::Symbol* scope, node::Call* call_node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (call_node != NULL);
   DEBUG_REQUIRE (call_node->CallerNode() != NULL);

   node::Node* base_object = call_node->CallerNode();
   this->visitExpr(scope, base_object);

   if (call_node->hasParamsNode())
   {
      visitExprList(scope, call_node->ParamsNode());
   }

   if (base_object->hasBoundSymbol())
   {
      // Macro call
      if (base_object->BoundSymbol()->isMacro())
      {
         visitMacroCall(scope, call_node);
      }
      // Function call
      else if (base_object->BoundSymbol()->isFuncSymbol())
      {
         visitFunctionCall(scope, call_node);
      }
      // Function pointer call
      else if (st::util::isFunctorType(base_object->ExprType()))
      {
         visitFunctorCall(scope, call_node);
      }
      else
      {
         call_node->setExprType(BugType());

         log::CallNonFunction* err = new log::CallNonFunction();
         err->sObjectName(base_object->BoundSymbol()->Name());
         err->sObjectTypeName(base_object->BoundSymbol()->gQualifiedName());
         err->setPosition(base_object->Position()->copy());
         err->format();
         log(err);
      }
   }
   else
   {
      call_node->setBoundSymbol(BugType());
   }

   // FIXME We cannot assert this since it can be a macro that may not have
   // an expression type
   //DEBUG_ENSURE(call_node->hasExprType());
}

void
BlockTypesChecker::visitDot (st::Symbol* scope, node::Dot* dot_node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (dot_node != NULL);
   DEBUG_REQUIRE (dot_node->LeftNode() != NULL);
   DEBUG_REQUIRE (dot_node->RightNode() != NULL);

   node::Node* left_node = dot_node->LeftNode();
   node::Node* right_node = dot_node->RightNode();

   visitExpr(scope, left_node);
   visitFinalId(left_node->BoundSymbol(), static_cast<node::FinalId*>(right_node));

   assert(right_node->isIdNode());

   if (left_node->hasBoundSymbol())
   {
      dot_node->setBoundSymbol(right_node->BoundSymbol());

      if (dot_node->hasBoundSymbol())
      {
         st::Symbol* expr_ty = st::util::getExprType(dot_node->BoundSymbol());
         if (expr_ty == NULL)
         {
            expr_ty = dot_node->BoundSymbol();
         }

         right_node->setBoundSymbol(dot_node->BoundSymbol());
         right_node->setExprType(st::util::getExprType(dot_node->BoundSymbol()));

         // If we are not accessing a class member, we can just flatten the dot
         // node by replacing it by final id.
         if (left_node->BoundSymbol()->isClassType()
            || left_node->BoundSymbol()->isEnumType()
            || left_node->BoundSymbol()->isNamespace())
         {
            ast::node::FinalId* fid = new ast::node::FinalId();
            fid->sValue(right_node->BoundSymbol()->Name());
            fid->setBoundSymbol(right_node->BoundSymbol());
            if (expr_ty->isAnyType())
            {
               fid->setExprType(expr_ty);
            }
            dot_node->Parent()->replaceChild(dot_node, fid);
            delete dot_node;
            dot_node = NULL;
         }
         else
         {
            dot_node->setExprType(static_cast<st::Type*>(expr_ty));
         }
      }
      else
      {
         dot_node->setExprType(BugType());

         log::SymbolNotFound* err = new log::SymbolNotFound();
         err->sSymbolName(static_cast<node::Text*>(right_node)->gValue());
         err->sScopeName(left_node->ExprType()->gQualifiedName());
         err->format();
         err->setPosition(right_node->copyPosition());
         log(err);
      }
   }

   //DEBUG_ENSURE (dot_node->hasExprType());
   //DEBUG_ENSURE (dot_node->hasBoundSymbol());
}

void
BlockTypesChecker::visitExprList (st::Symbol* scope, node::Node* node)
{
   node::Node* subnode = NULL;
   for (size_t i = 0; i < node->ChildCount(); ++i)
   {
      subnode = node->getChild(i);
      visitExpr(scope, subnode);
   }
}

void
BlockTypesChecker::visitExpr (st::Symbol* scope, node::Node* node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (node != NULL);

   switch (node->Kind())
   {
      case node::Kind::OP_DIV:
      case node::Kind::OP_MODULO:
      case node::Kind::OP_MUL:
      case node::Kind::OP_PLUS:
      case node::Kind::OP_MINUS:
      case node::Kind::OP_LSHIFT:
      case node::Kind::OP_RSHIFT:
      case node::Kind::OP_BIT_OR:
      case node::Kind::OP_BIT_AND:
      case node::Kind::OP_XOR:
         visitArithmeticOp(scope, node);
         break;

      case node::Kind::OP_NE:
      case node::Kind::OP_EQ_EQ:
      case node::Kind::OP_LT:
      case node::Kind::OP_LTE:
      case node::Kind::OP_GT:
      case node::Kind::OP_GTE:
         visitCompOp(scope, static_cast<node::BinaryOp*>(node));
         break;

      case node::Kind::ARRAY:
         visitArray (scope, util::castTo<node::Array*, node::Kind::ARRAY>(node));
         break;

      case node::Kind::BRACKET_OP:
         visitBracketOp(scope, util::castTo<node::BracketOp*,
            node::Kind::BRACKET_OP>(node));
         break;

      case node::Kind::OP_AND:
      case node::Kind::OP_OR:
         visitLogicalExpr(scope, node);
         break;

      case node::Kind::OP_CAST:
         visitCastOperator (scope, util::castTo<node::CastOp*,
            node::Kind::OP_CAST>(node));
         break;

      case node::Kind::AMPERSAND:
         visitAmpersand(scope, node);
         break;

      case node::Kind::CALL:
         visitCall(scope, util::castTo<node::Call*, node::Kind::CALL>(node));
         break;

      case node::Kind::DEREF:
         visitDeref(scope, node);
         break;

      case node::Kind::ENUM:
         // Don't do anything, it's taken care of by ::TopTypesChecker.
         break;

      case node::Kind::GROUP:
         visitGroup(scope, node);
         break;

      case node::Kind::IF:
         visitIf(scope, util::castTo<node::If*, node::Kind::IF>(node));
         break;

      case node::Kind::FINAL_ID:
         visitFinalId(scope, util::castTo<node::FinalId*, node::Kind::FINAL_ID>(node));
         break;

      case node::Kind::FOR:
         visitFor(scope, util::castTo<node::For*, node::Kind::FOR>(node));
         break;

      case node::Kind::EXPRESSION_LIST:
         visitExprList(scope, node);
         break;

      case node::Kind::NEW:
         visitNew(scope, util::castTo<node::New*, node::Kind::NEW>(node));
         break;

      case node::Kind::RETURN:
         visitReturn(scope, util::castTo<node::Return*, node::Kind::RETURN>(node));
         break;

      case node::Kind::WHILE:
         visitWhile(scope, util::castTo<node::While*, node::Kind::WHILE>(node));
         break;

      case node::Kind::POINTER:
         visitPointer(scope, util::castTo<node::Ptr*, node::Kind::POINTER>(node));
         break;

      case node::Kind::DOT:
         visitDot(scope, util::castTo<node::Dot*, node::Kind::DOT>(node));
         break;

      case node::Kind::NUMBER:
         visitNumber(scope, util::castTo<node::Number*, node::Kind::NUMBER>(node));
         break;

      case node::Kind::STRING:
         visitString(scope, util::castTo<node::String*, node::Kind::STRING>(node));
         break;

      case node::Kind::TUPLE:
         visitTuple(scope, static_cast<node::Tuple*>(node));
         break;

      case node::Kind::TUPLE_TYPE:
         visitTupleType(scope, static_cast<node::TupleType*>(node));
         break;

      case node::Kind::VARIABLE_DECLARATION:
         visitVarDecl(scope, static_cast<node::VarDecl*>(node));
         break;

      case node::Kind::VARIABLE_ASSIGNMENT:
         visitVarAssign(scope, static_cast<node::VarAssign*>(node));
         break;

      default:
         DEBUG_PRINTF("Unsupported node kind {kind: %d, name: %s}\n",
            node->Kind(),
            node::kKIND_NAMES[node->Kind()]);
         assert(false);
   }
}

void
BlockTypesChecker::visitFinalId (st::Symbol* scope, node::FinalId* id_node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (id_node != NULL);

   st::Symbol* sym = _symbols->lookupSymbol(scope, id_node->gValue());

   if (sym != NULL)
   {
      if (sym->isAliasSymbol())
      {
         id_node->setBoundSymbol(static_cast<st::Alias*>(sym)->Aliased());
      }
      else
      {
         id_node->setBoundSymbol(sym);
      }

      st::Type* expr_ty = expr_ty = st::util::getExprType(sym);

      if (expr_ty != NULL)
      {
         id_node->setExprType(expr_ty);
      }
   }
   else
   {
      id_node->setBoundSymbol(BugType());
      id_node->setExprType(BugType());

      logSymbolNotFound(scope, id_node, id_node->gValue());
   }

   DEBUG_ENSURE(id_node->hasBoundSymbol());
}

void
BlockTypesChecker::visitFor (st::Symbol* scope, node::For* n)
{
   visitExpr(scope, n->InitializationNode());

   visitExpr(scope, n->ConditionNode());
   ensureBoolExpr(n->ConditionNode());

   visitExpr(scope, n->IterationNode());

   visitBlock(scope, n->BlockNode());
}
void
BlockTypesChecker::visitFunctionCall (st::Symbol* scope, node::Call* call_n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (call_n != NULL);

   node::Node* base_object = call_n->CallerNode();
   st::Func* base_func = static_cast<st::Func*>(base_object->BoundSymbol());
   call_n->setExprType(base_func->ReturnType());

   if (base_object->isDotNode())
   {
      node::Dot* dot_n = static_cast<node::Dot*>(base_object);
      // We are calling an instance object
      // FIXME Spaghetti
      if (dot_n->LeftNode()->BoundSymbol()->isVarSymbol())
      {
         std::string func_name = static_cast<st::Var*>(dot_n->LeftNode()->BoundSymbol())->Type()->Name();
         func_name += ".";
         func_name += dot_n->RightNode()->BoundSymbol()->Name();

         node::FinalId* func_id = new node::FinalId();
         func_id->sValue(func_name);
         func_id->setBoundSymbol(base_func);
         func_id->setExprType(base_func->Type());

         call_n->setCaller(dot_n->LeftNode()->BoundSymbol());
         call_n->setIsInstanceCall(true);
         dot_n->Parent()->replaceChild(dot_n, func_id);

         node::Node* obj_n = dot_n->removeChild(dot_n->LeftNode());
         call_n->ParamsNode()->insertChild(obj_n);

         delete dot_n;
         dot_n = NULL;
      }
   }

   // Search for an overriding function that may fit the same signature
   // FIXME Spaghetti
   if (call_n->IsInstanceCall())
   {
      st::Class* cls = static_cast<st::Class*>(call_n->CallerNode()->BoundSymbol()->Parent());
      st::FunctionVector funcs = cls->getFunctionsLike(base_func->Name(), base_func->Type());
      st::Func* new_func = chooseOverridenFunction (funcs, call_n->ParamsNode()->packChildrenExprTypes());
      call_n->CallerNode()->setBoundSymbol(new_func);
   }

   if (call_n->hasParamsNode())
   {
      checkCallParameters(call_n->Caller(), base_func->Type(), call_n->ParamsNode());
   }

   DEBUG_ENSURE(call_n->hasExprType());
}

void
BlockTypesChecker::visitFunctorCall (st::Symbol* scope, node::Call* call_n)
{
   node::Node* base_object = call_n->CallerNode();
   st::PointerType* ptr_ty = static_cast<st::PointerType*>(base_object->ExprType());
   st::FunctionType* func_ty = static_cast<st::FunctionType*>(ptr_ty->getNonPointerParent());
   call_n->setExprType(func_ty->ReturnType());

   if (call_n->hasParamsNode())
   {
      checkCallParameters(NULL, func_ty, call_n->ParamsNode());
   }
}

void
BlockTypesChecker::visitGroup (st::Symbol* scope, node::Node* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->getChild(0) != NULL);

   visitExpr(scope, n->getChild(0));
   n->setExprType(n->getChild(0)->ExprType());

   DEBUG_ENSURE(n->hasExprType());
}

void
BlockTypesChecker::visitIf (st::Symbol* scope, node::If* if_node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (if_node != NULL);

   // Check condition expression
   visitExpr(scope, if_node->ConditionNode());
   ensureBoolExpr(if_node->ConditionNode());

   // Check block statements
   // FIXME Should create a special type of Symbol here
   st::Symbol* if_block = new st::Symbol();
   if_block->hintName(scope, "~if");
   scope->addChild(if_block);
   if_node->IfBlockNode()->setBoundSymbol(if_block);

   visitBlock(if_block, if_node->IfBlockNode());

   if (if_node->hasElseBlockNode())
   {
      st::Symbol* else_block = new st::Symbol();
      else_block->hintName(scope, "~else");
      scope->addChild(else_block);
      if_node->ElseBlockNode()->setBoundSymbol(else_block);

      visitBlock(else_block, if_node->ElseBlockNode());
   }

   DEBUG_ENSURE (if_node->ConditionNode()->hasExprType());
   DEBUG_ENSURE (if_node->ConditionNode()->ExprType()->Name() == "bool");
}

void
BlockTypesChecker::visitMacroCall (st::Symbol* scope, node::Call* call_n)
{
   node::Node* base_object = call_n->CallerNode();
   st::Macro* macro_sym = static_cast<st::Macro*>(base_object->BoundSymbol());
   macro::Macro* macro = static_cast<macro::Macro*>(macro_sym->MacroExpander());
   node::Node* macro_result = macro->expand(call_n);
   if (call_n->_prev != NULL)
   {
      call_n->_prev->_next = macro_result;
   }
   if (call_n->_next != NULL)
   {
      call_n->_next->_prev = macro_result;
   }
   call_n->unlink();
   delete call_n;
   visitExpr(scope, macro_result);
}

void
BlockTypesChecker::visitNew (st::Symbol* scope, node::New* new_node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (new_node != NULL);

   node::Node* ty_node = new_node->TypeNode();
   assert (ty_node != NULL);

   visitExpr(scope, ty_node);
   ensureSymbolIsType(ty_node, ty_node->BoundSymbol());

   if (ty_node->BoundSymbol()->isArrayType())
   {
      st::ArrayType* unsized_arr_ty = st::util::getUnsizedArrayType(static_cast<st::ArrayType*>(ty_node->BoundSymbol()));
      st::Type* ptr_ty = st::util::getPointerType(unsized_arr_ty);
      new_node->setExprType(ptr_ty);
   }
   else
   {
      st::Type* ptr_ty = st::util::lookupPointer(scope, static_cast<st::Type*>(ty_node->ExprType()));
      new_node->setExprType(ptr_ty);
   }

   DEBUG_ENSURE(new_node->hasExprType());
}

void
BlockTypesChecker::visitNumber (st::Symbol* scope, node::Number* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->hasBoundSymbol());
   DEBUG_REQUIRE (n->BoundSymbol()->isIntConstant());
}

#if 0
void
BlockTypesChecker::visitVarLiteralNumber (st::Type* expected_type,
   node::Text* nb_node)
{
/**
   if (expected_type == this->_symbols->_glob_int_cls)
   {
      int val = 0;
      node::Number* num_node = new node::Number();

      if (mem::Util::getIntFromString(nb_node->gValue().c_str(), val))
      {
         printf("INT ! %d\n", val);
         nb_node->gParent()->replaceChild(nb_node, num_node);
         num_node->setInt(val);
         num_node->sExprType(this->_symbols->_glob_int_cls);
         delete nb_node;
      }
      else
      {
         printf("NOT int...\n");
      }
      //char* small = nb_node->gValue().substr(0, nb_node->gValue().length()-1);
   }
*/
}
#endif


void
BlockTypesChecker::visitBlock (st::Symbol* scope, node::Node* block)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (block != NULL);

   if (scope != NULL && block != NULL)
   {
      node::Node* st = NULL;

      for (size_t i = 0; i < block->ChildCount(); ++i)
      {
         st = block->getChild(i);
         visitExpr(scope, st);
      }
   }
}

void
BlockTypesChecker::visitPointer (st::Symbol* scope, node::Ptr* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);

   if (n->TypeNode() != NULL)
   {
      visitExpr(scope, n->TypeNode());

      ensureSymbolIsType(n->TypeNode(), n->TypeNode()->BoundSymbol());

      if (!n->TypeNode()->hasBoundSymbol())
      {
         n->TypeNode()->setBoundSymbol(BugType());
      }

      if (n->TypeNode()->hasBoundSymbol()
         && n->TypeNode()->BoundSymbol()->isAnyType())
      {
         st::Symbol* ptr_ty = st::util::lookupPointer(scope,
            static_cast<st::Type*>(n->TypeNode()->BoundSymbol()));
         assert (ptr_ty != NULL);
         n->setBoundSymbol(ptr_ty);
         n->setExprType(static_cast<st::Type*>(ptr_ty));
      }
      else
      {
         n->setBoundSymbol(BugType());
         n->setExprType(BugType());
      }
   }

   DEBUG_ENSURE (n->hasExprType());
   DEBUG_ENSURE (n->hasBoundSymbol());
}

void
BlockTypesChecker::visitReturn (st::Symbol* scope, node::Return* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);

   st::Func* parent_func = util::getParentFunction(n);
   assert (parent_func);
   assert (parent_func->isFuncSymbol());

   node::Node* value_node = n->ValueNode();
   assert (value_node != NULL);

   visitExpr(scope, value_node);

   if (checkAssignment(value_node, parent_func->ReturnType()))
   {
      n->setExprType(parent_func->ReturnType());
   }
   else
   {
      log::ReturnTypeDiffersFromPrototype* err = new
         log::ReturnTypeDiffersFromPrototype();
      err->sFuncName(parent_func->gQualifiedName());
      err->sRetTy(n->ValueNode()->ExprType());
      err->sExpectedRetTy(parent_func->ReturnType());
      //err->setPosition(value_node->copyPosition());
      err->format();
      log(err);

      n->setExprType(BugType());
   }

   DEBUG_ENSURE (n->hasExprType());
   DEBUG_ENSURE (n->ValueNode()->hasExprType());
}

void
BlockTypesChecker::visitString (st::Symbol* scope, node::String* n)
{
   DEBUG_REQUIRE(n != NULL);

   st::ArrayType* unsized_arr_ty = st::util::getUnsizedArrayType(_symbols->_core_types.gCharTy());
   n->setExprType(st::util::getPointerType(unsized_arr_ty));

   DEBUG_ENSURE (n->hasExprType());
}

void
BlockTypesChecker::visitTuple (st::Symbol* scope, node::Tuple* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);

   st::TypeVector tys;
   bool an_expr_failed = false;
   for (size_t i = 0; i < n->ChildCount(); ++i)
   {
      visitExpr(scope, n->getChild(i));
      if (n->getChild(i)->hasExprType())
      {
         tys.push_back(n->getChild(i)->ExprType());
      }
      else
      {
         an_expr_failed = true;
         break;
      }
   }

   if (!an_expr_failed)
   {
      st::TupleType* tuple_ty = st::util::getTupleType(_symbols->System(), tys);
      n->setExprType(tuple_ty);
      ensureSizedExprType(n);
   }
   else
   {
      n->setExprType(BugType());
   }

   DEBUG_ENSURE (n->hasExprType());
}

void
BlockTypesChecker::visitTupleType (st::Symbol* scope, node::TupleType* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);

   st::TypeVector tys;
   for (size_t i = 0; i < n->ChildCount(); ++i)
   {
      visitExpr(scope, n->getChild(i));
      ensureSizedExprType (n->getChild(i));
      assert(n->getChild(i)->hasExprType());
      tys.push_back(n->getChild(i)->ExprType());
   }

   st::TupleType* tuple_ty = st::util::getTupleType(_symbols->System(), tys);

   if (tuple_ty != NULL)
   {
      n->setExprType(tuple_ty);
      n->setBoundSymbol(tuple_ty);
   }
   else
   {
      n->setExprType(BugType());
      n->setBoundSymbol(BugType());
   }
}

void
BlockTypesChecker::visitVarAssign (st::Symbol* scope, node::VarAssign* node)
{
   DEBUG_REQUIRE (node != NULL);
   DEBUG_REQUIRE (node->NameNode() != NULL);
   DEBUG_REQUIRE (node->ValueNode() != NULL);

   visitExpr(scope, node->NameNode());
   visitExpr(scope, node->ValueNode());

   if (node->NameNode()->isAssignable())
   {
      if (node->NameNode()->hasExprType())
      {
         node->setExprType(node->NameNode()->ExprType());
      }
      else
      {
         node->NameNode()->setExprType(BugType());
         node->NameNode()->setBoundSymbol(BugType());
      }
      checkAssignment (node->ValueNode(), node->ExprType());
   }
   else
   {
      node->NameNode()->setExprType(BugType());
      node->NameNode()->setBoundSymbol(BugType());

      log::NotAssignable* e = new log::NotAssignable();
      //e->setPosition(node->NameNode()->copyPosition());
      e->format();
      log(e);
   }

   DEBUG_ENSURE (node->hasExprType());
   DEBUG_ENSURE (node->ValueNode()->hasExprType());
}

void
BlockTypesChecker::visitVarDecl (st::Symbol* scope,
   node::VarDecl* var_decl_node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (var_decl_node != NULL);
   DEBUG_REQUIRE (var_decl_node->NameNode() != NULL);
   DEBUG_REQUIRE (var_decl_node->TypeNode() != NULL);

   node::Text* name_node = var_decl_node->NameNode();
   node::Node* type_node = var_decl_node->TypeNode();
   node::Node* value_node = var_decl_node->ValueNode();

   // ------------------
   //  Check VALUE node
   // ------------------
   // Value is declared
   if (value_node != NULL)
   {
      visitExpr(scope, value_node);
      value_node = var_decl_node->ValueNode();
      if (!value_node->hasExprType()) value_node->setExprType(BugType());
   }

   // -----------------
   //  Check TYPE node
   // -----------------
   if (type_node->isPlaceHolderNode())
   {
      // Type is not explicitly declared (type inference)

      // If type is not declared, we MUST have a value node to infer type from
      assert (value_node != NULL);

      type_node->setExprType(value_node->ExprType());
      type_node->setBoundSymbol(value_node->ExprType());
   }
   else
   {
      // Type is explicity declared
      visitExpr(scope, type_node);
      type_node = var_decl_node->TypeNode();
   }
   if (!type_node->hasExprType()) type_node->setExprType(BugType());
   if (!type_node->hasBoundSymbol()) type_node->setBoundSymbol(BugType());

   var_decl_node->setExprType(type_node->ExprType());


   // Add the variable to the current scope
   if (type_node->hasExprType())
   {
      if (scope->getChild(var_decl_node->Name()) == NULL)
      {
         st::Var* var = new st::Var();
         var->setName(var_decl_node->Name());
         var->setType(type_node->ExprType());
         scope->addChild(var);

         name_node->setBoundSymbol(var);
         var_decl_node->setBoundSymbol(var);
      }
      else
      {
         var_decl_node->setBoundSymbol(BugType());

         log::VariableAlreadyDefined* err = new log::VariableAlreadyDefined();
         err->sVarName(var_decl_node->Name());
         err->setPosition(var_decl_node->copyPosition());
         err->format();
         log(err);
      }
   }

   ensureSizedExprType(type_node);
   if (var_decl_node->ValueNode() != NULL)
   {
      checkAssignment(var_decl_node->ValueNode(), var_decl_node->ExprType());
   }

   DEBUG_ENSURE (var_decl_node->hasExprType());
   DEBUG_ENSURE (var_decl_node->hasBoundSymbol());
   DEBUG_ENSURE (var_decl_node->TypeNode()->hasExprType());
   DEBUG_ENSURE (var_decl_node->TypeNode()->hasBoundSymbol());
}

void
BlockTypesChecker::visitWhile (st::Symbol* scope, node::While* while_node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (while_node != NULL);

   // Check condition node
   visitExpr(scope, while_node->ConditionNode());
   ensureBoolExpr(while_node->ConditionNode());

   // Check block node
   visitBlock(scope, while_node->BodyNode());

   DEBUG_ENSURE (while_node->ConditionNode()->hasExprType());
   DEBUG_ENSURE (while_node->ConditionNode()->ExprType()->Name() == "bool");
}


} } }
