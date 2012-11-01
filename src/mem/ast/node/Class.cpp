#include "mem/ast/node/Class.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Class::Class ()
{
   _nodeMembers = NULL;
   _nodeName = NULL;
   _nodeParentType = NULL;
   _type = Class::kTYPE;
}

Class::~Class ()
{
   delete _nodeMembers;
   delete _nodeName;
   delete _nodeParentType;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
Class::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _nodeName;
      case 1: return _nodeParentType;
      case 2: return _nodeMembers;
   }
   return NULL;
}

void
Class::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setMembersNode(node::cast<node::NodeList>(n)); break;
      case 1: setNameNode(n); break;
      case 2: setParentTypeNode(n); break;
   }
}

} } }
