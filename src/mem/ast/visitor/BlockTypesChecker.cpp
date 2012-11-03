#include "mem/ast/visitor/BlockTypesChecker.hpp"


namespace mem { namespace ast { namespace visitor {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

BlockTypesChecker::BlockTypesChecker ()
{
   _name = "ast.BlockTypesChecker";
}



//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
BlockTypesChecker::checkCallParameters (st::Symbol* symCaller, st::FunctionType* symFunc, node::Node* nodeParams)
{
   DEBUG_REQUIRE (symFunc != NULL);

   if (nodeParams != NULL)
   {
      size_t nParams = nodeParams->ChildCount();

      if (symFunc->ArgumentCount() == nParams)
      {
         // Each parameter node must have the same expr type as declared in its
         // function definition.
         for (size_t i = 0; i < nodeParams->ChildCount(); ++i)
         {
            checkAssignment(nodeParams->getChild(i), symFunc->getArgument(i));
         }
      }
      else
      {
         log::BadParameterCount* err = new log::BadParameterCount();
         err->setExpectedParamCount(symFunc->ArgumentCount());
         err->setParamCount(nParams);
         err->format();
         err->setPosition(nodeParams->copyPosition());
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
   if (node != NULL)
   {
      if (node::isa<node::Func>(node))
      {
         node::Func* func = node::cast<node::Func>(node);

         if (func->BodyNode() != NULL)
         {
            visitBlock(node->BoundSymbol(), func->BodyNode());
         }
         return false;
      }
   }
   return true;
}

void
BlockTypesChecker::visitAmpersand (st::Symbol* scope, node::UnaryOp* node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (node != NULL);
   DEBUG_REQUIRE (node::isa<node::UnaryOp>(node));

   node::Node* nodeValue = node->ValueNode();

   visitExpr(scope, nodeValue);

   if (nodeValue->hasExprType())
   {
      st::Type* symPointerBaseType = st::cast<st::Type>(nodeValue->ExprType());
      std::string base_ty_name = symPointerBaseType->Name();
      st::Type* symAmpType = st::util::getPointerType(symPointerBaseType);

      assert (symAmpType != NULL);
      node->setExprType(symAmpType);

      // FIXME There should be more checks. For ex you should not be able to
      // do : &2
   }
   else
   {
      nodeValue->setExprType(BugType());
   }

   DEBUG_ENSURE (node->hasExprType());
   DEBUG_ENSURE (nodeValue != NULL);
   DEBUG_ENSURE (nodeValue->hasExprType());
}

void
BlockTypesChecker::visitArithmeticOp (st::Symbol* scope, node::BinaryOp* node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (node != NULL);
   DEBUG_REQUIRE (node::isa<node::BinaryOp>(node));
   DEBUG_REQUIRE (node->LeftNode() != NULL);
   DEBUG_REQUIRE (node->RightNode() != NULL);

   // Check left node
   node::Node* nodeLeft = node->LeftNode();
   visitExpr(scope, nodeLeft);

   // Check right node
   node::Node* nodeRight = node->RightNode();
   visitExpr(scope, nodeRight);

   std::string op_name;
   switch (node->Kind())
   {
      case node::MetaKind::OP_BIT_AND: op_name = "band"; break;
      case node::MetaKind::OP_BIT_OR:  op_name = "bor"; break;
      case node::MetaKind::OP_XOR:     op_name = "xor"; break;
      case node::MetaKind::OP_LSHIFT:  op_name = "<<"; break;
      case node::MetaKind::OP_RSHIFT:  op_name = ">>"; break;
      case node::MetaKind::OP_PLUS:    op_name = "+"; break;
      case node::MetaKind::OP_MINUS:   op_name = "-"; break;
      case node::MetaKind::OP_MODULO:  op_name = "%"; break;
      case node::MetaKind::OP_MUL:     op_name = "*"; break;
      case node::MetaKind::OP_DIV:     op_name = "/"; break;

      default:
         DEBUG_PRINTF("Unsupported arithmetic operator (%s)",
            node->KindName().c_str());
         assert (false);
   }

   st::Type* symLeftType = nodeLeft->ExprType();
   st::Type* symRightType = nodeRight->ExprType();

   if (op_name.size() != 0)
   {
      st::Type* symCommonType = st::util::getBiggestIntType(
         st::cast<st::IntType>(symLeftType),
         st::cast<st::IntType>(symRightType));
      // FIXME Must check operand types
      node->setExprType(symCommonType);
   }
   else
   {
      fs::position::Composite* pos = new fs::position::Composite();
      pos->addChild(nodeLeft->copyPosition());
      pos->addChild(nodeRight->copyPosition());

      log::UnsupportedArithmeticOperation* err =
         new log::UnsupportedArithmeticOperation();
      err->setLeftTypeName(symLeftType->NameCstr());
      err->setOpName(op_name.c_str());
      err->setRightTypeName(symRightType->NameCstr());
      err->format();
      err->setPosition(pos);
      log(err);
   }

   DEBUG_ENSURE(node->hasExprType());
   DEBUG_ENSURE(node->LeftNode()->hasExprType());
   DEBUG_ENSURE(node->RightNode()->hasExprType());
}

void
BlockTypesChecker::visitArrayType (st::Symbol* scope, node::ArrayType* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (node::isa<node::ArrayType>(n));


   int nArraySize = -1;


   // -----------
   //  Item type
   // -----------
   node::Node* nodeItemType = n->TypeNode();
   st::Type* symItemType = NULL;

   if (nodeItemType != NULL)
   {
      visitExpr(scope, nodeItemType);
      if (ensureSymbolIsType(nodeItemType, nodeItemType->BoundSymbol()))
      {
         symItemType = st::cast<st::Type>(nodeItemType->BoundSymbol());
      }
      else
      {
         symItemType = BugType();
      }
   }

   // ------
   //  Size
   // ------
   node::Node* nodeLength = n->LengthNode();

   if (nodeLength != NULL)
   {
      visitExpr(scope, nodeLength);

      if (node::isa<node::Number>(nodeLength)
         && nodeLength->hasBoundSymbol()
         && st::isa<st::IntConstant>(nodeLength->BoundSymbol())
         && st::isa<st::IntType>(nodeLength->ExprType()))
      {
         st::IntConstant* i_const = st::cast<st::IntConstant>(nodeLength->BoundSymbol());
         // FIXME This may break since it returns an int64_t
         nArraySize = (int)i_const->getSignedValue();
      }
   }

   // ------------
   //  Array type
   // ------------
   st::Symbol* symArrayType = BugType();

   if (symItemType != BugType())
   {
      // Unsized array
      if (nArraySize == -1)
      {
         symArrayType = st::util::getUnsizedArrayType(symItemType);
      }
      // Sized array
      else
      {
         symArrayType = st::util::getSizedArrayType(symItemType, nArraySize);
      }
   }

   n->setBoundSymbol(symArrayType);
   n->setExprType(st::cast<st::Type>(symArrayType));

   DEBUG_ENSURE (n->hasBoundSymbol());
   DEBUG_ENSURE (n->hasExprType());
   DEBUG_ENSURE (nodeItemType != NULL);
   DEBUG_ENSURE (nodeItemType->hasBoundSymbol());
   DEBUG_ENSURE (nodeItemType->hasExprType());
}

void
BlockTypesChecker::visitBracketOp (st::Symbol* scope, node::BracketOp* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (node::isa<node::BracketOp>(n));

   visitExpr (scope, n->ValueNode());
   visitExpr (scope, n->IndexNode());

   node::Node* nodeValue = n->ValueNode();
   node::Node* nodeIndex = n->IndexNode();
   st::Type* symValueType = nodeValue->ExprType();

   if (symValueType != NULL)
   {
      if (st::isa<st::PointerType>(symValueType))
      {
         symValueType = st::cast<st::PointerType>(symValueType)->PointedType();
      }

      if (st::isa<st::ArrayType>(symValueType))
      {
         st::ArrayType* arr = st::cast<st::ArrayType>(symValueType);
         n->setExprType(arr->ItemType());
      }
      else if (st::isa<st::TupleType>(symValueType))
      {
         // FIXME Nothing super safe here...
         if (node::cast<node::Number>(nodeIndex)
            && nodeIndex->hasBoundSymbol()
            && st::isa<st::IntConstant>(nodeIndex->BoundSymbol()))
         {
            node::Number* nodeIndexNb = node::cast<node::Number>(nodeIndex);
            st::IntConstant* i_const = st::cast<st::IntConstant>(nodeIndexNb->BoundSymbol());

            // FIXME This may break, it returns an int64_t
            int item_index = (int)i_const->getSignedValue();
            // FIXME No bound checking...
            n->setExprType(st::cast<st::TupleType>(symValueType)->Subtypes()[item_index]);
         }
      }
      else
      {
         log::Error* err = new log::Error();
         err->setPrimaryText("Subscripted value is not of array or tuple type");
         err->setPosition(nodeValue->copyPosition());
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
   DEBUG_REQUIRE (node::isa<node::CastOp>(n));

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
      /*
      st::Type* src_ty = n->ValueNode()->ExprType();
      st::Type* dest_ty = st::castToType(n->TypeNode()->BoundSymbol());

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
   DEBUG_REQUIRE (node::isa<node::BinaryOp>(n));
   DEBUG_REQUIRE (n->LeftNode() != NULL);
   DEBUG_REQUIRE (n->RightNode() != NULL);

   visitExpr(scope, n->LeftNode());
   visitExpr(scope, n->RightNode());

   st::Type* symLeftType = n->LeftNode()->ExprType();
   st::Type* symRightType = n->RightNode()->ExprType();

   // FIXME Must check that type is a primitive type

   if (symLeftType == symRightType)
   {
      n->setExprType(_core_types->BoolTy());
   }
   else
   {
      fs::position::Composite* pos = new fs::position::Composite();
      pos->addChild(n->LeftNode()->Position()->copy_range());
      pos->addChild(n->RightNode()->Position()->copy_range());

      n->setExprType(BugType());

      log::DifferentOperandsType* err = new log::DifferentOperandsType();
      err->setLeftType(symLeftType);
      err->setRightType(symRightType);
      err->setPosition(pos);
      err->format();
      log(err);
   }

   DEBUG_REQUIRE (n->hasExprType());
}

void
BlockTypesChecker::visitDeref (st::Symbol* scope, node::Node* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->getChild(0) != NULL);

   node::Node* nodeValue = n->getChild(0);
   visitExpr(scope, nodeValue);

   st::Type* symValueType = nodeValue != NULL ? nodeValue->ExprType() : NULL;

   if (symValueType != NULL)
   {
      if (st::isa<st::PointerType>(symValueType))
      {
         n->setExprType(st::cast<st::PointerType>(symValueType)->PointedType());
      }
      else
      {
         n->setExprType(BugType());

         log::DerefNonPointer* err = new log::DerefNonPointer();
         err->setTypeName(symValueType->Name());
         err->setPosition(nodeValue->copyPosition());
         err->format();
         log(err);
      }
   }
}

void
BlockTypesChecker::visitLogicalExpr (st::Symbol* scope, node::Node* node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (node != NULL);
   DEBUG_REQUIRE (node->getChild(0) != NULL);
   DEBUG_REQUIRE (node->getChild(1) != NULL);

   node::Node* nodeLeft = node->getChild(0);
   node::Node* nodeRight = node->getChild(1);

   if (node->Kind() == node::MetaKind::OP_AND || node->Kind() == node::MetaKind::OP_OR)
   {
      visitExpr(scope, nodeLeft);
      ensureBoolExpr(nodeLeft);

      visitExpr(scope, nodeRight);
      ensureBoolExpr(nodeRight);

      node->setExprType(_core_types->BoolTy());
   }

   DEBUG_ENSURE (node->hasExprType());
}

void
BlockTypesChecker::visitCall (st::Symbol* scope, node::Call* nodeCall)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeCall != NULL);
   DEBUG_REQUIRE (node::isa<node::Call>(nodeCall));
   DEBUG_REQUIRE (nodeCall->CallerNode() != NULL);

   node::Node* nodeCaller = nodeCall->CallerNode();
   assert (nodeCaller != NULL);
   visitExpr(scope, nodeCaller);

   if (nodeCall->hasParamsNode())
   {
      visitExprList(scope, nodeCall->ParamsNode());
   }

   /*
   if (node::isa<node::Dot>(base_object))
   {
      call_node->setIsInstanceCall(true);
      node::Dot* dot_n = node::cast<node::Dot>(base_object);

      node::Node* obj_n = dot_n->LeftNode()->copy();
      call_node->insertParam(obj_n);
   }
   */

   if (nodeCaller->hasBoundSymbol())
   {
      // Macro call
      if (st::isa<st::Macro>(nodeCaller->BoundSymbol()))
      {
         visitMacroCall(scope, nodeCall);
      }
      // Function call
      else if (st::isa<st::Func>(nodeCaller->BoundSymbol()))
      {
         visitFunctionCall(scope, nodeCall);
      }
      // Function pointer call
      else if (st::util::isFunctorType(nodeCaller->ExprType()))
      {
         visitFunctorCall(scope, nodeCall);
      }
      else
      {
         nodeCall->setExprType(BugType());

         log::CallNonFunction* err = new log::CallNonFunction();
         err->setObjectName(nodeCaller->BoundSymbol()->Name());
         err->setObjectTypeName(nodeCaller->ExprType()->gQualifiedName());
         err->setPosition(nodeCaller->Position()->copy());
         err->format();
         log(err);
      }
   }
   else
   {
      nodeCall->setBoundSymbol(BugType());
   }

   // FIXME We cannot assert this since it can be a macro that may not have
   // an expression type
   //DEBUG_ENSURE(call_node->hasExprType());
}

void
BlockTypesChecker::visitDot (st::Symbol* scope, node::Dot* nodeDot)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeDot != NULL);
   DEBUG_REQUIRE (node::isa<node::Dot>(nodeDot));
   DEBUG_REQUIRE (nodeDot->LeftNode() != NULL);
   DEBUG_REQUIRE (nodeDot->RightNode() != NULL);

   node::Node* nodeLeft = nodeDot->LeftNode();
   node::Node* nodeRight = nodeDot->RightNode();

   visitExpr(scope, nodeLeft);
   visitSymbolName(nodeLeft->ExprType(), node::cast<node::Text>(nodeRight));

   assert(node::isa<node::Id>(nodeRight));

   if (nodeLeft->hasBoundSymbol())
   {
      nodeDot->setBoundSymbol(nodeRight->BoundSymbol());

      if (nodeDot->hasBoundSymbol())
      {
         st::Symbol* expr_ty = st::util::getExprType(nodeDot->BoundSymbol());
         if (expr_ty == NULL)
         {
            expr_ty = nodeDot->BoundSymbol();
         }

         //right_node->setBoundSymbol(dot_node->BoundSymbol());
         nodeRight->setExprType(st::util::getExprType(nodeDot->BoundSymbol()));

         // If we are not accessing a class member, we can just flatten the dot
         // node by replacing it by final id.
         if (st::isa<st::Class>(nodeLeft->BoundSymbol())
            || st::isa<st::EnumType>(nodeLeft->BoundSymbol())
            || st::isa<st::Namespace>(nodeLeft->BoundSymbol()))
         {
            ast::node::FinalId* fid = new ast::node::FinalId();
            fid->setValue(nodeRight->BoundSymbol()->Name());
            fid->setBoundSymbol(nodeRight->BoundSymbol());
            if (st::isa<st::Type>(expr_ty))
            {
               fid->setExprType(expr_ty);
            }
            nodeDot->Parent()->replaceChild(nodeDot, fid);
            delete nodeDot;
         }
         else
         {
            nodeDot->setExprType(st::cast<st::Type>(expr_ty));
         }
      }
      else
      {
         nodeDot->setExprType(BugType());

         log::SymbolNotFound* err = new log::SymbolNotFound();
         err->setSymbolName(node::cast<node::Text>(nodeRight)->Value());
         err->setScopeName(nodeLeft->ExprType()->gQualifiedName());
         err->format();
         err->setPosition(nodeRight->copyPosition());
         log(err);
      }
   }

   //DEBUG_ENSURE (dot_node->hasExprType());
   //DEBUG_ENSURE (dot_node->hasBoundSymbol());
}

void
BlockTypesChecker::visitExprList (st::Symbol* scope, node::Node* node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (node != NULL);

   std::vector<st::Type*> types;
   node::Node* nodeChild = NULL;
   for (size_t i = 0; i < node->ChildCount(); ++i)
   {
      nodeChild = node->getChild(i);
      if (nodeChild != NULL)
      {
         visitExpr(scope, nodeChild);
         types.push_back(nodeChild->ExprType());
      }
   }

   st::TupleType* typeExprList = st::util::getTupleType(scope, types);
   node->setExprType(typeExprList);
}

void
BlockTypesChecker::visitExpr (st::Symbol* scope, node::Node* node)
{
   if (node == NULL) return;
   if (scope == NULL) return;

   switch (node->Kind())
   {
      case node::MetaKind::OP_DIV:
      case node::MetaKind::OP_MODULO:
      case node::MetaKind::OP_MUL:
      case node::MetaKind::OP_PLUS:
      case node::MetaKind::OP_MINUS:
      case node::MetaKind::OP_LSHIFT:
      case node::MetaKind::OP_RSHIFT:
      case node::MetaKind::OP_BIT_OR:
      case node::MetaKind::OP_BIT_AND:
      case node::MetaKind::OP_XOR:
         visitArithmeticOp(scope, node::cast<node::BinaryOp>(node));
         break;

      case node::MetaKind::OP_NE:
      case node::MetaKind::OP_EQ_EQ:
      case node::MetaKind::OP_LT:
      case node::MetaKind::OP_LTE:
      case node::MetaKind::OP_GT:
      case node::MetaKind::OP_GTE:
         visitCompOp(scope, node::cast<node::BinaryOp>(node));
         break;

      case node::MetaKind::ARRAY:
         visitArrayType (scope, node::cast<node::ArrayType>(node));
         break;

      case node::MetaKind::BRACKET_OP:
         visitBracketOp(scope, node::cast<node::BracketOp>(node));
         break;

      case node::MetaKind::OP_AND:
      case node::MetaKind::OP_OR:
         visitLogicalExpr(scope, node);
         break;

      case node::MetaKind::OP_CAST:
         visitCastOperator(scope, node::cast<node::CastOp>(node));
         break;

      case node::MetaKind::AMPERSAND:
         visitAmpersand(scope, node::cast<node::UnaryOp>(node));
         break;

      case node::MetaKind::CALL:
         visitCall(scope, node::cast<node::Call>(node));
         break;

      case node::MetaKind::DEREF:
         visitDeref(scope, node);
         break;

      case node::MetaKind::ENUM:
         // Don't do anything, it's taken care of by ::TopTypesChecker.
         break;

      case node::MetaKind::GROUP:
         visitGroup(scope, node);
         break;

      case node::MetaKind::IF:
         visitIf(scope, node::cast<node::If>(node));
         break;

      case node::MetaKind::FINAL_ID:
      case node::MetaKind::TYPE:
         visitSymbolName(scope, node::cast<node::Text>(node));
         break;

      case node::MetaKind::FOR:
         visitFor(scope, node::cast<node::For>(node));
         break;

      case node::MetaKind::NODE_LIST:
      case node::MetaKind::EXPRESSION_LIST:
         visitExprList(scope, node);
         break;

      case node::MetaKind::NEW:
         visitNew(scope, node::cast<node::New>(node));
         break;

      case node::MetaKind::RETURN:
         visitReturn(scope, node::cast<node::Return>(node));
         break;

      case node::MetaKind::WHILE:
         visitWhile(scope, node::cast<node::While>(node));
         break;

      case node::MetaKind::POINTER_TYPE:
         visitPointer(scope, node::cast<node::PointerType>(node));
         break;

      case node::MetaKind::DOT:
         visitDot(scope, node::cast<node::Dot>(node));
         break;

      case node::MetaKind::NUMBER:
         visitNumber(scope, node::cast<node::Number>(node));
         break;

      case node::MetaKind::STRING:
         visitString(scope, node::cast<node::String>(node));
         break;

      case node::MetaKind::TUPLE:
         visitTuple(scope, node::cast<node::Tuple>(node));
         break;

      case node::MetaKind::TUPLE_TYPE:
         visitTupleType(scope, node::cast<node::TupleType>(node));
         break;

      case node::MetaKind::VARIABLE_DECLARATION:
         visitVarDecl(scope, node::cast<node::VarDecl>(node));
         break;

      case node::MetaKind::VARIABLE_ASSIGNMENT:
         visitVarAssign(scope, node::cast<node::VarAssign>(node));
         break;

      default:
         DEBUG_PRINTF("Unsupported node kind {kind: %d, name: %s}\n",
            node->Kind(),
            node->KindNameCstr());
         assert(false);
   }
}

void
BlockTypesChecker::visitSymbolName (st::Symbol* scope, node::Node* nodeId)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeId != NULL);

   st::Symbol* sym = _symbols->lookupSymbol(scope, nodeId->Value());

   if (sym != NULL)
   {
      if (st::isa<st::Alias>(sym))
      {
         nodeId->setBoundSymbol(st::cast<st::Alias>(sym)->Aliased());
      }
      else
      {
         nodeId->setBoundSymbol(sym);
      }

      st::Type* symExprType = st::util::getExprType(sym);

      if (symExprType != NULL)
      {
         nodeId->setExprType(symExprType);
      }
      else
      {
         nodeId->setExprType(BugType());
      }
   }
   else
   {
      nodeId->setBoundSymbol(BugType());
      nodeId->setExprType(BugType());

      logSymbolNotFound(scope, nodeId, nodeId->Value());
   }

   DEBUG_ENSURE(nodeId->hasBoundSymbol());
}

void
BlockTypesChecker::visitFor (st::Symbol* scope, node::For* nodeFor)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeFor != NULL);
   DEBUG_REQUIRE (node::isa<node::For>(nodeFor));

