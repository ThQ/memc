#include "mem/ast/visitor/Prechecker.hpp"


namespace mem { namespace ast { namespace visitor {


Prechecker::Prechecker ()
{
   this->_name = "Prechecker";
}

bool
Prechecker::visit (node::Node* node)
{
   if (node->_position == NULL && node->_type != MEM_NODE_ROOT && node->_type != MEM_NODE_FILE)
   {
      this->_logger->warning("Node(%s) has no position", node::Node::get_type_name(node->_type));
   }

   if (node->_type == 0)
   {
      this->_logger->warning("Node has an unknown type", "");
   }

   if (node->_type != MEM_NODE_ROOT && node->_parent == NULL)
   {
      this->_logger->warning("Node(%s) has no parent", node::Node::get_type_name(node->_type));
   }
   return true;
}


} } }
