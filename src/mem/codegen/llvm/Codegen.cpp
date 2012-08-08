#include "mem/codegen/llvm/Codegen.hpp"


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

void
Codegen::_dumpTypes ()
{
   std::map<st::Type*, llvm::Type*>::iterator i;
   for (i = _type_bindings.begin() ; i != _type_bindings.end(); ++i)
   {
      printf("`%s'\n", (*i).first->gQualifiedNameCstr());
   }
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
      common_ty = static_cast<st::Type*>(left_ty);
   }
   else if (!right_ty->isPointerType())
   {
      common_ty = static_cast<st::Type*>(right_ty);
   }
   // Both operands are pointers
   else
   {
      common_ty = st::util::getPointerBaseType(static_cast<st::PointerType*>(left_ty));
   }

   return common_ty;
}

llvm::Type*
Codegen::_getLlvmIntTy (size_t size)
{
   return llvm::Type::getIntNTy(_module->getContext(), size * 8);
}

llvm::Type*
Codegen::_codegenArrayType (st::ArrayType* t)
{
   DEBUG_REQUIRE (t != NULL);

   llvm::Type* lty = NULL;
   llvm::Type* item_lty = _getLlvmTy(t->ItemType());

   if (t->hasLength())
   {
      lty = llvm::ArrayType::get(item_lty, t->ArrayLength());
   }
   else
   {
      lty = llvm::PointerType::get(item_lty, 0);
   }

   addType(t, lty);

   DEBUG_ENSURE (lty != NULL);
   return lty;
}

llvm::StructType*
Codegen::_codegenClassType (st::Class* cls_sym)
{
   DEBUG_REQUIRE (cls_sym->isClassType());
   DEBUG_REQUIRE (_type_bindings.find(cls_sym) != _type_bindings.end());

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

   return ty;
}

llvm::FunctionType*
Codegen::_codegenFunctionType (st::FunctionType* t)
{
   std::vector<llvm::Type*> args;
   for (size_t i = 0; i < t->ArgumentCount(); ++i)
   {
      args.push_back(_getLlvmTy(t->getArgument(i)));
   }

   return llvm::FunctionType::get(_getLlvmTy(t->ReturnType()), args, false);
}

llvm::PointerType*
Codegen::_codegenPointerType (st::PointerType* t)
{
   return llvm::PointerType::get(_getLlvmTy(t->PointedType()), 0);
}

llvm::Type*
Codegen::_codegenPrimitiveType (st::PrimitiveType* t)
{
   if (_st->isVoidType(t))
   {
      return llvm::Type::getVoidTy(_module->getContext());
   }
   return NULL;
}

llvm::StructType*
Codegen::_codegenTupleType (st::TupleType* t)
{
   DEBUG_REQUIRE (t != NULL);
   DEBUG_REQUIRE (_type_bindings.find(t) != _type_bindings.end());

   std::vector<llvm::Type*> ltys;
   for (size_t i=0; i < t->Subtypes().size(); ++i)
   {
      ltys.push_back(_getLlvmTy(t->Subtypes()[i]));
   }

   llvm::StructType* tuple_lty = llvm::StructType::create(ltys, "tuple");
   addType(t, tuple_lty);
   return tuple_lty;
}

llvm::Type*
Codegen::_codegenType (st::Type* mem_ty)
{
   switch (mem_ty->Kind())
   {
      case st::ARRAY:
         return _codegenArrayType(static_cast<st::ArrayType*>(mem_ty));

      case st::CLASS:
         return _codegenClassType(static_cast<st::Class*>(mem_ty));

      case st::FUNCTION_TYPE:
         return _codegenFunctionType(static_cast<st::FunctionType*>(mem_ty));

      case st::TUPLE_TYPE:
         return _codegenTupleType(static_cast<st::TupleType*>(mem_ty));

      case st::INT_TYPE:
         return _getLlvmIntTy(mem_ty->ByteSize());

      case st::POINTER:
         return _codegenPointerType(static_cast<st::PointerType*>(mem_ty));

      case st::PRIMITIVE_TYPE:
         return _codegenPrimitiveType(static_cast<st::PrimitiveType*>(mem_ty));

      default:
         DEBUG_PRINTF("Unsupported mem type {Kind: %d, Name: %s}\n",
            mem_ty->Kind(), mem_ty->gQualifiedNameCstr());
         assert(false);
   }

   return NULL;
}

