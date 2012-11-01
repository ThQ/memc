#include "mem/ast/node/Return.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Return::Return ()
{
   _nodeValue = NULL;
   _type = Return::kTYPE;
}

Return::~Return ()
{
   delete _nodeValue;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
Return::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeValue;
   }
   assert(false);
   return NULL;
}

void
Return::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ValueNode() != NULL, "Return must have a value node");
}

void
Return::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setValueNode(n); break;
   }
   assert(false);
}


} } }
