#include "mem/ast/node/Use.hpp"


namespace mem { namespace ast { namespace node {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Use::Use ()
{
   _type = Use::kTYPE;
   _nodeId = NULL;
}

Use::~Use ()
{
   delete _nodeId;
}

//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
Use::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeId;
   }
   assert(false);
   return NULL;
}

void
Use::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ChildCount() == 1, "Use must have exactly 1 child");
}


void
Use::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setIdNode(node::cast<node::FinalId>(n)); break;
   }
   assert(false);
}

} } }
