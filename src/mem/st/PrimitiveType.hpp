#ifndef _MEM__ST__PRIMITIVE_TYPE__HPP
#define _MEM__ST__PRIMITIVE_TYPE__HPP


#include "mem/st/Type.hpp"


namespace mem { namespace st {


class PrimitiveType : public Type
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   PrimitiveType ();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual inline bool
   addChild (Symbol* s) {assert(false && "Cannot add child to Primitive");return false;}
};


} }

#endif
