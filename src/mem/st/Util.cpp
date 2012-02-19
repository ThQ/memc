#include "mem/st/Util.hpp"

namespace mem { namespace st {

Class*
Util::lookup_class (Symbol* scope, std::string cls_name)
{
   Symbol* cls = Util::lookup_symbol(scope, cls_name);
   if (cls != NULL && cls->is(CLASS))
   {
      return (Class*)cls;
   }
   return NULL;
}

Function*
Util::lookup_function (Symbol* scope, std::string func_name)
{
   Symbol* func = Util::lookup_symbol(scope, func_name);
   if (func != NULL && func->is(FUNCTION))
   {
      return static_cast<Function*>(func);
   }
   return NULL;
}

Symbol*
Util::lookup_member (Symbol* scope, std::string symbol_name)
{
   Symbol* res = NULL;
   if (scope->_kind == INSTANCE)
   {
      scope = static_cast<Instance*>(scope)->_type; //static_cast<Class*>(scope)->g_instance_type();
   }

   while (scope != NULL)
   {
      res = scope->getChild(symbol_name);
      if (res != NULL) return res;
      scope = static_cast<Class*>(scope)->_parent_type;
   }

   return NULL;
}

Symbol*
Util::lookup_symbol (Symbol* scope, std::string symbol_name)
{
   Symbol* res = NULL;
   if (scope->_kind == INSTANCE)
   {
      scope = static_cast<Class*>(scope)->g_instance_type();
   }

   while (scope != NULL)
   {
      res = scope->getChild(symbol_name);
      if (res != NULL)
      {
         return res;
      }
      scope = scope->_parent;
   }
   return NULL;
}

Symbol*
Util::get_eval_type (Symbol* symbol)
{
   switch (symbol->_kind)
   {
      case VAR:
         return static_cast<Var*>(symbol)->_type;
      case FUNCTION:
         return static_cast<Function*>(symbol)->_return_type;
      default:
         return symbol;

   }
}

std::string
Util::get_function_path (SymbolTable* st, ast::node::Node* func)
{
   std::string func_path = "";
   ast::node::Node* node = func;

   while (node != NULL)
   {
      if (node->_type == MEM_NODE_FUNCTION_DECLARATION || node->_type == MEM_NODE_CLASS || node->_type == MEM_NODE_NAMESPACE)
      {
         if (func_path != "")
         {
            func_path.insert(0, ".");
         }
         func_path.insert(0, static_cast<ast::node::Text*>(node)->_value);
      }
      node = node->_parent;
   }
   return func_path;
}

Function*
Util::get_function (SymbolTable* st, ast::node::Node* func)
{
   assert (st != NULL);
   assert (func != NULL);

   std::string func_path = Util::get_function_path(st, func);
   Function* st_func = static_cast<Function*>(st->get_symbol(func_path));

   return st_func;
}

} }
