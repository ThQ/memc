#ifndef _MEM__ST__ARRAY__HPP_
#define _MEM__ST__ARRAY__HPP_


#include "mem/st/Type.hpp"


namespace mem { namespace st {


class Array : public Type
{
   protected:

   st::Type* _base_type;
   int _array_length;

   // -------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   // -------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Array();


   GETTER(BaseType, st::Type*) {return _base_type;}
   SETTER(BaseType, st::Type*) {_base_type = val;}

   GETTER (ArrayLength, int) {return _array_length;}
   SETTER (ArrayLength, int) {_array_length = val;}


   // -------------------------------------------------------------------------
   // PUBLIC METHODS
   // -------------------------------------------------------------------------
   public:

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Array");return false;}
};

} }


#endif
