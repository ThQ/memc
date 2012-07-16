#include "mem/ast/node/Dot.hpp"


namespace mem { namespace ast { namespace node {


Dot::Dot ()
{
   _type = MEM_NODE_DOT;
}

void
Dot::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Validate the number of children (2) of their types
}

} } }
