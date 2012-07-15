#include "mem/codegen/llvm/Codegen.hpp"


namespace mem { namespace codegen { namespace llvm_ {


std::string
Codegen::_getCodegenFuncName (st::Func* func)
{
   std::string name = "";

   if (func->gMd()->has("external"))
   {
      name = func->gName();
   }
   else
   {
      name = func->gQualifiedName();
   }

   return name;
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
   // Type is found
   if (_classes.find(mem_ty->gQualifiedName()) != _classes.end())
   {
      return _classes[mem_ty->gQualifiedName()];
   }
   // Type is NOT found, so ?
   else
   {
      // Create the pointer type
      if (mem_ty->isPtrSymbol())
      {
         llvm::Type* base_ty = _getLlvmTy(
            static_cast<mem::st::Ptr*>(mem_ty)->gBaseType());
         if (base_ty != NULL)
         {
            // TODO What is the second parameter (AddressSpace) ?
             return llvm::PointerType::get(base_ty, 0);
         }
      }
   }
   return NULL;
}

std::vector<llvm::Type*>
Codegen::_getFuncParamsTy (st::Func* func)
{
   std::vector<llvm::Type*> params_ty;
   llvm::Type* cur_ty = NULL;

   for (size_t i = 0; i < func->gParamCount(); ++i)
   {
      cur_ty = _getLlvmTy(func->getParam(i)->gType());
      assert (cur_ty != NULL);
      params_ty.push_back(cur_ty);
   }

   return params_ty;
}

llvm::Type*
Codegen::_getFuncReturnTy (ast::node::Func* func)
{
   llvm::Type* ty = NULL;

   if (func->gReturnTypeNode() != NULL)
   {
      ty = _classes[func->gExprType()->gQualifiedName()];
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
   if (mem_ty->is(st::PRIMITIVE))
   {
      // TODO This is very ugly...
      if (mem_ty == _st->_core_types.gIntTy())
      {
         _classes[mem_ty->gQualifiedName()] = _getLlvmIntTy(sizeof(int));
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
   for (size_t i = 0; i < root->gChildCount(); ++i)
   {
      cgFile(static_cast<ast::node::File*>(root->getChild(i)), true);
   }

   // ... then codegen functions by traversing files
   for (size_t i = 0; i < root->gChildCount(); ++i)
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
   /*
   llvm::GetElementPtrInst* gep = llvm::GetElementPtrInst::Create(load,
      llvm::ConstantInt::get(_module->getContext(), llvm::APInt(32, 0)),
      "dot", _cur_bb);
   */

   return base_val;
}

llvm::Value*
Codegen::cgBinaryExpr (ast::node::Node* node)
{
   llvm::Value* val = NULL;
   llvm::Value* left_val = cgExpr(node->getChild(0));
   llvm::Value* right_val = cgExpr(node->getChild(1));

   switch (node->gType())
   {
      case MEM_NODE_PLUS:
         val = builder.CreateAdd(left_val, right_val);
         break;

      default:
         printf("Unsupported arithmetic operation\n");
         assert (false);
   }

   assert (val != NULL);
   return val;
}

void
Codegen::cgBlock (ast::node::Block* block)
{
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
Codegen::cgCallExpr (ast::node::Call* node)
{
   st::Func* func_sym = static_cast<st::Func*>(node->gCallerNode()->gBoundSymbol());
   std::vector<llvm::Value*> params;

   if (node->gParamsNode() != NULL)
   {
      ast::node::Node* cur_param = node->gParamsNode()->_first_child;
      while (cur_param != NULL)
      {
         params.push_back(cgExpr(cur_param));
         cur_param = cur_param->_next;
      }
   }

   assert (_functions[_getCodegenFuncName(func_sym)] != NULL);

   if (params.size() > 0)
   {
      return llvm::CallInst::Create(_functions[_getCodegenFuncName(func_sym)],
         params, "", _cur_bb);
   }
   else
   {
      return llvm::CallInst::Create(_functions[_getCodegenFuncName(func_sym)],
         "", _cur_bb);
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
         fields.push_back(_getLlvmTy(field->gType()));
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
Codegen::cgDotExpr (ast::node::Node* node)
{
   assert(node->isDotNode());

   int field_index = static_cast<st::Field*>(node->gBoundSymbol())->_field_index;

   std::vector<llvm::Value*> gep;
   gep.push_back(llvm::ConstantInt::get(_module->getContext(), llvm::APInt(32, 0)));
   gep.push_back(llvm::ConstantInt::get(_module->getContext(), llvm::APInt(32, field_index)));

   llvm::Value* left_node = cgExpr(node->getChild(0));
   assert (left_node != NULL);

   if (!node->getChild(0)->gExprType()->isPtrSymbol())
   {
      st::Type* base_mem_ty = static_cast<st::Type*>(st::Util::lookupSymbol(
         node->getChild(0)->gExprType()->_parent,
         node->getChild(0)->gExprType()->gName() + "*"));

      llvm::Type* base_ty = _getLlvmTy(base_mem_ty);
      assert(base_ty != NULL);

      llvm::AllocaInst* tmp = new llvm::AllocaInst(base_ty, NULL, "dot", _cur_bb);
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

   llvm::Value* gep_inst = llvm::GetElementPtrInst::Create(left_node, gep, "dot",
      _cur_bb);
   assert(gep_inst != NULL);

   llvm::LoadInst* load_inst = new llvm::LoadInst(gep_inst, "dot", _cur_bb);
   assert(load_inst != NULL);

   return load_inst;
}

llvm::Value*
Codegen::cgExpr (ast::node::Node* node)
{
   assert (node != NULL);
   llvm::Value* res = NULL;

   switch (node->gType())
   {
      case MEM_NODE_AMPERSAND:
         res = cgAmpersandExpr (node);
         break;

      case MEM_NODE_CALL:
         res = cgCallExpr (static_cast<ast::node::Call*>(node));
         break;

      case MEM_NODE_DOT:
         res = cgDotExpr (node);
         break;

      case MEM_NODE_IF:
         cgIfStatement (static_cast<ast::node::If*>(node));
         break;

      case MEM_NODE_FINAL_ID:
         res = cgFinalIdExpr (static_cast<ast::node::Text*>(node));
         break;

      case MEM_NODE_NEW:
         res = cgNewExpr (static_cast<ast::node::New*>(node));
         break;

      case MEM_NODE_NUMBER:
         res = cgNumberExpr(static_cast<ast::node::Number*>(node));
         assert (res != NULL);
         break;

      case MEM_NODE_PLUS:
         res = cgBinaryExpr(node);
         break;

      case MEM_NODE_RETURN:
         cgReturnStatement (node);
         break;

      case MEM_NODE_VARIABLE_ASSIGNMENT:
         cgVarAssignStatement (static_cast<ast::node::VarAssign*>(node));
         break;

      case MEM_NODE_VARIABLE_DECLARATION:
         cgVarDeclStatement (static_cast<ast::node::VarDecl*>(node));
         break;

      default:
         printf("Unsupported node type %s\n",
            ast::node::Node::get_type_name(node->gType()));
         assert(false);
   }

   return res;
}

void
Codegen::cgFile (ast::node::File* file_node, bool cg_func_def)
{
   ast::node::Node* node = NULL;

   if (cg_func_def)
   {
      // Codegen function definitions
      for (size_t i = 0 ; i < file_node->gChildCount(); ++i)
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
      for (size_t i = 0 ; i < file_node->gChildCount(); ++i)
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
   if (func_node->gBodyNode() != NULL)
   {

      st::Func* func_sym = static_cast<st::Func*>(func_node->gBoundSymbol());
      assert (func_sym != NULL);

      llvm::Function* func = _functions[_getCodegenFuncName(func_sym)];
      assert (func != NULL);

      llvm::BasicBlock& block = func->getEntryBlock();
      _cur_bb = &block;

      builder.SetInsertPoint(&block);

      cgBlock(static_cast<ast::node::Block*>(func_node->gBodyNode()));

      if (func_sym->gReturnType() == _st->_core_types.gVoidTy())
      {
         builder.CreateRetVoid();
      }

   }

   _cur_bb = NULL;
}

void
Codegen::cgFunctionDef (ast::node::Func* func_node)
{

   st::Func* func_sym = static_cast<st::Func*>(func_node->gBoundSymbol());
   std::vector<llvm::Type*> func_ty_args;
   std::string func_name;

   if (func_sym->gIsEntryPoint())
   {
      func_name = "main";
   }
   else
   {
      func_name = _getCodegenFuncName(func_sym);
   }

   llvm::FunctionType* func_ty = llvm::FunctionType::get(
      _getFuncReturnTy(func_node),
      _getFuncParamsTy(func_sym),
      /*isVarArg=*/false);

   llvm::GlobalValue::LinkageTypes func_link;
   if (func_sym->gMd()->has("external"))
   {
      func_link = llvm::GlobalValue::DLLImportLinkage;
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
   if (func_node->gBodyNode() != NULL)
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

   // After if
   llvm::BasicBlock* after_block = llvm::BasicBlock::Create(
      llvm::getGlobalContext(), "after_cont", _cur_func);

   // TRUE block
   llvm::BasicBlock* true_block = llvm::BasicBlock::Create(
      llvm::getGlobalContext(), "if_true", _cur_func);
   _cur_bb = true_block;
   cgBlock(static_cast<ast::node::Block*>(node->gIfBlockNode()));
   true_block->getInstList().push_back(llvm::BranchInst::Create(after_block));

   // FALSE block
   llvm::BasicBlock* false_block = llvm::BasicBlock::Create(
      llvm::getGlobalContext(), "if_false", _cur_func);
   _cur_bb = false_block;
   cgBlock(static_cast<ast::node::Block*>(node->gElseBlockNode()));
   false_block->getInstList().push_back(llvm::BranchInst::Create(after_block));

   // BRANCH
   llvm::Value* cond = cgExpr(node->gConditionNode());
   llvm::LoadInst* load = new llvm::LoadInst(cond, "ifcond", false, cur_bb);

   if (node->hasElseBlockNode())
   {
      llvm::BranchInst* br = llvm::BranchInst::Create(true_block, false_block,
         load, cur_bb);
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
      llvm::GlobalValue::DLLImportLinkage,
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
   assert (_getLlvmTy(node->gExprType()) != NULL);
   llvm::Value* ret = new llvm::BitCastInst(malloc_call, _getLlvmTy(
      node->gExprType()), "new_cast", _cur_bb);

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
   addType (prim, ty);
}

void
Codegen::cgReturnStatement (ast::node::Node* node)
{
   assert(node != NULL);
   assert(node->isReturnNode());
   assert(node->getChild(0) != NULL);

   llvm::Value* val = cgExpr(node->getChild(0));
   assert(val != NULL);

   llvm::ReturnInst::Create(_module->getContext(), val, _cur_bb);
}

void
Codegen::cgVarAssignStatement (ast::node::VarAssign* node)
{
   std::string var_name = node->gNameNode()->gBoundSymbol()->gName();
   llvm::Value* val = cgExpr(node->gValueNode());
   new llvm::StoreInst(val, _stack.get(var_name), _cur_bb);
}

void
Codegen::cgVarDeclStatement (ast::node::VarDecl* node)
{
   assert(node != NULL);
   assert(node->isVarDeclNode());
   assert(node->gExprType() != NULL);

   llvm::Value* var = new llvm::AllocaInst(_getLlvmTy(node->gExprType()), NULL,
      node->gName(), _cur_bb);

   if (node->gValueNode() != NULL)
   {
      llvm::Value* var_val = cgExpr(node->gValueNode());
      assert (var_val != NULL);
      new llvm::StoreInst(var_val, var, _cur_bb);
   }

   //var = new llvm::LoadInst(var, "", _cur_bb);

   _stack.set(node->gName(), var);
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