   // Block scope
   st::Symbol* nodeBlock = new st::Symbol();
   nodeBlock->hintName(scope, "~for");
   scope->addChild(nodeBlock);
   nodeFor->BlockNode()->setBoundSymbol(nodeBlock);

   // Initialization
   visitExpr(nodeBlock, nodeFor->InitializationNode());

   // Condition
   visitExpr(nodeBlock, nodeFor->ConditionNode());
   ensureBoolExpr(nodeFor->ConditionNode());

   // Iteration
   visitExpr(nodeBlock, nodeFor->IterationNode());

   // Block
   visitBlock(nodeBlock, nodeFor->BlockNode());

   DEBUG_ENSURE(nodeFor->ConditionNode()->hasExprType());
}

void
BlockTypesChecker::visitFunctionCall (st::Symbol* scope, node::Call* nodeCall)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeCall != NULL);
   DEBUG_REQUIRE (node::isa<node::Call>(nodeCall));
   DEBUG_REQUIRE (nodeCall->CallerNode() != NULL);
   DEBUG_REQUIRE (nodeCall->CallerNode()->BoundSymbol() != NULL);
   DEBUG_REQUIRE (st::isa<st::Func>(nodeCall->CallerNode()->BoundSymbol()));

   node::Node* nodeCaller = nodeCall->CallerNode();

   st::Func* symCaller = st::cast<st::Func>(nodeCaller->BoundSymbol());
   nodeCall->setExprType(symCaller->ReturnType());

   // Search for an overriding function that may fit the same signature
   // FIXME Spaghetti
   if (nodeCall->IsInstanceCall())
   {
      st::Class* cls = st::cast<st::Class>(symCaller->Parent());
      st::FunctionVector funcs = cls->getFunctionsLike(symCaller->Name(), symCaller->Type());
      st::Func* symNewCaller = chooseOverridenFunction (funcs, nodeCall->ParamsNode()->packChildrenExprTypes());
      nodeCall->CallerNode()->setBoundSymbol(symNewCaller);
   }

   if (nodeCall->hasParamsNode())
   {
      checkCallParameters(nodeCall->Caller(), symCaller->Type(), nodeCall->ParamsNode());
   }

   DEBUG_ENSURE(nodeCall->hasExprType());
}

