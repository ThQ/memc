#include "mem/ast/visitor/VariableTypesChecker.hpp"

namespace mem { namespace ast { namespace visitor {


VariableTypesChecker::VariableTypesChecker ()
{
   this->_name = "VariableTypesChecker";
}

bool
VariableTypesChecker::visit (node::Node* node)
{
   assert(node != NULL);

   if (node->_type == MEM_NODE_VARIABLE_DECLARATION)
   {
      assert(node->get_child(0) != NULL);
      assert(node->get_child(1) != NULL);

      node::Text* type_node = static_cast<node::Text*>(node->get_child(1));
      std::string class_name(type_node->_value);

      if (class_name[0]!='$')
      {
         st::Symbol* var_st_type = this->_symbols->get_symbol(class_name);
         if (var_st_type != NULL)
         {
            node->_exp_type = static_cast<st::Class*>(var_st_type)->g_instance_type();
            node->get_child(1)->_exp_type = node->_exp_type;
         }
      }
   }

   return true;
}


} } }
