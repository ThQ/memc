#ifndef _MEM__CODEGEN__LLVM__CODEGEN__HPP_
#define _MEM__CODEGEN__LLVM__CODEGEN__HPP_


#include <llvm/CodeGen/AsmPrinter.h>
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/PassManager.h>
#include <llvm/Module.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetData.h>
#include <llvm/Target/TargetMachine.h>
#include "llvm/Support/FormattedStream.h"
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <map>
#include "mem/ast/node/Array.hpp"
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
#include "mem/ast/node/String.hpp"
#include "mem/ast/node/Tuple.hpp"
#include "mem/ast/node/VarAssign.hpp"
#include "mem/ast/node/While.hpp"
#include "mem/codegen/ICodegen.hpp"
#include "mem/codegen/TStack.hpp"
#include "mem/st/Class.hpp"
#include "mem/st/EnumType.hpp"
#include "mem/st/Field.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/PointerType.hpp"
#include "mem/st/util.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace codegen { namespace llvm_ {


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
class Codegen : public mem::codegen::ICodegen
{
   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   std::map<st::Type*, llvm::Type*> _type_bindings;
   llvm::BasicBlock* _cur_bb;
   llvm::Function* _cur_func;
   llvm::BasicBlock* _exit_block;
   std::map<std::string, llvm::Function*> _functions;
   llvm::Module* _module;
   st::SymbolTable* _st;
   TStack<st::Symbol*, llvm::Value*> _stack;


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   inline void
   SymbolTable (st::SymbolTable* st) {_st=st;}

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   Codegen ();


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   llvm::Type*
   _codegenArrayType (st::ArrayType* t);

   llvm::StructType*
   _codegenClassType (st::Class* cls_symb);

   llvm::Type*
   _codegenEnumType (st::EnumType* t);

   llvm::FunctionType*
   _codegenFunctionType (st::FunctionType* t);

   llvm::PointerType*
   _codegenPointerType (st::PointerType* t);

   llvm::Type*
   _codegenPrimitiveType (st::PrimitiveType* t);

   llvm::StructType*
   _codegenTupleType (st::TupleType* t);

   llvm::Type*
   _codegenType (st::Type* ty);

   llvm::Constant*
   _getLlvmConstant (st::Constant* c);

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

   void
   _dumpStack();

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
   _getCodegenFuncName (st::Func* func);

   st::Type*
   _getLowestCommonType (st::Symbol* left_ty, st::Symbol* right_ty);

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

   /*
   inline llvm::Type*
   _getLlvmTy (std::string st_name) {llvm::Type* ty= _classes[st_name];assert(ty != NULL);return ty;}
   */

   llvm::Type*
   _getLlvmTy (st::Symbol* mem_ty) {return _getLlvmTy(static_cast<st::Type*>(mem_ty));}

   llvm::Type*
   _getLlvmTy (st::Type* mem_ty);

   std::string
   _getLlvmTypeName (llvm::Type* ty);

   /**
    * Returns the void LLVM type.
    */
   llvm::Type*
   _getVoidTy ();

   llvm::Type*
   _getVoidPointerLlvmType () {return llvm::Type::getInt32PtrTy(_module->getContext());}

   bool
   _mustBeLoaded (ast::node::Node* n);

   /**
    * Associates an ST type with an LLVM type.
    */
   void
   addType (st::Type* mem_ty, llvm::Type* llvm_ty);

   llvm::Value*
   cgAmpersandExpr (ast::node::Node* node);

   llvm::Value*
   cgBinaryExpr (ast::node::Node* node);

   inline void
   cgBlock (ast::node::Node* block)
   {
      assert(block->isBlockNode());
      cgBlock(static_cast<ast::node::Block*>(block));
   }

   void
   cgBlock (ast::node::Block* block);

   llvm::Value*
   cgBracketOpExpr (ast::node::BracketOp* n);

   llvm::Value*
   cgCastExpr (ast::node::CastOp* n);

   llvm::Value*
   cgCallExpr (ast::node::Call* node);

   llvm::Value*
   cgCompOp (ast::node::BinaryOp* node);

   llvm::Value*
   cgDotExpr (ast::node::Dot* node);

   void
   cgFile (ast::node::File* file_node);

   llvm::Value*
   cgFinalIdExpr (ast::node::Text* node);

   /**
    * Codegen a node.
    */
   llvm::Value*
   cgExpr (ast::node::Node* node);

   llvm::Value*
   cgExprAndLoad (ast::node::Node* node);

   llvm::Value*
   cgExprAndLoad (ast::node::Node* node, st::Type* dest_ty);

   /**
    * Codegen a node and generate a LLVM Load instruction if necessary.
    */
    /*
   llvm::Value*
   cgExprAndLoad (ast::node::Node* node, st::Symbol* source_ty, st::Symbol* dest_ty);

   llvm::Value*
   cgExprAndLoad (ast::node::Node* src, st::Symbol* dest_ty);
   */

   void
   cgFunctionBody (ast::node::Func* func_node);

   void
   cgFunctionDef (ast::node::Func* func_node);

   void
   cgForStatement (ast::node::For* n);

   void
   cgIfStatement (ast::node::If* node);

   void
   codegenMemoryFunctions ();

   llvm::Value*
   cgNewExpr (ast::node::New* node);

   llvm::Value*
   cgNumberExpr (ast::node::Number* node);

   void
   cgPrimitiveType (st::PrimitiveType* prim);

   llvm::Value*
   cgDerefExpr (ast::node::Node* node);

   void
   cgReturnStatement (ast::node::Node* node);

   llvm::Value*
   cgString (ast::node::String* n);

   void
   codegenTupleTypes ();

   void
   cgVarAssignStatement (ast::node::VarAssign* node);

   void
   cgVarDeclStatement (ast::node::VarDecl* node);

   void
   cgWhileStatement (ast::node::While* n);

   void
   codegenFunctionDeclarations ();

   void
   codegenFunctionType (st::Func* func_ty);

   void
   codegenFunctionBodies (ast::node::Root* root_n);

   llvm::Value*
   codegenTuple (ast::node::Tuple* n);

   virtual void
   gen (ast::node::Node* root);

   std::string
   getLlvmByteCode ();
};


} } }

#endif
