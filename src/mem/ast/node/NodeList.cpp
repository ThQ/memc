#include "mem/ast/node/NodeList.hpp"

namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

NodeList::NodeList ()
{
   _type = Kind::NODE_LIST;
}

NodeList::~NodeList ()
{
   for (size_t i = 0; i < ChildCount(); ++i)
   {
      delete _children[i];
   }
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
NodeList::addChild (Node* n)
{
   if (n != NULL)
   {
      _children.push_back(n);
      n->setParent(this);
   }
}

void
NodeList::eat (NodeList* n)
{
   Node* cur_n = NULL;
   for (size_t i = 0; i < n->ChildCount(); ++i)
   {
      cur_n = n->getChild(i);
      cur_n->setParent(this);
      this->addChild(cur_n);
   }
}

Node*
NodeList::getChild(size_t i) const
{
   return _children[i];
}

void
NodeList::insertChild (Node* n)
{
   _children.insert(_children.begin(), n);
}

NodeList*
castToNodeList (Node* n)
{
   assert(n != NULL && n->isKind(Kind::NODE_LIST));
   return static_cast<NodeList*>(n);
}


} } }
