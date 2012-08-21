#include "codegen/llvm/TypeMaker.hpp"

#ifdef HAVE_LLVM

namespace codegen { namespace llvm_ {


TypeMaker::TypeMaker ()
{
   _module = NULL;
   _st = NULL;
   _stack = NULL;
}

void
TypeMaker::bind (mem::st::Type* mem_ty, llvm::Type* llvm_ty)
{
   if (mem_ty->isAnyPrimitiveType())
   {
      if (mem_ty->isIntType())
      {
         _type_bindings[mem_ty] = makeIntType(mem_ty->ByteSize());
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
TypeMaker::dump ()
{
   std::map<mem::st::Type*, llvm::Type*>::iterator i;
   for (i = _type_bindings.begin() ; i != _type_bindings.end(); ++i)
   {
      printf("`%s'\n", (*i).first->gQualifiedNameCstr());
   }
}

llvm::Type*
TypeMaker::get (mem::st::Type* mem_ty)
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
      ty = makeType (mem_ty);
   }

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

llvm::Type*
TypeMaker::makeArrayType (mem::st::ArrayType* t)
{
   DEBUG_REQUIRE (t != NULL);

   llvm::Type* lty = NULL;
   llvm::Type* item_lty = get(t->ItemType());

   if (t->hasLength())
   {
      lty = llvm::ArrayType::get(item_lty, t->ArrayLength());
   }
   else
   {
      lty = item_lty; //llvm::PointerType::get(item_lty, 0);
   }

   bind(t, lty);

   DEBUG_ENSURE (lty != NULL);
   return lty;
}

llvm::StructType*
TypeMaker::makeClassType (mem::st::Class* cls_sym)
{
   DEBUG_REQUIRE (cls_sym != NULL);
   DEBUG_REQUIRE (cls_sym->isClassType());

   // -------------
   //  Struct type
   // -------------
   llvm::StructType* ty = llvm::StructType::create(_module->getContext(),
      cls_sym->gQualifiedName());

   bind(cls_sym, ty);

   // --------
   //  Fields
   // --------
   std::vector<llvm::Type*> fields;
   if (1)//cls_sym->_cur_field_index > 0)
   {
      std::vector<mem::st::Field*> f = cls_sym->getOrderedFields();
      mem::st::Field* field = NULL;
      for (size_t i=0; i < f.size(); ++i)
      {
         assert(f[i] != NULL);
         field = f[i];
         fields.push_back(get(field->Type()));
      }
   }

   ty->setBody(fields, false /* packed */);


   return ty;
}

llvm::Constant*
TypeMaker::makeConstant (mem::st::Constant* c)
{
   llvm::Constant* lconst = NULL;

   // FIXME This only works for signed integer values
   switch (c->Kind())
   {
      case mem::st::INT_CONSTANT:
      {
         mem::st::IntConstant* ic = mem::st::castToIntConstant(c);
         if (ic->IsSigned())
         {
            lconst = llvm::ConstantInt::get(get(c->Type()),
               mem::st::castToIntConstant(c)->getSignedValue(),
               true); /* Signed */
         }
      }
      break;
      default:
         assert(false);
   }

   assert(lconst != NULL);
   return lconst;
}

llvm::Constant*
TypeMaker::makeDefaultConstant (mem::st::Type* t)
{
   llvm::Constant* cns = NULL;
   if (t->isIntType())
   {
      mem::st::IntType* int_ty = mem::st::castToIntType(t);
      cns = llvm::ConstantInt::get(get(t), 0, true /* is signed */);
   }
   else if (t->isPointerType())
   {
      cns = llvm::ConstantPointerNull::get(static_cast<llvm::PointerType*>(get(t)));
   }
   else
   {
      assert(false);
   }
   return cns;
}

llvm::Type*
TypeMaker::makeEnumType (mem::st::EnumType* t)
{
   mem::st::SymbolMapIterator i;
   for (i = t->Children().begin(); i != t->Children().end(); ++i)
   {
      llvm::GlobalVariable* v = new llvm::GlobalVariable(
        *_module,
         get(t->Type()),
         true, /* isConstant */
         llvm::GlobalValue::InternalLinkage,
         makeConstant(mem::st::castToVar(i->second)->ConstantValue()),
         i->second->gQualifiedName());
      _stack->setGlobal(i->second, v);
   }
   return get(t->Type());
}

llvm::FunctionType*
TypeMaker::makeFunctionType (mem::st::FunctionType* t)
{
   std::vector<llvm::Type*> args;
   for (size_t i = 0; i < t->ArgumentCount(); ++i)
   {
      args.push_back(get(t->getArgument(i)));
   }

   return llvm::FunctionType::get(get(t->ReturnType()), args, false);
}

llvm::Type*
TypeMaker::makeIntType (size_t size)
{
   return llvm::Type::getIntNTy(_module->getContext(), size * 8);
}

llvm::PointerType*
TypeMaker::makePointerType (mem::st::PointerType* t)
{
   return llvm::PointerType::get(get(t->PointedType()), 0);
}

llvm::Type*
TypeMaker::makePrimitiveType (mem::st::PrimitiveType* t)
{
   if (_st->isVoidType(t))
   {
      return llvm::Type::getVoidTy(_module->getContext());
   }
   return NULL;
}

llvm::StructType*
TypeMaker::makeTupleType (mem::st::TupleType* t)
{
   DEBUG_REQUIRE (t != NULL);
   DEBUG_REQUIRE (_type_bindings.find(t) != _type_bindings.end());

   std::vector<llvm::Type*> ltys;
   for (size_t i=0; i < t->Subtypes().size(); ++i)
   {
      ltys.push_back(get(t->Subtypes()[i]));
   }

   llvm::StructType* tuple_lty = llvm::StructType::create(ltys, "tuple");
   bind(t, tuple_lty);
   return tuple_lty;
}

llvm::Type*
TypeMaker::makeType (mem::st::Type* mem_ty)
{
   switch (mem_ty->Kind())
   {
      case mem::st::ARRAY:
         return makeArrayType(static_cast<mem::st::ArrayType*>(mem_ty));

      case mem::st::CLASS:
         return makeClassType(mem::st::castToClassType(mem_ty));

      case mem::st::ENUM_TYPE:
         return makeEnumType(static_cast<mem::st::EnumType*>(mem_ty));

      case mem::st::FUNCTION_TYPE:
         return makeFunctionType(static_cast<mem::st::FunctionType*>(mem_ty));

      case mem::st::TUPLE_TYPE:
         return makeTupleType(static_cast<mem::st::TupleType*>(mem_ty));

      case mem::st::INT_TYPE:
         return makeIntType(mem_ty->ByteSize());

      case mem::st::POINTER:
         return makePointerType(mem::st::castToPointerType(mem_ty));

      case mem::st::PRIMITIVE_TYPE:
         return makePrimitiveType(static_cast<mem::st::PrimitiveType*>(mem_ty));

      case mem::st::VOID_TYPE:
         return makeVoidType();

      default:
         DEBUG_PRINTF("Unsupported mem type {Kind: %d, Name: %s}\n",
            mem_ty->Kind(), mem_ty->gQualifiedNameCstr());
         assert(false);
   }

   return NULL;
}

} }

#endif // HAVE_LLVM
