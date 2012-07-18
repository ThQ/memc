#include "mem/ast/node/If.hpp"


namespace mem { namespace ast { namespace node {


If::If ()
{
   _type = Kind::IF;
}

void
If::isValid (NodeValidator* v)
{
   Node::isValid(v);

   v->ensure(hasConditionNode(), "If must have a condition node");

   if (hasConditionNode())
   {
      v->ensure(ConditionNode()->hasExprType(),
         "If : condition node must have an expression type");

      if (ConditionNode()->hasExprType())
      {
         v->ensure(ConditionNode()->ExprType()->Name() == "bool",
            "If : condition node must have bool type");
      }
   }
}

} } }
