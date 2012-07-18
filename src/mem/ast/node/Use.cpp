#include "mem/ast/node/Use.hpp"


namespace mem { namespace ast { namespace node {


Use::Use ()
{
   _type = Kind::USE;
}


void
Use::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ChildCount() == 0, "Use cannot have children");
}


} } }
