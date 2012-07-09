#ifndef _MEM__CODEGEN__LLVM__CODEGEN__HPP_
#define _MEM__CODEGEN__LLVM__CODEGEN__HPP_


#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <map>
#include "mem/ast/node/Func.hpp"
#include "mem/codegen/ICodegen.hpp"
#include "mem/st/Class.hpp"
#include "mem/st/Func.hpp"


namespace mem { namespace codegen { namespace llvm_ {


static llvm::IRBuilder<> builder(llvm::getGlobalContext());

class Codegen : public mem::codegen::ICodegen
{
   private: std::map<std::string, llvm::Type*> _classes;
   private: llvm::Module* _module;
   public: st::SymbolTable* _st;

   public: void addType (st::Type* mem_ty, llvm::Type* llvm_ty);
   public: void cgClass (st::Class* cls_symb);
   public: void cgFile (ast::node::File* file_node);
   public: void cgFunction (ast::node::Func* func_node);
   public: virtual void gen (ast::node::Node* root);
   public: llvm::Type* _getVoidTy ();
   public: llvm::Type* _getFuncReturnTy (ast::node::Func* func);
   public: std::vector<llvm::Type*> _getFuncParamsTy (st::Func* func);
   public: std::string getLlvmByteCode ();
};


} } }

#endif
