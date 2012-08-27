#include "mem/ast/node/Decorator.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Decorator::Decorator ()
{
   _name_node = NULL;
   _type = Decorator::kTYPE;
}

Decorator::~Decorator ()
{
   delete _name_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
Decorator::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _name_node;
   }
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
}

} } }
