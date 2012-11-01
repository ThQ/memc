#include "mem/ast/node/VarAssign.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

VarAssign::VarAssign ()
{
   _nodeName = NULL;
   _nodeValue = NULL;
   _type = VarAssign::kTYPE;
}

VarAssign::~VarAssign ()
{
   delete _nodeName;
   delete _nodeValue;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
VarAssign::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeName;
      case 1: return _nodeValue;
   }
   assert(false);
   return NULL;
}

void
VarAssign::isValid (NodeValidator* v)
{
   // Check self
   Node::isValid(v);
   v->ensure(ChildCount() == 2, "VarAssign must have exactly 2 children");
   v->ensure(hasExprType(), "VarAssign must have an expression type");

   // Check NAME node
   v->ensure(NameNode() != NULL, "VarAssign must have a name node");
   if (NameNode() != NULL)
   {
      v->ensure(NameNode()->hasExprType(), "VarAssign : Name node must have an expression type");
   }

   if (ValueNode() != NULL)
   {
      // Check VALUE node
      v->ensure(ValueNode()->hasExprType(), "VarAssign : Value node must have an expression type");

      // TODO Should check that the var type and the value type have the expr type.
      // Take care of pointers.
   }
}

void
VarAssign::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setNameNode(n); break;
      case 1: setValueNode(n); break;
   }
   assert(false);
}


} } }
