#include "mem/ast/node/For.hpp"


namespace mem { namespace ast { namespace node {


For::For ()
{
   _type = Kind::FOR;
}

void
For::isValid (NodeValidator* v)
{
   Node::isValid(v);

   if (ConditionNode() != NULL)
   {
      v->ensure(ConditionNode()->ExprType()->Name() == "bool",
         "For: condition node must have a bool expression type");
   }

   v->ensure(BlockNode() != NULL, "For node must have a block node");
}

} } }
