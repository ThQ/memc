#include "mem/st/IntType.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

IntType::IntType ()
{
   _kind = IntType::kTYPE;
}

IntType::IntType (std::string name, int byte_size)
{
   _kind = IntType::kTYPE;
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

   if (st::isa<st::IntType>(dest_ty) && dest_ty->hasByteSize())
   {
      return ByteSize() <= dest_ty->ByteSize();
   }
   return false;
}


} }
