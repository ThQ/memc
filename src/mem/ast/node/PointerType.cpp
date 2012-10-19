#include "mem/ast/node/PointerType.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

PointerType::PointerType ()
{
   _type = PointerType::kTYPE;
   _type_node = NULL;
}

PointerType::~PointerType ()
{
   delete _type_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
PointerType::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _type_node;
   }
   return NULL;
}

void
PointerType::isValid (NodeValidator* v)
{
   Node::isValid(v);

   v->ensure(TypeNode() != NULL, "Ptr must have a type node");
}

void
PointerType::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setTypeNode(n); break;
   }
}


} } }
