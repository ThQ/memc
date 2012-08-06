#include "mem/st/Macro.hpp"


namespace mem { namespace st {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------
Macro::Macro ()
{
   _kind = MACRO;
   _macro_expander = NULL;
}


} }
