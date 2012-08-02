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
Util::getExprType (Symbol* s)
{
   assert (s != NULL);

   st::Type* ret = NULL;

   if (s->isAnyTypeSymbol())
   {
      ret = static_cast<st::Type*>(s);
   }
   else if (s->isArgSymbol())
   {
      ret = static_cast<st::Arg*>(s)->Type();
   }
   else if (s->isFieldSymbol())
   {
      ret = static_cast<st::Field*>(s)->Type();
   }
   else if (s->isVarSymbol())
   {
      ret = static_cast<st::Var*>(s)->Type();
   }
   else if (s->isFuncSymbol())
   {
      ret = static_cast<st::Type*>(static_cast<st::Func*>(s)->ReturnType());
   }

   return ret;
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

Ptr*
Util::getPointerType (Type* base_ty)
{
   if (base_ty != NULL && base_ty->Parent() != NULL)
   {
      st::Symbol* ty = base_ty->Parent()->getChild(base_ty->Name() + "*");
      if (ty == NULL)
      {
         st::Ptr* ptr_ty = new Ptr();
         ptr_ty->setName(base_ty->Name() + "*");
         ptr_ty->setBaseType(base_ty);
         base_ty->Parent()->addChild(ptr_ty);
         return ptr_ty;
      }
      else if (ty->isPtrSymbol())
      {
         return static_cast<st::Ptr*>(ty);
      }
   }

   return NULL;
}

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
   //DEBUG_PRINT("getSymbol()\n");
   Symbol* res = NULL;

   if (scope != NULL && sym_name.size() != 0)
   {
      Symbol* origin_scope = scope;

      while (scope != NULL)
      {
         //DEBUG_PRINTF("looking sym <%s> in <%s>\n", sym_name.c_str(), scope->Name().c_str());
         res = scope->getChild(sym_name);
         if (res != NULL)
         {
            break;
         }
         scope = scope->_parent;
      }
      if (res != NULL && res->isAliasSymbol())
      {
         res = static_cast<st::Alias*>(res)->Aliased();
      }
   }

   return res;
}

ArrayType*
Util::getUnsizedArrayType (ArrayType* sized_array)
{
   return getUnsizedArrayType(sized_array->BaseType());
}

ArrayType*
Util::getUnsizedArrayType (Type* base_ty)
{
   if (base_ty != NULL)
   {
      std::stringstream arr_ty_name;
      arr_ty_name << "[" << base_ty->Name() << "]";
      Symbol* sym = base_ty->Parent()->getChild(arr_ty_name.str());

      if (sym == NULL)
      {
         st::ArrayType* ty = new ArrayType();
         ty->setBaseType(base_ty);
         ty->setName(arr_ty_name.str());
         ty->setArrayLength(-1);
         base_ty->Parent()->addChild(ty);

         return ty;
      }
      else
      {
         return static_cast<st::ArrayType*>(sym);
      }
      DEBUG_UNREACHABLE;
   }
   return NULL;
}

