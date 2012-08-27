#include "mem/ast/node/Dot.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Dot::Dot ()
{
   _type = Dot::kTYPE;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
Dot::isValid (NodeValidator* v)
{
   BinaryOp::isValid(v);
}

} } }
