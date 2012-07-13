#include "mem/ast/node/Use.hpp"


namespace mem { namespace ast { namespace node {


Use::Use ()
{
   _type = MEM_NODE_USE;
}


void
Use::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(gChildCount() == 0, "Use cannot have children");
}


} } }
