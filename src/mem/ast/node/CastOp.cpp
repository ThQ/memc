#include "mem/ast/node/CastOp.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

CastOp::CastOp ()
{
   _type = CastOp::kTYPE;
   _nodeType = NULL;
   _nodeValue = NULL;
}

CastOp::~CastOp ()
{
   delete _nodeType;
   delete _nodeValue;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
CastOp::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeValue;
      case 1: return _nodeType;
   }
   return NULL;
}

void
CastOp::isValid (NodeValidator* v)
{
   Node::isValid(v);

   v->ensure(TypeNode() != NULL, "CastOp must have a type node");
   v->ensure(ValueNode() != NULL, "CastOp must have a value node");
}

void
CastOp::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setValueNode(n); break;
      case 1: setTypeNode(n); break;
   }
}


} } }
