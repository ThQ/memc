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
   v->ensure(gCallerNode() != NULL, "Call must have a caller node");
   if (gCallerNode() != NULL)
   {
      v->ensure(gCallerNode()->hasExprType(), "CallerNode must have an expression type");
      v->ensure(gCallerNode()->hasBoundSymbol(), "Caller node must have a bound symbol");
   }
}

} } }
