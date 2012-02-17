#include "mem/ast/util.hpp"


namespace mem { namespace ast { namespace util {


st::Symbol*
find_local_variable_type(node::Node* start_at, std::string var_name)
{
   node::Node* cur_node = start_at;
   while (cur_node != NULL)
   {
      if (cur_node ->_type == MEM_NODE_FUNCTION_DECLARATION)
      {
         node::Node* cur_param = (cur_node->get_child(0))->get_child(0);
         while (cur_param != NULL)
         {
            node::Text* param_type = static_cast<node::Text*>
               (cur_param->get_child(0));
            if (param_type->_value == var_name)
            {
               return cur_param->get_child(1)->_exp_type;
            }
            cur_param = cur_param->_next;
         }
         return NULL;
      }
      else
      {
         node::Node* cur_child_node = cur_node->_first_child;
         while (cur_child_node != NULL)
         {
            if(cur_child_node->_type == MEM_NODE_VARIABLE_DECLARATION)
            {
               node::Text* var_type = static_cast<node::Text*>
                  (cur_child_node->get_child(0));
               if (var_type->_value == var_name)
               {
                  return cur_child_node->get_child(1)->_exp_type;
               }
            }
            cur_child_node = cur_child_node->_next;
         }
         cur_node = cur_node->_parent;
      }
   }
   return NULL;
}

st::Symbol*
find_self_type (node::Node* start_at)
{
   node::Node* cur_node = start_at;
   while (cur_node != NULL)
   {
      switch (cur_node->_type)
      {
         case MEM_NODE_CLASS:
            assert(cur_node->_exp_type != NULL);
            return cur_node->_exp_type;
         default:
            cur_node = cur_node->_parent;
      }
   }
   return NULL;
}


} } }
