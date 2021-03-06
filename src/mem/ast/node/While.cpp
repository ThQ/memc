#include "mem/ast/node/While.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

While::While ()
{
   _nodeBlock = NULL;
   _nodeCondition = NULL;
   _type = While::kTYPE;
}

While::~While ()
{
   delete _nodeBlock;
   delete _nodeCondition;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
While::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeCondition;
      case 1: return _nodeBlock;
   }
   assert(false);
   return NULL;
}

void
While::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ChildCount() == 2, "While must have exactly 2 children");

   if (ConditionNode() != NULL)
   {
      v->ensure(ConditionNode()->ExprType()->Name() == "bool",
         "While: condition node must have a bool expression type");
   }

   v->ensure(BlockNode() != NULL, "While node must have a block node");
}

void
While::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setConditionNode(n); break;
      case 1: setBlockNode(node::cast<Block>(n)); break;
   }
   assert(false);
}


} } }
