#include "mem/codegen/llvm/Codegen.hpp"


namespace mem { namespace codegen { namespace llvm_ {


llvm::Type*
Codegen::_getLlvmIntTy (size_t size)
{
   return llvm::Type::getIntNTy(_module->getContext(), size * 8);
   /*
   switch (size)
   {
      case 1:
         return llvm::Type::getInt16Ty(_module->getContext());
      case 2:
         return llvm::Type::getInt32Ty(_module->getContext());
      case 4:
         return llvm::Type::getInt32Ty(_module->getContext());
      default:
         printf("Undefined type size : %d\n", size);
         assert(false);
   }
   return NULL;
   */
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
         _classes[mem_ty->gQualifiedName()] = _getLlvmIntTy(sizeof(bool));
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

   // Codegen classes first...
   st::Type* ty = NULL;
   std::map<std::string, st::Type*> types = _st->gTypes();
   std::map<std::string, st::Type*>::iterator i;

   for (i = types.begin() ; i != types.end(); ++i)
   {
      ty = (*i).second;

      if (ty->is(st::CLASS) || ty->is(st::PRIMITIVE))
      {
         cgClass(static_cast<st::Class*>(ty));
      }
   }

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

   assert (_functions[func_sym->gQualifiedName()] != NULL);

   if (params.size() > 0)
   {
      return builder.CreateCall(_functions[func_sym->gQualifiedName()]);
   }
   else
   {
      return builder.CreateCall(_functions[func_sym->gQualifiedName()], params);
   }
}

void
Codegen::cgClass (st::Class* cls_sym)
{
   std::vector<llvm::Type*> fields;
   //fields.push_back(llvm::IntegerType::get(_module->getContext(), 8));

   llvm::StructType* ty = llvm::StructType::create(_module->getContext(),
      cls_sym->gQualifiedName());
   if (ty->isOpaque())
   {
      ty->setBody(fields, false /* packed */);
   }
   addType (cls_sym, ty);
}

llvm::Value*
Codegen::cgExpr (ast::node::Node* node)
{
   llvm::Value* res = NULL;

   switch (node->gType())
   {
      case MEM_NODE_PLUS:
         res = cgBinaryExpr(node);
         break;
      case MEM_NODE_NUMBER:
         res = cgNumberExpr(static_cast<ast::node::Number*>(node));
         break;
      case MEM_NODE_VARIABLE_DECLARATION:
         cgVarDecl (static_cast<ast::node::VarDecl*>(node));
         break;
      case MEM_NODE_FINAL_ID:
         res = cgFinalId (static_cast<ast::node::Text*>(node));
         break;
      case MEM_NODE_CALL:
         res = cgCallExpr (static_cast<ast::node::Call*>(node));
         break;
      default:
         printf("Unsupported node type %s\n", ast::node::Node::get_type_name(node->gType()));
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
Codegen::cgFinalId (ast::node::Text* node)
{
   llvm::LoadInst* inst = builder.CreateLoad(_block_vars[node->gValue()], node->gValue());

   return inst; //_block_vars[node->gValue()]; //inst->getPointerOperand();
}

void
Codegen::cgFunctionBody (ast::node::Func* func_node)
{
   assert(func_node->isFuncNode());
   _block_vars.clear();

   st::Func* func_sym = static_cast<st::Func*>(func_node->gBoundSymbol());
   assert (func_sym != NULL);
   llvm::Function* func = _functions[func_sym->gQualifiedName()];
   assert (func != NULL);

   llvm::BasicBlock& block = func->getEntryBlock();

   builder.SetInsertPoint(&block);

   ast::node::Node* cur_node = func_node->gBodyNode()->_first_child;
   while (cur_node != NULL)
   {
      cgExpr(cur_node);
      cur_node = cur_node->_next;
   }
   if (func_sym->gReturnType() == _st->_core_types.gVoidTy())
   {
      builder.CreateRetVoid();
   }
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
      func_name = func_sym->gQualifiedNameCstr();
   }

   llvm::FunctionType* func_ty = llvm::FunctionType::get(
      _getFuncReturnTy(func_node),
      _getFuncParamsTy(func_sym),
      /*isVarArg=*/false);

   llvm::Function* func = llvm::Function::Create(func_ty,
      llvm::GlobalValue::ExternalLinkage,
      func_name,
      _module);

   llvm::BasicBlock* block = llvm::BasicBlock::Create(llvm::getGlobalContext(),
      "entry", func);

   func->getEntryBlock();

   _functions[func_sym->gQualifiedName()] = func;
}

llvm::Value*
Codegen::cgNumberExpr (ast::node::Number* node)
{
   llvm::Value* val = NULL;
   switch (node->_format)
   {
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
Codegen::cgVarDecl (ast::node::VarDecl* node)
{
   _block_vars[node->gName()] = builder.CreateAlloca(
      _classes[node->gExprType()->gName()],
      cgExpr(node->gValueNode()),
      node->gName());
}

std::vector<llvm::Type*>
Codegen::_getFuncParamsTy (st::Func* func)
{
   std::vector<llvm::Type*> params_ty;
   llvm::Type* cur_ty = NULL;

   for (size_t i = 0; i < func->gParamCount(); ++i)
   {
      cur_ty = this->_classes[func->getParam(i)->gType()->gQualifiedName()];
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
      ty = this->_classes[func->gExprType()->gQualifiedName()];
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

std::string
Codegen::getLlvmByteCode ()
{
   std::string bc;
   llvm::raw_string_ostream stream(bc);
   _module->print(stream, NULL);
   return bc;
}

} } }
