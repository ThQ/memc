#include "mem/ast/node/Class.hpp"


namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Class::Class ()
{
   _members_node = NULL;
   _name_node = NULL;
   _parent_type_node = NULL;
   _type = Class::kTYPE;
}

Class::~Class ()
{
   delete _members_node;
   delete _name_node;
   delete _parent_type_node;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Node*
Class::getChild (size_t i) const
{
   switch (i)
   {
      case 0: return _name_node;
      case 1: return _parent_type_node;
      case 2: return _members_node;
   }
   return NULL;
}

void
Class::setChild (size_t i, Node* n)
{
   switch (i)
   {
      case 0: setMembersNode(node::castToNodeList(n)); break;
      case 1: setNameNode(n); break;
      case 2: setParentTypeNode(n); break;
   }
}

} } }
