#include "mem/ast/node/Call.hpp"

namespace mem { namespace ast { namespace node {

Call::Call ()
{
   _caller = NULL;
   _is_instance_call = false;
   _type = Kind::CALL;
}

void
Call::insertParam (Node* node)
{
   assert(ChildCount() >= 1);

   if (ParamsNode() == NULL)
   {
      node::Node* params = new node::Node();
      params->setKind(Kind::EXPRESSION_LIST);
      pushChild(params);
      assert (ChildCount() == 2);
   }
   ParamsNode()->insertChild(node);
}

void
Call::isValid (NodeValidator* v)
{
   // Check SELF
   Node::isValid(v);
   v->ensure(ChildCount() <= 2, "Call cannot have more than 2 children");
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
