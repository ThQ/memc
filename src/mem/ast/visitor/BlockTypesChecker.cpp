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
            this->visit_block(node->gBoundSymbol(), static_cast<node::Function*>(node)->g_body_node());
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

bool
BlockTypesChecker::is_compatible_function_signature (st::FunctionSignature* sign_sym, node::Node* params_node)
{
   int params_count = params_node == NULL ? 0 : params_node->_child_count;
   if (sign_sym->_params.size() == params_count)
   {
      bool params_ok = true;
      for (size_t i = 0 ; i < sign_sym->_params.size() && params_ok ; ++i)
      {
         if(!params_node->getChild(i)->gExprType()->isSubclass(static_cast<st::Type*>(sign_sym->_params[i])))
         {
            params_ok = false;
         }
      }
      return params_ok;
   }
   return false;
}


void
BlockTypesChecker::pick_function_signature (st::Function* func_sym, node::Node* call_node, node::Node* params_node)
{
   std::vector<st::FunctionSignature*> compat_sigs;
   std::map<std::string, st::Symbol*>::iterator i;
   st::FunctionSignature* sig_sym = NULL;
   for (i=func_sym->_children.begin(); i != func_sym->_children.end(); ++i)
   {
      if (i->second->is(st::FUNCTION_SIGNATURE))
      {
         sig_sym = static_cast<st::FunctionSignature*>(i->second);
         if (this->is_compatible_function_signature(sig_sym, params_node))
         {
            compat_sigs.push_back(sig_sym);
         }
      }
   }
   // @TODO Can be more precise, think type precision
   if (compat_sigs.size() >= 1)
   {
      call_node->sBoundSymbol(compat_sigs[0]);
   }
   else
   {
      std::string func_sig = "";
      if (params_node != NULL)
      {
         for (unsigned int i = 0 ; i < params_node->_child_count ; ++i)
         {
            if (func_sig != "")
            {
               func_sig += ", ";
            }
            if (params_node->getChild(i)->gExprType() != NULL)
            {
               func_sig += params_node->getChild(i)->gExprType()->gQualifiedName();
            }
            else
            {
               func_sig += "?";
            }
         }
      }

      std::string sigs_found = "";
      for (i=func_sym->_children.begin() ; i != func_sym->_children.end() ; ++i)
      {
         if (i->second->is(st::FUNCTION_SIGNATURE))
         {
            sigs_found += "\t" + static_cast<st::FunctionSignature*>(i->second)->gSignature() + "\n";
         }
      }

      log::Message* err = new log::Message(log::ERROR);
      err->sMessage("Cannot find the function definition");
      err->formatDescription("Looking for signature :\n\t%s (%s)\nFound :\n%s",
         func_sym->gNameCstr(),
         func_sig.c_str(),
         sigs_found.c_str());
      err->sPosition(call_node->getChild(0)->copy_position());
      this->_logger->log(err);
   }
}

void
BlockTypesChecker::visit_call (st::Symbol* scope, node::Node* call_node)
{
   node::Node* base_object = call_node->getChild(0);
   this->visit_exp(scope, base_object);

   if (call_node->_child_count >= 2)
   {
      this->visit_call_parameters(scope, call_node->getChild(1), NULL);
   }

   if (base_object->gBoundSymbol() != NULL)
   {
      if (base_object->gBoundSymbol()->is(st::FUNCTION))
      {
         this->pick_function_signature(static_cast<st::Function*>(base_object->gBoundSymbol()), call_node, call_node->getChild(1));
         //call_node->sBoundSymbol(base_object->gBoundSymbol());
         call_node->sExprType(static_cast<st::Function*>(base_object->gExprType())->gReturnType());
      }
      else
      {
         log::Message* err = new log::Message(log::ERROR);
         err->formatMessage(
            "Trying to call an object that is not a function but a {symbol:%s} (%s)",
            base_object->gBoundSymbol()->gNameCstr(),
            base_object->gBoundSymbol()->gQualifiedNameCstr()
            );
         this->_logger->log(err);
      }
   }
}

void
BlockTypesChecker::visit_call_parameters (st::Symbol* scope, node::Node* params_node, st::Function* func_sym)
{
   int params_count = params_node == NULL ? 0 : params_node->_child_count;

   // Call has parameters
   if (params_count > 0)
   {
      this->visit_expr_list (scope, params_node);
   }
}

