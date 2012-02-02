#include "mem/ast/visitor/Visitor.hpp"

namespace mem { namespace ast { namespace visitor {


bool
Visitor::visit (node::Node* node)
{
   return false;
}

void
Visitor::visit_preorder (node::Node* node)
{
   if (this->visit(node))
   {
      node::Node* child_node = node->_first_child;
      while (child_node != NULL)
      {
         this->visit_preorder(child_node);
         child_node = child_node->_next;
      }
   }
}


} } }
