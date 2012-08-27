#include "mem/ast/node/String.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

String::String ()
{
   _type = String::kTYPE;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
String::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ChildCount() == 0, "[String] cannot have children");
   v->ensure(hasExprType(), "[String] must have an expression type");
}


} } }
