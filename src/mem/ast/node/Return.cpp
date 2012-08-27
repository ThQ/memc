#include "mem/ast/node/Return.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Return::Return ()
{
   _type = Return::kTYPE;
   _value_node = NULL;
}

Return::~Return ()
{
   delete _value_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
Return::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _value_node;
   }
   return NULL;
}

void
Return::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ValueNode() != NULL, "Return must have a value node");
}

void
Return::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setValueNode(n); break;
   }
}


} } }
