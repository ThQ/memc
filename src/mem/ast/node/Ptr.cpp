#include "mem/ast/node/Ptr.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Ptr::Ptr ()
{
   _type = Ptr::kTYPE;
   _type_node = NULL;
}

Ptr::~Ptr ()
{
   delete _type_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
Ptr::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _type_node;
   }
   return NULL;
}

void
Ptr::isValid (NodeValidator* v)
{
   Node::isValid(v);

   v->ensure(TypeNode() != NULL, "Ptr must have a type node");
}

void
Ptr::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setTypeNode(n); break;
   }
}


} } }
