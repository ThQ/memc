#include "mem/ast/node/If.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

If::If ()
{
   _nodeCondition = NULL;
   _nodeElseBlock = NULL;
   _nodeIfBlock = NULL;
   _type = If::kTYPE;
}

If::~If ()
{
   delete _nodeCondition;
   delete _nodeIfBlock;
   delete _nodeElseBlock;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
If::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeCondition;
      case 1: return _nodeIfBlock;
      case 2: return _nodeElseBlock;
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
