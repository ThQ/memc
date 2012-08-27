#include "mem/ast/node/New.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

New::New ()
{
   _type = New::kTYPE;
   _type_node = NULL;
}

New::~New ()
{
   delete _type_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
New::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _type_node;
   }
   return NULL;
}

void
New::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(TypeNode() != NULL, "New must have a type node");
   v->ensure(hasExprType(), "New must have an expression type");

   if (TypeNode() != NULL)
   {
      v->ensure(TypeNode()->hasBoundSymbol(),
         "New : first child must have a bound symbol");
   }
}

void
New::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setTypeNode(n);
   }
}


} } }