void
BlockTypesChecker::visitFunctorCall (st::Symbol* scope, node::Call* nodeCall)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeCall != NULL);
   DEBUG_REQUIRE (node::isa<node::Call>(nodeCall));

   node::Node* nodeCaller = nodeCall->CallerNode();
   st::PointerType* symPointerType = st::cast<st::PointerType>(nodeCaller->ExprType());
   st::FunctionType* symFuncType = st::cast<st::FunctionType>(symPointerType->getNonPointerParent());
   nodeCall->setExprType(symFuncType->ReturnType());

   if (nodeCall->hasParamsNode())
   {
      checkCallParameters(NULL, symFuncType, nodeCall->ParamsNode());
   }
}

void
BlockTypesChecker::visitGroup (st::Symbol* scope, node::Node* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->getChild(0) != NULL);

   // FIXME Rather strange... shouldn't we iterate over all children ?
   visitExpr(scope, n->getChild(0));
   n->setExprType(n->getChild(0)->ExprType());

   DEBUG_ENSURE(n->hasExprType());
}

void
BlockTypesChecker::visitIf (st::Symbol* scope, node::If* nodeIf)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeIf != NULL);
   DEBUG_REQUIRE (node::isa<node::If>(nodeIf));

   // Check condition expression
   visitExpr(scope, nodeIf->ConditionNode());
   ensureBoolExpr(nodeIf->ConditionNode());

   // Check block statements
   // FIXME Should create a special type of Symbol here
   st::Symbol* symIfBlock = new st::Symbol();
   symIfBlock->hintName(scope, "~if");
   scope->addChild(symIfBlock);
   nodeIf->IfBlockNode()->setBoundSymbol(symIfBlock);

   visitBlock(symIfBlock, nodeIf->IfBlockNode());

   if (nodeIf->hasElseBlockNode())
   {
      st::Symbol* symElseBlock = new st::Symbol();
      symElseBlock->hintName(scope, "~else");
      scope->addChild(symElseBlock);
      nodeIf->ElseBlockNode()->setBoundSymbol(symElseBlock);

      visitBlock(symElseBlock, nodeIf->ElseBlockNode());
   }

   DEBUG_ENSURE (nodeIf->ConditionNode()->hasExprType());
}

