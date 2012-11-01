#include "mem/ast/node/Id.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Id::Id ()
{
   _type = Id::kTYPE;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
Id::copy () const
{
   Id* n = new Id ();
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
Id::isValid (NodeValidator* v)
{
   Node::isValid(v);
}


} } }