ArrayType*
Util::lookupArrayType (Symbol* scope, std::string base_ty_name, int size)
{
   ArrayType* arr_ty = NULL;
   Symbol* base_ty = Util::lookupSymbol(scope, base_ty_name);

   if (base_ty != NULL && base_ty->isAnyTypeSymbol())
   {
      std::stringstream str;
      str << "[";
      str << base_ty->Name();
      str << ",";
      str << size;
      str << "]";

      arr_ty = new ArrayType();
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
   Symbol* res = NULL;

   if (scope != NULL && symbol_name.size() != 0)
   {
      res= getSymbol(scope, symbol_name);

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

      if (res != NULL && res->isAliasSymbol())
      {
         res = static_cast<st::Alias*>(res)->Aliased();
      }
   }

   return res;
}

Symbol*
Util::lookupSymbol (Symbol* scope, std::vector<std::string> parts)
{
   DEBUG_REQUIRE (scope != NULL);

   Symbol* cur_scope = scope;
   Symbol* inner_symbol = NULL;
   size_t i = 0;
   while (cur_scope != NULL)
   {
      inner_symbol = cur_scope;
      for (i = 0; i < parts.size(); ++i)
      {
         inner_symbol = inner_symbol->getChild(parts[i]);
         if (inner_symbol == NULL) break;
      }

      if (i == parts.size() && inner_symbol->Name() == parts[i-1])
      {
         return inner_symbol;
      }
      cur_scope = cur_scope->_parent;
   }

   return NULL;
}

st::Ptr*
Util::lookupPointer(Symbol* scope, Type* base_ty)
{
   st::Symbol* parent = base_ty->_parent;
   if (parent != NULL && parent->isAliasSymbol())
   {
      parent = static_cast<st::Alias*>(parent)->Aliased();
   }
   st::Symbol* ptr = parent->getChild(base_ty->Name() + "*");

   if (ptr == NULL)
   {
      st::Ptr* ptr_ty = new Ptr();
      ptr_ty->setName(base_ty->Name() + "*");
      ptr_ty->setBaseType(base_ty);
      parent->addChild(ptr_ty);

      return ptr_ty;
   }
   else if (ptr->isPtrSymbol())
   {
      return static_cast<st::Ptr*>(ptr);
   }

   return NULL;
}

st::Ptr*
Util::lookupPointer (Symbol* scope, std::string base_ty_name, size_t ptr_level)
{
   DEBUG_REQUIRE(scope != NULL);
   DEBUG_REQUIRE(ptr_level > 0);

   st::Type* tmp_ptr = NULL;
   st::Type* cur_sym = NULL;
   std::string cur_ptr_name = base_ty_name;

   for (int i = 0; i <= ptr_level; ++i)
   {
      if (i == 0)
      {
         cur_sym = static_cast<st::Type*>(lookupSymbol(scope, base_ty_name));
         if (cur_sym == NULL) break;
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
            IF_DEBUG
            {
               if (cur_sym->_parent == NULL)
               {
                  DEBUG_PRINTF("Symbol <%s>(%d) must have a parent",
                     cur_sym->Name().c_str(), cur_sym->Kind());
               }
               assert(cur_sym->_parent != NULL);
            }

            cur_sym->_parent->addChild(ptr_symb);
            cur_sym = ptr_symb;
         }
      }
      cur_ptr_name += "*";
   }

   DEBUG_ENSURE(cur_sym == NULL || cur_sym->isPtrSymbol());

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
   core_types._bool->setByteSize(sizeof(bool));
   Util::registerType(&st, st.gRoot(), core_types._bool);

   st.gRoot()->addChild(new st::Var("true", core_types._bool));
   st.gRoot()->addChild(new st::Var("false", core_types._bool));
}

void
Util::setupBugType (SymbolTable& st, CoreTypes& core_types)
{
   core_types._bug_type = new st::Primitive();
   core_types._bug_type->setName("#BadType");
   Util::registerType(&st, st.gRoot(), core_types._bug_type);
}

void
Util::setupInts (SymbolTable& st, CoreTypes& core_types)
{
   // Type : char
   core_types._char = new st::Primitive();
   core_types._char->setName("char");
   core_types._char->setByteSize(sizeof(char));
   Util::registerType(&st, st.gRoot(), core_types._char);

   // Type : short
   core_types._short = new st::Primitive();
   core_types._short->setName("short");
   core_types._short->setByteSize(sizeof(short));
   Util::registerType(&st, st.gRoot(), core_types._short);

   // Type : int
   core_types._int = new st::Primitive();
   core_types._int->setName("int");
   core_types._int->setByteSize(sizeof(int));
   Util::registerType(&st, st.gRoot(), core_types._int);
}

void
Util::setupVoid (SymbolTable& st, CoreTypes& core_types)
{
   core_types._void = new st::Primitive();
   core_types._void->setName("void");
   Util::registerType(&st, st.gRoot(), core_types._void);

   st.gRoot()->addChild(new st::Var("null", core_types._void));
}

std::vector<std::string>
Util::splitQualifiedName (std::string name)
{
   std::vector<std::string> parts;
   std::string buffer = "";
   for (size_t i = 0; i < name.size(); ++i)
   {
      if (name[i] == '.')
      {
         if (buffer.size() != 0)
         {
            parts.push_back(buffer);
            buffer = "";
         }
      }
      else
      {
         buffer += name[i];
      }
   }
   if (buffer.size() != 0) parts.push_back(buffer);

   return parts;
}

} }
