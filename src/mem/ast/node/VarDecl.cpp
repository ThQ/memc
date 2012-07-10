#include "mem/ast/node/VarDecl.hpp"

namespace mem { namespace ast { namespace node {


VarDecl::VarDecl ()
{
   _type = MEM_NODE_VARIABLE_DECLARATION;
}


bool
VarDecl::isValid ()
{
   // Check self
   NODE_ENSURE( Node::isValid() )
   NODE_ENSURE( gChildCount() <= 3 )
   NODE_ENSURE( hasExprType() )
   NODE_ENSURE( hasBoundSymbol() )

   // Check NAME node
   NODE_ENSURE( gNameNode()->hasBoundSymbol() )

   // Check TYPE node
   NODE_ENSURE( gTypeNode()->hasExprType() )
   NODE_ENSURE( gTypeNode()->hasBoundSymbol() )

   return true;
}

} } }
