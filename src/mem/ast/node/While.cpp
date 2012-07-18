#include "mem/ast/node/While.hpp"


namespace mem { namespace ast { namespace node {


While::While ()
{
   _type = Kind::WHILE;
}

void
While::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ChildCount() == 2, "While must have exactly 2 children");
}


} } }
