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
         err->setPosition(params->copyPosition());
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

   node::Node* value_n = node->ValueNode();

   visitExpr(scope, value_n);

   if (value_n->hasExprType())
   {
      st::Type* ptr_base_ty = st::cast<st::Type>(value_n->ExprType());
      std::string base_ty_name = ptr_base_ty->Name();
      st::Type* amp_ty = st::util::getPointerType(ptr_base_ty);

      assert (amp_ty != NULL);
      node->setExprType(amp_ty);

      // FIXME There should be more checks. For ex you should not be able to
      // do : &2
   }
   else
   {
      value_n->setExprType(BugType());
   }

   DEBUG_ENSURE (node->hasExprType());
   DEBUG_ENSURE (value_n != NULL);
   DEBUG_ENSURE (value_n->hasExprType());
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

   if (op_name.size() != 0)
   {
      st::Type* left_ty = left_node->ExprType();
      st::Type* right_ty = right_node->ExprType();
      st::Type* common_ty = st::util::getBiggestIntType(
         st::cast<st::IntType>(left_ty),
         st::cast<st::IntType>(right_ty));
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
BlockTypesChecker::visitArrayType (st::Symbol* scope, node::ArrayType* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (node::isa<node::ArrayType>(n));

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
      if (ensureSymbolIsType(type_n, type_n->BoundSymbol()))
      {
         item_ty = st::cast<st::Type>(type_n->BoundSymbol());
      }
      else
      {
         item_ty = BugType();
      }
   }

   // ------
   //  Size
   // ------
   if (length_n != NULL)
   {
      visitExpr(scope, length_n);
      if (node::isa<node::Number>(length_n)
         && length_n->hasBoundSymbol()
         && st::isa<st::IntConstant>(length_n->BoundSymbol())
         && st::isa<st::IntType>(length_n->ExprType()))
      {
         st::IntConstant* i_const = st::cast<st::IntConstant>(length_n->BoundSymbol());
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
   n->setExprType(st::cast<st::Type>(arr_sym));

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
   DEBUG_REQUIRE (node::isa<node::BracketOp>(n));

   visitExpr (scope, n->ValueNode());
   visitExpr (scope, n->IndexNode());

   node::Node* value_node = n->ValueNode();
   node::Node* index_n = n->IndexNode();
   st::Type* value_ty = value_node->ExprType();

   if (value_ty != NULL)
   {
      if (st::isa<st::PointerType>(value_ty))
      {
         value_ty = st::cast<st::PointerType>(value_ty)->PointedType();
      }

      if (st::isa<st::ArrayType>(value_ty))
      {
         st::ArrayType* arr = st::cast<st::ArrayType>(value_ty);
         n->setExprType(arr->ItemType());
      }
      else if (st::isa<st::TupleType>(value_ty))
      {
         // FIXME Nothing super safe here...
         if (node::cast<node::Number>(index_n)
            && index_n->hasBoundSymbol()
            && st::isa<st::IntConstant>(index_n->BoundSymbol()))
         {
            node::Number* index_nb_n = node::cast<node::Number>(index_n);
            st::IntConstant* i_const = st::cast<st::IntConstant>(index_nb_n->BoundSymbol());

            // FIXME This may break, it returns an int64_t
            int item_index = (int)i_const->getSignedValue();
            // FIXME No bound checking...
            n->setExprType(st::cast<st::TupleType>(value_ty)->Subtypes()[item_index]);
         }
      }
      else
      {
         log::Error* err = new log::Error();
         err->setPrimaryText("Subscripted value is not of array or tuple type");
         err->setPosition(value_node->copyPosition());
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

   st::Type* left_ty = n->LeftNode()->ExprType();
   st::Type* right_ty = n->RightNode()->ExprType();

   // FIXME Must check that type is a primitive type

   if (left_ty == right_ty)
   {
      n->setExprType(_core_types->BoolTy());
   }
   else
   {
      fs::position::Composite* pos = new fs::position::Composite();
      pos->addChild(n->LeftNode()->Position()->copy_range());
      //pos->addChild(n->RightNode()->Position()->copy_range());

      n->setExprType(BugType());

      log::DifferentOperandsType* err = new log::DifferentOperandsType();
      err->sLeftType(left_ty);
      err->sRightType(right_ty);
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

   visitExpr(scope, n->getChild(0));
   node::Node* value_node = n->getChild(0);
   st::Type* value_ty = value_node != NULL ? value_node->ExprType() : NULL;

   if (value_ty != NULL)
   {
      if (st::isa<st::PointerType>(value_ty))
      {
         n->setExprType(st::cast<st::PointerType>(value_ty)->PointedType());
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

   if (expr_node->Kind() == node::MetaKind::OP_AND || expr_node->Kind() == node::MetaKind::OP_OR)
   {
      visitExpr(scope, expr_node->getChild(0));
      visitExpr(scope, expr_node->getChild(1));

      ensureBoolExpr(expr_node->getChild(0));
      ensureBoolExpr(expr_node->getChild(1));

      expr_node->setExprType(_core_types->BoolTy());
   }

   DEBUG_ENSURE (expr_node->hasExprType());
}

void
BlockTypesChecker::visitCall (st::Symbol* scope, node::Call* call_node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (call_node != NULL);
   DEBUG_REQUIRE (node::isa<node::Call>(call_node));
   DEBUG_REQUIRE (call_node->CallerNode() != NULL);

   node::Node* base_object = call_node->CallerNode();
   visitExpr(scope, base_object);

   if (call_node->hasParamsNode())
   {
      visitExprList(scope, call_node->ParamsNode());
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

   if (base_object->hasBoundSymbol())
   {
      // Macro call
      if (st::isa<st::Macro>(base_object->BoundSymbol()))
      {
         visitMacroCall(scope, call_node);
      }
      // Function call
      else if (st::isa<st::Func>(base_object->BoundSymbol()))
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
         err->sObjectTypeName(base_object->ExprType()->gQualifiedName());
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
   DEBUG_REQUIRE (node::isa<node::Dot>(dot_node));
   DEBUG_REQUIRE (dot_node->LeftNode() != NULL);
   DEBUG_REQUIRE (dot_node->RightNode() != NULL);

   node::Node* left_node = dot_node->LeftNode();
   node::Node* right_node = dot_node->RightNode();

   visitExpr(scope, left_node);
   // Left node is a variable container an object
   if (left_node->hasExprType())
   {
      visitSymbolName(left_node->ExprType(), node::cast<node::Text>(right_node));
   }
   else
   {
      visitSymbolName(left_node->BoundSymbol(), node::cast<node::Text>(right_node));
   }

   assert(node::isa<node::Id>(right_node));

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
         if (st::isa<st::Class>(left_node->BoundSymbol())
            || st::isa<st::EnumType>(left_node->BoundSymbol())
            || st::isa<st::Namespace>(left_node->BoundSymbol()))
         {
            ast::node::FinalId* fid = new ast::node::FinalId();
            fid->setValue(right_node->BoundSymbol()->Name());
            fid->setBoundSymbol(right_node->BoundSymbol());
            if (st::isa<st::Type>(expr_ty))
            {
               fid->setExprType(expr_ty);
            }
            dot_node->Parent()->replaceChild(dot_node, fid);
            //dot_node->unlink();
            delete dot_node;
         }
         else
         {
            dot_node->setExprType(st::cast<st::Type>(expr_ty));
         }
      }
      else
      {
         dot_node->setExprType(BugType());

         log::SymbolNotFound* err = new log::SymbolNotFound();
         err->sSymbolName(node::cast<node::Text>(right_node)->Value());
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
   if (scope != NULL) return;
   if (node != NULL) return;

   node::Node* subnode = NULL;
   for (size_t i = 0; i < node->ChildCount(); ++i)
   {
      subnode = node->getChild(i);
      if (subnode != NULL)
      {
         visitExpr(scope, subnode);
      }
   }
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
         visitArithmeticOp(scope, node);
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
            node::kKIND_NAMES[node->Kind()]);
         assert(false);
   }
}

void
BlockTypesChecker::visitSymbolName (st::Symbol* scope, node::Node* id_node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (id_node != NULL);

   st::Symbol* sym = _symbols->lookupSymbol(scope, id_node->Value());

   if (sym != NULL)
   {
      if (st::isa<st::Alias>(sym))
      {
         id_node->setBoundSymbol(st::cast<st::Alias>(sym)->Aliased());
      }
      else
      {
         id_node->setBoundSymbol(sym);
      }

      st::Type* expr_ty = st::util::getExprType(sym);

      if (expr_ty != NULL)
      {
         id_node->setExprType(expr_ty);
      }
   }
   else
   {
      id_node->setBoundSymbol(BugType());
      id_node->setExprType(BugType());

      logSymbolNotFound(scope, id_node, id_node->Value());
   }

   DEBUG_ENSURE(id_node->hasBoundSymbol());
}

void
BlockTypesChecker::visitFor (st::Symbol* scope, node::For* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (node::isa<node::For>(n));

   visitExpr(scope, n->InitializationNode());

   visitExpr(scope, n->ConditionNode());
   ensureBoolExpr(n->ConditionNode());

   visitExpr(scope, n->IterationNode());

   visitBlock(scope, n->BlockNode());

   DEBUG_ENSURE(n->ConditionNode()->hasExprType());
}

void
BlockTypesChecker::visitFunctionCall (st::Symbol* scope, node::Call* call_n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (call_n != NULL);
   DEBUG_REQUIRE (node::isa<node::Call>(call_n));
   DEBUG_REQUIRE (call_n->CallerNode() != NULL);
   DEBUG_REQUIRE (call_n->CallerNode()->BoundSymbol() != NULL);
   DEBUG_REQUIRE (st::isa<st::Func>(call_n->CallerNode()->BoundSymbol()));

   node::Node* base_object = call_n->CallerNode();

   st::Func* base_func = st::cast<st::Func>(base_object->BoundSymbol());
   call_n->setExprType(base_func->ReturnType());

   // Search for an overriding function that may fit the same signature
   // FIXME Spaghetti
   if (call_n->IsInstanceCall())
   {
      st::Class* cls = st::cast<st::Class>(base_func->Parent());
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
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (call_n != NULL);
   DEBUG_REQUIRE (node::isa<node::Call>(call_n));

   node::Node* base_object = call_n->CallerNode();
   st::PointerType* ptr_ty = st::cast<st::PointerType>(base_object->ExprType());
   st::FunctionType* func_ty = st::cast<st::FunctionType>(ptr_ty->getNonPointerParent());
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
   DEBUG_REQUIRE (node::isa<node::If>(if_node));

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
}

void
BlockTypesChecker::visitMacroCall (st::Symbol* scope, node::Call* call_n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (call_n != NULL);
   DEBUG_REQUIRE (node::isa<node::Call>(call_n));

   node::Node* base_object = call_n->CallerNode();
   st::Macro* macro_sym = st::cast<st::Macro>(base_object->BoundSymbol());
   macro::Macro* macro = static_cast<macro::Macro*>(macro_sym->MacroExpander());
   node::Node* macro_result = macro->expand(call_n);
   delete call_n;
   visitExpr(scope, macro_result);
}

void
BlockTypesChecker::visitNew (st::Symbol* scope, node::New* new_node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (new_node != NULL);
   DEBUG_REQUIRE (node::isa<node::New>(new_node));

   node::Node* ty_node = new_node->TypeNode();
   assert (ty_node != NULL);

   visitExpr(scope, ty_node);
   ensureSymbolIsType(ty_node, ty_node->BoundSymbol());

   if (st::isa<st::ArrayType>(ty_node->BoundSymbol()))
   {
      st::ArrayType* arr_ty = st::cast<st::ArrayType>(ty_node->BoundSymbol());
      st::ArrayType* unsized_arr_ty = st::util::getUnsizedArrayType(arr_ty);
      st::Type* ptr_ty = st::util::getPointerType(unsized_arr_ty);
      new_node->setExprType(ptr_ty);
   }
   else
   {
      st::Type* ptr_ty = st::util::getPointerType(ty_node->ExprType());
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
BlockTypesChecker::visitPointer (st::Symbol* scope, node::PointerType* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (node::isa<node::PointerType>(n));

   if (n->TypeNode() != NULL)
   {
      visitExpr(scope, n->TypeNode());

      ensureSymbolIsType(n->TypeNode(), n->TypeNode()->BoundSymbol());

      if (!n->TypeNode()->hasBoundSymbol())
      {
         n->TypeNode()->setBoundSymbol(BugType());
      }

      if (n->TypeNode()->hasBoundSymbol()
         && st::isa<st::Type>(n->TypeNode()->BoundSymbol()))
      {
         st::Symbol* ptr_ty = st::util::lookupPointer(scope,
            st::cast<st::Type>(n->TypeNode()->BoundSymbol()));
         assert (ptr_ty != NULL);
         n->setBoundSymbol(ptr_ty);
         n->setExprType(st::cast<st::Type>(ptr_ty));
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
   DEBUG_REQUIRE (node::isa<node::Return>(n));

   st::Func* parent_func = util::getParentFunction(n);
   assert (parent_func);
   assert (st::isa<st::Func>(parent_func));

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
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (node::isa<node::String>(n));

   st::IntType* char_ty = _symbols->_core_types.CharTy();
   st::ArrayType* unsized_arr_ty = st::util::getUnsizedArrayType(char_ty);
   n->setExprType(st::util::getPointerType(unsized_arr_ty));

   DEBUG_ENSURE (n->hasExprType());
}

void
BlockTypesChecker::visitTuple (st::Symbol* scope, node::Tuple* n)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (n != NULL);
   DEBUG_REQUIRE (node::isa<node::Tuple>(n));

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
   DEBUG_REQUIRE (node::isa<node::TupleType>(n));

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
   DEBUG_REQUIRE (node::isa<node::VarAssign>(node));
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
}

void
BlockTypesChecker::visitVarDecl (st::Symbol* scope,
   node::VarDecl* var_decl_node)
{
   DEBUG_REQUIRE (scope != NULL);
   DEBUG_REQUIRE (var_decl_node != NULL);
   DEBUG_REQUIRE (node::isa<node::VarDecl>(var_decl_node));
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
   if (type_node->Kind() == node::MetaKind::PLACE_HOLDER)
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
         name_node->setExprType(var->Type());
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
   DEBUG_REQUIRE (node::isa<node::While>(while_node));

   // Check condition node
   visitExpr(scope, while_node->ConditionNode());
   ensureBoolExpr(while_node->ConditionNode());

   // Check block node
   st::Symbol* while_block = new st::Symbol();
   while_block->hintName(scope, "~if");
   scope->addChild(while_block);
   while_node->BlockNode()->setBoundSymbol(while_block);

   visitBlock(while_block, while_node->BlockNode());

   DEBUG_ENSURE (while_node->ConditionNode()->hasExprType());
   DEBUG_ENSURE (while_node->ConditionNode()->ExprType()->Name() == "bool");
}


} } }
