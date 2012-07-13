#include "mem/ast/node/VarDecl.hpp"

namespace mem { namespace ast { namespace node {


VarDecl::VarDecl ()
{
   _type = MEM_NODE_VARIABLE_DECLARATION;
}


void
VarDecl::isValid (NodeValidator* v)
{
   // Check self
   Node::isValid(v);
   v->ensure(gChildCount() <= 3, "VarDecl must have at most 3 children");
   v->ensure(hasExprType(), "VarDecl must have an expression type");
   v->ensure(hasBoundSymbol(), "VarDecl must have a bound symbol");

   if (gNameNode() != NULL)
   {
      // Check NAME node
      v->ensure(gNameNode()->hasBoundSymbol(), "VarDecl : Name node must have a bound symbol");
   }

   if (gTypeNode() != NULL)
   {
      // Check TYPE node
      v->ensure(gTypeNode()->hasExprType(), "VarDecl : Type node must have an expression type");
      v->ensure(gTypeNode()->hasBoundSymbol(), "VarDecl : Type node must have a bound symbol");
   }
}

} } }
