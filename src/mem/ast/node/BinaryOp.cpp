#include "mem/ast/node/BinaryOp.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

BinaryOp::BinaryOp ()
{
   _left_node = NULL;
   _right_node = NULL;
   _type = BinaryOp::kTYPE;
}

BinaryOp::~BinaryOp ()
{
   delete _left_node;
   delete _right_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
BinaryOp::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _left_node;
      case 1: return _right_node;
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
      case 0: _left_node = n; break;
      case 1: _right_node = n; break;
   }
}


} } }
