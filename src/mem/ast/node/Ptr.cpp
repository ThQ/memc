#include "mem/ast/node/Ptr.hpp"


namespace mem { namespace ast { namespace node {


Ptr::Ptr ()
{
   _type = Kind::POINTER;
}

void
Ptr::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Validate something here
}


} } }