void
BlockTypesChecker::visitMacroCall (st::Symbol* scope, node::Call* nodeCall)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeCall != NULL);
   DEBUG_REQUIRE (node::isa<node::Call>(nodeCall));

   node::Node* nodeMacro = nodeCall->CallerNode();
   st::Macro* symMacro = st::cast<st::Macro>(nodeMacro->BoundSymbol());
   macro::Macro* macro = static_cast<macro::Macro*>(symMacro->MacroExpander());
   node::Node* nodeMacroResult = macro->expand(nodeCall);
   delete nodeCall;

   visitExpr(scope, nodeMacroResult);
}

void
BlockTypesChecker::visitNew (st::Symbol* scope, node::New* nodeNew)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeNew != NULL);
   DEBUG_REQUIRE (node::isa<node::New>(nodeNew));

   node::Node* nodeType = nodeNew->TypeNode();
   assert (nodeType != NULL);

   visitExpr(scope, nodeType);
   ensureSymbolIsType(nodeType, nodeType->BoundSymbol());

   st::Type* symPointerType = NULL;
   if (st::isa<st::ArrayType>(nodeType->BoundSymbol()))
   {
      st::ArrayType* symArrayType = st::cast<st::ArrayType>(nodeType->BoundSymbol());
      st::ArrayType* symUnsizedArrayType = st::util::getUnsizedArrayType(symArrayType);

      symPointerType = st::util::getPointerType(symUnsizedArrayType);
   }
   else
   {
      symPointerType = st::util::getPointerType(nodeType->ExprType());
   }

   nodeNew->setExprType(symPointerType);

   DEBUG_ENSURE(nodeNew->hasExprType());
}

