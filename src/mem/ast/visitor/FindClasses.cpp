#include "mem/ast/visitor/FindClasses.hpp"


namespace mem { namespace ast { namespace visitor {


FindClasses::FindClasses ()
{
   this->_name = "FindClasses";
}

bool
FindClasses::visit (node::Node* node)
{
   assert (node != NULL);


   if (node->_type == MEM_NODE_CLASS || node->_type == MEM_NODE_PRIMITIVE)
   {
      node::Class* cls_node = (node::Class*)node;

      assert(node->_parent != NULL);
      assert(node->_parent->_type == MEM_NODE_FILE);

      st::Class* cls = new st::Class();
      cls->_name = static_cast<node::Text*>(node)->_value;
      this->_symbols->_root->add_child(cls);
      cls_node->s_bound_symbol(cls);


      node::Text* parent_type_node = cls_node->g_parent_type_node();
      if (parent_type_node != NULL && parent_type_node->_type == MEM_NODE_ID)
      {
         st::Class* parent_cls = st::Util::lookup_class(this->_symbols->_root, parent_type_node->_value);
         if (parent_cls != NULL)
         {
            parent_type_node->_bound_type = parent_cls;
            cls->_parent_type = parent_cls;
         }
         else
         {
            log::Message* err = new log::Message(log::ERROR);
            err->format_message("Symbol not found {symbol:%s} in {symbol:%s}",
               cls_node->g_value_cstr(),
               this->_symbols->_root->g_qualified_name_cstr());
            err->set_position(parent_type_node->copy_position());
            this->_logger->log(err);
         }
      }
   }

   return true;
}


} } }
