#include "mem/ast/node/VarDecl.hpp"

namespace mem { namespace ast { namespace node {


VarDecl::VarDecl ()
{
   _type = Kind::VARIABLE_DECLARATION;
}


void
VarDecl::isValid (NodeValidator* v)
{
   // Check self
   Node::isValid(v);
   v->ensure(ChildCount() <= 3, "VarDecl must have at most 3 children");
   v->ensure(hasExprType(), "VarDecl must have an expression type");
   v->ensure(hasBoundSymbol(), "VarDecl must have a bound symbol");

   if (NameNode() != NULL)
   {
      // Check NAME node
      v->ensure(NameNode()->hasBoundSymbol(), "VarDecl : Name node must have a bound symbol");
      v->ensure(NameNode()->isIdNode(), "VarDecl : Name node must be an ID");
   }

   if (TypeNode() != NULL)
   {
      // Check TYPE node
      v->ensure(TypeNode()->hasExprType(), "VarDecl : Type node must have an expression type");
      v->ensure(TypeNode()->hasBoundSymbol(), "VarDecl : Type node must have a bound symbol");
   }
}

} } }
