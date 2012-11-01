#include "mem/ast/node/UnaryOp.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

UnaryOp::UnaryOp ()
{
   _nodeValue = NULL;
   _type = UnaryOp::kTYPE;
}

UnaryOp::~UnaryOp ()
{
   delete _nodeValue;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
UnaryOp::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeValue;
   }
   assert(false);
   return NULL;
}

void
UnaryOp::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ValueNode() != NULL, "UnaryOp must have a value node");
}

void
UnaryOp::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setValueNode(n);
   }
   assert(false);
}

} } }
