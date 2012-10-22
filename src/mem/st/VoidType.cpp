#include "mem/st/VoidType.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

VoidType::VoidType ()
{
   _kind = VoidType::kTYPE;
   _name = "void";
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
VoidType::canCastTo (class Type* dest_ty) const
{
   return true;
}

} }
