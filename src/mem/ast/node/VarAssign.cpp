#include "mem/ast/node/VarAssign.hpp"

namespace mem { namespace ast { namespace node {


VarAssign::VarAssign ()
{
   _type = MEM_NODE_VARIABLE_ASSIGNMENT;
}


void
VarAssign::isValid (NodeValidator* v)
{
   // Check self
   Node::isValid(v);
   v->ensure(gChildCount() == 2, "VarAssign must have exactly 2 children");
   v->ensure(hasExprType(), "VarAssign must have an expression type");
   v->ensure(hasBoundSymbol(), "VarAssign must have an expression type");

   // Check NAME node
   if (gNameNode() != NULL)
   {
      v->ensure(gNameNode()->hasBoundSymbol(), "VarAssign : Name node must have a bound symbol");
      v->ensure(gNameNode()->hasExprType(), "VarAssign : Name node must have an expression type");
   }

   if (gValueNode() != NULL)
   {
      // Check VALUE node
      v->ensure(gValueNode()->hasExprType(), "VarAssign : Value node must have an expression type");

      // TODO Should check that the var type and the value type have the expr type.
      // Take care of pointers.
   }
}

} } }
