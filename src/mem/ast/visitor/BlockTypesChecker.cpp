#include "mem/ast/visitor/BlockTypesChecker.hpp"


namespace mem { namespace ast { namespace visitor {


BlockTypesChecker::BlockTypesChecker ()
{
   _name = "ast.BlockTypesChecker";
}

void
BlockTypesChecker::checkCallParameters (st::Func* func_sym, node::Node* params)
{
   assert(func_sym != NULL);

   if (params != NULL && func_sym->gParamCount() != params->gChildCount())
   {
      log::BadParameterCount* err = new log::BadParameterCount();
      err->sExpectedParamCount(func_sym->gParamCount());
      err->sParamCount(params->gChildCount());
      err->format();
      err->sPosition(params->copyPosition());
      log(err);
   }
   else if (params != NULL)
   {
      // Each parameter node must have the same expr type as declared in its
      // function definition.
      for (size_t i = 0; i < func_sym->gParamCount(); ++i)
      {
         if (func_sym->getParam(i)->gType() != params->getChild(i)->gExprType())
         {
            ensureExprType(params->getChild(i), func_sym->getParam(i)->gType());
         }
      }

   }
}

bool
BlockTypesChecker::visit (node::Node* node)
{
   if (node->isFuncNode())
   {
      node::Func* func = static_cast<node::Func*>(node);

      if (func->gBodyNode() != NULL)
      {
         visitBlock(node->gBoundSymbol(), func->gBodyNode());
      }
      return false;
   }
   return true;
}
/*
bool
BlockTypesChecker::isCompatibleFuncSign (st::FunctionSignature* sign_sym,
   node::Node* params_node)
{
   unsigned int params_count = params_node == NULL ? 0 : params_node->gChildCount();

   if (sign_sym->_params.size() == params_count)
   {
      bool params_ok = true;
      node::Node* param = NULL;
      st::Type* expected_param_ty = NULL;

      for (size_t i = 0 ; i < sign_sym->_params.size() && params_ok ; ++i)
      {
         param = params_node->getChild(i);
         expected_param_ty = static_cast<st::Type*>(sign_sym->_params[i]);

         if(!param->gExprType()->isSubclass(expected_param_ty))
         {
            params_ok = false;
         }
      }
      return params_ok;
   }
   return false;
}
*/


void
BlockTypesChecker::pickFuncSign (st::Func* func_sym, node::Node* call_node,
   node::Node* params_node)
{
   /*
   std::vector<st::Symbol*> func_params;

   if (params_node != NULL)
   {
      func_params = params_node->packChildrenExprTypes();
   }

   std::vector<st::FunctionSignature*> compat_sigs;
   std::map<std::string, st::Symbol*>::iterator i;
   size_t j;
   //st::FunctionSignature* sig_sym = NULL;
   //st::Class* cur_class = static_cast<st::Class*>(func_sym->_parent);
   //st::Func* cur_func_sym = NULL;
   std::vector<st::FunctionSignature*> matching_signs =
      st::Util::listFuncSigns(static_cast<st::Class*>(func_sym->_parent),
      func_sym->gName());

   for (j=0; j < matching_signs.size() ; ++j)
   {
      assert(matching_signs[j]->is(st::FUNCTION_SIGNATURE));
      if (!matching_signs[j]->isOverloaded() &&
         this->isCompatibleFuncSign(matching_signs[j], params_node))
      {
         compat_sigs.push_back(matching_signs[j]);
      }
   }

   if (compat_sigs.size() == 1)
   {
      call_node->sBoundSymbol(compat_sigs[0]);
   }
   // No compatible functions found
   else if (compat_sigs.size() == 0)
   {
      std::string func_sig = "";
      if (params_node != NULL)
      {
         node::Node* param_node = NULL;

         for (unsigned int i = 0 ; i < params_node->gChildCount() ; ++i)
         {
            param_node = params_node->getChild(i);

            if (func_sig != "")
            {
               func_sig += ", ";
            }

            if (param_node->hasExprType())
            {
               func_sig += ":";
               func_sig += param_node->gExprType()->gQualifiedName();
            }
            else
            {
               func_sig += "?";
            }
         }
      }

      std::string sigs_found = "";
      for (j=0 ; j < matching_signs.size() ; ++j)
      {
         if (matching_signs[j]->is(st::FUNCTION_SIGNATURE))
         {
            sigs_found += "\t";
            sigs_found += matching_signs[j]->gSignature();
            sigs_found += "\n";
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
   // At least 2 compatible functions found (ambiguity)
   else
   {
      std::string sigs_found = "";
      for (j=0; j < compat_sigs.size(); ++j)
      {
         sigs_found += "\t";
         sigs_found += compat_sigs[j]->gSignature();
         sigs_found += "\n";
      }

      log::Message* err = new log::Error();
      err->sMessage("Ambiguity in function call");
      err->formatDescription("Found:\n%s", sigs_found.c_str());
      err->sPosition(call_node->getChild(0)->copyPosition());
      this->log(err);
   }
   */
}

void
BlockTypesChecker::visitAmpersand (st::Symbol* scope, node::Node* node)
{
   visitExpr(scope, node->getChild(0));

   if (node->getChild(0)->gExprType() != NULL)
   {
      std::string amp_ty_name = node->getChild(0)->gExprType()->gName() + "*";
      st::Type* amp_ty = static_cast<st::Type*>(
         st::Util::lookupSymbol(scope, amp_ty_name));

      assert (amp_ty != NULL);

      node->sExprType(amp_ty);

      // FIXME There should be more checks. For ex you should not be able to
      // do : &2
   }
}

void
BlockTypesChecker::visitArithmeticOp (st::Symbol* scope, node::Node* node)
{
   // Check left node
   node::Node* left_node = node->getChild(0);
   visitExpr(scope, left_node);

   // Check right node
   node::Node* right_node = node->getChild(1);
   visitExpr(scope, right_node);

   std::string op_name;
   switch (node->gType())
   {
      case MEM_NODE_PLUS:
         op_name = "plus";
         break;

      default:
         // FIXME Must fail properly if op is not found.
         assert (false && "Unknown arithmetic operator.");

   }

   std::string op_func_name;
   op_func_name += left_node->gExprType()->gName();
   op_func_name += "_" + op_name + "_";
   op_func_name += right_node->gExprType()->gName();

   st::Func* op_func = static_cast<st::Func*>(
      _symbols->gRoot()->getChild(op_func_name));

   if (op_func != NULL)
   {
      // FIXME Must check parameters type
      node->sExprType(op_func->gReturnType());
   }
   else
   {
      fs::position::Composite* pos = new fs::position::Composite();
      pos->addChild(left_node->copyPosition());
      pos->addChild(right_node->copyPosition());

      log::UnsupportedArithmeticOperation* err =
         new log::UnsupportedArithmeticOperation();
      err->sLeftTypeName(left_node->gExprType()->gNameCstr());
      err->sOpName(op_name.c_str());
      err->sRightTypeName(right_node->gExprType()->gNameCstr());
      err->format();
      err->sPosition(pos);
      log(err);
   }
}

void
BlockTypesChecker::visitLogicalExpr (st::Symbol* scope, node::Node* expr_node)
{
   if (expr_node->isAndNode() || expr_node->isOrNode())
   {
      visitExpr(scope, expr_node->getChild(0));
      visitExpr(scope, expr_node->getChild(1));

      ensureBoolExpr(expr_node->getChild(0));
      ensureBoolExpr(expr_node->getChild(1));

      expr_node->sExprType(_core_types->gBoolTy());
   }
}

void
BlockTypesChecker::visitCall (st::Symbol* scope, node::Call* call_node)
{
   assert (scope != NULL);
   assert (call_node != NULL);

   node::Node* base_object = call_node->gCallerNode();
   this->visitExpr(scope, base_object);

   if (call_node->hasParamsNode())
   {
      visitExprList(scope, call_node->gParamsNode());
   }

   if (base_object->hasBoundSymbol())
   {
      if (base_object->gBoundSymbol()->isFuncSymbol())
      {
         st::Func* base_func = static_cast<st::Func*>(
            base_object->gBoundSymbol());
         call_node->sExprType(base_func->gReturnType());
         if (call_node->hasParamsNode())
         {
            checkCallParameters(base_func, call_node->gParamsNode());
         }
      }
      else
      {
         log::CallNonFunction* err = new log::CallNonFunction();
         err->sObjectName(base_object->gBoundSymbol()->gName());
         err->sObjectTypeName(base_object->gBoundSymbol()->gQualifiedName());
         err->format();
         log(err);
      }
   }
}

void
BlockTypesChecker::visitDot (st::Symbol* scope, node::Node* dot_node)
{
   node::Node* left_node = dot_node->getChild(0);
   node::Node* right_node = dot_node->getChild(1);

   visitExpr(scope, left_node);
   visitExpr(scope, right_node);

   assert(right_node->isIdNode());

   if (left_node->hasExprType())
   {
      dot_node->sBoundSymbol(st::Util::lookupMember(
         left_node->gExprType(),
         static_cast<node::Text*>(right_node)->gValue()));

      if (dot_node->hasBoundSymbol())
      {
         right_node->sBoundSymbol(dot_node->gBoundSymbol());
         dot_node->sExprType(dot_node->gBoundSymbol()->gExprType());
         printf("BOUND_SYM[%s] -> [%d]\n", dot_node->gBoundSymbol()->gNameCstr(), dot_node->gBoundSymbol()->_kind);
         assert (dot_node->gExprType() != NULL);
      }
      else
      {
         log::SymbolNotFound* err = new log::SymbolNotFound();
         err->sSymbolName(static_cast<node::Text*>(right_node)->gValue());
         err->sScopeName(left_node->gExprType()->gQualifiedName());
         err->format();
         err->sPosition(right_node->copyPosition());
         log(err);
      }
   }
}

void
BlockTypesChecker::visitExprList (st::Symbol* scope, node::Node* node)
{
   node::Node* subnode = NULL;
   for (size_t i = 0; i < node->gChildCount(); ++i)
   {
      subnode = node->getChild(i);
      visitExpr(scope, subnode);
   }
}

void
BlockTypesChecker::visitExpr (st::Symbol* scope, node::Node* node)
{
   assert(scope != NULL);
   assert(node != NULL);

   switch (node->gType())
   {
      case MEM_NODE_DIV:
      case MEM_NODE_MINUS:
      case MEM_NODE_PLUS:
      case MEM_NODE_POW:
         visitArithmeticOp(scope, node);
         break;

      case MEM_NODE_AND:
      case MEM_NODE_OR:
         visitLogicalExpr(scope, node);
         break;

      case MEM_NODE_AMPERSAND:
         visitAmpersand(scope, node);
         break;

      case MEM_NODE_CALL:
         visitCall(scope, static_cast<node::Call*>(node));
         break;

      case MEM_NODE_IF:
         visitIf(scope, node);
         break;

      case MEM_NODE_FINAL_ID:
         visitFinalId(scope, static_cast<node::Text*>(node));
         break;

      case MEM_NODE_GROUP:
         visitExpr(scope, node->getChild(0));
         node->sExprType(node->getChild(0)->gExprType());
         break;

      case MEM_NODE_EXPR_LIST:
         visitExprList(scope, node);
         break;

      case MEM_NODE_NEW:
         visitNew(scope, static_cast<node::New*>(node));
         break;

      case MEM_NODE_RETURN:
         visitReturn(scope, node);
         break;

      case MEM_NODE_WHILE:
         visitWhile(scope, static_cast<node::While*>(node));
         break;

      case MEM_NODE_DOT:
         visitDot(scope, node);
         break;
   }
}

void
BlockTypesChecker::visitIf (st::Symbol* scope, node::Node* if_node)
{
   // Check condition expression
   visitExpr(scope, if_node->getChild(0));
   ensureBoolExpr(if_node->getChild(0));

   // Check block statements
   visitBlock(scope, if_node->getChild(1));
}

void
BlockTypesChecker::visitNew (st::Symbol* scope, node::New* new_node)
{
   assert(new_node != NULL);

   node::Node* ty_node = new_node->gTypeNode();

   visitExpr(scope, ty_node);
   ensureSymbolIsType(ty_node, ty_node->gBoundSymbol());

   if (!ty_node->gBoundSymbol()->isPtrSymbol())
   {
      std::string ptr_ty_name = ty_node->gBoundSymbol()->gName() + "*";
      st::Symbol* ptr_ty = st::Util::lookupSymbol(scope, ptr_ty_name);
      new_node->sExprType(static_cast<st::Ptr*>(ptr_ty));
   }
   // Trying to instantiate pointer type
   else
   {
      // Recover by using base type instead of pointer type
      std::string ptr_ty_name = 
         static_cast<st::Ptr*>(ty_node->gBoundSymbol())->gBaseType()->gName();
      ptr_ty_name += "*";
      st::Symbol* ptr_ty = st::Util::lookupSymbol(scope, ptr_ty_name);
      new_node->sExprType(static_cast<st::Ptr*>(ptr_ty));

      log::CannotInstantiatePointerType* err =
         new log::CannotInstantiatePointerType();
      err->sPointerTypeName(ty_node->gBoundSymbol()->gQualifiedName());
      err->sPosition(ty_node->copyPosition());
      err->format();
      log(err);
   }
}

void
BlockTypesChecker::visitVarLiteralNumber (st::Type* expected_type,
   node::Text* nb_node)
{
/**
   if (expected_type == this->_symbols->_glob_int_cls)
   {
      int val = 0;
      node::Number* num_node = new node::Number();

      if (mem::Util::getIntFromString(nb_node->gValue().c_str(), val))
      {
         printf("INT ! %d\n", val);
         nb_node->gParent()->replaceChild(nb_node, num_node);
         num_node->setInt(val);
         num_node->sExprType(this->_symbols->_glob_int_cls);
         delete nb_node;
      }
      else
      {
         printf("NOT int...\n");
      }
      //char* small = nb_node->gValue().substr(0, nb_node->gValue().length()-1);
   }
*/
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
      assert (id_node->hasBoundSymbol());

      // FIXME This shouldn't be done here, there should be a function to get
      // the expression type from a symbol
      if (sym->isAnyTypeSymbol())
      {
         id_node->sExprType(sym);
      }
      else if (sym->isVarSymbol())
      {
         id_node->sExprType(static_cast<st::Var*>(sym)->gType());
      }
      else if (sym->isFuncSymbol())
      {
         id_node->sExprType(static_cast<st::Func*>(sym)->gReturnType());
      }
      else
      {
         assert (false && "Unsupported symbol type.");
      }

      assert (id_node->hasExprType());
   }
   else
   {
      log::SymbolNotFound* err = new log::SymbolNotFound();
      err->sSymbolName(id_node->gValue());
      err->sScopeName(scope->gQualifiedName());
      err->sPosition(id_node->copyPosition());
      err->format();
      log(err);
   }
}

void
BlockTypesChecker::visitBlock (st::Symbol* scope, node::Node* block)
{
   node::Node* st = NULL;

   for (size_t i = 0; i < block->gChildCount(); ++i)
   {
      st = block->getChild(i);

      switch (st->gType())
      {
         case MEM_NODE_VARIABLE_DECLARATION:
            visitVarDecl(scope, static_cast<node::VarDecl*>(st));
            break;

         case MEM_NODE_VARIABLE_ASSIGNMENT:
            visitVarAssign(scope, static_cast<node::VarAssign*>(st));
            break;

         default:
            visitExpr(scope, st);
      }
   }
}

void
BlockTypesChecker::visitReturn (st::Symbol* scope, node::Node* ret_node)
{
   //FIXME This should check that the expr type is the same as the function
   // definition
   visitExpr(scope, ret_node->getChild(0));
}

void
BlockTypesChecker::visitVarAssign (st::Symbol* scope, node::VarAssign* node)
{
   assert (node != NULL);
   assert (node->gNameNode() != NULL);
   assert (node->gValueNode() != NULL);

   visitFinalId(scope, static_cast<node::Text*>(node->gNameNode()));
   if (node->gNameNode()->gBoundSymbol() != NULL
      && node->gNameNode()->gBoundSymbol()->isVarSymbol())
   {
      st::Type* expected_ty = static_cast<st::Var*>(
         node->gNameNode()->gBoundSymbol())->gType();
      visitExpr(scope, node->gValueNode());
      ensureExprType(node->gValueNode(), expected_ty);

      node->sBoundSymbol(node->gNameNode()->gBoundSymbol());
      node->sExprType(node->gNameNode()->gExprType());
   }
}

void
BlockTypesChecker::visitVarDecl (st::Symbol* scope,
   node::VarDecl* var_decl_node)
{
   // Value is declared
   if (var_decl_node->gValueNode() != NULL)
   {
      visitExpr(scope, var_decl_node->gValueNode());
   }

   // Type is not explicitly declared (type inference)
   if (var_decl_node->gTypeNode()->isPlaceHolderNode())
   {
      var_decl_node->sExprType(var_decl_node->gValueNode()->gExprType());
      var_decl_node->gTypeNode()->sExprType(var_decl_node->gExprType());
      var_decl_node->gTypeNode()->sBoundSymbol(var_decl_node->gExprType());
   }
   else
   {
      // Check type node
      visitExpr(scope, var_decl_node->gTypeNode());
      var_decl_node->sExprType(var_decl_node->gTypeNode()->gExprType());
      if (!var_decl_node->gTypeNode()->hasExprType())
      {
         printf("<%s>.type_node has no expr type\n",
            var_decl_node->gNameNode()->gValue().c_str());
      }
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
         log::VariableAlreadyDefined* err = new log::VariableAlreadyDefined();
         err->sVarName(var_decl_node->gName());
         err->sPosition(var_decl_node->copyPosition());
         err->format();
         log(err);
      }
   }
}

void
BlockTypesChecker::visitWhile (st::Symbol* scope, node::While* while_node)
{
   // Check condition node
   visitExpr(scope, while_node->gConditionNode());
   ensureBoolExpr(while_node->gConditionNode());

   // Check block node
   visitBlock(scope, while_node->gBodyNode());
}


} } }
