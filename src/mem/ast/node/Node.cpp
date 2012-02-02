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
Node::get_child (unsigned int i)
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

void
Node::dump ()
{
   this->dump_self();
   this->dump_children();
}

void
Node::dump_depth ()
{
   if (this->_parent != 0)
   {
      for (unsigned int i = 0 ; i < this->_depth; ++ i)
      {
         printf("    ");
      }
   }
}

void
Node::dump_children ()
{
   Node* child = this->_first_child;
   while (child != 0)
   {
      child->dump();
      child = child->_next;
   }
}

void
Node::dump_self ()
{
   this->dump_depth();
   printf("%s", get_type_name(this->_type));

   if (this->_bound_type != NULL || this->_exp_type != NULL)
   {
      printf(" (");
      if (this->_bound_type != NULL)
      {
         printf("%s", this->_bound_type->get_qualified_name().c_str());
      }
      else
      {
         printf(" ");
      }
      printf(" -> ");
      if (this->_exp_type != NULL)
      {
         printf("%s", this->_exp_type->get_qualified_name().c_str());
      }
      else
      {
         printf(" ");
      }
      printf(")");
   }
   if (this->_position != NULL)
   {
      printf(" @%s:%d:%d", this->_position->_file->_path.c_str(), this->_position->_line, this->_position->_column_start);
   }
   printf("\n");
}

void
Node::push_child (Node* n)
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
      n->set_depth(this->_depth + 1);
      ++this->_child_count;
   }
}

void
Node::set_depth (unsigned long depth)
{
   this->_depth = depth;
   Node* node = this->_first_child;
   while (node != 0)
   {
      node->set_depth(depth + 1);
      node = node->_next;
   }
}

void
Node::set_position(fs::position::Range* pos)
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
