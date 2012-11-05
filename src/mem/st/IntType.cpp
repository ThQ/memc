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
IntType::canCastTo (Type* symDestType) const
{
   DEBUG_REQUIRE (symDestType != NULL);

   if (st::isa<st::IntType>(symDestType))
   {
      return symDestType->hasByteSize() && ByteSize() <= symDestType->ByteSize();
   }
   return false;
}


} }
