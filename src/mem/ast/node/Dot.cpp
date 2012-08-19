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

   v->ensure(ChildCount() == 2, "Dot must have exactly 2 children");
   if (ChildCount() == 2)
   {
      v->ensure(LeftNode()->isDotNode() || LeftNode()->isFinalIdNode(),
         "Left node must be either a DOT node or an ID node");
   }
}

Dot*
castToDot (Node* n)
{
   assert (n->isDotNode());
   return static_cast<Dot*>(n);
}
} } }
