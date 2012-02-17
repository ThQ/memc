#include "mem/ast/visitor/BlockTypesChecker.hpp"

namespace mem { namespace ast { namespace visitor {


BlockTypesChecker::BlockTypesChecker ()
{
   this->_name = "BlockTypesChecker";
}

bool
BlockTypesChecker::visit (node::Node* node)
{
   switch(node->_type)
   {
      case MEM_NODE_FUNCTION_DECLARATION:
      {
         if (((node::Function*)node)->g_body_node() != NULL)
         {
            this->visit_block(node->_bound_type, ((node::Function*)node)->g_body_node());
         }
         return false;
      }
      break;

      case MEM_NODE_VARIABLE_DECLARATION:
      {
         if (node->_child_count == 3)
         {
            //this->visit_variable_declaration_with_value(node);
         }
      }
      break;
   }
   return true;
}

void
BlockTypesChecker::visit_call (st::Symbol* scope, node::Node* call_node)
{
   node::Node* base_object = call_node->get_child(0);
   this->visit_exp(scope, base_object);

   if (base_object->_bound_type != NULL)
   {
      if (base_object->_bound_type->is(st::FUNCTION))
      {
         call_node->_bound_type = base_object->_bound_type;
         call_node->_exp_type = static_cast<st::Function*>(base_object->_exp_type)->_return_type;
      }
      else
      {
         log::Message* err = new log::Message(log::ERROR);
         err->format_message(
            "Trying to call an object that is not a function but a {symbol:%s} (%s)",
            base_object->_bound_type->_name.c_str(),
            base_object->_bound_type->get_qualified_name().c_str()
            );
         this->_logger->log(err);
      }
   }

   st::Function* func_sym = (st::Function*)(call_node->_bound_type);

   if (func_sym != NULL)
   {
      int params_count = call_node->_child_count < 2 ? 0 : call_node->get_child(1)->_child_count;

      // Check parameters count against function signature
      if (params_count != func_sym->_params.size())
      {
         log::Message* err = new log::Message(log::ERROR);
         err->set_message("Bad number of parameters in call");
         err->format_description("Function <%s> expects %d parameters, but got %d.",
            call_node->_bound_type->get_qualified_name().c_str(),
            ((st::Function*)(call_node->_bound_type))->_params.size(),
            params_count);
         err->set_position(call_node->get_child(0)->_position->copy());
         this->_logger->log(err);
      }


      // Call has parameters
      if (params_count > 0)
      {
         this->visit_expr_list (scope, call_node->get_child(1));

         // @TODO Parameters types could be checked even though there are not
         // enough parameters
         for (int i=0; i < call_node->get_child(1)->_child_count ; ++i)
         {
            if (call_node->get_child(1)->get_child(i)->_exp_type != func_sym->_params[i])
            {
               log::Message* err = new log::Message(log::ERROR);
               err->set_message("Bad parameter type");
               err->format_description("Parameter %d must be of type {type:%s}, but got a parameter of type {type:%s} instead.",
                  i+1,
                  func_sym->_params[i]->get_qualified_name().c_str(),
                  call_node->get_child(1)->get_child(i)->_exp_type->get_qualified_name().c_str());
               err->set_position(call_node->get_child(1)->get_child(i)->_position->copy());
               this->_logger->log(err);
            }
         }
      }
   }
}

void
BlockTypesChecker::visit_dot (st::Symbol* scope, node::Node* dot_node)
{
   this->visit_exp(scope, dot_node->get_child(0));
   this->visit_exp(scope, dot_node->get_child(1));

   assert(dot_node->get_child(1)->_type == MEM_NODE_ID);
   if (dot_node->get_child(0)->_exp_type != NULL)
   {
      dot_node->_bound_type = st::Util::lookup_member(
         dot_node->get_child(0)->_exp_type,
         static_cast<node::Text*>(dot_node->get_child(1))->_value);

      if (dot_node->_bound_type != NULL)
      {
         dot_node->get_child(1)->_bound_type = dot_node->_bound_type;
         dot_node->_exp_type = dot_node->_bound_type;
      }
      else
      {
         log::Message* err = new log::Message(log::ERROR);
         err->format_message(
            "Symbol {id:%s} not found in {id:%s}",
            static_cast<node::Text*>(dot_node->get_child(1))->_value.c_str(),
            static_cast<node::Text*>(dot_node->get_child(0))->_exp_type->get_qualified_name().c_str());
         err->set_position(dot_node->get_child(1)->_position->copy());
         this->_logger->log(err);
      }
   }
}

void
BlockTypesChecker::visit_expr_list (st::Symbol* scope, node::Node* node)
{
   //printf("VISITING EXPR_LIST...\n");
   node::Node* subnode = NULL;
   for (size_t i = 0 ; i < node->_child_count; ++i)
   {
      subnode = node->get_child(i);
      this->visit_exp(scope, subnode);
   }
}

void
BlockTypesChecker::visit_exp (st::Symbol* scope, node::Node* node)
{
   assert(scope != NULL);
   assert(node != NULL);
   //printf("VISITING EXP...\n");
   switch (node->_type)
   {
      case MEM_NODE_CALL:
         this->visit_call(scope, node);
         break;

      case MEM_NODE_IF:
         this->visit_if(scope, node);
         break;

      case MEM_NODE_FINAL_ID:
         this->visit_final_id(scope, static_cast<node::Text*>(node));
         break;

      case MEM_NODE_GROUP:
         this->visit_exp(scope, node->get_child(0));
         node->_exp_type = node->get_child(0)->_exp_type;
         break;

      case MEM_NODE_EXPR_LIST:
         this->visit_expr_list(scope, node);
         break;

      case MEM_NODE_WHILE:
         this->visit_while(scope, node);
         break;

      case MEM_NODE_DOT:
         this->visit_dot(scope, node);
         break;
   }
}

void
BlockTypesChecker::visit_if (st::Symbol* scope, node::Node* if_node)
{
   this->visit_exp(scope, if_node->get_child(0));
   this->visit_block(scope, if_node->get_child(1));

   if (if_node->get_child(0)->_exp_type != this->_symbols->_glob_bool_cls)
   {
      log::Message* err = new log::Message(log::ERROR);
      err->format_message("If expects an expression of type bool, but got %s instead",
         if_node->get_child(0)->_exp_type->get_qualified_name().c_str());
      err->set_position(if_node->get_child(0)->_position->copy());
      this->_logger->log(err);

   }
}

void
BlockTypesChecker::visit_final_id (st::Symbol* scope, node::Text* id_node)
{
   //printf("VISITING ID [%s]...\n", id_node->_value.c_str());
   assert(scope != NULL);
   assert(id_node != NULL);


   st::Symbol* sym = st::Util::lookup_symbol(scope, id_node->_value);

   if (sym != NULL)
   {
      id_node->_bound_type = sym;
      id_node->_exp_type = static_cast<st::Var*>(sym)->_type;
   }
   else
   {
      log::Message* err = new log::Message(log::ERROR);
      err->format_message("Symbol not found {symbol:%s} in {symbol:%s}",
         id_node->_value.c_str(),
         scope->get_qualified_name().c_str());
      err->set_position(id_node->_position->copy());
      this->_logger->log(err);
   }
}

void
BlockTypesChecker::visit_block (st::Symbol* scope, node::Node* block)
{
   node::Node* st = NULL;
   for (size_t i = 0; i < block->_child_count; ++i)
   {
      st = block->get_child(i);
      switch (st->_type)
      {
         case MEM_NODE_VARIABLE_DECLARATION:
            this->visit_var_decl(scope, static_cast<node::VarDecl*>(st));
            break;

         default:
            this->visit_exp(scope, st);
      }
   }
}

void
BlockTypesChecker::visit_var_decl (st::Symbol* scope, node::VarDecl* var_decl_node)
{
   //printf("Visit VAR_DECL\n");

   this->visit_exp(scope, var_decl_node->get_type_node());
   if (var_decl_node->get_value_node() != NULL)
   {
      this->visit_exp(scope, var_decl_node->get_value_node());
   }

   // Add the variable to the current scope
   if (var_decl_node->get_type_node()->_exp_type != NULL)
   {
      if (scope->get_child(var_decl_node->get_name()) == NULL)
      {
         st::Var* var = new st::Var();
         var->set_name(var_decl_node->get_name());
         var->set_type(var_decl_node->get_type_node()->_exp_type);
         //var->_pos = var_decl_node->_position->copy();
         var_decl_node->_bound_type = var;
         var_decl_node->get_name_node()->_bound_type = var;
         scope->add_child(var);
      }
      else
      {
         log::Message* err = new log::Message(log::ERROR);
         err->format_message("Variable %s already defined", var_decl_node->get_name().c_str());
         err->set_position(var_decl_node->_position->copy());
         this->_logger->log(err);
      }
   }
}

void
BlockTypesChecker::visit_while (st::Symbol* scope, node::Node* node)
{
   this->visit_exp(scope, node->get_child(0));
   this->visit_block(scope, node->get_child(1));
}

void
BlockTypesChecker::visit_variable_declaration_with_value (node::Node* node)
{
   /*
   st::Class* value_type = NULL;

   switch (node->get_child(2)->_type)
   {
      case MEM_NODE_ID:
         value_type = ast::util::find_local_variable_type(node,
            static_cast<node::Text*>(node->get_child(2))->_value);
         break;
      case MEM_NODE_SELF:static_cast
         value_type = ast::util::find_self_type(node);
         break;
      default:
         value_type = NULL;
   }

   if (value_type != NULL)
   {
      if (value_type == node->get_child(1)->_exp_type)
      {
         node->get_child(2)->_exp_type = value_type;
      }
      else
      {
         fs::position::Range* rnge_type = static_cast<fs::position::Range*>(
            node->get_child(1)->_position);
         fs::position::Range* rnge_value = static_cast<fs::position::Range*>(
            node->get_child(2)->_position);

         fs::position::Range* cur = static_cast<fs::position::Range*>(rnge_type->copy());
         //cur->_file = rnge_type->_file;
         //cur->_line = rnge_type->_line;

         // Look for an '=' since we didn't keep this token while parsing.
         // Fix me ?
         std::string* context_line = cur->_file->_lines[cur->_line-1];
         for (size_t i = rnge_type->_column_end ;
            i < context_line->size() ; ++i)
         {
            if (context_line->data()[i] == '=')
            {
               cur->_column_start = i+1;
            }
         }

         fs::position::Composite* pos = new fs::position::Composite();
         pos->add_child(rnge_type->copy());
         pos->add_child(rnge_value->copy());
         pos->add_child(cur);

         std::string desc = "Trying to assign expression of type\n   {type:";
         desc.append(value_type->_name);
         desc.append("}\n to variable {id:");
         desc.append(static_cast<node::Text*>(node->get_child(0))->_value);
         desc.append("} of type\n   {type:");
         desc.append(node->get_child(1)->_exp_type->_name);
         desc.append("}\n");

         log::Message* err = new log::Message(log::ERROR);
         err->set_message("Types mismatch in variable declaration");
         err->set_description(desc);
         err->set_position(pos);
         this->_logger->log(err);
      }
   }
   else
   {
      switch (node->get_child(2)->_type)
      {
         case MEM_NODE_ID:
            log::Message* err = new log::Message(log::ERROR);
            err->format_message("ID not found : {id:%s}",
               static_cast<node::Text*>(node->get_child(2))->_value.c_str());
            this->_logger->log(err);
            break;
      }
   }
   */
}


} } }
