#include "mem/ast/node/Call.hpp"

namespace mem { namespace ast { namespace node {

Call::Call ()
{
   _type = MEM_NODE_CALL;
}

void
Call::isValid (NodeValidator* v)
{
   // Check SELF
   Node::isValid(v);
   v->ensure(gChildCount() <= 2, "Call cannot have more than 2 children");
   v->ensure(hasExprType(), "Call must have an expression type");

   // Check CALLER node
   v->ensure(CallerNode() != NULL, "Call must have a caller node");
   if (CallerNode() != NULL)
   {
      v->ensure(CallerNode()->hasExprType(), "CallerNode must have an expression type");
      v->ensure(CallerNode()->hasBoundSymbol(), "Caller node must have a bound symbol");
   }
}

} } }
