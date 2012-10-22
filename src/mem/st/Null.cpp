#include "mem/st/Null.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Null::Null ()
{
   _kind = Null::kTYPE;
   _name = "NULL";
}

} }
