#ifndef _MEM__ST__VOID_TYPE__HPP_
#define _MEM__ST__VOID_TYPE__HPP_


#include "mem/st/Type.hpp"


namespace mem { namespace st {

// A base class for the type of the NULL constant.
class VoidType : public Type
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTORS
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   VoidType();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual bool
   canCastTo (class Type* dest_ty) const;
};

} }


#endif
