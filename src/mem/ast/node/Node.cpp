#include "mem/ast/node/Node.hpp"

namespace mem { namespace ast { namespace node {


Node::Node ()
{
   this->_accept_children = false;
   this->_depth = 0;
   this->_expected_child_count = -1;
   this->_first_child = 0;
   this->_last_child = 0;
   this->_next = 0;
   this->_parent = 0;
   this->_position = NULL;
   this->_prev = 0;
   this->_type = 0;
   this->_child_count = 0;
   this->_exp_type = NULL;
   this->_bound_type = NULL;
}

Node::Node (unsigned int type)
{
   this->_accept_children = false;
   this->_depth = 0;
   this->_expected_child_count = -1;
   this->_first_child = 0;
   this->_last_child = 0;
   this->_next = 0;
   this->_parent = 0;
   this->_position = NULL;
   this->_prev = 0;
   this->_type = type;
   this->_child_count = 0;
   this->_exp_type = NULL;
   this->_bound_type = NULL;
}

Node::~Node ()
{
   if (this->_first_child != NULL)
   {
      Node* cur_node = this->_first_child;
      Node* tmp_node = 0;
      while (cur_node != NULL)
      {
         tmp_node = cur_node;
         cur_node = cur_node->_next;
         delete tmp_node;
      }
   }
   delete this->_position;
}

void
Node::eat (Node* n)
{
   if (n != NULL)
   {
       if (n->_first_child != NULL)
       {
          this->_first_child = n->_first_child;
       }

       if (n->_last_child != NULL)
       {
          this->_last_child = n->_last_child;
       }

       Node* cur_node = n->_first_child;
       while (cur_node)
       {
         cur_node->_parent = this;
         cur_node = cur_node->_next;
       }
       this->_child_count = n->_child_count;
       n->unlink();
   }
}

Node*
Node::getChild (unsigned int i)
{
   Node* res = this->_first_child;
   for(unsigned int j = 0; j < i && res != NULL; ++j)
   {
      res = res->_next;
   }
   return res;
}

const char*
Node::get_type_name (unsigned int type)
{
    return mem::parser::node_names[type];
}

bool
Node::isText ()
{
   switch (this->_type)
   {
      case MEM_NODE_TEXT:
      case MEM_NODE_FUNCTION:
      case MEM_NODE_CLASS:
      case MEM_NODE_ID:
      case MEM_NODE_FINAL_ID:
         return true;
   }
   return false;
}

void
Node::pushChild (Node* n)
{
   if (n != NULL)
   {
      if (this->_first_child == 0)
      {
         this->_first_child = n;
      }
      if (this->_last_child != 0)
      {
         this->_last_child->_next = n;
      }
      n->_parent = this;
      n->_prev = this->_last_child;
      this->_last_child = n;
      n->sDepth(this->_depth + 1);
      ++this->_child_count;
   }
}

void
Node::sDepth (unsigned long depth)
{
   this->_depth = depth;
   Node* node = this->_first_child;
   while (node != 0)
   {
      node->sDepth(depth + 1);
      node = node->_next;
   }
}

void
Node::sPosition(fs::position::Range* pos)
{
   assert(pos != NULL);
   this->_position = pos;
}

void
Node::unlink ()
{
   this->_parent = NULL;
   this->_last_child = NULL;
   this->_first_child = NULL;
   this->_prev = NULL;
   this->_next = NULL;
}


} } }
