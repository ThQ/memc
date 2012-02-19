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
      node::Node* value_node = var_decl_node->gValueNode();
      node::Node* type_node = var_decl_node->gTypeNode();

      st::Symbol* var_type = var_decl_node->gExprType();
      st::Symbol* value_type = value_node->gExprType();

      if (var_type != NULL && value_type != NULL && !static_cast<st::Type*>(value_type)->isSubclass(static_cast<st::Type*>(var_type)) &&
         value_node != NULL && type_node != NULL)
      {
         log::Message* err = new log::Message(log::ERROR);
         err->formatMessage("Types mismatch in %s variable assignment",
            var_decl_node->gName().c_str());
         err->formatDescription("Variable expects value of type %s, but got %s instead",
            var_decl_node->gExprType()->gQualifiedNameCstr(),
            var_decl_node->gValueNode()->gExprType()->gQualifiedNameCstr()
         );

         if (type_node->_position != NULL && value_node->_position != NULL)
         {
            fs::position::Composite* pos = new fs::position::Composite();
            pos->add_child(type_node->_position->copy());
            pos->add_child(value_node->_position->copy());
            err->sPosition(pos);
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
