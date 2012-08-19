#include "mem/ast/node/Dot.hpp"


namespace mem { namespace ast { namespace node {


Dot::Dot ()
{
   _type = Kind::DOT;
}

void
Dot::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Validate the number of children (2) of their types
}

Dot*
castToDot (Node* n)
{
   assert (n->isDotNode());
   return static_cast<Dot*>(n);
}
} } }
