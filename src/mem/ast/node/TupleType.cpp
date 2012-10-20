#include "mem/ast/node/TupleType.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

TupleType::TupleType ()
{
   _type = TupleType::kTYPE;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
TupleType::addChild (Node* n)
{
   if (n != NULL)
   {
      _types.push_back(n);
      n->setParent(this);
   }
}

Node*
TupleType::getChild (size_t i) const
{
   return _types[i];
}

void
TupleType::insertChild (Node* n)
{
   _types.insert(_types.begin(), n);
}

} } }
