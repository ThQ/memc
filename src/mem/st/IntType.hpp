#ifndef _MEM__ST__INT_TYPE__HPP
#define _MEM__ST__INT_TYPE__HPP


#include "mem/st/PrimitiveType.hpp"


namespace mem { namespace st {


/**
 * A base class for signed integer types.
 */
class IntType : public PrimitiveType
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   IntType ();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTION
   //--------------------------------------------------------------------------
   public:

   virtual bool
   canCastTo(Type* dest_ty) const;
};


} }

#endif
