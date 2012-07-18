#include "mem/ast/node/Return.hpp"


namespace mem { namespace ast { namespace node {


Return::Return ()
{
   _type = Kind::RETURN;
}


void
Return::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ChildCount() == 1, "Return must have exactly 1 child");
}


} } }
