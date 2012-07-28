#include "mem/codegen/llvm/Codegen.hpp"


namespace mem { namespace codegen { namespace llvm_ {


void
Codegen::_dumpTypes ()
{
   std::map<std::string, llvm::Type*>::iterator i;
   for (i = _classes.begin() ; i != _classes.end(); ++i)
   {
      printf("%s\n", (*i).first.c_str());
   }
}

std::string
Codegen::_getCodegenFuncName (st::Func* func)
{
   std::string name = "";

   if (func->Metadata()->has("external"))
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
   if (!left_ty->isPtrSymbol())
   {
      common_ty = static_cast<st::Type*>(left_ty);
   }
   else if (!right_ty->isPtrSymbol())
   {
      common_ty = static_cast<st::Type*>(right_ty);
   }
   // Both operands are pointers
   else
   {
      common_ty = st::Util::getPointerBaseType(static_cast<st::Ptr*>(left_ty));
   }

   return common_ty;
}

llvm::Type*
Codegen::_getLlvmIntTy (size_t size)
{
   return llvm::Type::getIntNTy(_module->getContext(), size * 8);
}

llvm::Type*
Codegen::_getLlvmTy (st::Type* mem_ty)
{
   assert (mem_ty != NULL);
   llvm::Type* ty = NULL;

   // Type is found
   if (_classes.find(mem_ty->gQualifiedName()) != _classes.end())
   {
      ty = _classes[mem_ty->gQualifiedName()];
      assert(ty != NULL);
   }
   // Type is NOT found, so ?
   else
   {
      if (mem_ty->isPtrSymbol())
      {
         // Create the pointer type
         llvm::Type* base_ty = _getLlvmTy(
            static_cast<mem::st::Ptr*>(mem_ty)->BaseType());
         if (base_ty != NULL)
         {
            // TODO What is the second parameter (AddressSpace) ?
             ty = llvm::PointerType::get(base_ty, 0);
         }
      }
      else if (mem_ty->isArraySymbol())
      {
         st::Array* arr = static_cast<mem::st::Array*>(mem_ty);
         llvm::Type* base_ty = _getLlvmTy(arr->BaseType());
         if (base_ty != NULL)
         {
            ty = llvm::ArrayType::get(base_ty, arr->ArrayLength());
         }
      }
   }

   IF_DEBUG
   {
      if (ty == NULL)
      {
         DEBUG_PRINTF("Type <%s> not found.\n", mem_ty->NameCstr());
         assert(ty != NULL);
      }
   }
   return ty;
}

std::vector<llvm::Type*>
Codegen::_getFuncParamsTy (st::Func* func)
{
   std::vector<llvm::Type*> params_ty;
   llvm::Type* cur_ty = NULL;

   for (size_t i = 0; i < func->ParamCount(); ++i)
   {
      cur_ty = _getLlvmTy(func->getParam(i)->Type());
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
      ty = _classes[func->ExprType()->gQualifiedName()];
   }
   else
   {
      ty = _getVoidTy();
   }

   assert(ty != NULL);
   return ty;
}

llvm::Type*
Codegen::_getVoidTy ()
{
   return llvm::Type::getVoidTy(_module->getContext());
}

void
Codegen::addType (st::Type* mem_ty, llvm::Type* llvm_ty)
{
   if (mem_ty->isPrimitiveSymbol())
   {
      // TODO This is very ugly...
      if (mem_ty == _st->_core_types.gIntTy())
      {
         _classes[mem_ty->gQualifiedName()] = _getLlvmIntTy(sizeof(int));
         assert(_classes[mem_ty->gQualifiedName()] != NULL);
      }
      else if (mem_ty == _st->_core_types.gBoolTy())
      {
         _classes[mem_ty->gQualifiedName()] = llvm::Type::getIntNTy(
            _module->getContext(), 1);
      }
      else if (mem_ty == _st->_core_types.gCharTy())
      {
         _classes[mem_ty->gQualifiedName()] = _getLlvmIntTy(sizeof(char));
      }
      else if (mem_ty == _st->_core_types.gShortTy())
      {
         _classes[mem_ty->gQualifiedName()] = _getLlvmIntTy(sizeof(short));
      }
      else if (mem_ty == _st->_core_types.gVoidTy())
      {
         _classes[mem_ty->gQualifiedName()] = _getVoidTy();
      }
      else
      {
         printf("Primitive : %s\n", mem_ty->gQualifiedNameCstr());
         assert(false && "Primitive not defined as LLVM type.");
      }
   }
   else
   {
      _classes[mem_ty->gQualifiedName()] = llvm_ty;
   }
}

void
Codegen::gen (ast::node::Node* root)
{
   assert (_st != NULL);
   _module = new llvm::Module("top", llvm::getGlobalContext());

   _classes["void*"] = llvm::Type::getInt32PtrTy(_module->getContext());

   _stack.push();

   // Codegen classes first...
   st::Type* ty = NULL;
   std::map<std::string, st::Type*> types = _st->gTypes();
   std::map<std::string, st::Type*>::iterator i;

   for (i = types.begin() ; i != types.end(); ++i)
   {
      ty = (*i).second;

      if (ty->isClassSymbol())
      {
         cgClass(static_cast<st::Class*>(ty));
      }
      else if (ty->isPrimitiveSymbol())
      {
         cgPrimitive(static_cast<st::Primitive*>(ty));
      }
   }

   cgMemoryFunctions();

   // ... then codegen functions by traversing files
   for (size_t i = 0; i < root->ChildCount(); ++i)
   {
      cgFile(static_cast<ast::node::File*>(root->getChild(i)), true);
   }

   // ... then codegen functions by traversing files
   for (size_t i = 0; i < root->ChildCount(); ++i)
   {
      cgFile(static_cast<ast::node::File*>(root->getChild(i)), false);
   }
}

llvm::Value*
Codegen::cgAmpersandExpr (ast::node::Node* node)
{
   assert(node != NULL);
   assert(node->isAmpersandNode());

   std::string amp_label = "Amp";


   llvm::Value* base_val = cgExpr(node->getChild(0));
   /*
   llvm::Type* dest_ty = _getLlvmTy(node->gExprType());
   llvm::Value* tmp = new llvm::AllocaInst(dest_ty, NULL, amp_label + ".Alloca", _cur_bb);
   builder.CreateStore(base_val, tmp);
   llvm::Value* load = new llvm::LoadInst(tmp, amp_label + ".Load", _cur_bb);
   */
   //llvm::LoadInst* load = new llvm::LoadInst(base_val, "", _cur_bb);
   llvm::GetElementPtrInst* gep = llvm::GetElementPtrInst::Create(base_val,
      llvm::ConstantInt::get(_module->getContext(), llvm::APInt(32, 0)),
      "dot", _cur_bb);

   return gep;
}

llvm::Value*
Codegen::cgBinaryExpr (ast::node::Node* node)
{
   llvm::Value* val = NULL;
   ast::node::Node* left_node = node->getChild(0);
   ast::node::Node* right_node = node->getChild(1);

   st::Type* ty = _getLowestCommonType(left_node->ExprType(),
      right_node->ExprType());

   llvm::Value* left_val = cgExprAndLoad(left_node, left_node->ExprType(), ty);
   llvm::Value* right_val = cgExprAndLoad(right_node, right_node->ExprType(), ty);

   switch (node->Kind())
   {
      case ast::node::Kind::OP_PLUS:
         val = llvm::BinaryOperator::Create(llvm::Instruction::Add, left_val,
            right_val, "", _cur_bb);
         break;

      case ast::node::Kind::OP_MINUS:
         val = llvm::BinaryOperator::Create(llvm::Instruction::Sub, left_val,
            right_val, "", _cur_bb);
         break;

      case ast::node::Kind::OP_MUL:
         val = llvm::BinaryOperator::Create(llvm::Instruction::Mul, left_val,
            right_val, "", _cur_bb);
         break;

      default:
         DEBUG_PRINTF("Unsupported arithmetic operation : %s\n",
            node->KindName().c_str());
         assert (false);
   }

   assert (val != NULL);
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
   assert (n != NULL);

   // Taking care of VALUE
   llvm::Value* val = cgExpr(n->ValueNode());//, NULL, NULL);
   assert (val != NULL);

   // Taking care of INDEX
   llvm::Value* index = cgExprAndLoad(n->IndexNode(),
      n->IndexNode()->ExprType(), _st->gCoreTypes().gIntTy());
   assert (index != NULL);

   std::vector<llvm::Value*> idx;
   idx.push_back(llvm::ConstantInt::get(_module->getContext(),
      llvm::APInt(32, 0)));
   idx.push_back(index);

   // Compute address
   llvm::GetElementPtrInst* inst = llvm::GetElementPtrInst::Create(
      val, idx, "", _cur_bb);
   inst->setIsInBounds(true);

   return inst;
}

llvm::Value*
Codegen::cgCallExpr (ast::node::Call* node)
{
   st::Func* func_sym = static_cast<st::Func*>(
      node->CallerNode()->BoundSymbol());
   std::vector<llvm::Value*> params;

   if (node->ParamsNode() != NULL)
   {
      ast::node::Node* cur_param_node = NULL;
      st::Var* cur_param = NULL;
      llvm::Value* param_value = NULL;
      for (size_t i = 0; i < node->ParamsNode()->ChildCount(); ++i)
      {
         cur_param_node = node->ParamsNode()->getChild(i);
         cur_param = func_sym->getParam(i);

         param_value = cgExprAndLoad(cur_param_node,
            static_cast<st::Type*>(cur_param_node->ExprType()),
            cur_param->Type());

         params.push_back(param_value);
      }
   }

   assert (_functions[_getCodegenFuncName(func_sym)] != NULL);

   if (params.size() > 0)
   {
      return llvm::CallInst::Create(_functions[_getCodegenFuncName(func_sym)],
         params, "call." + func_sym->gQualifiedName(), _cur_bb);
   }
   else
   {
      return llvm::CallInst::Create(_functions[_getCodegenFuncName(func_sym)],
         "call." + func_sym->gQualifiedName(), _cur_bb);
   }
}

void
Codegen::cgClass (st::Class* cls_sym)
{
   assert (cls_sym->isClassSymbol());

   std::vector<llvm::Type*> fields;
   if (cls_sym->_cur_field_index > 0)
   {
      std::vector<st::Field*> f = cls_sym->getOrderedFields();
      st::Field* field = NULL;
      for (size_t i=0; i < f.size(); ++i)
      {
         assert(f[i] != NULL);
         field = f[i];
         fields.push_back(_getLlvmTy(field->Type()));
      }
   }

   llvm::StructType* ty = llvm::StructType::create(_module->getContext(),
      cls_sym->gQualifiedName());
   if (ty->isOpaque())
   {
      ty->setBody(fields, false /* packed */);
   }

   addType (cls_sym, ty);
}

llvm::Value*
Codegen::cgCompOp (ast::node::BinaryOp* n)
{
   assert (n != NULL);
   assert (_cur_bb != NULL);

   ast::node::Node* left_val_node = n->LeftNode();
   ast::node::Node* right_val_node = n->RightNode();

   st::Type* expected_operand_ty = _getLowestCommonType(
      left_val_node->ExprType(), right_val_node->ExprType());

   llvm::Value* left_val = cgExprAndLoad(left_val_node,
      left_val_node->ExprType(), expected_operand_ty);
   llvm::Value* right_val = cgExprAndLoad(right_val_node,
      right_val_node->ExprType(), expected_operand_ty);

   llvm::ICmpInst::Predicate pred;

   switch (n->Kind())
   {
      case ast::node::Kind::OP_EQ_EQ: pred = llvm::ICmpInst::ICMP_EQ; break;
      case ast::node::Kind::OP_LT:    pred = llvm::ICmpInst::ICMP_SLT; break;
      case ast::node::Kind::OP_LTE:   pred = llvm::ICmpInst::ICMP_SLE; break;
      case ast::node::Kind::OP_GT:    pred = llvm::ICmpInst::ICMP_SGT; break;
      case ast::node::Kind::OP_GTE:   pred = llvm::ICmpInst::ICMP_SGE; break;

      default:
         DEBUG_PRINTF("Unsupported comparison operator (%s)\n", n->KindName().c_str());
         assert(false);

   }

   llvm::CmpInst* comp_inst = new llvm::ICmpInst(*_cur_bb, pred, left_val,
      right_val, "");

   return comp_inst;
}

llvm::Value*
Codegen::cgDotExpr (ast::node::Dot* node)
{
   assert(node->isDotNode());

   int field_index = static_cast<st::Field*>(node->BoundSymbol())->_field_index;

   std::vector<llvm::Value*> gep;
   gep.push_back(llvm::ConstantInt::get(_module->getContext(),
      llvm::APInt(32, 0)));
   gep.push_back(llvm::ConstantInt::get(_module->getContext(),
      llvm::APInt(32, field_index)));

   llvm::Value* left_node = cgExpr(node->LeftNode());
   assert (left_node != NULL);

   if (!node->LeftNode()->ExprType()->isPtrSymbol())
   {
      st::Type* base_mem_ty = static_cast<st::Type*>(st::Util::lookupSymbol(
         node->LeftNode()->ExprType()->_parent,
         node->LeftNode()->ExprType()->Name() + "*"));

      llvm::Type* base_ty = _getLlvmTy(base_mem_ty);
      assert(base_ty != NULL);

      llvm::AllocaInst* tmp = new llvm::AllocaInst(base_ty, NULL, "dot",
         _cur_bb);
      assert(tmp != NULL);

      llvm::StoreInst* store = new llvm::StoreInst(left_node, tmp, _cur_bb);
      assert(store != NULL);

      left_node = new llvm::LoadInst(tmp, "dot", _cur_bb);
   }
   else
   {
      left_node = new llvm::LoadInst(left_node, "dot", _cur_bb);
   }
   assert (left_node != NULL);

   llvm::Value* gep_inst = llvm::GetElementPtrInst::Create(left_node, gep,
      "dot", _cur_bb);
   assert(gep_inst != NULL);

   //llvm::LoadInst* load_inst = new llvm::LoadInst(gep_inst, "dot", _cur_bb);
   //assert(load_inst != NULL);

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

      case ast::node::Kind::OP_EQ_EQ:
      case ast::node::Kind::OP_LT:
      case ast::node::Kind::OP_LTE:
      case ast::node::Kind::OP_GT:
      case ast::node::Kind::OP_GTE:
         res = cgCompOp(static_cast<ast::node::BinaryOp*>(node));
         break;

      case ast::node::Kind::IF:
         cgIfStatement(static_cast<ast::node::If*>(node));
         break;

      case ast::node::Kind::FINAL_ID:
         res = cgFinalIdExpr(static_cast<ast::node::FinalId*>(node));
         break;

      case ast::node::Kind::NEW:
         res = cgNewExpr(static_cast<ast::node::New*>(node));
         break;

      case ast::node::Kind::NUMBER:
         res = cgNumberExpr(static_cast<ast::node::Number*>(node));
         assert (res != NULL);
         break;

      case ast::node::Kind::OP_PLUS:
      case ast::node::Kind::OP_MINUS:
      case ast::node::Kind::OP_MUL:
         res = cgBinaryExpr(node);
         break;

      case ast::node::Kind::RETURN:
         cgReturnStatement (node);
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
Codegen::cgExprAndLoad (ast::node::Node* node, st::Symbol* src_ty, st::Symbol* dst_ty)
{
   assert(node != NULL);

   llvm::Value* val = cgExpr(node);
   assert(val != NULL);

   bool must_load = false;

   if (src_ty != NULL && dst_ty != NULL)
   {
      if (!src_ty->isPtrSymbol() && dst_ty->isPtrSymbol())
      {
         must_load = true;
      }
      else if (src_ty->isPtrSymbol() && !dst_ty->isPtrSymbol())
      {
         st::Ptr* src_ptr = static_cast<st::Ptr*>(src_ty);
         st::Ptr* dst_ptr = static_cast<st::Ptr*>(dst_ty);

         if (src_ptr->IndirectionLevel() > dst_ptr->IndirectionLevel())
         {
            must_load = true;
         }
      }
   }

   if (!must_load)
   {
      switch (node->Kind())
      {
         case ast::node::Kind::FINAL_ID:
         case ast::node::Kind::BRACKET_OP:
            must_load = true;
            break;
      }
   }

   if (must_load)
   {
      llvm::LoadInst* load_inst = new llvm::LoadInst(val, "", _cur_bb);
      assert (load_inst != NULL);
      return load_inst;
   }

   return val;
}

void
Codegen::cgFile (ast::node::File* file_node, bool cg_func_def)
{
   ast::node::Node* node = NULL;

   if (cg_func_def)
   {
      // Codegen function definitions
      for (size_t i = 0 ; i < file_node->ChildCount(); ++i)
      {
         node = file_node->getChild(i);
         if (node->isFuncNode())
         {
            cgFunctionDef(static_cast<ast::node::Func*>(node));
         }
      }
   }
   else
   {
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
}

llvm::Value*
Codegen::cgFinalIdExpr (ast::node::Text* node)
{
   llvm::Value* ty = _stack.get(node->gValue());
   return ty;
}

void
Codegen::cgFunctionBody (ast::node::Func* func_node)
{
   assert(func_node->isFuncNode());

   // Don't try to generate body for a virtual function
   if (func_node->BodyNode() != NULL)
   {
      st::Func* func_sym = static_cast<st::Func*>(func_node->BoundSymbol());
      assert (func_sym != NULL);

      llvm::Function* func = _functions[_getCodegenFuncName(func_sym)];
      assert (func != NULL);

      llvm::BasicBlock& block = func->getEntryBlock();
      _cur_bb = &block;
      _cur_func = func;

      _stack.push();

      // Set parameters
      // We set this here instead of cgFunctionDef because we can append the
      // parameters to the stack of the body of the function.
      st::Var* func_param = NULL;
      llvm::Argument* arg = NULL;
      for (size_t i = 0; i < func_sym->ParamCount(); ++i)
      {
         func_param = func_sym->_params[i];
         arg = new llvm::Argument(_getLlvmTy(func_param->Type()),
            func_param->Name(), func);
         _stack.set(func_param->Name(), arg);
      }

      cgBlock(static_cast<ast::node::Block*>(func_node->BodyNode()));
      _stack.pop();

      if (func_sym->ReturnType() == _st->_core_types.gVoidTy())
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
   st::Func* func_sym = static_cast<st::Func*>(func_node->BoundSymbol());
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
   if (func_sym->Metadata()->has("external"))
   {
      st::Var* func_param = NULL;
      for (size_t i = 0; i < func_sym->ParamCount(); ++i)
      {
         func_param = func_sym->_params[i];
         params.push_back(_getLlvmTy(func_param->Type()));
      }
   }

   llvm::FunctionType* func_ty = llvm::FunctionType::get(
      _getFuncReturnTy(func_node), params, false);

   llvm::GlobalValue::LinkageTypes func_link;
   if (func_sym->Metadata()->has("external"))
   {
      func_link = llvm::GlobalValue::ExternalLinkage;
   }
   else
   {
      func_link = llvm::GlobalValue::ExternalLinkage;
   }

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
}

void
Codegen::cgIfStatement (ast::node::If* node)
{
   llvm::BasicBlock* cur_bb = _cur_bb;
   bool if_is_last_child = node->Parent()->isLastChild(node);

   // After if
   llvm::BasicBlock* after_block = NULL;
   if (!if_is_last_child)
   {
      after_block = llvm::BasicBlock::Create(
         llvm::getGlobalContext(), "after_cont", _cur_func);
   }

   // TRUE block
   llvm::BasicBlock* true_block = llvm::BasicBlock::Create(
      llvm::getGlobalContext(), "if_true", _cur_func);
   _cur_bb = true_block;
   assert(node->IfBlockNode() != NULL);
   cgBlock(static_cast<ast::node::Block*>(node->IfBlockNode()));
   if (!if_is_last_child)
   {
      true_block->getInstList().push_back(llvm::BranchInst::Create(after_block));
   }

   // FALSE block
   llvm::BasicBlock* false_block = NULL;
   if (node->ElseBlockNode() != NULL)
   {
      false_block = llvm::BasicBlock::Create(llvm::getGlobalContext(),
         "if_false", _cur_func);
      _cur_bb = false_block;
      cgBlock(static_cast<ast::node::Block*>(node->ElseBlockNode()));
      if (!if_is_last_child)
      {
         false_block->getInstList().push_back(
            llvm::BranchInst::Create(after_block));
      }
   }

   // BRANCH
   assert (node->ConditionNode() != NULL);
   _cur_bb = cur_bb;
   llvm::Value* cond = cgExprAndLoad(node->ConditionNode(), node->ExprType(),
      node->ConditionNode()->ExprType());

   // IF/ELSE
   if (node->hasElseBlockNode())
   {
      llvm::BranchInst::Create(true_block, false_block, cond, cur_bb);
   }
   // Only If
   else
   {
      llvm::BranchInst::Create(true_block, after_block, cond, cur_bb);
   }

   _cur_bb = after_block;
}

void
Codegen::cgMemoryFunctions ()
{
   // MALLOC
   std::vector<llvm::Type*> malloc_tys;
   malloc_tys.push_back(llvm::Type::getInt32Ty(_module->getContext()));

   llvm::FunctionType* malloc_ty = llvm::FunctionType::get(
      _getLlvmTy("void*"),
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
   // Create the call
   llvm::Value* malloc_call = llvm::CallInst::Create(_functions["malloc"],
      llvm::ConstantInt::get(_classes["int"], 2), "", _cur_bb);
   assert(malloc_call != NULL);

   // Cast the return pointer to the appropriate pointer type
   assert (_getLlvmTy(node->ExprType()) != NULL);
   llvm::Value* ret = new llvm::BitCastInst(malloc_call, _getLlvmTy(
      node->ExprType()), "new_cast", _cur_bb);

   assert (ret != NULL);
   return ret;
}

llvm::Value*
Codegen::cgNumberExpr (ast::node::Number* node)
{
   llvm::Value* val = NULL;

   switch (node->_format)
   {
      case 'c':
         val = llvm::ConstantInt::get(llvm::getGlobalContext(),
            llvm::APInt(sizeof(char) * 8, node->getChar(), false));
         break;

      case 's':
         val = llvm::ConstantInt::get(llvm::getGlobalContext(),
            llvm::APInt(sizeof(short) * 8, node->getShort(), false));
         break;

      case 'i':
         val = llvm::ConstantInt::get(llvm::getGlobalContext(),
            llvm::APInt(sizeof(int) * 8, node->getInt(), false));
         break;

      case 'l':
         val = llvm::ConstantInt::get(llvm::getGlobalContext(),
            llvm::APInt(sizeof(long) * 8, node->getLong(), false));
         break;

      default:
         assert (false && "Invalid constant type.");
   }

   assert (val != NULL);

   return val;
}

void
Codegen::cgPrimitive (st::Primitive* prim)
{
   assert(prim != NULL);

   llvm::StructType* ty = llvm::StructType::create(_module->getContext(),
      prim->gQualifiedName());
   assert(ty != NULL);
   addType(prim, ty);
}

void
Codegen::cgReturnStatement (ast::node::Node* node)
{
   assert(_cur_bb != NULL);
   assert(node != NULL);
   assert(node->isReturnNode());
   assert(node->getChild(0) != NULL);

   // FIXME Not null
   llvm::Value* val = cgExprAndLoad(node->getChild(0),
      node->getChild(0)->ExprType(), node->ExprType());
   assert(val != NULL);

   llvm::ReturnInst::Create(_module->getContext(), val, _cur_bb);
}

void
Codegen::cgVarAssignStatement (ast::node::VarAssign* node)
{
   llvm::Value* left_val = cgExpr(node->NameNode());
   llvm::Value* right_val = cgExpr(node->ValueNode());

   if (node->ValueNode()->isFinalIdNode())
   {
      right_val = new llvm::LoadInst(right_val, "", _cur_bb);
   }

   new llvm::StoreInst(right_val, left_val, _cur_bb);
}

void
Codegen::cgVarDeclStatement (ast::node::VarDecl* node)
{
   assert(node != NULL);
   assert(node->isVarDeclNode());
   assert(node->hasExprType());

   llvm::Type* var_ty = NULL;
   llvm::Value* var_len = NULL;

   if (node->TypeNode()->isArrayNode())
   {
      ast::node::Array* arr = static_cast<ast::node::Array*>(node->TypeNode());
      assert (arr->LengthNode() != NULL);

      var_len = cgExpr(arr->LengthNode());
      var_ty = llvm::ArrayType::get(_getLlvmTy(arr->TypeNode()->ExprType()),
         static_cast<ast::node::Number*>(arr->LengthNode())->getInt());
   }
   else
   {
      var_ty = _getLlvmTy(node->ExprType());
   }

   assert(var_ty != NULL);

   llvm::Value* var = new llvm::AllocaInst(var_ty, var_len,
      node->Name(), _cur_bb);

   if (node->ValueNode() != NULL)
   {
      llvm::Value* var_val = cgExprAndLoad(node->ValueNode(),
         node->ValueNode()->ExprType(), node->TypeNode()->ExprType());
      assert (var_val != NULL);
      new llvm::StoreInst(var_val, var, _cur_bb);
   }

   //var = new llvm::LoadInst(var, "", _cur_bb);

   _stack.set(node->Name(), var);
}

void
Codegen::cgWhileStatement (ast::node::While* n)
{
   assert (n != NULL);

   llvm::BasicBlock* origin_block = _cur_bb;

   llvm::BasicBlock* while_head = llvm::BasicBlock::Create(
      llvm::getGlobalContext(), "while_head", _cur_func);
   _cur_bb = while_head;
   llvm::Value* cond = cgExpr(n->ConditionNode());
   assert(cond != NULL);

   llvm::BasicBlock* while_body = llvm::BasicBlock::Create(
      llvm::getGlobalContext(), "while_body", _cur_func);
   assert (while_body != NULL);
   _cur_bb = while_body;
   cgBlock(static_cast<ast::node::Block*>(n->BodyNode()));
   while_body->getInstList().push_back(llvm::BranchInst::Create(while_head));

   llvm::BasicBlock* while_after = llvm::BasicBlock::Create(
      llvm::getGlobalContext(), "while_after", _cur_func);
   assert (while_after != NULL);
   _cur_bb = while_after;

   origin_block->getInstList().push_back(llvm::BranchInst::Create(while_head));
   llvm::BranchInst::Create(while_body, while_after, cond, while_head);
}

std::string
Codegen::getLlvmByteCode ()
{
   std::string bc;
   llvm::raw_string_ostream stream(bc);
   _module->print(stream, NULL);
   return bc;
}

} } }
