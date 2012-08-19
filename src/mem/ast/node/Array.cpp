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

   v->ensure(ChildCount() >= 1 && ChildCount() <= 2, "ARRAY node must have 1 or 2 children");
   if (TypeNode() != NULL)
   {
      v->ensure(TypeNode()->hasBoundSymbol(), "ARRAY : type node must have a bound symbol");
   }
}

Array*
castToArray (Node* n)
{
   assert (n->isKind(Kind::ARRAY));
   return static_cast<Array*>(n);
}

} } }
