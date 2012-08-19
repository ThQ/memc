#include "mem/codegen/llvm/Codegen.hpp"

#ifdef HAVE_LLVM

namespace mem { namespace codegen { namespace llvm_ {


Codegen::Codegen ()
{
   _cur_bb = NULL;
   _cur_func = NULL;
   _exit_block = NULL;
   _module = NULL;
   _st = NULL;
   llvm::InitializeNativeTarget();

}

llvm::Value*
Codegen::_castLlvmValue (llvm::Value* val, st::Type* src_ty, st::Type* dest_ty)
{
   // Casting between two integer types
   if (src_ty->isIntType() && dest_ty->isIntType())
   {
      if (src_ty->ByteSize() == dest_ty->ByteSize())
      {
         // Don't do anything
      }
      // Extending (SAFE)
      if (src_ty->ByteSize() < dest_ty->ByteSize())
      {
         val = new llvm::SExtInst(val, _type_maker.get(dest_ty), "", _cur_bb);
      }
      // Truncating (UNSAFE)
      else if (src_ty->ByteSize() > dest_ty->ByteSize())
      {
         val = new llvm::TruncInst(val, _type_maker.get(dest_ty), "", _cur_bb);
      }
   }
   // Casting between two pointer types
   else if (src_ty->isPointerType() && dest_ty->isPointerType())
   {
      if (!_st->isVoidType(st::castToPointerType(dest_ty)->PointedType()))
      {
         val = new llvm::BitCastInst(val, _type_maker.get(dest_ty), "", _cur_bb);
      }
   }

   DEBUG_ENSURE (val != NULL);
   return val;

}

std::string
Codegen::_getLlvmTypeName (llvm::Type* ty)
{
   std::stringstream name;
   if (ty != NULL)
   {
      if (ty->isStructTy())
      {
         name << llvm::cast<llvm::StructType>(ty)->getName().str();
      }
      else if (ty->isPointerTy())
      {
         name << _getLlvmTypeName(llvm::cast<llvm::PointerType>(ty)->getElementType()) + "*";
      }
      else if (ty->isPrimitiveType())
      {
         name << "Primitive";
      }
      else if (ty->isArrayTy())
      {
         name << "[" + _getLlvmTypeName(llvm::cast<llvm::ArrayType>(ty)->getElementType()) + "]";
      }
      else if (ty->isVectorTy())
      {
         name << "<>";
      }
      else if (ty->isFunctionTy())
      {
         name << "Func";
      }
      else if (ty->isIntegerTy())
      {
         name << "i" << static_cast<llvm::IntegerType*>(ty)->getBitWidth();
      }
      else
      {
         name << "UnknownType";
      }
   }
   else
   {
      name << "NULL";
   }
   return name.str();
}

llvm::GetElementPtrInst*
Codegen::_createGepInst(llvm::Value* base, std::vector<llvm::Value*> idx)
{
   DEBUG_REQUIRE (base != NULL);

#if 1
   llvm::Type* base_ty = base->getType();
   std::string base_ty_name;
   if (base_ty != NULL)
   {
      base_ty_name = _getLlvmTypeName(base_ty);
   }
   std::string idx_name = "";
   for (size_t i = 0; i < idx.size(); ++i)
   {
      idx_name += "[";
      idx_name += _getLlvmTypeName(idx[i]->getType());
      idx_name += "]";
   }
   DEBUG_PRINTF("GEP %s%s\n", base_ty_name.c_str(), idx_name.c_str());
#endif

   llvm::GetElementPtrInst* gep_inst = llvm::GetElementPtrInst::Create(base, idx, "", _cur_bb);

   DEBUG_ENSURE (gep_inst != NULL && "Failed to create GEP instruction");

   return gep_inst;
}

std::string
Codegen::_getCodegenFuncName (st::Func* func)
{
   std::string name = "";

   if (func->IsExternal())
   {
      name = func->Name();
   }
   else
   {
      name = func->gQualifiedName();
   }

   return name;
}

st::Type*
Codegen::_getLowestCommonType (st::Symbol* left_ty, st::Symbol* right_ty)
{
   st::Type* common_ty = NULL;
   if (!left_ty->isPointerType())
   {
      common_ty = st::castToType(left_ty);
   }
   else if (!right_ty->isPointerType())
   {
      common_ty = st::castToType(right_ty);
   }
   // Both operands are pointers
   else
   {
      common_ty = st::util::getPointerBaseType(st::castToPointerType(left_ty));
   }

   return common_ty;
}



std::vector<llvm::Type*>
Codegen::_getFuncParamsTy (st::Func* func)
{
   std::vector<llvm::Type*> params_ty;
   llvm::Type* cur_ty = NULL;

   for (size_t i = 0; i < func->ParamCount(); ++i)
   {
      cur_ty = _type_maker.get(func->getParam(i)->Type());
      assert (cur_ty != NULL);
      params_ty.push_back(cur_ty);
   }

   return params_ty;
}

llvm::Type*
Codegen::_getFuncReturnTy (ast::node::Func* func)
{
   llvm::Type* ty = NULL;

   if (func->ReturnTypeNode() != NULL)
   {
      ty = _type_maker.get(func->ExprType());
   }
   else
   {
      ty = _type_maker.makeVoidType();
   }

   IF_DEBUG
   {
      if (ty == NULL)
      {
         DEBUG_PRINTF("Function <%s> : cannot find return type <%s>\n",
            func->gValueCstr(),
            func->ExprType()->gQualifiedNameCstr());
      }
   }
   assert(ty != NULL);
   return ty;
}

bool
Codegen::_mustBeLoaded (ast::node::Node* node)
{
   if (node->hasBoundSymbol())
   {
      if (!node->BoundSymbol()->isAnyConstant()
         && !node->BoundSymbol()->isFuncSymbol())
      {
         return true;
      }
   }

   if (node->hasExprType())
   {
      //return true;
   }

   if (node->isKind(ast::node::Kind::BRACKET_OP))
   {
      return true;
   }

   /*
   switch (node->Kind())
   {
      case ast::node::Kind::FINAL_ID:
         if (
            node->BoundSymbol()->isFuncSymbol()
            || node->BoundSymbol()->isAnyConstant())
         {
            return false;
         }
         return true;
         break;
      case ast::node::Kind::GROUP:
         return _mustBeLoaded(node->getChild(0));

      case ast::node::Kind::BRACKET_OP:
      case ast::node::Kind::DEREF:
      case ast::node::Kind::DOT:
      case ast::node::Kind::TUPLE:
         return true;
   }
   */
   return false;

}


void
Codegen::gen (ast::node::Node* root)
{
   assert (_st != NULL);
   _module = new llvm::Module("top", llvm::getGlobalContext());

   _type_maker.setModule(_module);
   _type_maker.setStack(&_stack);
   _type_maker.setSymbolTable(_st);

   st::PointerType* void_ptr = st::util::getPointerType(_st->_core_types.VoidTy());
   _type_maker.bind(void_ptr, _type_maker.makeVoidPointerType());
   _stack.push();
   _stack.set(_st->_core_types._null, llvm::ConstantPointerNull::get(_type_maker.makeVoidPointerType()));

   //codegenTupleTypes();
   codegenMemoryFunctions();
   codegenFunctionDeclarations();
   codegenFunctionBodies(static_cast<ast::node::Root*>(root));
}

llvm::Value*
Codegen::cgAmpersandExpr (ast::node::Node* node)
{
   assert(node != NULL);
   assert(node->isAmpersandNode());

   std::string amp_label = "Amp";

   llvm::Value* base_val = cgExpr(node->getChild(0));

   return base_val;
}

llvm::Value*
Codegen::cgBinaryExpr (ast::node::Node* node)
{
   DEBUG_REQUIRE (node != NULL);

   llvm::Value* val = NULL;
   ast::node::Node* left_node = node->getChild(0);
   ast::node::Node* right_node = node->getChild(1);

   llvm::Value* left_val = cgExprAndLoad(left_node, node->ExprType());
   llvm::Value* right_val = cgExprAndLoad(right_node, node->ExprType());
   llvm::Instruction::BinaryOps op;

   switch (node->Kind())
   {
      case ast::node::Kind::OP_BIT_OR:  op = llvm::Instruction::Or; break;
      case ast::node::Kind::OP_BIT_AND: op = llvm::Instruction::And; break;
      case ast::node::Kind::OP_XOR:     op = llvm::Instruction::Xor; break;
      case ast::node::Kind::OP_LSHIFT:  op = llvm::Instruction::Shl; break;
      case ast::node::Kind::OP_RSHIFT:  op = llvm::Instruction::LShr; break;
      case ast::node::Kind::OP_PLUS:    op = llvm::Instruction::Add; break;
      case ast::node::Kind::OP_MINUS:   op = llvm::Instruction::Sub; break;
      case ast::node::Kind::OP_MODULO:  op = llvm::Instruction::SRem; break;
      case ast::node::Kind::OP_MUL:     op = llvm::Instruction::Mul; break;
      case ast::node::Kind::OP_DIV:     op = llvm::Instruction::SDiv; break;

      default:
         DEBUG_PRINTF("Unsupported arithmetic operation : %s\n",
            node->KindName().c_str());
         assert (false);
   }

   val = llvm::BinaryOperator::Create(op, left_val,
      right_val, "", _cur_bb);

   DEBUG_ENSURE (val != NULL);
   return val;
}

void
Codegen::cgBlock (ast::node::Block* block)
{
   assert (block != NULL);
   _stack.push();

   ast::node::Node* cur_node = block->_first_child;
   while (cur_node != NULL)
   {
      cgExpr(cur_node);
      cur_node = cur_node->_next;
   }

   _stack.pop();
}

llvm::Value*
Codegen::cgBracketOpExpr (ast::node::BracketOp* n)
{
   DEBUG_REQUIRE (n != NULL);

   // -------
   //  VALUE
   // -------
   ast::node::Node* value_node = n->ValueNode();
   st::Type* value_ty = value_node->ExprType();
   llvm::Value* val = cgExpr(value_node);
   assert (val != NULL);

   // -------
   //  INDEX
   // -------
   llvm::Value* index = cgExprAndLoad(n->IndexNode(), _st->gCoreTypes().IntTy());
   assert (index != NULL);

   // If this is a pointer we have to dereference as much as
   // (indirection_level - 1)
   if (value_ty->isPointerType())
   {
      for (int i = 0; i < st::castToPointerType(value_ty)->IndirectionLevel(); ++i)
      {
         val = new llvm::LoadInst(val, "", _cur_bb);
      }
   }

   // FIXME What ?
   std::vector<llvm::Value*> idx;
   if (!value_ty->isPointerType())
   {
      idx.push_back(_createInt32Constant(0));
   }
   idx.push_back(index);

   // Compute address
   llvm::GetElementPtrInst* inst = _createGepInst(val, idx);
   inst->setIsInBounds(true);

   DEBUG_ENSURE (inst != NULL);

   return inst;
}

llvm::Value*
Codegen::cgCallExpr (ast::node::Call* node)
{
   DEBUG_REQUIRE (node != NULL);
   DEBUG_REQUIRE (node->CallerNode() != NULL);

   llvm::Value* callee = NULL;
   st::Type* caller_node_ty = node->CallerNode()->ExprType();
   st::FunctionType* func_ty = NULL;

   // Calling a classic function
   if (caller_node_ty->isFunctionType())
   {
      st::Func* func = st::castToFunc(node->CallerNode()->BoundSymbol());
      func_ty = static_cast<st::FunctionType*>(caller_node_ty);
      callee = _functions[_getCodegenFuncName(func)];
   }
   // Calling a functor
   else if (st::util::isFunctorType(caller_node_ty))
   {
      st::PointerType* fctor = st::castToPointerType(caller_node_ty);
      func_ty = static_cast<st::FunctionType*>(fctor->getNonPointerParent());
      callee = cgExprAndLoad(node->CallerNode(), func_ty);
   }
   else
   {
      assert(false);
   }

   assert(func_ty->isFunctionType());
   std::vector<llvm::Value*> params;

   // -----------------
   //  With parameters
   // -----------------
   if (node->ParamsNode() != NULL)
   {
      ast::node::Node* cur_param_node = NULL;
      llvm::Value* param_value = NULL;

      for (size_t i = 0; i < node->ParamsNode()->ChildCount(); ++i)
      {
         cur_param_node = node->ParamsNode()->getChild(i);
         param_value = cgExpr(cur_param_node);//, func_ty->getArgument(i));
         if (_mustBeLoaded(cur_param_node))
         {
            param_value = new llvm::LoadInst(param_value, "", _cur_bb);
         }
         param_value = _castLlvmValue(param_value, cur_param_node->ExprType(), func_ty->getArgument(i));
         params.push_back(param_value);
      }
   }
   llvm::CallInst* call = llvm::CallInst::Create(callee, params, "", _cur_bb);

   if (call != NULL && !_st->isVoidType(func_ty->ReturnType()))
   {
      call->setDoesNotReturn(true);
   }

   DEBUG_ENSURE (call != NULL);

   return call;
}

llvm::Value*
Codegen::cgCastExpr (ast::node::CastOp* n)
{
   DEBUG_REQUIRE (n != NULL);

   llvm::Value* src_val = cgExprAndLoad(n->ValueNode());
   st::Type* src_ty = n->ValueNode()->ExprType();
   st::Type* dest_ty = n->ExprType();
   llvm::Value* val = _castLlvmValue(src_val, src_ty, dest_ty);

   /*
   // Casting between two integer types
   if (src_ty->isIntType() && dest_ty->isIntType())
   {
      // Extending (SAFE)
      if (src_ty->ByteSize() < dest_ty->ByteSize())
      {
         val = new llvm::SExtInst(src_val, _type_maker.get(dest_ty), "", _cur_bb);
      }
      // Truncating (UNSAFE)
      else if (src_ty->ByteSize() > dest_ty->ByteSize())
      {
         val = new llvm::TruncInst(src_val, _type_maker.get(dest_ty), "", _cur_bb);
      }
      else
      {
         // No casting required
         val = src_val;
      }
   }
   // Casting between two pointer types
   else if (src_ty->isPointerType() && dest_ty->isPointerType())
   {
      if (static_cast<st::PointerType*>(dest_ty)->PointedType()->Name() == "void")
      {
         val = new llvm::BitCastInst(src_val, _type_maker.get(dest_ty), "", _cur_bb);
      }
   }
   */

   DEBUG_ENSURE (val != NULL);
   return val;
}


llvm::Value*
Codegen::cgCompOp (ast::node::BinaryOp* n)
{
   assert (n != NULL);
   assert (_cur_bb != NULL);

   ast::node::Node* left_val_node = n->LeftNode();
   ast::node::Node* right_val_node = n->RightNode();
   st::Type* left_ty = left_val_node->ExprType();
   st::Type* right_ty = right_val_node->ExprType();

   st::Type* expected_operand_ty = NULL;
   if (left_ty->isIntType() && right_ty->isIntType())
   {
      expected_operand_ty = st::util::getBiggestIntType(
         st::castToIntType(left_ty),
         st::castToIntType(right_ty));
   }

   llvm::Value* left_val = cgExprAndLoad(left_val_node, expected_operand_ty);
   llvm::Value* right_val = cgExprAndLoad(right_val_node, expected_operand_ty);

   llvm::ICmpInst::Predicate pred;

   switch (n->Kind())
   {
      case ast::node::Kind::OP_NE:    pred = llvm::ICmpInst::ICMP_NE; break;
      case ast::node::Kind::OP_EQ_EQ: pred = llvm::ICmpInst::ICMP_EQ; break;
      case ast::node::Kind::OP_LT:    pred = llvm::ICmpInst::ICMP_SLT; break;
      case ast::node::Kind::OP_LTE:   pred = llvm::ICmpInst::ICMP_SLE; break;
      case ast::node::Kind::OP_GT:    pred = llvm::ICmpInst::ICMP_SGT; break;
      case ast::node::Kind::OP_GTE:   pred = llvm::ICmpInst::ICMP_SGE; break;

      default:
         DEBUG_PRINTF("Unsupported comparison operator (%s)\n",
            n->KindName().c_str());
         assert(false);

   }

   llvm::CmpInst* comp_inst = new llvm::ICmpInst(*_cur_bb, pred, left_val,
      right_val, "");

   return comp_inst;
}

llvm::Value*
Codegen::cgDotExpr (ast::node::Dot* node)
{
   DEBUG_REQUIRE (node != NULL);
   DEBUG_REQUIRE (node->isDotNode());

   llvm::Value* left_node = NULL;
   // We can't rely on cgExpr here because it would load the left node and we
   // wouldn't be able to have a pointer to use GetElementPtr on.
   if (node->LeftNode()->isDotNode())
   {
      left_node = cgDotExpr(static_cast<ast::node::Dot*>(node->LeftNode()));
   }
   else
   {
      left_node = cgFinalIdExpr(static_cast<ast::node::Text*>(node->LeftNode()));
   }
   std::vector<llvm::Value*> idx;

   int indirection_level = 0;
   if (node->LeftNode()->ExprType()->isPointerType())
   {
      st::PointerType* ptr_ty = st::castToPointerType(node->LeftNode()->ExprType());
      indirection_level = ptr_ty->IndirectionLevel();
   }

   for (int i = 0; i <= indirection_level; ++i)
   {
      left_node = new llvm::LoadInst(left_node, "", _cur_bb);
      idx.push_back(_createInt32Constant(0));
      assert(left_node != NULL);
   }

   // Compute the field index in the whole type hierarchy
   st::Field* field = static_cast<st::Field*>(node->BoundSymbol());
   st::Class* cls_ty = st::castToClassType(field->Parent());
   int field_index = cls_ty->getFieldAbsoluteIndex(field->FieldIndex());

   idx.push_back(_createInt32Constant(field_index));

   llvm::Value* gep_inst = _createGepInst(left_node, idx);

   DEBUG_ENSURE (gep_inst!= NULL);

   return gep_inst;
}

llvm::Value*
Codegen::cgExpr (ast::node::Node* node)
{
   assert (node != NULL);
   llvm::Value* res = NULL;

   switch (node->Kind())
   {
      case ast::node::Kind::AMPERSAND:
         res = cgAmpersandExpr (node);
         break;

      case ast::node::Kind::BRACKET_OP:
         res = cgBracketOpExpr(static_cast<ast::node::BracketOp*>(node));
         break;

      case ast::node::Kind::CALL:
         res = cgCallExpr(static_cast<ast::node::Call*>(node));
         break;

      case ast::node::Kind::DOT:
         res = cgDotExpr(static_cast<ast::node::Dot*>(node));
         break;

      case ast::node::Kind::OP_NE:
      case ast::node::Kind::OP_EQ_EQ:
      case ast::node::Kind::OP_LT:
      case ast::node::Kind::OP_LTE:
      case ast::node::Kind::OP_GT:
      case ast::node::Kind::OP_GTE:
         res = cgCompOp(static_cast<ast::node::BinaryOp*>(node));
         break;

      case ast::node::Kind::OP_CAST:
         res = cgCastExpr (static_cast<ast::node::CastOp*>(node));
         break;

      case ast::node::Kind::GROUP:
         res = cgExpr(node->getChild(0));
         break;

      case ast::node::Kind::IF:
         cgIfStatement(static_cast<ast::node::If*>(node));
         break;

      case ast::node::Kind::FINAL_ID:
         res = cgFinalIdExpr(static_cast<ast::node::FinalId*>(node));
         break;

      case ast::node::Kind::FOR:
         cgForStatement(static_cast<ast::node::For*>(node));
         break;

      case ast::node::Kind::NEW:
         res = cgNewExpr(static_cast<ast::node::New*>(node));
         break;

      case ast::node::Kind::NUMBER:
         res = cgNumberExpr(static_cast<ast::node::Number*>(node));
         assert (res != NULL);
         break;

      case ast::node::Kind::OP_BIT_AND:
      case ast::node::Kind::OP_BIT_OR:
      case ast::node::Kind::OP_DIV:
      case ast::node::Kind::OP_LSHIFT:
      case ast::node::Kind::OP_RSHIFT:
      case ast::node::Kind::OP_MINUS:
      case ast::node::Kind::OP_MODULO:
      case ast::node::Kind::OP_MUL:
      case ast::node::Kind::OP_PLUS:
      case ast::node::Kind::OP_XOR:
         res = cgBinaryExpr(node);
         break;

      case ast::node::Kind::DEREF:
         res = cgDerefExpr(node);
         break;

      case ast::node::Kind::RETURN:
         cgReturnStatement (node);
         break;

      case ast::node::Kind::TUPLE:
         res = codegenTuple (static_cast<ast::node::Tuple*>(node));
         break;

      case ast::node::Kind::STRING:
         res = cgString(static_cast<ast::node::String*>(node));
         break;

      case ast::node::Kind::VARIABLE_ASSIGNMENT:
         cgVarAssignStatement (static_cast<ast::node::VarAssign*>(node));
         break;

      case ast::node::Kind::VARIABLE_DECLARATION:
         cgVarDeclStatement (static_cast<ast::node::VarDecl*>(node));
         break;

      case ast::node::Kind::WHILE:
         cgWhileStatement (static_cast<ast::node::While*>(node));
         break;

      default:
         DEBUG_PRINTF("Unsupported node type (%s)\n", node->KindName().c_str());
         assert(false);
   }

   return res;
}

llvm::Value*
Codegen::cgExprAndLoad (ast::node::Node* node)
{
   llvm::Value* val = cgExpr(node);
   bool must_load = false;

   if (val != NULL)
   {
      must_load = _mustBeLoaded(node);
   }

   if (must_load)
   {
      val = new llvm::LoadInst(val, "", _cur_bb);
   }

   return val;
}

llvm::Value*
Codegen::cgExprAndLoad (ast::node::Node* node, st::Type* dest_ty)
{
   llvm::Value* val = NULL;
   st::Type* src_ty = node->ExprType();

   if (dest_ty->isIntType() && node->isNumberNode())
   {
      val = _type_maker.makeConstant(static_cast<st::Constant*>(node->BoundSymbol()));
   }
   else
   {
      val = cgExpr(node);
   }
   bool must_load = _mustBeLoaded(node);


   if (src_ty != dest_ty)
   {
      val = _castLlvmValue(val, src_ty, dest_ty);
   }
   if (src_ty->isPointerType() && dest_ty->isPointerType())
   {
      st::PointerType* src_ptr_ty = st::castToPointerType(src_ty);
      st::PointerType* dest_ptr_ty = st::castToPointerType(dest_ty);
   }

   if (val != NULL && must_load)
   {
      val = new llvm::LoadInst(val, "", _cur_bb);
   }

   return val;
}


void
Codegen::cgFile (ast::node::File* file_node)
{
   ast::node::Node* node = NULL;

   // Codegen function bodies
   for (size_t i = 0 ; i < file_node->ChildCount(); ++i)
   {
      node = file_node->getChild(i);
      if (node->isFuncNode())
      {
         cgFunctionBody(static_cast<ast::node::Func*>(node));
      }
   }
}

llvm::Value*
Codegen::cgFinalIdExpr (ast::node::Text* node)
{
   DEBUG_REQUIRE (node->hasBoundSymbol());

   llvm::Value* ty = _stack.get(node->BoundSymbol());
   IF_DEBUG
   {
      if (ty == NULL)
      {
         DEBUG_PRINTF("Cannot find final id `%s' in the stack\n",
            node->gValueCstr());
      }
   }
   return ty;
}

void
Codegen::cgForStatement (ast::node::For* n)
{
   assert (n != NULL);

   cgExpr(n->InitializationNode());


   llvm::BasicBlock* body_block = llvm::BasicBlock::Create(
      llvm::getGlobalContext(), "for_block", _cur_func);

   llvm::BasicBlock* after_block = llvm::BasicBlock::Create(
      llvm::getGlobalContext(), "for_after", _cur_func);

   llvm::BasicBlock* cond_block = llvm::BasicBlock::Create(
      llvm::getGlobalContext(), "for_cond", _cur_func);

   _cur_bb->getInstList().push_back(llvm::BranchInst::Create(cond_block));

   _cur_bb = body_block;

   cgBlock(static_cast<ast::node::Block*>(n->BlockNode()));
   cgExpr(n->IterationNode());
   body_block->getInstList().push_back(llvm::BranchInst::Create(cond_block));

   _cur_bb = cond_block;
   llvm::Value* cond = cgExpr(n->ConditionNode());

   llvm::BranchInst::Create(body_block, after_block, cond, _cur_bb);

   _cur_bb = after_block;
}

void
Codegen::cgFunctionBody (ast::node::Func* func_node)
{
   assert(func_node->isFuncNode());

   // Don't try to generate body for a virtual function
   if (func_node->BodyNode() != NULL)
   {
      st::Func* func_sym = st::castToFunc(func_node->BoundSymbol());
      assert (func_sym != NULL);

      llvm::Function* func = _functions[_getCodegenFuncName(func_sym)];
      assert (func != NULL);

      llvm::BasicBlock& block = func->getEntryBlock();
      _cur_bb = &block;
      _exit_block = NULL;
      _cur_func = func;

      _stack.push();

      // Set parameters
      // We set this here instead of cgFunctionDef because we can append the
      // parameters to the stack of the body of the function.
      llvm::Function::arg_iterator i;
      int j;
      st::Var* func_param = NULL;
      llvm::Argument* arg = NULL;
      llvm::Value* alloc = NULL;
      llvm::Type* param_lty = NULL;
      for (i = func->arg_begin(), j=0; i != func->arg_end(); ++i, ++j)
      {
         func_param = func_sym->getParam(j);
         if (func_param != NULL)
         {
            i->setName(func_param->Name());
            param_lty = _type_maker.get(func_param->Type());
            alloc = new llvm::AllocaInst(param_lty, 0, "", _cur_bb);
            new llvm::StoreInst(&*i, alloc, false, _cur_bb);
            _stack.set(func_param, alloc);
         }
      }

      cgBlock(func_node->BodyNode());
      _stack.pop();

      if (func_sym->ReturnType() == _st->_core_types.VoidTy())
      {
         llvm::ReturnInst* t = llvm::ReturnInst::Create(_module->getContext(),
            NULL, _cur_bb);
      }

   }

   _cur_bb = NULL;
}

void
Codegen::cgFunctionDef (ast::node::Func* func_node)
{
   DEBUG_PRINT("\n");
   st::Func* func_sym = st::castToFunc(func_node->BoundSymbol());
   std::vector<llvm::Type*> func_ty_args;
   std::string func_name;

   if (func_sym->IsEntryPoint())
   {
      func_name = "main";
   }
   else
   {
      func_name = _getCodegenFuncName(func_sym);
   }

   // External function
   std::vector<llvm::Type*> params;
   if (func_sym->IsExternal())
   {
      st::Var* func_param = NULL;
      for (size_t i = 0; i < func_sym->ParamCount(); ++i)
      {
         func_param = func_sym->_params[i];
         params.push_back(_type_maker.get(func_param->Type()));
         assert (params[i] != NULL);
      }
   }
   llvm::FunctionType* func_ty = llvm::FunctionType::get(
      _getFuncReturnTy(func_node), params, false);

   llvm::GlobalValue::LinkageTypes func_link = llvm::GlobalValue::ExternalLinkage;

   llvm::Function* func = llvm::Function::Create(func_ty,
      func_link,
      func_name,
      _module);
   func->setCallingConv(llvm::CallingConv::C);
   _cur_func = func;

   // Don't codegen a body for a virtual/external function
   if (func_node->BodyNode() != NULL)
   {
      llvm::BasicBlock* block = llvm::BasicBlock::Create(
         llvm::getGlobalContext(), "entry", func);
   }

   _functions[_getCodegenFuncName(func_sym)] = func;
   _stack.set(func_sym, func);
}

void
Codegen::cgIfStatement (ast::node::If* node)
{
   assert (node != NULL);
   assert (_cur_bb != NULL);

   // ---------------
   //  Create blocks
   // ---------------
   llvm::BasicBlock* true_block = _createBasicBlock("if_true");
   llvm::BasicBlock* false_block = NULL;
   if (node->ElseBlockNode() != NULL)
   {
      false_block = _createBasicBlock("if_false");
   }
   llvm::BasicBlock* after_block = _createBasicBlock("if_after");


   // -----------
   //  Condition
   // -----------
   llvm::Value* cond = cgExpr(node->ConditionNode());

   _pushNewCondBranchInst(_cur_bb, cond, true_block, after_block);


   // ------------
   //  TRUE block
   // ------------
   _cur_bb = true_block;
   _exit_block = true_block;
   cgBlock(node->IfBlockNode());

   _pushNewBranchInst(_cur_bb, after_block);


   // -------------
   //  FALSE block
   // -------------
   if (false_block != NULL)
   {
      _cur_bb = false_block;
      _exit_block = after_block;
      cgBlock(node->ElseBlockNode());
   }

   _cur_bb = after_block;
}

void
Codegen::codegenMemoryFunctions ()
{
   // MALLOC
   std::vector<llvm::Type*> malloc_tys;
   malloc_tys.push_back(llvm::Type::getInt32Ty(_module->getContext()));

   llvm::FunctionType* malloc_ty = llvm::FunctionType::get(
      _type_maker.makeVoidPointerType(),
      malloc_tys,
      /*isVarArg=*/false);

   llvm::Function* malloc = llvm::Function::Create(malloc_ty,
      llvm::GlobalValue::ExternalLinkage,
      "malloc",
      _module);
   _functions["malloc"] = malloc;
}

llvm::Value*
Codegen::cgNewExpr (ast::node::New* node)
{
   llvm::Value* byte_size = NULL;

   ast::node::Node* type_node = node->getChild(0);
   st::Type* obj_ty = st::castToType(type_node->BoundSymbol());

   // FIXME Spaghetti code !
   if (type_node->BoundSymbol()->isArrayType())
   {
      st::ArrayType* arr_ty = static_cast<st::ArrayType*>(obj_ty);
      int type_byte_size = st::castToType(type_node->getChild(0)->BoundSymbol())->ByteSize();
      llvm::Value* num_obj = cgExprAndLoad(type_node->getChild(1), _st->_core_types.IntTy());
      llvm::Value* obj_size = _createInt32Constant(type_byte_size);
      byte_size = llvm::BinaryOperator::Create(llvm::Instruction::Mul, num_obj, obj_size, "", _cur_bb);
   }
   else
   {
      int type_byte_size = st::castToType(obj_ty)->ByteSize();
      byte_size = llvm::ConstantInt::get(_type_maker.get(_st->_core_types.IntTy()), type_byte_size);
   }

   // -------------
   //  Malloc call
   // -------------
   llvm::Value* malloc_call = llvm::CallInst::Create(_functions["malloc"],
      byte_size, "", _cur_bb);
   assert(malloc_call != NULL);

   // Cast the return pointer to the appropriate pointer type
   assert (_type_maker.get(node->ExprType()) != NULL);
   llvm::Value* ret = new llvm::BitCastInst(malloc_call, _type_maker.get(
      node->ExprType()), "new_cast", _cur_bb);

   // ------------------
   //  Constructor call
   // ------------------
   if (obj_ty->isClassType())
   {
      initializeValue(st::castToClassType(obj_ty), ret);
   }
   else if (obj_ty->isArrayType())
   {
      st::ArrayType* arr_ty = static_cast<st::ArrayType*>(obj_ty);
      initializeArrayOfClassInstances(arr_ty, ret, false);
   }
   else
   {
      assert(false);
   }

   assert (ret != NULL);
   return ret;
}

llvm::Value*
Codegen::cgNumberExpr (ast::node::Number* node)
{
   DEBUG_REQUIRE (node != NULL);
   DEBUG_REQUIRE (node->BoundSymbol() != NULL);
   DEBUG_REQUIRE (node->BoundSymbol()->isIntConstant());

   // FIXME This works only for signed integers
   st::IntConstant* i_const = st::castToIntConstant(node->BoundSymbol());
   llvm::Value* val = llvm::ConstantInt::get(llvm::getGlobalContext(),
      llvm::APInt(node->BoundSymbol()->ByteSize() * 8, i_const->getSignedValue(), false));

   DEBUG_ENSURE (val != NULL);

   return val;
}

llvm::Value*
Codegen::cgDerefExpr (ast::node::Node* node)
{
   llvm::Value* val = cgExpr(node->getChild(0));
   return new llvm::LoadInst(val, "", _cur_bb);
}

void
Codegen::cgReturnStatement (ast::node::Node* node)
{
   DEBUG_REQUIRE (node != NULL);
   DEBUG_REQUIRE (node->getChild(0) != NULL);

   llvm::Value* val = cgExprAndLoad(node->getChild(0), node->ExprType());
   assert(val != NULL);

   llvm::ReturnInst::Create(_module->getContext(), val, _cur_bb);
}

llvm::Value*
Codegen::cgString (ast::node::String* n)
{
   st::Type* mem_ty = st::util::lookupArrayType(_st->System(), "char", n->gValue().size() + 1);
   assert(mem_ty != NULL);

   llvm::Type* llvm_ty = _type_maker.get(mem_ty);
   assert(llvm_ty != NULL);

   llvm::Constant* str_val = llvm::ConstantArray::get(_module->getContext(), n->gValue().c_str(), true);

   llvm::GlobalVariable* cons = new llvm::GlobalVariable(*_module, llvm_ty, true,
      llvm::GlobalValue::PrivateLinkage, str_val, "");

   std::vector<llvm::Constant*> idx;
   idx.push_back(_createInt32Constant(0));
   idx.push_back(_createInt32Constant(0));

   llvm::Value* ret = llvm::ConstantExpr::getGetElementPtr(cons, idx);
   return ret;
}

void
Codegen::cgVarAssignStatement (ast::node::VarAssign* node)
{
   st::Type* right_ty = st::castToType(node->ValueNode()->ExprType());
   llvm::Value* left_val = cgExpr(node->NameNode());
   llvm::Value* right_val = cgExprAndLoad(node->ValueNode(), node->ExprType());

   new llvm::StoreInst(right_val, left_val, _cur_bb);
}

void
Codegen::cgVarDeclStatement (ast::node::VarDecl* node)
{
   DEBUG_REQUIRE (node != NULL);
   DEBUG_REQUIRE (node->isVarDeclNode());
   DEBUG_REQUIRE (node->hasExprType());

   llvm::Type* var_ty = NULL;
   llvm::Value* var_len = NULL;

   if (node->TypeNode()->isArrayNode())
   {
      ast::node::Array* arr = static_cast<ast::node::Array*>(node->TypeNode());
      assert (arr->LengthNode() != NULL);

      var_ty = _type_maker.get(node->TypeNode()->BoundSymbol());
   }
   else
   {
      var_ty = _type_maker.get(node->ExprType());
   }

   assert(var_ty != NULL);

   llvm::Value* var = new llvm::AllocaInst(var_ty, var_len,
      node->Name(), _cur_bb);

   if (node->ValueNode() != NULL)
   {
      llvm::Value* var_val = cgExprAndLoad(node->ValueNode(), node->ExprType());
      assert (var_val != NULL);
      new llvm::StoreInst(var_val, var, _cur_bb);
   }

   // ------------------
   //  Constructor call
   // ------------------
   st::Type* obj_ty = st::castToType(node->TypeNode()->BoundSymbol());
   // Single object static allocation
   if (obj_ty->isClassType() && node->ValueNode() == NULL)
   {
      st::Class* cls_ty = st::castToClassType(obj_ty);
      if (cls_ty->DefaultCtor() != NULL)
      {
         initializeValue(cls_ty, var);
      }
   }
   // Array static allocation
   else if (obj_ty->isArrayType() && node->ValueNode() == NULL)
   {

      st::ArrayType* arr_ty = static_cast<st::ArrayType*>(obj_ty);
      if (arr_ty->isArrayOfClassInstances())
      {
         //llvm::Value* var = new llvm::LoadInst(var, "", _cur_bb);
         initializeArrayOfClassInstances(arr_ty, var, true);
      }
   }

   _stack.set(node->BoundSymbol(), var);
}

void
Codegen::cgWhileStatement (ast::node::While* n)
{
   DEBUG_REQUIRE (n != NULL);

   llvm::BasicBlock* while_cond = _createBasicBlock("while_head");
   llvm::BasicBlock* while_body = _createBasicBlock("while_body");
   llvm::BasicBlock* while_after = _createBasicBlock("while_after");

   // Branch to the condition block (from the current block)
   _pushNewBranchInst(_cur_bb, while_cond);

   // -----------
   //  Condition
   // -----------
   _cur_bb = while_cond;
   llvm::Value* cond_val = cgExpr(n->ConditionNode());
   assert(cond_val != NULL);

   // Either branch the loop block or skip the loop
   _pushNewCondBranchInst(while_cond, cond_val, while_body, while_after);

   // ------------
   //  While body
   // ------------
   _cur_bb = while_body;
   cgBlock(static_cast<ast::node::Block*>(n->BodyNode()));

   // Branch to the condition block
   _pushNewBranchInst(_cur_bb, while_cond);


   _cur_bb = while_after;
}

void
Codegen::codegenFunctionDeclarations ()
{
   st::Func* func = _st->FunctionLinkedListHead();
   while (func != NULL)
   {
      codegenFunctionType (func);
      func = func->NextFunction();
   }
}

void
Codegen::codegenFunctionBodies (ast::node::Root* root_n)
{
   ast::node::File* file_node = NULL;
   ast::node::Func* func_node = NULL;
   for (size_t i = 0; i < root_n->ChildCount(); ++i)
   {
      file_node = static_cast<ast::node::File*>(root_n->getChild(i));
      func_node = file_node->FunctionLinkedListHead();
      while (func_node != NULL)
      {
         cgFunctionBody(func_node);
         func_node = func_node->NextFunction();
      }
   }
}

void
Codegen::codegenFunctionType (st::Func* func_ty)
{
   std::vector<llvm::Type*> func_ty_args;
   std::string func_name;

   if (func_ty->IsEntryPoint())
   {
      func_name = "main";
   }
   else
   {
      func_name = _getCodegenFuncName(func_ty);
   }

   // ------------
   //  PARAMETERS
   // ------------
   std::vector<llvm::Type*> params;
   st::Var* func_param = NULL;
   // We will set their names in ::codegenFunctionBody so that we append
   // them to the stack
   for (size_t i = 0; i < func_ty->ParamCount(); ++i)
   {
      func_param = func_ty->_params[i];
      params.push_back(_type_maker.get(func_param->Type()));
      assert (params[i] != NULL);
   }

   // -------------
   //  RETURN TYPE
   // -------------
   llvm::FunctionType* func_lty = NULL;
   st::Type* return_ty = func_ty->ReturnType();
   llvm::Type* return_lty = NULL;
   if (!_st->isVoidType(return_ty))
   {
      return_lty = _type_maker.get(return_ty);
   }
   else
   {
      return_lty = _type_maker.makeVoidType();
   }
   assert (return_lty != NULL);
   func_lty = llvm::FunctionType::get(return_lty, params, false);
   assert (func_lty != NULL);

   llvm::GlobalValue::LinkageTypes func_link;
   if (func_ty->IsExternal())
   {
      func_link = llvm::GlobalValue::ExternalLinkage;
   }
   else
   {
      func_link = llvm::GlobalValue::ExternalLinkage;
   }

   llvm::Function* func = llvm::Function::Create(func_lty,
      func_link,
      func_name,
      _module);
   func->setCallingConv(llvm::CallingConv::C);
   _cur_func = func;

   // Don't codegen a body for a virtual/external function
   if (func_ty->HasBody())
   {
      llvm::BasicBlock* block = llvm::BasicBlock::Create(
         llvm::getGlobalContext(), "entry", func);
   }

   _functions[_getCodegenFuncName(func_ty)] = func;
   _stack.set(func_ty, func);

}

llvm::Value*
Codegen::codegenTuple (ast::node::Tuple* n)
{
   DEBUG_REQUIRE (n != NULL);

   st::TupleType* tuple_ty = static_cast<st::TupleType*>(n->ExprType());
   llvm::Type* tuple_lty = _type_maker.get(tuple_ty);
   llvm::AllocaInst* var = new llvm::AllocaInst(tuple_lty, 0, "", _cur_bb);

   llvm::Value* field = NULL;
   llvm::Value* field_val = NULL;
   std::vector<llvm::Value*> field_idx;
   field_idx.push_back(_createInt32Constant(0));
   field_idx.push_back(NULL); // Reserved for the field index

   for (size_t i = 0; i < n->ChildCount(); ++i)
   {
      field_idx[1] = _createInt32Constant(i);
      field = _createGepInst(var, field_idx);

      field_val = cgExprAndLoad(n->getChild(i), tuple_ty->Subtypes()[i]);
      new llvm::StoreInst(field_val, field, "", _cur_bb);
   }

   return var;
}

std::string
Codegen::getLlvmByteCode ()
{
#if 0
   // Don't delete that !
   //
   // I seem to be on the right track but, for some reason, no code is emited

   const llvm::Target* target = NULL;

   for (llvm::TargetRegistry::iterator it = llvm::TargetRegistry::begin(),
           ie = llvm::TargetRegistry::end(); it != ie; ++it)
   {
      if (strcmp(it->getName(),"x86")==0)
      {
         target = &*it;
      }
   }

   if (target != NULL)
   {
      std::string err;
      llvm::raw_fd_ostream obj_file("/home/thomas/test.s", err);
      llvm::formatted_raw_ostream out(obj_file);
      DEBUG_PRINTF("Errors ? %s\n", err.c_str());

      llvm::TargetMachine* t = target->createTargetMachine(_module->getTargetTriple(), "", "");
      assert (t != NULL);
      llvm::PassManager pm;
      pm.add(new llvm::TargetData(_module));
      t->addPassesToEmitFile(pm, out, llvm::TargetMachine::CGFT_AssemblyFile,llvm::CodeGenOpt::Less);
      pm.run(*_module);

   }
   else
   {
      DEBUG_PRINT("Architecture not supported\n");
   }
#endif

   std::string bc;
   llvm::raw_string_ostream stream(bc);
   _module->print(stream, NULL);
   return bc;
}

void
Codegen::initializeValue (st::Type* ty, llvm::Value* val)
{
   if (ty->isClassType())
   {
      st::Class* cls_ty = st::castToClassType(ty);

      // 0 initialize
      llvm::Constant* init = llvm::ConstantAggregateZero::get(_type_maker.get(cls_ty));
      new llvm::StoreInst(init, val, "", _cur_bb);

      // Call constructor
      if (cls_ty->DefaultCtor() != NULL)
      {
         llvm::CallInst::Create(
            _functions[cls_ty->DefaultCtor()->gQualifiedName()],
            val, "", _cur_bb);
      }
   }
   else if (ty->isIntType())
   {
      st::IntType* int_ty = st::castToIntType(ty);

      llvm::Constant* init = llvm::ConstantInt::get(_type_maker.get(int_ty), 0, true);
      new llvm::StoreInst(init, val, "", _cur_bb);
   }
}

void
Codegen::initializeArrayOfClassInstances (st::ArrayType* arr_ty, llvm::Value* arr, bool is_static)
{
   DEBUG_REQUIRE (arr_ty != NULL);
   DEBUG_REQUIRE (arr_ty->isArrayType());
   DEBUG_REQUIRE (arr_ty->ItemType() != NULL);
   DEBUG_REQUIRE (arr_ty->ItemType()->isAnyType());
   DEBUG_REQUIRE (arr != NULL);

   llvm::BasicBlock* cond_bb = _createBasicBlock("ctor.cond");
   llvm::BasicBlock* body_bb = _createBasicBlock("ctor.body");
   llvm::BasicBlock* after_bb = _createBasicBlock("ctor.after");

   llvm::AllocaInst* counter_var = new llvm::AllocaInst(
      _type_maker.get(_st->_core_types.IntTy()), 0, "ctor.i", _cur_bb);
   new llvm::StoreInst(_createInt32Constant(0), counter_var, false, _cur_bb);
   llvm::AllocaInst* counter_max = new llvm::AllocaInst(
      _type_maker.get(_st->_core_types.IntTy()), 0, "ctor.i_max", _cur_bb);
   new llvm::StoreInst(_createInt32Constant(arr_ty->ArrayLength()), counter_max, false, _cur_bb);

   // --------
   //  Before
   // --------
   llvm::BranchInst::Create(cond_bb, _cur_bb);

   // -----------
   //  Condition
   // -----------
   llvm::Value* cond_value = new llvm::ICmpInst(*cond_bb, llvm::ICmpInst::ICMP_SLT, counter_var, counter_max);
   llvm::BranchInst::Create(body_bb, after_bb, cond_value, cond_bb);

   // ------
   //  Body
   // ------
   llvm::Value* counter_val = new llvm::LoadInst(counter_var, "", body_bb);
   std::vector<llvm::Value*> gep_idx;
   if (is_static) gep_idx.push_back(_createInt32Constant(0));
   gep_idx.push_back(counter_val);
   llvm::Value* item_val = llvm::GetElementPtrInst::Create(arr, gep_idx,
      "", body_bb);
   _cur_bb = body_bb;
   initializeValue(arr_ty->ItemType(), item_val);

   llvm::BranchInst::Create(cond_bb, body_bb);

   _cur_bb = after_bb;
}

void
Codegen::tearDown ()
{
   llvm::llvm_shutdown();
}

} } }

#endif // HAVE_LLVM
