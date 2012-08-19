#include "mem/ast/node/Array.hpp"


namespace mem { namespace ast { namespace node {


Array::Array ()
{
   _type = Kind::ARRAY;
}

void
Array::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Validate something here
}

Array*
castToArray (Node* n)
{
   assert (n->isKind(Kind::ARRAY));
   return static_cast<Array*>(n);
}

} } }
