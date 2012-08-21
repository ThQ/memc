#ifndef _MEM__CODEGEN__LLVM__TYPE_MAKER__HPP_
#define _MEM__CODEGEN__LLVM__TYPE_MAKER__HPP_

#include "config.h"

#ifdef HAVE_LLVM

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
#include "codegen/TStack.hpp"
#include "mem/st/Class.hpp"
#include "mem/st/EnumType.hpp"
#include "mem/st/Field.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/PointerType.hpp"
#include "mem/st/util.hpp"
#include "mem/st/Var.hpp"


namespace codegen { namespace llvm_ {

typedef TStack<mem::st::Symbol*,llvm::Value*> LlvmStack;

// An helper class to codegen LLVM types
class TypeMaker
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   TypeMaker ();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   SETTER(Module, llvm::Module*) {_module = val;}
   SETTER(SymbolTable, mem::st::SymbolTable*) {_st = val;}
   SETTER(Stack, LlvmStack*) {_stack = val;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   // Bind an ST type with an LLVM type.
   void
   bind (mem::st::Type* mem_ty, llvm::Type* llvm_ty);

   void
   dump ();

   inline llvm::Type*
   get (mem::st::Symbol* type) {return get(static_cast<mem::st::Type*>(type));}

   llvm::Type*
   get (mem::st::Type* type);

   llvm::Type*
   makeArrayType (mem::st::ArrayType* t);

   llvm::StructType*
   makeClassType (mem::st::Class* cls_symb);

   llvm::Constant*
   makeConstant (mem::st::Constant* c);

   llvm::Constant*
   makeDefaultConstant (mem::st::Type* c);

   llvm::Type*
   makeEnumType (mem::st::EnumType* t);

   llvm::FunctionType*
   makeFunctionType (mem::st::FunctionType* t);

   // Returns the LLVM int type of a given length.
   llvm::Type*
   makeIntType (size_t size);

   llvm::PointerType*
   makePointerType (mem::st::PointerType* t);

   llvm::Type*
   makePrimitiveType (mem::st::PrimitiveType* t);

   llvm::StructType*
   makeTupleType (mem::st::TupleType* t);

   llvm::Type*
   makeType (mem::st::Type* ty);

   llvm::Type*
   makeVoidType () {return llvm::Type::getVoidTy(_module->getContext());}

   llvm::PointerType*
   makeVoidPointerType () {return llvm::Type::getInt32PtrTy(_module->getContext());}


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   llvm::Module* _module;
   mem::st::SymbolTable* _st;
   std::map<mem::st::Type*, llvm::Type*> _type_bindings;
   LlvmStack* _stack;
};

} }

#endif // HAVE_LLVM
#endif
