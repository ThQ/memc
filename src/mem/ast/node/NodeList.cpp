#include "mem/ast/node/NodeList.hpp"

namespace mem { namespace ast { namespace node {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

NodeList::NodeList ()
{
   _type = NodeList::kTYPE;
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
      DEBUG_REQUIRE (n != this);
      DEBUG_REQUIRE (n != this->Parent());

      _children.push_back(n);
      n->setParent(this);

      assert(_checkCircularDependencies());
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
NodeList::getChild (size_t i) const
{
   return _children[i];
}

void
NodeList::insertChild (Node* n)
{
   _children.insert(_children.begin(), n);
}


} } }
