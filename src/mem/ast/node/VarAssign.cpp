#include "mem/ast/node/VarAssign.hpp"

namespace mem { namespace ast { namespace node {


VarAssign::VarAssign ()
{
   _type = MEM_NODE_VARIABLE_ASSIGNMENT;
}


bool
VarAssign::isValid ()
{
   // Check self
   NODE_ENSURE( Node::isValid() )
   NODE_ENSURE( gChildCount() == 2 )
   NODE_ENSURE( hasExprType() )
   NODE_ENSURE( hasBoundSymbol() )

   // Check NAME node
   NODE_ENSURE( gNameNode()->hasBoundSymbol() )
   NODE_ENSURE( gNameNode()->hasExprType() )

   // Check VALUE node
   NODE_ENSURE( gValueNode()->hasExprType() )

   // TODO Should check that the var type and the value type have the expr type.
   // Take care of pointers.

   return true;
}

} } }
