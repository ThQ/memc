#include "mem/ast/node/FinalId.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

FinalId::FinalId ()
{
   _type = FinalId::kTYPE;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
FinalId::copy () const
{
   FinalId* n = new FinalId ();
   n->setValue(Value());
   n->setBoundSymbol(BoundSymbol());
   n->setExprType(ExprType());
   if (Position() != NULL)
   {
      n->setPosition(Position()->copy_range());
   }
   return n;
}

void
FinalId::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ChildCount() == 0, "FinalId cannot have children");
   //v->ensure(hasExprType(), "FinalId must have an expression type");
   //v->ensure(hasBoundSymbol(), "FinalId must have a bound symbol");
}

} } }
