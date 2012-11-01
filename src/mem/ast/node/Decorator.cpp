#include "mem/ast/node/Decorator.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Decorator::Decorator ()
{
   _nodeName = NULL;
   _type = Decorator::kTYPE;
}

Decorator::~Decorator ()
{
   delete _nodeName;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
Decorator::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeName;
   }
   assert(false);
   return NULL;
}

void
Decorator::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Validate something !
}

void
Decorator::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setNameNode(n); break;
   }
   assert(false);
}

} } }
