#include "mem/ast/node/New.hpp"


namespace mem { namespace ast { namespace node {


New::New ()
{
   _type = Kind::NEW;
}


void
New::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ChildCount() == 1, "New must have exactly 1 child");
   v->ensure(hasExprType(), "New must have an expression type");

   if (ChildCount() == 1)
   {
      v->ensure(getChild(0)->hasBoundSymbol(),
         "New : first child must have a bound symbol");
   }
}


} } }
