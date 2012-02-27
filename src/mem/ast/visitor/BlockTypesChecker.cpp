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
         if (((node::Func*)node)->gBodyNode() != NULL)
         {
            this->visitBlock(node->gBoundSymbol(),
               static_cast<node::Func*>(node)->gBodyNode());
         }
         return false;
      }
   }
   return true;
}

bool
BlockTypesChecker::isCompatibleFuncSign (st::FunctionSignature* sign_sym, node::Node* params_node)
{
   int params_count = params_node == NULL ? 0 : params_node->gChildCount();
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
BlockTypesChecker::pickFuncSign (st::Func* func_sym, node::Node* call_node,
   node::Node* params_node)
{
   std::vector<st::FunctionSignature*> compat_sigs;
   std::map<std::string, st::Symbol*>::iterator i;
   st::FunctionSignature* sig_sym = NULL;

   st::Func* cur_func_sym = func_sym;
   while (cur_func_sym != NULL)
   {
      for (i=cur_func_sym->_children.begin(); i != cur_func_sym->_children.end(); ++i)
      {
         if (i->second->is(st::FUNCTION_SIGNATURE))
         {
            sig_sym = static_cast<st::FunctionSignature*>(i->second);
            if (this->isCompatibleFuncSign(sig_sym, params_node))
            {
               compat_sigs.push_back(sig_sym);
            }
         }
      }
      cur_func_sym = static_cast<st::Func*>(cur_func_sym->_parent);
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
         for (unsigned int i = 0 ; i < params_node->gChildCount() ; ++i)
         {
            if (func_sig != "")
            {
               func_sig += ", ";
            }
            if (params_node->getChild(i)->hasExprType())
            {
               func_sig += ":";
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

      log::Message* err = new log::Error();
      err->sMessage("Cannot find the function definition");
      err->formatDescription("Looking for signature :\n\t%s (%s)\nFound :\n%s",
         func_sym->gNameCstr(),
         func_sig.c_str(),
         sigs_found.c_str());
      err->sPosition(call_node->getChild(0)->copyPosition());
      this->log(err);
   }
}

void
BlockTypesChecker::visitCall (st::Symbol* scope, node::Node* call_node)
{
   node::Node* base_object = call_node->getChild(0);
   this->visitExpr(scope, base_object);

   if (call_node->gChildCount() >= 2)
   {
      this->visitExprList (scope, call_node->getChild(1));
   }

   if (base_object->hasBoundSymbol())
   {
      if (base_object->gBoundSymbol()->is(st::FUNCTION))
      {
         this->pickFuncSign(static_cast<st::Func*>(base_object->gBoundSymbol()), call_node, call_node->getChild(1));
         //call_node->sBoundSymbol(base_object->gBoundSymbol());
         call_node->sExprType(static_cast<st::Func*>(base_object->gExprType())->gReturnType());
      }
      else
      {
         log::Message* err = new log::Error();
         err->formatMessage(
            "Trying to call an object that is not a function but a {symbol:%s} (%s)",
            base_object->gBoundSymbol()->gNameCstr(),
            base_object->gBoundSymbol()->gQualifiedNameCstr());
         this->log(err);
      }
   }
}

void
BlockTypesChecker::visitDot (st::Symbol* scope, node::Node* dot_node)
{
   node::Node* left_node = dot_node->getChild(0);
   node::Node* right_node = dot_node->getChild(1);

   this->visitExpr(scope, left_node);
   this->visitExpr(scope, right_node);

   assert(right_node->isType(MEM_NODE_ID));

   if (left_node->hasExprType())
   {
      dot_node->sBoundSymbol(st::Util::lookupMember(
         left_node->gExprType(),
         static_cast<node::Text*>(right_node)->gValue()));

      if (dot_node->hasBoundSymbol())
      {
         right_node->sBoundSymbol(dot_node->gBoundSymbol());
         dot_node->sExprType(dot_node->gBoundSymbol());
      }
      else
      {
         log::Message* err = new log::Error();
         err->formatMessage(
            "Symbol {id:%s} not found in {id:%s}",
            static_cast<node::Text*>(right_node)->gValueCstr(),
            static_cast<node::Text*>(left_node)->gExprType()->gQualifiedNameCstr());
         err->sPosition(right_node->copyPosition());
         this->log(err);
      }
   }
}

void
BlockTypesChecker::visitExprList (st::Symbol* scope, node::Node* node)
{
   node::Node* subnode = NULL;
   for (size_t i = 0 ; i < node->gChildCount(); ++i)
   {
      subnode = node->getChild(i);
      this->visitExpr(scope, subnode);
   }
}

void
BlockTypesChecker::visitExpr (st::Symbol* scope, node::Node* node)
{
   assert(scope != NULL);
   assert(node != NULL);

   switch (node->_type)
   {
      case MEM_NODE_CALL:
         this->visitCall(scope, node);
         break;

      case MEM_NODE_IF:
         this->visitIf(scope, node);
         break;

      case MEM_NODE_FINAL_ID:
         this->visitFinalId(scope, static_cast<node::Text*>(node));
         break;

      case MEM_NODE_GROUP:
         this->visitExpr(scope, node->getChild(0));
         node->sExprType(node->getChild(0)->gExprType());
         break;

      case MEM_NODE_EXPR_LIST:
         this->visitExprList(scope, node);
         break;

      case MEM_NODE_WHILE:
         this->visitWhile(scope, node);
         break;

      case MEM_NODE_DOT:
         this->visitDot(scope, node);
         break;
   }
}

void
BlockTypesChecker::visitIf (st::Symbol* scope, node::Node* if_node)
{
   this->visitExpr(scope, if_node->getChild(0));
   this->ensureBoolExpr(if_node->getChild(0));

   this->visitBlock(scope, if_node->getChild(1));
}

void
BlockTypesChecker::visitFinalId (st::Symbol* scope, node::Text* id_node)
{
   assert(scope != NULL);
   assert(id_node != NULL);

   st::Symbol* sym = st::Util::lookupSymbol(scope, id_node->gValue());

   if (sym != NULL)
   {
      id_node->sBoundSymbol(sym);
      id_node->sExprType(static_cast<st::Var*>(sym)->_type);
   }
   else
   {
      log::Message* err = new log::Error();
      err->formatMessage("Symbol not found {symbol:%s} in {symbol:%s}",
         id_node->gValueCstr(),
         scope->gQualifiedNameCstr());
      err->sPosition(id_node->copyPosition());
      this->log(err);
   }
}

void
BlockTypesChecker::visitBlock (st::Symbol* scope, node::Node* block)
{
   node::Node* st = NULL;
   for (size_t i = 0; i < block->_child_count; ++i)
   {
      st = block->getChild(i);
      switch (st->_type)
      {
         case MEM_NODE_VARIABLE_DECLARATION:
            this->visitVarDecl(scope, static_cast<node::VarDecl*>(st));
            break;

         default:
            this->visitExpr(scope, st);
      }
   }
}

void
BlockTypesChecker::visitVarDecl (st::Symbol* scope, node::VarDecl* var_decl_node)
{
   this->visitExpr(scope, var_decl_node->gTypeNode());
   if (var_decl_node->gValueNode() != NULL)
   {
      this->visitExpr(scope, var_decl_node->gValueNode());
   }

   // Add the variable to the current scope
   if (var_decl_node->gTypeNode()->hasExprType())
   {
      if (scope->getChild(var_decl_node->gName()) == NULL)
      {
         st::Var* var = new st::Var();
         var->sName(var_decl_node->gName());
         var->sType(var_decl_node->gTypeNode()->gExprType());
         var_decl_node->sBoundSymbol(var);
         var_decl_node->gNameNode()->sBoundSymbol(var);
         scope->addChild(var);
      }
      else
      {
         log::Message* err = new log::Error();
         err->formatMessage("Variable %s already defined",
            var_decl_node->gNameCstr());
         err->sPosition(var_decl_node->copyPosition());
         this->log(err);
      }
   }
}

void
BlockTypesChecker::visitWhile (st::Symbol* scope, node::Node* node)
{
   this->visitExpr(scope, node->getChild(0));
   this->ensureBoolExpr(node->getChild(0));

   this->visitBlock(scope, node->getChild(1));
}


} } }