void
BlockTypesChecker::visitNumber (st::Symbol* scope, node::Number* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (n->hasBoundSymbol());
   DEBUG_REQUIRE (st::isa<st::IntConstant>(n->BoundSymbol()));
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
BlockTypesChecker::visitPointer (st::Symbol* scope, node::PointerType* nodePointerType)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodePointerType != NULL);
   DEBUG_REQUIRE (node::isa<node::PointerType>(nodePointerType));
   DEBUG_REQUIRE (nodePointerType->TypeNode() != NULL);

   visitExpr(scope, nodePointerType->TypeNode());

   node::Node* nodeType = nodePointerType->TypeNode();

   ensureSymbolIsType(nodeType, nodeType->BoundSymbol());

   if (!nodeType->hasBoundSymbol())
   {
      nodeType->setBoundSymbol(BugType());
   }

   if (nodeType->hasBoundSymbol()
      && st::isa<st::Type>(nodeType->BoundSymbol()))
   {
      st::Symbol* symPointerType = st::util::lookupPointer(scope, st::cast<st::Type>(nodeType->BoundSymbol()));
      nodePointerType->setBoundSymbol(symPointerType);
      nodePointerType->setExprType(st::cast<st::Type>(symPointerType));
   }
   else
   {
      nodePointerType->setBoundSymbol(BugType());
      nodePointerType->setExprType(BugType());
   }

   DEBUG_ENSURE (nodePointerType->hasExprType());
   DEBUG_ENSURE (nodePointerType->hasBoundSymbol());
}

