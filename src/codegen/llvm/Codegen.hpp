#ifndef _MEM__CODEGEN__LLVM__CODEGEN__HPP_
#define _MEM__CODEGEN__LLVM__CODEGEN__HPP_

#include "config.h"

#ifdef HAVE_LLVM

#include <llvm/Support/ManagedStatic.h>
#include <map>
#include "codegen/llvm/TypeMaker.hpp"
#include "codegen/ICodegen.hpp"
#include "codegen/TStack.hpp"
#include "mem/ast/node/ArrayType.hpp"
#include "mem/ast/node/BinaryOp.hpp"
#include "mem/ast/node/BracketOp.hpp"
#include "mem/ast/node/Call.hpp"
#include "mem/ast/node/CastOp.hpp"
#include "mem/ast/node/Dot.hpp"
#include "mem/ast/node/FinalId.hpp"
#include "mem/ast/node/For.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/If.hpp"
#include "mem/ast/node/New.hpp"
#include "mem/ast/node/Return.hpp"
#include "mem/ast/node/String.hpp"
#include "mem/ast/node/Tuple.hpp"
#include "mem/ast/node/VarAssign.hpp"
#include "mem/ast/node/While.hpp"


namespace codegen { namespace llvm_ {


// Emit LLVM assembly from an AST and a ST.
//
// References :
// - LLVM assembly language reference
//   <http://http://llvm.org/docs/LangRef.html>
// - Try LLVM online (can generate C++ or LLVM assembly from C/C++)
//   <http://llvm.org/demo/>
// - API documentation for llvm::IRBuilder (an helper class to generate LLVM
//   instructions)
//   <http://llvm.org/docs/doxygen/html/classllvm_1_1IRBuilder.html>
//
// FIXME: We should create an helper class for all LLVM type creation
class Codegen : public codegen::ICodegen
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   Codegen ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   SETTER(SymbolTable, mem::st::SymbolTable*) {_st = val;}


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   llvm::Value*
   _castLlvmValue (llvm::Value* val, mem::st::Type* src_ty, mem::st::Type* dest_ty);

   inline llvm::BasicBlock*
   _createBasicBlock(std::string name="")
   {
      llvm::BasicBlock* bb = llvm::BasicBlock::Create(llvm::getGlobalContext(),
         name, _cur_func);
      assert (bb != NULL);
      return bb;
   }

   inline llvm::Constant*
   _createInt32Constant (int val)
   {
      return llvm::ConstantInt::get(_module->getContext(), llvm::APInt(32, val));
   }

   inline llvm::Constant*
   _createInt64Constant (int val)
   {
      return llvm::ConstantInt::get(_module->getContext(), llvm::APInt(64, val));
   }

   inline llvm::GetElementPtrInst*
   _createGepInst(llvm::Value* base, std::vector<llvm::Value*> idx);

   inline void
   _pushNewBranchInst (llvm::BasicBlock* parent, llvm::BasicBlock* dest)
   {
      parent->getInstList().push_back(llvm::BranchInst::Create(dest));
   }

   inline void
   _pushNewCondBranchInst (llvm::BasicBlock* parent, llvm::Value* cond, llvm::BasicBlock* dest_true, llvm::BasicBlock* dest_false)
   {
      llvm::BranchInst::Create(dest_true, dest_false, cond, parent);
   }

   void
   _dumpTypes ();

   std::string
   _getCodegenFuncName (mem::st::Func* func);

   mem::st::Type*
   _getLowestCommonType (mem::st::Symbol* left_ty, mem::st::Symbol* right_ty);

   /**
    * Returns the LLVM type associated with an AST function node.
    */
   llvm::Type*
   _getFuncReturnTy (mem::ast::node::Func* func);

   /**
    * Returns the LLVM types associated with the parameters of a ST function.
    */
   std::vector<llvm::Type*>
   _getFuncParamsTy (mem::st::Func* func);

   std::string
   _getLlvmTypeName (llvm::Type* ty);

