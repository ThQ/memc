#include "mem/ast/node/Call.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Call::Call ()
{
   _caller = NULL;
   _caller_node = NULL;
   _is_instance_call = false;
   _params_node = NULL;
   _type = Call::kTYPE;
}

Call::~Call ()
{
   delete _caller_node;
   delete _params_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
Call::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _caller_node;
      case 1: return _params_node;
   }
   return NULL;
}

void
Call::insertParam (Node* node)
{
   if (ParamsNode() == NULL)
   {
      node::NodeList* params = new node::NodeList();
      setParamsNode(params);
   }
   ParamsNode()->insertChild(node);
}

void
Call::isValid (NodeValidator* v)
{
   // Check SELF
   Node::isValid(v);
   v->ensure(hasExprType(), "Call must have an expression type");

   // Check CALLER node
   v->ensure(CallerNode() != NULL, "Call must have a caller node");
   if (CallerNode() != NULL)
   {
      v->ensure(CallerNode()->hasExprType(), "CallerNode must have an expression type");
      v->ensure(CallerNode()->hasBoundSymbol(), "Caller node must have a bound symbol");
   }
}

void
Call::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setCallerNode(n); break;
      case 1: setParamsNode(node::cast<node::NodeList>(n)); break;
   }
}


} } }
