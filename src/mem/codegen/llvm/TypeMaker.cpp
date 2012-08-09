#include "mem/codegen/llvm/TypeMaker.hpp"

namespace mem { namespace codegen { namespace llvm_ {


TypeMaker::TypeMaker ()
{
   _module = NULL;
   _st = NULL;
   _stack = NULL;
}

void
TypeMaker::bind (st::Type* mem_ty, llvm::Type* llvm_ty)
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
   std::map<st::Type*, llvm::Type*>::iterator i;
   for (i = _type_bindings.begin() ; i != _type_bindings.end(); ++i)
   {
      printf("`%s'\n", (*i).first->gQualifiedNameCstr());
   }
}

llvm::Type*
TypeMaker::get (st::Type* mem_ty)
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
TypeMaker::makeArrayType (st::ArrayType* t)
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
      lty = llvm::PointerType::get(item_lty, 0);
   }

   bind(t, lty);

   DEBUG_ENSURE (lty != NULL);
   return lty;
}

llvm::StructType*
TypeMaker::makeClassType (st::Class* cls_sym)
{
   DEBUG_REQUIRE (cls_sym != NULL);
   DEBUG_REQUIRE (cls_sym->isClassType());

   std::vector<llvm::Type*> fields;
   if (cls_sym->_cur_field_index > 0)
   {
      std::vector<st::Field*> f = cls_sym->getOrderedFields();
      st::Field* field = NULL;
      for (size_t i=0; i < f.size(); ++i)
      {
         assert(f[i] != NULL);
         field = f[i];
         fields.push_back(get(field->Type()));
      }
   }

   llvm::StructType* ty = llvm::StructType::create(_module->getContext(),
      cls_sym->gQualifiedName());
   if (ty->isOpaque())
   {
      ty->setBody(fields, false /* packed */);
   }

   bind(cls_sym, ty);

   return ty;
}

llvm::Constant*
TypeMaker::makeConstant (st::Constant* c)
{
   llvm::Constant* lconst = NULL;

   // FIXME This only works for signed integer values
   switch (c->Kind())
   {
      case st::INT_CONSTANT:
         st::IntConstant* ic = static_cast<st::IntConstant*>(c);
         if (ic->IsSigned())
         {
            lconst = llvm::ConstantInt::get(get(c->Type()),
               static_cast<st::IntConstant*>(c)->getSignedValue(),
               true); /* Signed */
         }
         break;
   }

   assert(lconst != NULL);
   return lconst;
}

llvm::Type*
TypeMaker::makeEnumType (st::EnumType* t)
{
   st::SymbolMapIterator i;
   for (i = t->Children().begin(); i != t->Children().end(); ++i)
   {
      llvm::GlobalVariable* v = new llvm::GlobalVariable(
        *_module,
         get(t->Type()),
         true, /* isConstant */
         llvm::GlobalValue::InternalLinkage,
         makeConstant(static_cast<st::Var*>(i->second)->ConstantValue()),
         i->second->gQualifiedName());
      _stack->setGlobal(i->second, v);
   }
   return get(t->Type());
}

llvm::FunctionType*
TypeMaker::makeFunctionType (st::FunctionType* t)
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
TypeMaker::makePointerType (st::PointerType* t)
{
   return llvm::PointerType::get(get(t->PointedType()), 0);
}

llvm::Type*
TypeMaker::makePrimitiveType (st::PrimitiveType* t)
{
   if (_st->isVoidType(t))
   {
      return llvm::Type::getVoidTy(_module->getContext());
   }
   return NULL;
}

llvm::StructType*
TypeMaker::makeTupleType (st::TupleType* t)
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
TypeMaker::makeType (st::Type* mem_ty)
{
   switch (mem_ty->Kind())
   {
      case st::ARRAY:
         return makeArrayType(static_cast<st::ArrayType*>(mem_ty));

      case st::CLASS:
         return makeClassType(static_cast<st::Class*>(mem_ty));

      case st::ENUM_TYPE:
         return makeEnumType(static_cast<st::EnumType*>(mem_ty));

      case st::FUNCTION_TYPE:
         return makeFunctionType(static_cast<st::FunctionType*>(mem_ty));

      case st::TUPLE_TYPE:
         return makeTupleType(static_cast<st::TupleType*>(mem_ty));

      case st::INT_TYPE:
         return makeIntType(mem_ty->ByteSize());

      case st::POINTER:
         return makePointerType(static_cast<st::PointerType*>(mem_ty));

      case st::PRIMITIVE_TYPE:
         return makePrimitiveType(static_cast<st::PrimitiveType*>(mem_ty));

      default:
         DEBUG_PRINTF("Unsupported mem type {Kind: %d, Name: %s}\n",
            mem_ty->Kind(), mem_ty->gQualifiedNameCstr());
         assert(false);
   }

   return NULL;
}

} } }
