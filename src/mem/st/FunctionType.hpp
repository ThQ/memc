#ifndef _MEM__ST__FUNCTION_TYPE__HPP
#define _MEM__ST__FUNCTION_TYPE__HPP


#include <vector>
#include "mem/st/PointerType.hpp"
#include "mem/st/Type.hpp"


namespace mem { namespace st {


class FunctionType: public Type
{
   public:
   static const int kTYPE = MetaKind::FUNCTION_TYPE;

   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   FunctionType();

   // Default destructor.
   ~FunctionType();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // Arguments
   GETTER (Arguments, TypeVector) {return _arguments;}

   // ParamCount
   GETTER(ArgumentCount, size_t) {return _arguments.size();}

   // FunctorType
   GETTER(FunctorType, PointerType*) {return _functor_type;}
   SETTER(FunctorType, PointerType*) {_functor_type = val;}

   // ReturnType
   GETTER(ReturnType, Type*) {return _return_type;}
   SETTER(ReturnType, Type*) {_return_type = val; _computeName();}


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   // Add a function parameter given its name and type.
   void
   addArgument (st::Type* ty);

   void
   addArguments (TypeVector tys);

   virtual bool
   canCastTo (Type* dest_ty) const;

   // Return the Nth parameter.
   st::Type*
   getArgument (int i) const;

   bool
   isLike (TypeVector arguments, Type* return_type);

   bool
   isLike (FunctionType* func_ty) { return isLike(Arguments(), ReturnType());}

   bool
   isOverridenCandidate (FunctionType* candidate);


   //==========================================================================
   // PROTECTED FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   void
   _computeName ();


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   TypeVector _arguments;
   Type* _return_type;
   PointerType* _functor_type;
};

} }

#endif
