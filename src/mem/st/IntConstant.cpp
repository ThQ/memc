#include "mem/st/IntConstant.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------
IntConstant::IntConstant ()
{
   _kind = INT_CONSTANT;
   _is_signed = false;
   _type = NULL;
}


//-----------------------------------------------------------------------------
// STATIC FUNCTIONS
//-----------------------------------------------------------------------------

IntConstant*
castToIntConstant (Symbol* s)
{
   assert (s != NULL);
   assert (s->isIntConstant());
   return static_cast<IntConstant*>(s);
}

} }
