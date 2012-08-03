#include "mem/st/IntType.hpp"

namespace mem { namespace st {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

IntType::IntType ()
{
   _kind = INT_TYPE;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
IntType::canCastTo (Type* dest_ty) const
{
   DEBUG_REQUIRE (dest_ty);

   if (dest_ty->isIntType() && dest_ty->hasByteSize())
   {
      return ByteSize() <= dest_ty->ByteSize();
   }
   return false;
}


} }
