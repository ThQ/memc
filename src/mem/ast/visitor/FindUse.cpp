#include "mem/ast/visitor/FindUse.hpp"

namespace mem { namespace ast { namespace visitor {


FindUse::FindUse ()
{
   this->_name = "FindUser";
}

bool
FindUse::visit (node::Node* node)
{
   if (node->_type == MEM_NODE_USE)
   {
      node::Text* text_node = static_cast<node::Text*>(node);
      this->_uses.push_back(text_node->_value);
   }
   return true;
}


} } }