void
BlockTypesChecker::visitReturn (st::Symbol* scope, node::Return* nodeReturn)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeReturn != NULL);
   DEBUG_REQUIRE (node::isa<node::Return>(nodeReturn));

   st::Func* symParentFunc = util::getParentFunction(nodeReturn);

   node::Node* nodeValue = nodeReturn->ValueNode();

   visitExpr(scope, nodeValue);

   if (checkAssignment(nodeValue, symParentFunc->ReturnType()))
   {
      nodeReturn->setExprType(symParentFunc->ReturnType());
   }
   else
   {
      nodeReturn->setExprType(BugType());

      log::ReturnTypeDiffersFromPrototype* err = new log::ReturnTypeDiffersFromPrototype();
      err->setFuncName(symParentFunc->gQualifiedName());
      err->setRetTy(nodeValue->ExprType());
      err->setExpectedRetTy(symParentFunc->ReturnType());
      err->setPosition(nodeValue->copyPosition());
      err->format();
      log(err);
   }

   DEBUG_ENSURE (nodeReturn->hasExprType());
   DEBUG_ENSURE (nodeReturn->ValueNode()->hasExprType());
}

void
BlockTypesChecker::visitString (st::Symbol* scope, node::String* nodeString)
{
   DEBUG_REQUIRE (nodeString != NULL);
   DEBUG_REQUIRE (node::isa<node::String>(nodeString));

   st::IntType* symCharType = _symbols->_core_types.CharTy();
   st::ArrayType* symUnsizedArrayType = st::util::getUnsizedArrayType(symCharType);
   nodeString->setExprType(st::util::getPointerType(symUnsizedArrayType));

   DEBUG_ENSURE (nodeString->hasExprType());
}

