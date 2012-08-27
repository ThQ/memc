#include "mem/ast/node/For.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

For::For ()
{
   _block_node = NULL;
   _condition_node = NULL;
   _initialization_node = NULL;
   _iteration_node = NULL;
   _type = For::kTYPE;
}

For::~For ()
{
   delete _block_node;
   delete _condition_node;
   delete _initialization_node;
   delete _iteration_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
For::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _initialization_node;
      case 1: return _condition_node;
      case 2: return _iteration_node;
      case 4: return _block_node;
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
