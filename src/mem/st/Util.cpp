#include "mem/st/Util.hpp"

namespace mem { namespace st {

Class*
Util::lookupClass (Symbol* scope, std::string cls_name)
{
   Symbol* cls = Util::lookupSymbol(scope, cls_name);
   if (cls != NULL && cls->is(CLASS))
   {
      return static_cast<Class*>(cls);
   }
   return NULL;
}

Func*
Util::lookupFunction (Symbol* scope, std::string func_name)
{
   Symbol* func = Util::lookupSymbol(scope, func_name);
   if (func != NULL && func->is(FUNCTION))
   {
      return static_cast<Func*>(func);
   }
   return NULL;
}

Symbol*
Util::lookupMember (Symbol* scope, std::string symbol_name)
{
   Symbol* res = NULL;

   while (scope != NULL)
   {
      res = scope->getChild(symbol_name);
      if (res != NULL) return res;
      scope = static_cast<Class*>(scope)->_parent_type;
   }

   return NULL;
}

Symbol*
Util::lookupSymbol (Symbol* scope, std::string symbol_name)
{
   Symbol* res = NULL;

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


} }
