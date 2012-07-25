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
         cur_ns->setName(ns_name_parts[i]);
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

Type*
Util::getPointerBaseType (Ptr* ptr)
{
   Type* base_ty = NULL;
   while (ptr->isPtrSymbol())
   {
      ptr = static_cast<st::Ptr*>(ptr->BaseType());
   }
   if (!ptr->isPtrSymbol())
   {
      base_ty = ptr;
   }
   return base_ty;
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

size_t
Util::getIndirectionCount (std::string ty_name)
{
   size_t indir_count = 0;
   std::string::iterator i;

   for (i = ty_name.end()-1; i >= ty_name.begin(); --i)
   {
      if (*i == '*')
      {
         indir_count ++;
      }
      else
      {
         break;
      }
   }

   return indir_count;
}

Symbol*
Util::getSymbol (Symbol* scope, std::string sym_name)
{
   Symbol* res = NULL;

   if (scope != NULL && sym_name.size() != 0)
   {
      Symbol* origin_scope = scope;

      while (scope != NULL)
      {
         res = scope->getChild(sym_name);
         if (res != NULL)
         {
            break;
         }
         scope = scope->_parent;
      }
   }

   return res;
}

Array*
Util::lookupArrayType (Symbol* scope, std::string base_ty_name, int size)
{
   Array* arr_ty = NULL;
   Symbol* base_ty = Util::lookupSymbol(scope, base_ty_name);

   if (base_ty != NULL && base_ty->isAnyTypeSymbol())
   {
      std::stringstream str;
      str << "[";
      str << base_ty->Name();
      str << ",";
      str << size;
      str << "]";

      arr_ty = new Array();
      arr_ty->setBaseType(static_cast<Type*>(base_ty));
      arr_ty->setName(str.str());
      arr_ty->setArrayLength(size);

      base_ty->_parent->addChild(arr_ty);
   }

   return arr_ty;
}

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
   assert(scope != NULL);
   assert(symbol_name.size() != 0);

   Symbol* res = getSymbol(scope, symbol_name);

   // Symbol is not found, maybe it is a pointer
   if (res == NULL)
   {
      size_t ptr_level = getIndirectionCount(symbol_name);

      // It is a pointer, look the base type up
      if (ptr_level > 0)
      {
         std::string base_ty_name = symbol_name.substr(0, symbol_name.size() - ptr_level);
         res = lookupPointer(scope, base_ty_name, ptr_level);
      }
   }

   IF_DEBUG
   {
      if (res == NULL)
      {
         DEBUG_PRINTF("Symbol <%s> not found in <%s>.\n",
            scope->gQualifiedNameCstr(), symbol_name.c_str());
      }
   }
   return res;
}

st::Ptr*
Util::lookupPointer (Symbol* scope, std::string base_ty_name, size_t ptr_level)
{
   assert(ptr_level > 0);

   st::Type* tmp_ptr = NULL;
   st::Type* cur_sym = NULL;
   std::string cur_ptr_name = base_ty_name;

   for (int i = 0; i <= ptr_level; ++i)
   {
      if (i == 0)
      {
         cur_sym = static_cast<st::Type*>(lookupSymbol(scope, base_ty_name));
      }
      else
      {
         tmp_ptr = static_cast<st::Ptr*>(getSymbol(scope, cur_ptr_name));

         if (tmp_ptr != NULL)
         {
            cur_sym = tmp_ptr;
         }
         else
         {
            // Create the pointer type
            Ptr* ptr_symb = new Ptr();
            ptr_symb->setName(cur_ptr_name);
            ptr_symb->setBaseType(cur_sym);

            // Add the pointer at the same level as the base type
            cur_sym->_parent->addChild(ptr_symb);

            cur_sym = ptr_symb;
         }
      }
      cur_ptr_name += "*";
   }

   assert(cur_sym->isPtrSymbol());
   return static_cast<Ptr*>(cur_sym);
}

bool
Util::parseArrayTypeName (std::string name, std::string& base_ty_name,
   int& array_len)
{
   base_ty_name = "";
   array_len = -1;

   if (name[0] == ']' && name[name.size()-1] == ']')
   {
      size_t comma_pos = name.find_first_of(',');
      if (comma_pos != std::string::npos)
      {
         base_ty_name = name[1, comma_pos];
         // FIXME This may fail badly
         array_len = atoi(name.substr(comma_pos+1,name.size()-2).c_str());
      }
      else
      {
         base_ty_name = name[1, name.size()-2];
      }
      return true;
   }
   return false;
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
   core_types._bool->setName("bool");
   Util::registerType(&st, st.gRoot(), core_types._bool);

   st.gRoot()->addChild(new st::Var("true", core_types._bool));
   st.gRoot()->addChild(new st::Var("false", core_types._bool));
}

void
Util::setupInts (SymbolTable& st, CoreTypes& core_types)
{
   // Type : char
   core_types._char = new st::Primitive();
   core_types._char->setName("char");
   Util::registerType(&st, st.gRoot(), core_types._char);

   // Type : short
   core_types._short = new st::Primitive();
   core_types._short->setName("short");
   Util::registerType(&st, st.gRoot(), core_types._short);

   // Function : short_add_short
   st::Func* func_s_add_s = new st::Func();
   func_s_add_s->setName("short_plus_short");
   func_s_add_s->addParam("base_short", core_types._short);
   func_s_add_s->addParam("short_to_add", core_types._short);
   func_s_add_s->setReturnType(core_types._short);
   st.gRoot()->addChild(func_s_add_s);

   // Type : int
   core_types._int = new st::Primitive();
   core_types._int->setName("int");
   Util::registerType(&st, st.gRoot(), core_types._int);

   // Function : int_add_int
   st::Func* func_i_add_i = new st::Func();
   func_i_add_i->setName("int_plus_int");
   func_i_add_i->addParam("base_int", core_types._int);
   func_i_add_i->addParam("int_to_add", core_types._int);
   func_i_add_i->setReturnType(core_types._int);
   st.gRoot()->addChild(func_i_add_i);

   // Function : int_add_short
   st::Func* func_i_add_s = new st::Func();
   func_i_add_s->setName("int_plus_short");
   func_i_add_s->addParam("base_int", core_types._int);
   func_i_add_s->addParam("short_to_add", core_types._short);
   func_i_add_s->setReturnType(core_types._int);
   st.gRoot()->addChild(func_i_add_s);
}

void
Util::setupVoid (SymbolTable& st, CoreTypes& core_types)
{
   core_types._void = new st::Primitive();
   core_types._void->setName("void");
   Util::registerType(&st, st.gRoot(), core_types._void);

   st.gRoot()->addChild(new st::Var("null", core_types._void));
}

} }
