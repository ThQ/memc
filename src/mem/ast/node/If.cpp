#include "mem/ast/node/If.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

If::If ()
{
   _condition_node = NULL;
   _else_block_node = NULL;
   _if_block_node = NULL;
   _type = If::kTYPE;
}

If::~If ()
{
   delete _condition_node;
   delete _if_block_node;
   delete _else_block_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
If::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _condition_node;
      case 1: return _if_block_node;
      case 2: return _else_block_node;
   }
   return NULL;
}

void
If::isValid (NodeValidator* v)
{
   Node::isValid(v);

   v->ensure(hasConditionNode(), "If must have a condition node");

   if (hasConditionNode())
   {
      v->ensure(ConditionNode()->hasExprType(),
         "If : condition node must have an expression type");

      if (ConditionNode()->hasExprType())
      {
         v->ensure(ConditionNode()->ExprType()->Name() == "bool",
            "If : condition node must have bool type");
      }
   }
}

void
If::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setConditionNode(n); break;
      case 1: setIfBlockNode(node::cast<Block>(n)); break;
      case 2: setElseBlockNode(node::cast<Block>(n)); break;
   }
}


} } }