llvm::Type*
Codegen::_getLlvmTy (st::Type* mem_ty)
{
   assert (mem_ty != NULL);
   llvm::Type* ty = NULL;

   // Type is found
   if (_type_bindings.find(mem_ty) != _type_bindings.end())
   {
      ty = _type_bindings[mem_ty];
      assert(ty != NULL);
   }
   // Type is not already codegened, do it
   else
   {
      ty = _codegenType (mem_ty);
   }
      /*
      if (mem_ty->isPointerType())
      {
         st::PointerType* ptr_ty = static_cast<st::PointerType*>(mem_ty);

         // Create the pointer type
         llvm::Type* base_ty = _getLlvmTy(ptr_ty->PointedType());
         if (base_ty != NULL)
         {
            if (ptr_ty->PointedType()->isArrayType() && !static_cast<st::ArrayType*>(ptr_ty->PointedType())->hasLength())
            {
               ty = llvm::PointerType::get(_getLlvmTy(static_cast<st::ArrayType*>(ptr_ty->PointedType())->ItemType()), 0);
            }
            else
            {
               // TODO What is the second parameter (AddressSpace) ?
                ty = llvm::PointerType::get(base_ty, 0);
                _classes[mem_ty->gQualifiedName()] = ty;
            }
         }
      }
      else if (mem_ty->isArrayType())
      {
         st::ArrayType* arr = static_cast<mem::st::ArrayType*>(mem_ty);
         llvm::Type* base_ty = _getLlvmTy(arr->ItemType());
         if (base_ty != NULL)
         {
            if (arr->hasLength())
            {
               ty = llvm::ArrayType::get(base_ty, arr->ArrayLength());
               _classes[mem_ty->gQualifiedName()] = ty;
            }
            else
            {
               ty = llvm::PointerType::get(base_ty, 0);
               _classes[mem_ty->gQualifiedName()] = ty;
            }
         }
      }
      */

   IF_DEBUG
   {
      if (ty == NULL)
      {
         DEBUG_PRINTF("Type symbol `%s' {Kind: %d} has no associated LLVM type\n",
            mem_ty->gQualifiedNameCstr(), mem_ty->Kind());
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
      ty = _getLlvmTy(func->ExprType());
   }
   else
   {
      ty = _getVoidTy();
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

llvm::Type*
Codegen::_getVoidTy ()
{
   return llvm::Type::getVoidTy(_module->getContext());
}

bool
Codegen::_mustBeLoaded (ast::node::Node* node)
{
   switch (node->Kind())
   {
      case ast::node::Kind::FINAL_ID:
         if (node->BoundSymbol()->isFuncSymbol())
         {
            DEBUG_PRINT("Don't load functor\n");
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
   return false;

}
void
Codegen::addType (st::Type* mem_ty, llvm::Type* llvm_ty)
{
   if (mem_ty->isAnyPrimitiveType())
   {
      if (mem_ty->isIntType())
      {
         _type_bindings[mem_ty] = _getLlvmIntTy(mem_ty->ByteSize());
         assert(_type_bindings[mem_ty] != NULL);
      }
      // Internal type
      else if (mem_ty->Name()[0] == '#' || mem_ty->Name()=="void")
      {
      }
      else
      {
         DEBUG_PRINTF("Unsupported primitive type for type `%s'\n",
            mem_ty->NameCstr());
         assert(false);
      }
   }
   else
   {
      _type_bindings[mem_ty] = llvm_ty;
   }
}

void
Codegen::gen (ast::node::Node* root)
{
   assert (_st != NULL);
   _module = new llvm::Module("top", llvm::getGlobalContext());

   st::PointerType* void_ptr = st::util::getPointerType(_st->_core_types._void);
   _type_bindings[void_ptr] = _getVoidPointerLlvmType();

   _stack.push();

   // Codegen classes first...
   st::Type* ty = NULL;
   std::map<std::string, st::Type*> types = _st->gTypes();
   std::map<std::string, st::Type*>::iterator i;

   // Codegen primitives
   for (i = types.begin() ; i != types.end(); ++i)
   {
      ty = (*i).second;
      if (ty->isAnyPrimitiveType())
      {
         //cgPrimitiveType(static_cast<st::PrimitiveType*>(ty));
      }
   }

   // Codegen classes
   for (i = types.begin() ; i != types.end(); ++i)
   {
      ty = (*i).second;
      if (ty->isClassType())
      {
         //cgClass(static_cast<st::Class*>(ty));
      }
   }

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
   /*
   llvm::Type* dest_ty = _getLlvmTy(node->gExprType());
   llvm::Value* tmp = new llvm::AllocaInst(dest_ty, NULL, amp_label + ".Alloca", _cur_bb);
   builder.CreateStore(base_val, tmp);
   llvm::Value* load = new llvm::LoadInst(tmp, amp_label + ".Load", _cur_bb);
   //llvm::LoadInst* load = new llvm::LoadInst(base_val, "", _cur_bb);
   llvm::GetElementPtrInst* gep = llvm::GetElementPtrInst::Create(base_val,
      _createInt32Constant(0),
      "dot", _cur_bb);
   */

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

   // Taking care of VALUE
   llvm::Value* val = cgExpr(n->ValueNode());
   assert (val != NULL);
   //val = new llvm::LoadInst(val, "", _cur_bb);
   //assert (val != NULL);


   // Taking care of INDEX
   llvm::Value* index = cgExprAndLoad(n->IndexNode(), _st->gCoreTypes()._int);
   assert (index != NULL);

   ast::node::Node* value_node = n->ValueNode();
   st::Type* value_ty = value_node->ExprType();

   std::vector<llvm::Value*> idx;
   /*
   if (value_ty->isArrayType()
      || (value_ty->isPointerType() && static_cast<st::PointerType*>(value_ty)->isPointerToArray()))
   {
      val = new llvm::LoadInst(val, "", _cur_bb);
      //idx.push_back(_createInt32Constant(0));
   }
   else if (value_ty->isTupleType())
   {
      val = new llvm::LoadInst(val, "", _cur_bb);
   }
   */
   if (value_ty->isPointerType())
   {
      for (int i = 0; i < static_cast<st::PointerType*>(value_ty)->IndirectionLevel(); ++i)
      {
         val = new llvm::LoadInst(val, "", _cur_bb);
      }
   }
   if (!value_ty->isPointerType() && ! static_cast<st::PointerType*>(value_ty)->isPointerToArray())
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

   if (caller_node_ty->isFunctionType())
   {
      func_ty = static_cast<st::FunctionType*>(caller_node_ty);
      callee = _functions[_getCodegenFuncName(static_cast<st::Func*>(node->CallerNode()->BoundSymbol()))];
   }
   else if (st::util::isFunctorType(caller_node_ty))
   {
      func_ty = static_cast<st::FunctionType*>(static_cast<st::PointerType*>(caller_node_ty)->getNonPointerParent());
      DEBUG_PRINTF("CAller node : %s\n", node->CallerNode()->KindNameCstr());
      callee = cgExprAndLoad(node->CallerNode(), func_ty);
   }
   else
   {
      assert(false);
   }

   assert(func_ty->isFunctionType());
   std::vector<llvm::Value*> params;

   // Instance call
   if (node->Caller() != NULL)
   {
      llvm::Value* caller = cgExprAndLoad(node->getChild(0)->getChild(0));
      st::Type* caller_expected_ty = func_ty->getArgument(0);

      // Function belongs to an ancestor of the caller type, we have to cast
      // the caller
      if (node->CallerNode()->ExprType() != caller_expected_ty)
      {
         caller = new llvm::BitCastInst(caller, _getLlvmTy(caller_expected_ty),
            "", _cur_bb);
      }

      params.push_back(caller);
   }

   if (node->ParamsNode() != NULL)
   {
      assert(func_ty->ArgumentCount() == node->ParamsNode()->ChildCount());
      ast::node::Node* cur_param_node = NULL;
      llvm::Value* param_value = NULL;
      for (size_t i = 0; i < node->ParamsNode()->ChildCount(); ++i)
      {
         cur_param_node = node->ParamsNode()->getChild(i);
         param_value = cgExprAndLoad(cur_param_node, func_ty->getArgument(i));
         params.push_back(param_value);
      }
   }

   /*
   IF_DEBUG
   {
      if (_functions[_getCodegenFuncName(func_sym)] == NULL)
      {
         DEBUG_PRINTF("Cannot find function with name `%s'\n",
            _getCodegenFuncName(func_ty).c_str());
      }
   }
   assert (_functions[_getCodegenFuncName(func_sym)] != NULL);
   */
   llvm::CallInst* call = NULL;
   call = llvm::CallInst::Create(callee, params, "", _cur_bb);

   if (call != NULL && !_st->isVoidType(func_ty->ReturnType()))
   {
      call->setDoesNotReturn(true);
   }
   //DEBUG_ENSURE (call != NULL);

   return call;
}

llvm::Value*
Codegen::cgCastExpr (ast::node::CastOp* n)
{
   DEBUG_REQUIRE (n != NULL);

   llvm::Value* src_val = cgExprAndLoad(n->ValueNode());
   st::Type* src_ty = n->ValueNode()->ExprType();
   st::Type* dest_ty = n->ExprType();
   llvm::Value* val = NULL;

   if (src_ty->isIntType() && dest_ty->isIntType())
   {
      // Extending (SAFE)
      if (src_ty->ByteSize() < dest_ty->ByteSize())
      {
         val = new llvm::SExtInst(src_val, _getLlvmTy(dest_ty), "", _cur_bb);
      }
      // Truncating (UNSAFE)
      else if (src_ty->ByteSize() > dest_ty->ByteSize())
      {
         val = new llvm::TruncInst(src_val, _getLlvmTy(dest_ty), "", _cur_bb);
      }
      else
      {
         // No casting required
         val = src_val;
      }
   }
   else if (src_ty->isPointerType() && dest_ty->isPointerType())
   {
      if (static_cast<st::PointerType*>(dest_ty)->PointedType()->Name() == "void")
      {
         val = new llvm::BitCastInst(src_val, _getLlvmTy(dest_ty), "", _cur_bb);
      }
   }

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

   st::Type* expected_operand_ty = _getLowestCommonType(
      left_val_node->ExprType(), right_val_node->ExprType());

   llvm::Value* left_val = cgExprAndLoad(left_val_node);
   llvm::Value* right_val = cgExprAndLoad(right_val_node);

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

   if (node->LeftNode()->ExprType()->isPointerType())
   {
      st::PointerType* ptr_ty = static_cast<st::PointerType*>(node->LeftNode()->ExprType());
      for (int i = 0; i < ptr_ty->IndirectionLevel(); ++i)
      {
         left_node = new llvm::LoadInst(left_node, "", _cur_bb);
         assert(left_node != NULL);
      }
      for (int i = 0; i < ptr_ty->IndirectionLevel(); ++i)
      {
         idx.push_back(_createInt32Constant(0));
      }
   }

   // Compute the field index in the whole type hierarchy
   st::Field* field = static_cast<st::Field*>(node->BoundSymbol());
   st::Class* cls_ty = static_cast<st::Class*>(field->Parent());
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
   DEBUG_PRINT("\n");
   if (node->hasBoundSymbol())
   {
      DEBUG_PRINTF("Load ? %s\n", node->BoundSymbol()->gQualifiedNameCstr());
   }

   llvm::Value* val = NULL;
   st::Type* src_ty = node->ExprType();

   if (dest_ty->isIntType() && node->isNumberNode())
   {
      src_ty = dest_ty;
      int i_val = static_cast<ast::node::Number*>(node)->getInt();
      val = llvm::ConstantInt::get(_module->getContext(), llvm::APInt(dest_ty->ByteSize() * 8, i_val));
   }
   else
   {
      val = cgExpr(node);
   }
   bool must_load = false;


   if (src_ty != dest_ty)
   {
      if (src_ty->isIntType() && dest_ty->isIntType())
      {
         val = new llvm::SExtInst(val, _getLlvmTy(dest_ty), "", _cur_bb);
      }
   }

   if (val != NULL) must_load = _mustBeLoaded(node);
   if (must_load)
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
      st::Func* func_sym = static_cast<st::Func*>(func_node->BoundSymbol());
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
            param_lty = _getLlvmTy(func_param->Type());
            alloc = new llvm::AllocaInst(param_lty, 0, "", _cur_bb);
            new llvm::StoreInst(&*i, alloc, false, _cur_bb);
            _stack.set(func_param, alloc);
         }
      }

      cgBlock(func_node->BodyNode());
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
   DEBUG_PRINT("\n");
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
   if (func_sym->IsExternal())
   {
      st::Var* func_param = NULL;
      for (size_t i = 0; i < func_sym->ParamCount(); ++i)
      {
         func_param = func_sym->_params[i];
         params.push_back(_getLlvmTy(func_param->Type()));
         assert (params[i] != NULL);
      }
   }
   DEBUG_PRINTF("Func has %d params\n", func_sym->ParamCount());
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

   llvm::BasicBlock* cur_bb = _cur_bb;
   llvm::BasicBlock* origin_exit_block = _exit_block;
   if (origin_exit_block == NULL) origin_exit_block = _cur_bb;

   bool if_is_last_child = node->Parent()->isLastChild(node);

   // After if
   llvm::BasicBlock* true_block = _createBasicBlock("if_true");
   llvm::BasicBlock* false_block = NULL;
   if (node->ElseBlockNode() != NULL)
   {
      false_block = _createBasicBlock("if_false");
   }
   llvm::BasicBlock* after_block = _createBasicBlock("if_after");

   // TRUE block
   _cur_bb = true_block;
   _exit_block = true_block;
   cgBlock(node->IfBlockNode());

   // FALSE block
   if (false_block != NULL)
   {
      _exit_block = after_block;
      cgBlock(node->ElseBlockNode());
   }
   //_exit_block = origin_exit_block;

   _cur_bb = cur_bb;
   llvm::Value* cond = cgExpr(node->ConditionNode());

   // ---------
   // BRANCHING
   // ---------

   // Branching at the end of the TRUE block
   if (false_block == NULL)
   {
      _pushNewBranchInst(_exit_block, after_block);
   }
   else
   {
      // Branching at the end of the FALSE block
      _pushNewBranchInst(false_block, after_block);
   }

   // IF/ELSE
   llvm::BasicBlock* after_if_block = NULL;

   if (node->hasElseBlockNode())
   {
      after_if_block = false_block;
   }
   // Only If
   else
   {
      after_if_block = after_block;
   }

   assert (true_block != NULL);
   assert (after_if_block != NULL);
   assert (cond != NULL);
   assert (cur_bb != NULL);

   _pushNewCondBranchInst(cur_bb, cond, true_block, after_if_block);

   _cur_bb = after_if_block;
   _exit_block = after_if_block;
}

void
Codegen::codegenMemoryFunctions ()
{
   // MALLOC
   std::vector<llvm::Type*> malloc_tys;
   malloc_tys.push_back(llvm::Type::getInt32Ty(_module->getContext()));

   llvm::FunctionType* malloc_ty = llvm::FunctionType::get(
      _getVoidPointerLlvmType(),
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

   if (type_node->BoundSymbol()->isArrayType())
   {
      st::ArrayType* arr_ty = static_cast<st::ArrayType*>(type_node->BoundSymbol());
      int type_byte_size = static_cast<st::Type*>(type_node->getChild(0)->BoundSymbol())->ByteSize();
      llvm::Value* num_obj = cgExprAndLoad(type_node->getChild(1));
      llvm::Value* obj_size = _createInt32Constant(type_byte_size);
      byte_size = llvm::BinaryOperator::Create(llvm::Instruction::Mul, num_obj, obj_size, "", _cur_bb);
   }
   else
   {
      int type_byte_size = static_cast<st::Type*>(type_node->BoundSymbol())->ByteSize();
      byte_size = llvm::ConstantInt::get(_getLlvmTy(_st->_core_types._int), type_byte_size);
   }

   // Create the call
   llvm::Value* malloc_call = llvm::CallInst::Create(_functions["malloc"],
      byte_size, "", _cur_bb);
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
         assert (false && "Invalid number constant type.");
   }

   assert (val != NULL);

   return val;
}

void
Codegen::cgPrimitiveType (st::PrimitiveType* prim)
{
   DEBUG_REQUIRE (prim != NULL);

   llvm::StructType* ty = llvm::StructType::create(_module->getContext(),
      prim->gQualifiedName());
   assert(ty != NULL);
   addType(prim, ty);
}

void
Codegen::codegenTupleTypes ()
{
   st::Symbol::SymbolCollection::iterator i;
   for (i = _st->System()->Children().begin(); i != _st->System()->Children().end(); ++i)
   {
      if (i->second->isTupleType())
      {
         //codegenTupleType (static_cast<st::TupleType*>(i->second));
      }
   }
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

   llvm::Type* llvm_ty = _getLlvmTy(mem_ty);
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
   st::Type* right_ty = static_cast<st::Type*>(node->ValueNode()->ExprType());
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

      //var_len = cgExpr(arr->LengthNode());
      var_ty = _getLlvmTy(node->TypeNode()->BoundSymbol());
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
      llvm::Value* var_val = cgExprAndLoad(node->ValueNode(), node->ExprType());
      assert (var_val != NULL);
      new llvm::StoreInst(var_val, var, _cur_bb);
   }

   _stack.set(node->BoundSymbol(), var);
}

void
Codegen::cgWhileStatement (ast::node::While* n)
{
   DEBUG_REQUIRE (n != NULL);

   llvm::BasicBlock* while_head = _createBasicBlock("while_head");
   llvm::BasicBlock* while_body = _createBasicBlock("while_body");
   llvm::BasicBlock* while_after = _createBasicBlock("while_after");
   assert(while_head != NULL && while_body != NULL && while_after != NULL);

   llvm::BasicBlock* origin_block = _cur_bb;
   if (_exit_block == NULL) _exit_block = while_body;
   llvm::BasicBlock* origin_exit_block = _exit_block;


   // ==================
   // == CODEGEN BODY ==

   // While condition
   _cur_bb = while_head;
   llvm::Value* cond = cgExpr(n->ConditionNode());
   assert(cond != NULL);

   // While body
   _cur_bb = while_body;
   _exit_block = while_after;
   cgBlock(static_cast<ast::node::Block*>(n->BodyNode()));


   // ===============
   // == BRANCHING ==

   // Going to the condition block from current block
   _pushNewBranchInst(origin_block, while_head);

   // Returning to the while condition at the end of the body block
   _pushNewBranchInst(_cur_bb, while_head);

   // Conditional branching
   _pushNewCondBranchInst(while_head, cond, while_body, while_after);

   _cur_bb = while_after;
   _exit_block = origin_exit_block;
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

   // ----------
   // PARAMETERS
   // ----------
   // Those are only set for external functions, because, for bodied functions,
   // the arguments are defined in ::cgFunctionBody.
   std::vector<llvm::Type*> params;
   //if (func_ty->IsExternal())
   {
      st::Var* func_param = NULL;
      for (size_t i = 0; i < func_ty->ParamCount(); ++i)
      {
         func_param = func_ty->_params[i];
         params.push_back(_getLlvmTy(func_param->Type()));
         assert (params[i] != NULL);
      }
   }

   // -----------
   // RETURN TYPE
   // -----------
   llvm::FunctionType* func_lty = NULL;
   st::Type* return_ty = func_ty->ReturnType();
   llvm::Type* return_lty = NULL;
   if (!_st->isVoidType(return_ty))
   {
      return_lty = _getLlvmTy(return_ty);
   }
   else
   {
      return_lty = _getVoidTy();
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

   /*
   // ---------
   // ARGUMENTS
   // ---------
   if (!func_ty->IsExternal())
   {
      st::Var* func_param = NULL;
      llvm::Type* param_lty = NULL;
      for (size_t i = 0; i < func_ty->ParamCount(); ++i)
      {
         func_param = func_ty->getParam(i);
         param_lty = _getLlvmTy(func_param->Type());
         new llvm::Argument(param_lty, func_param->Name());//, func);
      }
   }
   */

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
   llvm::Type* tuple_lty = _getLlvmTy(tuple_ty);
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

} } }
