#include "mem/st/Util.hpp"

namespace mem { namespace st {

st::Namespace*
Util::createNamespace (Symbol* scope, std::vector<std::string> ns_name_parts)
{
   st::Symbol* existing_ns = NULL;
   st::Symbol* cur_ns = NULL;
   Symbol* cur_scope = scope;

   for (size_t i = 0; i < ns_name_parts.size() ; ++i)
   {
      existing_ns = cur_scope->getChild(ns_name_parts[i]);
      if (existing_ns == NULL)
      {
         cur_ns = new st::Namespace();
         cur_ns->sName(ns_name_parts[i]);
         cur_scope->addChild(cur_ns);
      }
      else
      {
         cur_ns = existing_ns;
      }
      cur_scope = cur_ns;
   }
   assert(cur_scope->_parent != NULL);
   assert(cur_ns->is(NAMESPACE));
   return static_cast<st::Namespace*>(cur_ns);
}

/*
st::FunctionSignature*
Util::lookupFunctionSignature(Symbol* scope, Func* base_func, std::vector<st::Symbol*> params)
{
   printf("lookup func [%s] in [%s]\n", base_func->gQualifiedNameCstr(), scope->gQualifiedNameCstr());
   Func* func = Util::lookupFunction(static_cast<st::Class*>(scope)->gParentType(), base_func->gName());

   while (func != NULL)
   {
      std::map<std::string, st::Symbol*>::iterator i;
      for (i = func->_children.begin(); i != func->_children.end() ; ++i)
      {
         printf ("- Testing %s\n", static_cast<st::FunctionSignature*>((*i).second)->gSignature().c_str());

         if(static_cast<st::FunctionSignature*>((*i).second)->canOverride(params))
         {
            printf ("-> OKAY !!\n");
            return static_cast<st::FunctionSignature*>((*i).second);
         }
      }
      func = func->gOverloadedFunc();
   }
   return NULL;
}
*/

/*
std::vector<st::FunctionSignature*>
Util::listFuncSigns (st::Class* cls_sym, std::string func_name)
{
   std::vector<st::FunctionSignature*> signs;

   st::Class* cur_class = cls_sym;
   st::Func* cur_func = NULL;

   while (cur_class != NULL)
   {
      cur_func = Util::lookupFunction(cur_class, func_name);
      if (cur_func != NULL)
      {
         for (std::map<std::string, st::Symbol*>::iterator i=cur_func->_children.begin();
            i != cur_func->_children.end(); ++i)
         {
            signs.push_back(static_cast<st::FunctionSignature*>(i->second));
         }
      }
      cur_class = static_cast<st::Class*>(cur_class->_parent_type);
   }
   return signs;
}
*/

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
   Symbol* origin_scope = scope;

   // Lookup the symbol regardless of whether it's a pointer
   while (scope != NULL)
   {
      res = scope->getChild(symbol_name);
      if (res != NULL)
      {
         break;
      }
      scope = scope->_parent;
   }

   // Symbol is not found, maybe it is a pointer
   if (res == NULL)
   {
      int ptr_level = 0;

      for (std::string::iterator i = symbol_name.end()-1; i >= symbol_name.begin(); --i)
      {
         if (*i == '*')
         {
            ptr_level ++;
         }
         else
         {
            break;
         }
      }

      // It is a pointer, look the base type up
      if (ptr_level > 0)
      {
         std::string origin_symbol_name = symbol_name;
         symbol_name = symbol_name.substr(0, symbol_name.size() - ptr_level);

         st::Symbol* base_ty = lookupSymbol(origin_scope, symbol_name);
         if (base_ty != NULL && base_ty->isAnyTypeSymbol())
         {
            Ptr* ptr_symb = new Ptr();
            ptr_symb->sName(origin_symbol_name);
            ptr_symb->sBaseType(static_cast<Class*>(base_ty));
            base_ty->_parent->addChild(ptr_symb);
            res = ptr_symb;
         }
      }
   }

   if (res == NULL)
   {
      printf("SYMB_NOT_FOUND <%s>\n", symbol_name.c_str());
   }
   return res;
}

void
Util::registerType (SymbolTable* st, Symbol* scope, Type* ty)
{
   scope->addChild(ty);
   st->_types[ty->gQualifiedName()] = ty;
}

void
Util::setupBool (SymbolTable& st, CoreTypes& core_types)
{
   core_types._bool = new st::Primitive();
   core_types._bool->sName("bool");
   Util::registerType(&st, st.gRoot(), core_types._bool);

   st.gRoot()->addChild(new st::Var("true", core_types._bool));
   st.gRoot()->addChild(new st::Var("false", core_types._bool));
}

void
Util::setupInts (SymbolTable& st, CoreTypes& core_types)
{
   // Type : char
   core_types._char = new st::Primitive();
   core_types._char->sName("char");
   Util::registerType(&st, st.gRoot(), core_types._char);

   // Type : short
   core_types._short = new st::Primitive();
   core_types._short->sName("short");
   Util::registerType(&st, st.gRoot(), core_types._short);

   // Function : short_add_short
   st::Func* func_s_add_s = new st::Func();
   func_s_add_s->sName("short_plus_short");
   func_s_add_s->addParam("base_short", core_types._short);
   func_s_add_s->addParam("short_to_add", core_types._short);
   func_s_add_s->sReturnType(core_types._short);
   st.gRoot()->addChild(func_s_add_s);

   // Type : int
   core_types._int = new st::Primitive();
   core_types._int->sName("int");
   Util::registerType(&st, st.gRoot(), core_types._int);

   // Function : int_add_int
   st::Func* func_i_add_i = new st::Func();
   func_i_add_i->sName("int_plus_int");
   func_i_add_i->addParam("base_int", core_types._int);
   func_i_add_i->addParam("int_to_add", core_types._int);
   func_i_add_i->sReturnType(core_types._int);
   st.gRoot()->addChild(func_i_add_i);

   // Function : int_add_short
   st::Func* func_i_add_s = new st::Func();
   func_i_add_s->sName("int_plus_short");
   func_i_add_s->addParam("base_int", core_types._int);
   func_i_add_s->addParam("short_to_add", core_types._short);
   func_i_add_s->sReturnType(core_types._int);
   st.gRoot()->addChild(func_i_add_s);
}

void
Util::setupVoid (SymbolTable& st, CoreTypes& core_types)
{
   core_types._void = new st::Primitive();
   core_types._void->sName("void");
   Util::registerType(&st, st.gRoot(), core_types._void);

   st.gRoot()->addChild(new st::Var("null", core_types._void));
}

} }
