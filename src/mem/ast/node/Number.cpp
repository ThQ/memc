#include "mem/ast/node/Number.hpp"


namespace mem { namespace ast { namespace node {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Number::Number ()
{
   _type = Kind::NUMBER;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
Number::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ChildCount() == 0, "Number cannot have children");
   v->ensure(hasExprType(), "Number must have an expression type");
   v->ensure(hasBoundSymbol(), "Number must be bounded (to constant symbol)");
}

} } }
