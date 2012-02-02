#include "mem/ast/Ast.hpp"

namespace mem { namespace ast {


Ast::Ast ()
{
   this->_root = new node::Root();
   this->_current = this->_root;
}

Ast::~Ast ()
{
   delete this->_root;
}

void
Ast::dump ()
{
   ASSERT_NOT_NULL(this->_root);
   this->_root->dump();
}

void
Ast::push_node (node::Node* n)
{
   if (this->_current->_accept_children)
   {
      this->_current->push_child(n);
   }
   else
   {
      this->_current->_next = n;
      n->_depth = this->_current->_depth;
      n->_parent = this->_current->_parent;
   }
   this->_current = n;
}

void
Ast::reset ()
{
   this->_root = new node::Root();
   this->_current = this->_root;
}


} }
