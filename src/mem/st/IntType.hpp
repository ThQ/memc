#ifndef _MEM__ST__INT_TYPE__HPP
#define _MEM__ST__INT_TYPE__HPP


#include "mem/st/PrimitiveType.hpp"


namespace mem { namespace st {


// A base class for signed integer types.
class IntType : public PrimitiveType
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Default constructor.
   IntType ();

   // Construct an integer type given its name and size.
   IntType (std::string name, int size);


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual bool
   canCastTo(Type* dest_ty) const;
};


} }

#endif
