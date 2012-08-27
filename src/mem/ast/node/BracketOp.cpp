#include "mem/ast/node/BracketOp.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

BracketOp::BracketOp ()
{
   _index_node = NULL;
   _type = BracketOp::kTYPE;
   _value_node = NULL;
}

BracketOp::~BracketOp ()
{
   delete _index_node;
   delete _value_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
BracketOp::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _value_node;
      case 1: return _index_node;
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
      case 0: _value_node = n; break;
      case 1: _index_node = n; break;
   }
}


} } }
