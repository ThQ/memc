#ifndef _MEM__ST__PRIMITIVE_TYPE__HPP
#define _MEM__ST__PRIMITIVE_TYPE__HPP


#include "mem/st/Type.hpp"


namespace mem { namespace st {

// A base class for all primitive types : int, float, void, etc.
class PrimitiveType : public Type
{
   public:
   static const int kTYPE = MetaKind::PRIMITIVE_TYPE;

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
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
