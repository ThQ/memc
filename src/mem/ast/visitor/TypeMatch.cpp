#include "mem/ast/visitor/TypeMatch.hpp"


namespace mem { namespace ast { namespace visitor {


TypeMatch::TypeMatch (st::SymbolTable* symbols, log::Logger* logger)
{
   assert(logger != 0);
   assert(symbols != 0);

   this->_logger = logger;
   this->_symbols = symbols;
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
      st::Symbol* var_type = var_decl_node->_exp_type;
      st::Symbol* value_type = var_decl_node->get_value_node()->_exp_type;

      if (var_type != NULL && value_type != NULL && var_type != value_type)
      {
         fs::position::Composite* pos = new fs::position::Composite();
         pos->add_child(var_decl_node->get_type_node()->_position->copy());
         pos->add_child(var_decl_node->get_value_node()->_position->copy());

         log::Message* err = new log::Message(log::ERROR);
         err->format_message("Types mismatch in %s variable assignment",
            var_decl_node->get_name().c_str());
         err->format_description("Variable expects value type = %s\n Value type = %s",
            var_decl_node->_exp_type->get_qualified_name().c_str(),
            var_decl_node->get_value_node()->_exp_type->get_qualified_name().c_str()
         );
         err->set_position(pos);
         this->_logger->log(err);

      }
   }
}

} } }
