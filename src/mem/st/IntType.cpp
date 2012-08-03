#include "mem/st/IntType.hpp"

namespace mem { namespace st {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

IntType::IntType ()
{
   _kind = INT_TYPE;
}

IntType::IntType (std::string name, int byte_size)
{
   _kind = INT_TYPE;
   setName(name);
   setByteSize(byte_size);
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
