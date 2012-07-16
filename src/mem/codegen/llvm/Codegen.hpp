#ifndef _MEM__CODEGEN__LLVM__CODEGEN__HPP_
#define _MEM__CODEGEN__LLVM__CODEGEN__HPP_


#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <map>
#include "mem/ast/node/Call.hpp"
#include "mem/ast/node/Dot.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/If.hpp"
#include "mem/ast/node/New.hpp"
#include "mem/ast/node/VarAssign.hpp"
#include "mem/codegen/ICodegen.hpp"
#include "mem/codegen/TStack.hpp"
#include "mem/st/Class.hpp"
#include "mem/st/Field.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/Ptr.hpp"
#include "mem/st/Util.hpp"


namespace mem { namespace codegen { namespace llvm_ {


/**
 * Emit LLVM assembly from an AST and a ST.
 *
 * References :
 * - LLVM assembly language reference
     <http://http://llvm.org/docs/LangRef.html>
 * - Try LLVM online (can generate C++ or LLVM assembly from C/C++)
     <http://llvm.org/demo/>
 * - API documentation for llvm::IRBuilder (an helper class to generate LLVM
     instructions)
     <http://llvm.org/docs/doxygen/html/classllvm_1_1IRBuilder.html>
 */
class Codegen : public mem::codegen::ICodegen
{
   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   std::map<std::string, llvm::Type*> _classes;
   llvm::BasicBlock* _cur_bb;
   llvm::Function* _cur_func;
   std::map<std::string, llvm::Function*> _functions;
   llvm::Module* _module;
   st::SymbolTable* _st;
   TStack<llvm::Value*> _stack;


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   inline void
   SymbolTable (st::SymbolTable* st) {_st=st;}


   //--------------------------------------------------------------------------
   // FUNCTIONS
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

   llvm::Type*
   _getLlvmTy (st::Type* mem_ty);

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
   cgAmpersandExpr (ast::node::Node* node);

   llvm::Value*
   cgBinaryExpr (ast::node::Node* node);

   void
   cgBlock (ast::node::Block* block);

   llvm::Value*
   cgCallExpr (ast::node::Call* node);

   void
   cgClass (st::Class* cls_symb);

   llvm::Value*
   cgDotExpr (ast::node::Dot* node);

   void
   cgFile (ast::node::File* file_node, bool cg_func_def);

   llvm::Value*
   cgFinalIdExpr (ast::node::Text* node);

   /**
    * Codegen a node.
    */
   llvm::Value*
   cgExpr (ast::node::Node* node);

   /**
    * Codegen a node and generate a LLVM Load instruction if necessary.
    */
   llvm::Value*
   cgExprAndLoad (ast::node::Node* node);

   void
   cgFunctionBody (ast::node::Func* func_node);

   void
   cgFunctionDef (ast::node::Func* func_node);

   void
   cgIfStatement (ast::node::If* node);

   void
   cgMemoryFunctions ();

   llvm::Value*
   cgNewExpr (ast::node::New* node);

   llvm::Value*
   cgNumberExpr (ast::node::Number* node);

   void
   cgPrimitive (st::Primitive* prim);

   void
   cgReturnStatement (ast::node::Node* node);

   void
   cgVarAssignStatement (ast::node::VarAssign* node);

   void
   cgVarDeclStatement (ast::node::VarDecl* node);

   virtual void
   gen (ast::node::Node* root);

   std::string
   getLlvmByteCode ();
};


} } }

#endif