void
BlockTypesChecker::visitTuple (st::Symbol* scope, node::Tuple* nodeTuple)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeTuple != NULL);
   DEBUG_REQUIRE (node::isa<node::Tuple>(nodeTuple));

   st::TypeVector tys;
   bool an_expr_failed = false;
   node::Node* nodeChildType = NULL;

   for (size_t i = 0; i < nodeTuple->ChildCount(); ++i)
   {
      nodeChildType = nodeTuple->getChild(i);

      visitExpr(scope, nodeChildType);
      if (nodeChildType->hasExprType())
      {
         tys.push_back(nodeChildType->ExprType());
      }
      else
      {
         an_expr_failed = true;
         break;
      }
   }

   if (!an_expr_failed)
   {
      st::TupleType* symTupleType = st::util::getTupleType(_symbols->System(), tys);
      nodeTuple->setExprType(symTupleType);
      ensureSizedExprType(nodeTuple);
   }
   else
   {
      nodeTuple->setExprType(BugType());
   }

   DEBUG_ENSURE (nodeTuple->hasExprType());
}

void
BlockTypesChecker::visitTupleType (st::Symbol* scope, node::TupleType* nodeTupleType)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeTupleType != NULL);
   DEBUG_REQUIRE (node::isa<node::TupleType>(nodeTupleType));

   st::TypeVector tys;
   node::Node* nodeChildType = NULL;
   for (size_t i = 0; i < nodeTupleType->ChildCount(); ++i)
   {
      nodeChildType = nodeTupleType->getChild(i);

      visitExpr(scope, nodeChildType);
      ensureSizedExprType(nodeChildType);
      tys.push_back(nodeChildType->ExprType());
   }

   st::TupleType* symTupleType = st::util::getTupleType(_symbols->System(), tys);

   if (symTupleType != NULL)
   {
      nodeTupleType->setExprType(symTupleType);
      nodeTupleType->setBoundSymbol(symTupleType);
   }
   else
   {
      nodeTupleType->setExprType(BugType());
      nodeTupleType->setBoundSymbol(BugType());
   }

   DEBUG_ENSURE (nodeTupleType->hasExprType());
   DEBUG_ENSURE (nodeTupleType->hasBoundSymbol());
}