void
BlockTypesChecker::visit_dot (st::Symbol* scope, node::Node* dot_node)
{
   this->visit_exp(scope, dot_node->getChild(0));
   this->visit_exp(scope, dot_node->getChild(1));

   assert(dot_node->getChild(1)->_type == MEM_NODE_ID);
   if (dot_node->getChild(0)->gExprType() != NULL)
   {
      dot_node->_bound_type = st::Util::lookup_member(
         dot_node->getChild(0)->gExprType(),
         static_cast<node::Text*>(dot_node->getChild(1))->gValue());

      if (dot_node->gBoundSymbol() != NULL)
      {
         dot_node->getChild(1)->sBoundSymbol(dot_node->gBoundSymbol());
         dot_node->sExprType(dot_node->gBoundSymbol());
      }
      else
      {
         log::Message* err = new log::Message(log::ERROR);
         err->formatMessage(
            "Symbol {id:%s} not found in {id:%s}",
            static_cast<node::Text*>(dot_node->getChild(1))->gValueCstr(),
            static_cast<node::Text*>(dot_node->getChild(0))->gExprType()->gQualifiedNameCstr());
         err->sPosition(dot_node->getChild(1)->copy_position());
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
      subnode = node->getChild(i);
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
         this->visit_exp(scope, node->getChild(0));
         node->sExprType(node->getChild(0)->gExprType());
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
   this->visit_exp(scope, if_node->getChild(0));
   this->visit_block(scope, if_node->getChild(1));

   if (if_node->getChild(0)->gExprType() != this->_symbols->_glob_bool_cls)
   {
      log::Message* err = new log::Message(log::ERROR);
      err->formatMessage("If expects an expression of type bool, but got %s instead",
         if_node->getChild(0)->gExprType()->gQualifiedNameCstr());
      err->sPosition(if_node->getChild(0)->copy_position());
      this->_logger->log(err);

   }
}

void
BlockTypesChecker::visit_final_id (st::Symbol* scope, node::Text* id_node)
{
   //printf("VISITING ID [%s]...\n", id_node->_value.c_str());
   assert(scope != NULL);
   assert(id_node != NULL);

   st::Symbol* sym = st::Util::lookup_symbol(scope, id_node->gValue());

   if (sym != NULL)
   {
      id_node->sBoundSymbol(sym);
      id_node->sExprType(static_cast<st::Var*>(sym)->_type);
   }
   else
   {
      log::Message* err = new log::Message(log::ERROR);
      err->formatMessage("Symbol not found {symbol:%s} in {symbol:%s}",
         id_node->gValueCstr(),
         scope->gQualifiedNameCstr());
      err->sPosition(id_node->copy_position());
      this->_logger->log(err);
   }
}

void
BlockTypesChecker::visit_block (st::Symbol* scope, node::Node* block)
{
   node::Node* st = NULL;
   for (size_t i = 0; i < block->_child_count; ++i)
   {
      st = block->getChild(i);
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

   this->visit_exp(scope, var_decl_node->gTypeNode());
   if (var_decl_node->gValueNode() != NULL)
   {
      this->visit_exp(scope, var_decl_node->gValueNode());
   }

   // Add the variable to the current scope
   if (var_decl_node->gTypeNode()->gExprType() != NULL)
   {
      if (scope->getChild(var_decl_node->gName()) == NULL)
      {
         st::Var* var = new st::Var();
         var->sName(var_decl_node->gName());
         var->sType(var_decl_node->gTypeNode()->gExprType());
         //var->_pos = var_decl_node->_position->copy();
         var_decl_node->sBoundSymbol(var);
         var_decl_node->gNameNode()->sBoundSymbol(var);
         scope->addChild(var);
      }
      else
      {
         log::Message* err = new log::Message(log::ERROR);
         err->formatMessage("Variable %s already defined", var_decl_node->gNameCstr());
         err->sPosition(var_decl_node->copy_position());
         this->_logger->log(err);
      }
   }
}

void
BlockTypesChecker::visit_while (st::Symbol* scope, node::Node* node)
{
   this->visit_exp(scope, node->getChild(0));
   this->visit_block(scope, node->getChild(1));
}

void
BlockTypesChecker::visit_variable_declaration_with_value (node::Node* node)
{
   /*
   st::Class* value_type = NULL;

   switch (node->getChild(2)->_type)
   {
      case MEM_NODE_ID:
         value_type = ast::util::find_local_variable_type(node,
            static_cast<node::Text*>(node->getChild(2))->_value);
         break;
      case MEM_NODE_SELF:static_cast
         value_type = ast::util::find_self_type(node);
         break;
      default:
         value_type = NULL;
   }

   if (value_type != NULL)
   {
      if (value_type == node->getChild(1)->_exp_type)
      {
         node->getChild(2)->_exp_type = value_type;
      }
      else
      {
         fs::position::Range* rnge_type = static_cast<fs::position::Range*>(
            node->getChild(1)->_position);
         fs::position::Range* rnge_value = static_cast<fs::position::Range*>(
            node->getChild(2)->_position);

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
         desc.append(static_cast<node::Text*>(node->getChild(0))->_value);
         desc.append("} of type\n   {type:");
         desc.append(node->getChild(1)->_exp_type->_name);
         desc.append("}\n");

         log::Message* err = new log::Message(log::ERROR);
         err->sMessage("Types mismatch in variable declaration");
         err->sDescription(desc);
         err->sPosition(pos);
         this->_logger->log(err);
      }
   }
   else
   {
      switch (node->getChild(2)->_type)
      {
         case MEM_NODE_ID:
            log::Message* err = new log::Message(log::ERROR);
            err->formatMessage("ID not found : {id:%s}",
               static_cast<node::Text*>(node->getChild(2))->_value.c_str());
            this->_logger->log(err);
            break;
      }
   }
   */
}


} } }
