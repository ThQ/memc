#include "mem/st/Constant.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Constant::Constant ()
{
   _kind = Constant::kTYPE;
   _type = NULL;
}

} }