void
BlockTypesChecker::visitVarAssign (st::Symbol* scope, node::VarAssign* nodeAssign)
{
   DEBUG_REQUIRE (nodeAssign != NULL);
   DEBUG_REQUIRE (node::isa<node::VarAssign>(nodeAssign));
   DEBUG_REQUIRE (nodeAssign->NameNode() != NULL);
   DEBUG_REQUIRE (nodeAssign->ValueNode() != NULL);

   node::Node* nodeName = nodeAssign->NameNode();
   node::Node* nodeValue = nodeAssign->ValueNode();

   visitExpr(scope, nodeName);
   visitExpr(scope, nodeValue);

   if (nodeName->isAssignable() && nodeName->hasExprType())
   {
      nodeAssign->setExprType(nodeName->ExprType());
      checkAssignment(nodeValue, nodeAssign->ExprType());
   }
   else
   {
      nodeName->setExprType(BugType());
      nodeName->setBoundSymbol(BugType());

      log::NotAssignable* err = new log::NotAssignable();
      err->setPosition(nodeName->copyPosition());
      err->format();
      log(err);
   }

   DEBUG_ENSURE (nodeAssign->hasExprType());
}

void
BlockTypesChecker::visitVarDecl (st::Symbol* scope, node::VarDecl* nodeDecl)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeDecl != NULL);
   DEBUG_REQUIRE (node::isa<node::VarDecl>(nodeDecl));
   DEBUG_REQUIRE (nodeDecl->NameNode() != NULL);
   DEBUG_REQUIRE (nodeDecl->TypeNode() != NULL);

   // ------------------
   //  Check VALUE node
   // ------------------
   node::Node* nodeValue = nodeDecl->ValueNode();

   // Value is declared
   if (nodeValue != NULL)
   {
      visitExpr(scope, nodeValue);

      if (!nodeValue->hasExprType())
      {
         nodeValue->setExprType(BugType());
      }
   }

   // -----------------
   //  Check TYPE node
   // -----------------
   node::Node* nodeType = nodeDecl->TypeNode();

   // Type is not explicitly declared (type inference)
   if (nodeType->Kind() == node::MetaKind::PLACE_HOLDER)
   {
      // If type is not declared, we MUST have a value node to infer type from
      assert (nodeValue != NULL);

      nodeType->setExprType(nodeValue->ExprType());
      nodeType->setBoundSymbol(nodeValue->ExprType());
   }
   // Type is explicity declared
   else
   {
      visitExpr(scope, nodeType);
   }

   if (!nodeType->hasExprType())
   {
      nodeType->setExprType(BugType());
   }

   if (!nodeType->hasBoundSymbol())
   {
      nodeType->setBoundSymbol(BugType());
   }

   nodeDecl->setExprType(nodeType->ExprType());


   // ---------------------------------------
   //  Add the variable to the current scope
   // ---------------------------------------
   node::Text* nodeName = nodeDecl->NameNode();

   if (nodeType->hasExprType())
   {
      if (scope->getChild(nodeDecl->Name()) == NULL)
      {
         st::Var* symVar = new st::Var();
         symVar->setName(nodeDecl->Name());
         symVar->setType(nodeType->ExprType());
         scope->addChild(symVar);

         nodeName->setBoundSymbol(symVar);
         nodeName->setExprType(symVar->Type());
         nodeDecl->setBoundSymbol(symVar);
      }
      else
      {
         nodeDecl->setBoundSymbol(BugType());

         log::VariableAlreadyDefined* err = new log::VariableAlreadyDefined();
         err->setVarName(nodeDecl->Name());
         err->setPosition(nodeDecl->copyPosition());
         err->format();
         log(err);
      }
   }

   ensureSizedExprType(nodeType);
   if (nodeValue != NULL)
   {
      checkAssignment(nodeValue, nodeDecl->ExprType());
   }

   DEBUG_ENSURE (nodeDecl->hasExprType());
   DEBUG_ENSURE (nodeDecl->hasBoundSymbol());
   DEBUG_ENSURE (nodeDecl->TypeNode()->hasExprType());
   DEBUG_ENSURE (nodeDecl->TypeNode()->hasBoundSymbol());
}

void
BlockTypesChecker::visitWhile (st::Symbol* scope, node::While* nodeWhile)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (nodeWhile != NULL);
   DEBUG_REQUIRE (node::isa<node::While>(nodeWhile));

   // ----------------------
   //  Check condition node
   // ----------------------
   visitExpr(scope, nodeWhile->ConditionNode());
   ensureBoolExpr(nodeWhile->ConditionNode());

   // ------------------
   //  Check block node
   // ------------------
   st::Symbol* symWhileBlock = new st::Symbol();
   symWhileBlock->hintName(scope, "~while");
   scope->addChild(symWhileBlock);
   nodeWhile->BlockNode()->setBoundSymbol(symWhileBlock);

   visitBlock(symWhileBlock, nodeWhile->BlockNode());

   DEBUG_ENSURE (nodeWhile->ConditionNode()->hasExprType());
   DEBUG_ENSURE (nodeWhile->ConditionNode()->ExprType()->Name() == "bool");
}


} } }
