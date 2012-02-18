#include "mem/ast/visitor/TypeMatch.hpp"


namespace mem { namespace ast { namespace visitor {


TypeMatch::TypeMatch ()
{
   this->_name = "TypeMatch";
}

bool
TypeMatch::visit (node::Node* node)
{
   switch (node->_type)
   {
      case MEM_NODE_VARIABLE_DECLARATION:
         this->visit_var_decl(static_cast<node::VarDecl*>(node));
         return false;
   }
   return true;
}

void
TypeMatch::visit_var_decl (node::VarDecl* var_decl_node)
{
   if (var_decl_node->_child_count == 3)
   {
      node::Node* value_node = var_decl_node->get_value_node();
      node::Node* type_node = var_decl_node->get_type_node();

      st::Symbol* var_type = var_decl_node->_exp_type;
      st::Symbol* value_type = value_node->_exp_type;

      if (var_type != NULL && value_type != NULL && !static_cast<st::Type*>(value_type)->is_subclass(static_cast<st::Type*>(var_type)) &&
         value_node != NULL && type_node != NULL)
      {
         log::Message* err = new log::Message(log::ERROR);
         err->format_message("Types mismatch in %s variable assignment",
            var_decl_node->get_name().c_str());
         err->format_description("Variable expects value of type %s, but got %s instead",
            var_decl_node->g_expr_type()->g_qualified_name_cstr(),
            var_decl_node->get_value_node()->_exp_type->g_qualified_name_cstr()
         );

         if (type_node->_position != NULL && value_node->_position != NULL)
         {
            fs::position::Composite* pos = new fs::position::Composite();
            pos->add_child(type_node->_position->copy());
            pos->add_child(value_node->_position->copy());
            err->set_position(pos);
         }
         else
         {
            this->_logger->debug("Node has a missing position in either value or type\n", "");
         }
         this->_logger->log(err);
      }
   }
}


} } }
