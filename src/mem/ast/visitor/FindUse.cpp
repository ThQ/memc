#include "mem/ast/visitor/FindUse.hpp"


namespace mem { namespace ast { namespace visitor {


FindUse::FindUse ()
{
   _name = "FindUse";
}

bool
FindUse::visit (node::Node* node)
{
   if (node->isUseNode())
   {
      node::Text* text_node = static_cast<node::Text*>(node);
      _uses.push_back(text_node->gValue());
   }
   return true;
}


} } }
