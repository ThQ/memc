#ifndef _MEM__ST__ARRAY__HPP_
#define _MEM__ST__ARRAY__HPP_


#include "mem/st/Type.hpp"


namespace mem { namespace st {


// A base class for Array types.
//
// If an array type has a length, then it is staticaly declared, ortherwise it
// is dynamicaly allocated.
class ArrayType : public Type
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   ArrayType();


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(ItemType, st::Type*) {return _item_type;}
   SETTER(ItemType, st::Type*) {_item_type = val; _computeByteSize();}

   GETTER (ArrayLength, int) {return _array_length;}
   SETTER (ArrayLength, int) {_array_length = val; _computeByteSize();}


   //--------------------------------------------------------------------------
   // PUBLIC METHODS
   //--------------------------------------------------------------------------
   public:

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Array");return false;}

   virtual bool
   canCastTo (Type* dest_ty) const;

   // Return true if the array is sized (staticaly allocated).
   bool
   hasLength() const {return _array_length != -1;}

   bool
   isArrayOfClassInstances () const { return _item_type->isClassType(); }


   //--------------------------------------------------------------------------
   // PROTECTED FUNCTIONS
   //--------------------------------------------------------------------------
   protected:

   void
   _computeByteSize();


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   st::Type* _item_type;
   int _array_length;

};

} }


#endif
