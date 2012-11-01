#include "mem/ast/node/PointerType.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

PointerType::PointerType ()
{
   _nodeType = NULL;
   _type = PointerType::kTYPE;
}

PointerType::~PointerType ()
{
   delete _nodeType;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
PointerType::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeType;
   }
   assert(false);
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
   assert(false);
}


} } }
