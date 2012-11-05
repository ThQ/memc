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
   public:
   static const int kTYPE = MetaKind::ENUM_TYPE;

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

   virtual GETTER(ByteSize, int) {return ParentType() != NULL ? ParentType()->ByteSize() : -1;}

   GETTER(Type, st::Type*) {return _type;}
   SETTER(Type, st::Type*) {_type = val; _byte_size = _type->ByteSize();}


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   st::Type* _type;

};

} }


#endif
