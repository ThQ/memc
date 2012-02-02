#include "mem/ast/visitor/TopTypesChecker.hpp"

namespace mem { namespace ast { namespace visitor {


TopTypesChecker::TopTypesChecker (st::SymbolTable* symbols,
   log::Logger* logger)
{
   assert(logger != 0);
   assert(symbols != 0);

   this->_logger = logger;
   this->_symbols = symbols;
}

bool
TopTypesChecker::visit (node::Node* node)
{
   assert(node != NULL);

   node::Class* cls = static_cast<node::Class*>(node->_parent);
   st::Symbol* class_scope = NULL;

   switch (node->_type)
   {
      case MEM_NODE_FIELD:
      {
         class_scope = cls->_bound_type;
         this->visit_field(class_scope, static_cast<node::Field*>(node));
         return false;
      }
      case MEM_NODE_FUNCTION_DECLARATION:
      {
         class_scope = cls->_bound_type;
         this->visit_function_declaration(class_scope, static_cast<node::Text*>(node));
         return false;
      }
   }
   return true;
}

void
TopTypesChecker::visit_field (st::Symbol* scope, node::Field* field)
{
   assert(scope!=NULL);
   assert(field!=NULL);

   this->visit_qualified_name(scope, static_cast<node::Text*>(field->get_child(1)));

   if (field->get_child(1)->_exp_type != NULL)
   {
      st::Var* sym_field = new st::Var();
      sym_field->set_name(static_cast<node::Text*>(field->get_child(0))->_value);
      sym_field->set_type(static_cast<st::Class*>(field->get_child(1)->_exp_type)->g_instance_type());
      scope->add_child(sym_field);

      field->get_child(0)->_bound_type = sym_field;
      field->_bound_type = sym_field;
      field->_exp_type = sym_field->_type;
      assert (sym_field->_type != NULL);
   }
}

void
TopTypesChecker::visit_qualified_name (st::Symbol* scope, node::Text* name_node)
{
   assert (scope != NULL);
   assert (name_node != NULL);

   //printf("VISITING QUALIFIED NAME [%s]...\n", name_node->_value.c_str());
   if (name_node->is_type(MEM_NODE_FINAL_ID))
   {
      name_node->_exp_type = st::Util::lookup_symbol(scope, name_node->_value);
      if (name_node->_exp_type == NULL)
      {
         log::Message* err = new log::Message(log::ERROR);
         err->format_message("Unknown symbol (%s) in scope (%s)",
            name_node->_value.c_str(),
            scope->get_qualified_name().c_str());
         err->set_position(name_node->_position->copy());
         this->_logger->log(err);
      }
   }
   // @FIXME : Make this happen
   else
   {
      /*
      node::Text* sub_node = NULL;
      st::Symbol* node_expr_type = NULL;

      for (size_t i = 0 ; i < name_node->_child_count; ++i)
      {
      }
      */
   }
}

void
TopTypesChecker::visit_function_declaration (st::Symbol* scope, node::Text* func_decl)
{
   assert(scope != NULL);
   assert(func_decl->get_child(0) != NULL);
   assert(func_decl->get_child(1) != NULL);

   // Add the function to the symbol table
   st::Function* func_sym = new st::Function();
   func_sym->set_name(func_decl->_value);
   scope->add_child(func_sym);

   // Add {this} to the symbol table
   st::Var* vthis = new st::Var();
   vthis->set_name("this");
   vthis->set_type(static_cast<st::Class*>(func_sym->_parent)->g_instance_type());
   func_sym->add_child(vthis);

   // Visit return type node
   this->visit_qualified_name(func_sym->_parent, static_cast<node::Text*>(func_decl->get_child(1)));
   func_decl->_bound_type = func_sym;
   if (func_decl->get_child(1)->_exp_type != NULL)
   {
      func_sym->_return_type = static_cast<st::Class*>(st::Util::get_eval_type(func_decl->get_child(1)->_exp_type))->g_instance_type();
      func_decl->_exp_type = func_sym->_return_type;
   }

   // Visit function parameters
   st::Var* param_sym = NULL;
   node::Node* func_params = func_decl->get_child(0);
   node::Node* param_node = NULL;
   for (size_t i = 0; i < func_params->_child_count; ++i)
   {
      param_node = func_params->get_child(i);
      this->visit_func_param(scope, param_node);

      param_sym = new st::Var();
      param_sym->set_name(static_cast<node::Text*>(param_node->get_child(0))->_value);
      if (param_node->get_child(1)->_exp_type != NULL)
      {
         param_sym->set_type(static_cast<st::Class*>(param_node->get_child(1)->_exp_type)->g_instance_type());
      }
      func_sym->add_child(param_sym);

      param_node->get_child(0)->_bound_type = param_sym;
      param_node->_bound_type = param_sym;
      param_node->_exp_type = param_sym->_type;
   }
}

void
TopTypesChecker::visit_func_param(st::Symbol* scope, node::Node* param_node)
{
   this->visit_qualified_name(scope, static_cast<node::Text*>(param_node->get_child(1)));
}


} } }
