#include "mem/ast/node/Enum.hpp"


namespace mem { namespace ast { namespace node {


Enum::Enum ()
{
   _type = Kind::ENUM;
}

void
Enum::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Validate something here
}


} } }