   /**
    * Returns the void LLVM type.
    */
   llvm::Type*
   _getVoidTy ();

   bool
   _mustBeLoaded (mem::ast::node::Node* n);

   llvm::Value*
   cgAmpersandExpr (mem::ast::node::Node* node);

   llvm::Value*
   cgBinaryExpr (mem::ast::node::Node* node);

   inline void
   cgBlock (mem::ast::node::Node* block)
   {
      assert(mem::ast::node::isa<mem::ast::node::Block>(block));
      cgBlock(mem::ast::node::cast<mem::ast::node::Block>(block));
   }

   void
   cgBlock (mem::ast::node::Block* block);

   llvm::Value*
   cgBracketOpExpr (mem::ast::node::BracketOp* n);

   llvm::Value*
   cgCastExpr (mem::ast::node::CastOp* n);

   llvm::Value*
   cgCallExpr (mem::ast::node::Call* node);

   llvm::Value*
   cgCompOp (mem::ast::node::BinaryOp* node);

   llvm::Value*
   cgDotExpr (mem::ast::node::BinaryOp* node);

   void
   cgFile (mem::ast::node::File* file_node);

   llvm::Value*
   cgFinalIdExpr (mem::ast::node::Text* node);

   /**
    * Codegen a node.
    */
   llvm::Value*
   cgExpr (mem::ast::node::Node* node);

   llvm::Value*
   cgExprAndLoad (mem::ast::node::Node* node);

   llvm::Value*
   cgExprAndLoad (mem::ast::node::Node* node, mem::st::Type* dest_ty);

   /**
    * Codegen a node and generate a LLVM Load instruction if necessary.
    */
    /*
   llvm::Value*
   cgExprAndLoad (mem::ast::node::Node* node, mem::st::Symbol* source_ty, mem::st::Symbol* dest_ty);

   llvm::Value*
   cgExprAndLoad (mem::ast::node::Node* src, mem::st::Symbol* dest_ty);
   */

   void
   cgFunctionBody (mem::ast::node::Func* func_node);

   void
   cgFunctionDef (mem::ast::node::Func* func_node);

   void
   cgForStatement (mem::ast::node::For* n);

   void
   cgIfStatement (mem::ast::node::If* node);

   void
   codegenMemoryFunctions ();

   llvm::Value*
   cgNewExpr (mem::ast::node::New* node);

   llvm::Value*
   cgNumberExpr (mem::ast::node::Number* node);

   llvm::Value*
   cgDerefExpr (mem::ast::node::Node* node);

   void
   cgReturnStatement (mem::ast::node::Return* node);

   llvm::Value*
   cgString (mem::ast::node::String* n);

   void
   cgVarAssignStatement (mem::ast::node::VarAssign* node);

   void
   cgVarDeclStatement (mem::ast::node::VarDecl* node);

   void
   cgWhileStatement (mem::ast::node::While* n);

   void
   codegenFunctionDeclarations ();

   void
   codegenFunctionType (mem::st::Func* func_ty);

   void
   codegenFunctionBodies (mem::ast::node::Root* root_n);

   llvm::Value*
   codegenTuple (mem::ast::node::Tuple* n);

   virtual void
   gen (mem::ast::node::Node* root);

   std::string
   getLlvmByteCode ();

   void
   initializeArrayOfClassInstances (mem::st::ArrayType* cls_ty, llvm::Value* arr, bool is_static);

   void
   initializeValue (mem::st::Type* ty, llvm::Value* val);

   void
   tearDown ();

   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   llvm::BasicBlock* _cur_bb;
   llvm::Function* _cur_func;
   llvm::BasicBlock* _exit_block;
   std::map<std::string, llvm::Function*> _functions;
   llvm::Module* _module;
   mem::st::SymbolTable* _st;
   TStack<mem::st::Symbol*, llvm::Value*> _stack;
   TypeMaker _type_maker;
};


} }

#endif // HAVE_LLVM
#endif
