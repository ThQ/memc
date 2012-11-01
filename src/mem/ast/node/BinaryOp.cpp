#include "mem/ast/node/BinaryOp.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

BinaryOp::BinaryOp ()
{
   _nodeLeft = NULL;
   _nodeRight = NULL;
   _type = BinaryOp::kTYPE;
}

BinaryOp::~BinaryOp ()
{
   delete _nodeLeft;
   delete _nodeRight;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
BinaryOp::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeLeft;
      case 1: return _nodeRight;
   }
   return NULL;
}

void
BinaryOp::isValid (NodeValidator* v)
{
   Node::isValid(v);

   v->ensure(LeftNode() != NULL, "BinaryOp must have a left node");
   v->ensure(RightNode() != NULL, "BinaryOp must have a right node");
}

void
BinaryOp::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setLeftNode(n); break;
      case 1: setRightNode(n); break;
   }
}


} } }
