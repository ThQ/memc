#include "mem/ast/node/For.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

For::For ()
{
   _nodeBlock = NULL;
   _nodeCondition = NULL;
   _nodeInitialization = NULL;
   _nodeIteration = NULL;
   _type = For::kTYPE;
}

For::~For ()
{
   delete _nodeBlock;
   delete _nodeCondition;
   delete _nodeInitialization;
   delete _nodeIteration;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
For::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeInitialization;
      case 1: return _nodeCondition;
      case 2: return _nodeIteration;
      case 4: return _nodeBlock;
   }
   return NULL;
}

void
For::isValid (NodeValidator* v)
{
   Node::isValid(v);

   if (ConditionNode() != NULL)
   {
      v->ensure(ConditionNode()->ExprType()->Name() == "bool",
         "For: condition node must have a bool expression type");
   }

   v->ensure(BlockNode() != NULL, "For node must have a block node");
}

void
For::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setInitializationNode(n); break;
      case 1: setConditionNode(n); break;
      case 2: setIterationNode(n); break;
      case 4: setBlockNode(node::cast<Block>(n)); break;
   }
}

} } }
