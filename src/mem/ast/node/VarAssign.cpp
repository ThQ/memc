#include "mem/ast/node/VarAssign.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

VarAssign::VarAssign ()
{
   _name_node = NULL;
   _type = VarAssign::kTYPE;
   _value_node = NULL;
}

VarAssign::~VarAssign ()
{
   delete _name_node;
   delete _value_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
VarAssign::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _name_node;
      case 1: return _value_node;
   }
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
}


} } }
