#include "mem/ast/visitor/FindClasses.hpp"

namespace mem { namespace ast { namespace visitor {


FindClasses::FindClasses (st::SymbolTable* symbols)
{
   this->_symbols = symbols;
}


bool
FindClasses::visit (node::Node* node)
{
   if (node->_type == MEM_NODE_CLASS || node->_type == MEM_NODE_PRIMITIVE)
   {
      assert(node->_parent != NULL);
      assert(node->_parent->_type == MEM_NODE_FILE);

      st::Class* cls = new st::Class();
      cls->_name = static_cast<node::Text*>(node)->_value;
      this->_symbols->_root->add_child(cls);

      node->_bound_type = cls;
   }
   return true;
}


} } }
