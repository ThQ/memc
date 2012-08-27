#include "mem/ast/node/Use.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Use::Use ()
{
   _type = Use::kTYPE;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
Use::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ChildCount() == 0, "Use cannot have children");
}


} } }
