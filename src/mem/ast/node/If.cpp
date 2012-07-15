#include "mem/ast/node/If.hpp"


namespace mem { namespace ast { namespace node {


If::If ()
{
   _type = MEM_NODE_IF;
}

void
If::isValid (NodeValidator* v)
{
   Node::isValid(v);

   v->ensure(hasConditionNode(), "If must have a condition node");

   if (hasConditionNode())
   {
      v->ensure(gConditionNode()->hasExprType(),
         "If : condition node must have an expression type");

      if (gConditionNode()->hasExprType())
      {
         v->ensure(gConditionNode()->gExprType()->gName() == "bool",
            "If : condition node must have bool type");
      }
   }
}

} } }
