#include "mem/st/IntConstant.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------
IntConstant::IntConstant ()
{
   _kind = IntConstant::kTYPE;
   _is_signed = false;
   _type = NULL;
}


} }
