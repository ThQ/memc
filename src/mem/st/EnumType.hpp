#ifndef _MEM__ST__ENUM_TYPE__HPP_
#define _MEM__ST__ENUM_TYPE__HPP_


#include "mem/st/Type.hpp"


namespace mem { namespace st {


// A base class for Array types.
//
// If an array type has a length, then it is staticaly declared, ortherwise it
// is dynamicaly allocated.
class EnumType : public Type
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   EnumType();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(Type, st::Type*) {return _type;}
   SETTER(Type, st::Type*) {_type = val; _byte_size = _type->ByteSize();}

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual bool
   canCastTo (class Type* dest_ty) const {return dest_ty == this;}


   //--------------------------------------------------------------------------
   // PROTECTED FUNCTIONS
   //--------------------------------------------------------------------------
   protected:


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   st::Type* _type;

};

} }


#endif
