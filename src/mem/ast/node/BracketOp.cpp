#include "mem/ast/node/BracketOp.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

BracketOp::BracketOp ()
{
   _nodeIndex = NULL;
   _nodeValue = NULL;
   _type = BracketOp::kTYPE;
}

BracketOp::~BracketOp ()
{
   delete _nodeIndex;
   delete _nodeValue;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
BracketOp::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeValue;
      case 1: return _nodeIndex;
   }
   return NULL;
}

void
BracketOp::isValid (NodeValidator* v)
{
   Node::isValid(v);

   // FIXME Validate the number of children (2)
}

void
BracketOp::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setValueNode(n); break;
      case 1: setIndexNode(n); break;
   }
}


} } }
