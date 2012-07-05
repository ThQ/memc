#include "mem/codegen/llvm/Codegen.hpp"


namespace mem { namespace codegen { namespace llvm_ {


void
Codegen::addType (st::Type* mem_ty, llvm::Type* llvm_ty)
{
   if (mem_ty->is(st::PRIMITIVE))
   {
      // TODO This is very ugly...
      if (mem_ty == _st->_core_types.gIntTy())
      {
         _classes[mem_ty->gQualifiedName()] = llvm::Type::getInt32Ty(_module->getContext());
      }
      else if (mem_ty == _st->_core_types.gBoolTy())
      {
         _classes[mem_ty->gQualifiedName()] = llvm::Type::getInt32Ty(_module->getContext());
      }
      else if (mem_ty == _st->_core_types.gCharTy())
      {
         _classes[mem_ty->gQualifiedName()] = llvm::Type::getInt32Ty(_module->getContext());
      }
      else if (mem_ty == _st->_core_types.gShortTy())
      {
         _classes[mem_ty->gQualifiedName()] = llvm::Type::getInt32Ty(_module->getContext());
      }
      else if (mem_ty == _st->_core_types.gVoidTy())
      {
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
      cgFile(static_cast<ast::node::File*>(root->getChild(i)));
   }

   _module->dump();
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
   //this->_classes[cls_sym->gQualifiedName()] =  ty;
}

void
Codegen::cgFile (ast::node::File* file_node)
{
   ast::node::Node* node = NULL;

   // ... then functions
   for (size_t i = 0 ; i < file_node->gChildCount(); ++i)
   {
      node = file_node->getChild(i);
      if (node->isFuncNode())
      {
         cgFunction(static_cast<ast::node::Func*>(node));
      }
   }
}

void
Codegen::cgFunction (ast::node::Func* func_node)
{
   assert(func_node->isFuncNode());

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

   llvm::Function::Create(func_ty,
      llvm::GlobalValue::ExternalLinkage,
      func_name,
      _module);
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


} } }
