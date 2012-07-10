#ifndef _MEM__CODEGEN__LLVM__CODEGEN__HPP_
#define _MEM__CODEGEN__LLVM__CODEGEN__HPP_


#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <map>
#include "mem/ast/node/Call.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/codegen/ICodegen.hpp"
#include "mem/st/Class.hpp"
#include "mem/st/Func.hpp"


namespace mem { namespace codegen { namespace llvm_ {


static llvm::IRBuilder<> builder(llvm::getGlobalContext());

class Codegen : public mem::codegen::ICodegen
{
   private: std::map<std::string, llvm::Value*> _block_vars;

   private: std::map<std::string, llvm::Type*> _classes;
   private: std::map<std::string, llvm::Function*> _functions;

   private: llvm::Module* _module;
   public: st::SymbolTable* _st;

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   std::string
   _getCodegenFuncName (st::Func* func);

   /**
    * Returns the LLVM type associated with an AST function node.
    */
   llvm::Type*
   _getFuncReturnTy (ast::node::Func* func);

   /**
    * Returns the LLVM types associated with the parameters of a ST function.
    */
   std::vector<llvm::Type*>
   _getFuncParamsTy (st::Func* func);

   /**
    * Returns the LLVM int type of a given length.
    */
   llvm::Type*
   _getLlvmIntTy (size_t size);

   inline llvm::Type*
   _getLlvmTy (std::string st_name) {return _classes[st_name];}

   /**
    * Returns the void LLVM type.
    */
   llvm::Type*
   _getVoidTy ();

   /**
    * Associates an ST type with an LLVM type.
    */
   void
   addType (st::Type* mem_ty, llvm::Type* llvm_ty);

   llvm::Value*
   cgBinaryExpr (ast::node::Node* node);

   llvm::Value*
   cgCallExpr (ast::node::Call* node);

   void
   cgClass (st::Class* cls_symb);

   void
   cgFile (ast::node::File* file_node, bool cg_func_def);

   llvm::Value*
   cgFinalId (ast::node::Text* node);

   llvm::Value*
   cgExpr (ast::node::Node* node);

   void
   cgFunctionBody (ast::node::Func* func_node);

   void
   cgFunctionDef (ast::node::Func* func_node);

   llvm::Value*
   cgNumberExpr (ast::node::Number* node);

   void
   cgReturnStatement (ast::node::Node* node);

   void
   cgVarDecl (ast::node::VarDecl* node);

   virtual void
   gen (ast::node::Node* root);

   std::string
   getLlvmByteCode ();
};


} } }

#endif
