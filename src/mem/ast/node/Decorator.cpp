#include "mem/ast/node/Decorator.hpp"


namespace mem { namespace ast { namespace node {


Decorator::Decorator ()
{
   _type = Kind::DECORATOR;
}

void
Decorator::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Validate something !
}

} } }
