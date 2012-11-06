#include "mem/st/util.hpp"


namespace mem { namespace st { namespace util {

st::Namespace*
createNamespace (Symbol* scope, std::vector<std::string> ns_name_parts)
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
   assert(cur_scope->Parent() != NULL);
   assert(cur_ns->Kind() == st::MetaKind::NAMESPACE);
   return static_cast<st::Namespace*>(cur_ns);
}

Type*
getExprType (Symbol* s)
{
   assert (s != NULL);

   st::Type* ret = NULL;

   if (st::isa<st::Type>(s))
   {
      ret = st::cast<st::Type>(s);
   }
   else if (st::isa<st::Arg>(s))
   {
      ret = st::cast<st::Arg>(s)->Type();
   }
   else if (st::isa<st::Field>(s))
   {
      ret = st::cast<st::Field>(s)->Type();
   }
   else if (st::isa<st::Var>(s) || st::isa<st::Null>(s))
   {
      ret = st::cast<st::Var>(s)->Type();
   }
   else if (st::isa<st::Func>(s))
   {
      // FIXME : Which one ?
      ret = st::cast<st::Func>(s)->Type();
      ret = st::cast<st::FunctionType>(ret)->FunctorType();
   }

   return ret;
}

FunctionType*
getFunctionType (Symbol* scope, TypeVector arguments, Type* return_type)
{
   st::Symbol* child = NULL;
   Symbol::SymbolCollectionIterator i;

   for (i = scope->Children().begin(); i != scope->Children().end(); ++i)
   {
      child = i->second;
      if (st::isa<st::FunctionType>(child) && st::cast<st::FunctionType>(child)->isLike(arguments, return_type))
      {
         return st::cast<st::FunctionType>(child);
      }
   }

   // Function type was not found, create it
   st::FunctionType* func_ty = new st::FunctionType();
   func_ty->setReturnType(return_type);
   func_ty->addArguments(arguments);
   scope->addChild(func_ty);

   return func_ty;
}

IntConstant*
getNativeCharConstant(Symbol* scope, char i)
{
   IntConstant* c = new IntConstant();
   c->setChar(i);
   scope->addChild(c);
   return c;
}

IntConstant*
getNativeShortConstant(Symbol* scope, short i)
{
   IntConstant* c = new IntConstant();
   c->setShort(i);
   scope->addChild(c);
   return c;
}

IntConstant*
getNativeIntConstant(Symbol* scope, int i)
{
   IntConstant* c = new IntConstant();
   c->setInt(i);
   scope->addChild(c);
   return c;
}

Type*
getPointerBaseType (PointerType* ptr)
{
   Type* base_ty = NULL;
   while (st::isa<st::PointerType>(ptr))
   {
      ptr = st::cast<st::PointerType>(ptr->PointedType());
   }
   if (!st::isa<st::PointerType>(ptr))
   {
      base_ty = ptr;
   }
   return base_ty;
}

PointerType*
getPointerType (Type* base_ty)
{
   if (base_ty != NULL && base_ty->Parent() != NULL)
   {
      st::Symbol* ty = base_ty->Parent()->getChild(base_ty->Name() + "*");
      if (ty == NULL)
      {
         st::PointerType* ptr_ty = new PointerType();
         ptr_ty->setName(base_ty->Name() + "*");
         ptr_ty->setPointedType(base_ty);
         base_ty->Parent()->addChild(ptr_ty);
         return ptr_ty;
      }
      else if (st::isa<st::PointerType>(ty))
      {
         return st::cast<st::PointerType>(ty);
      }
   }

   return NULL;
}

size_t
getIndirectionCount (std::string ty_name)
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
getSymbol (Symbol* scope, std::string sym_name)
{
   //DEBUG_PRINT("getSymbol()\n");
   Symbol* res = NULL;

   if (scope != NULL && sym_name.size() != 0)
   {
      while (scope != NULL)
      {
         res = scope->getChild(sym_name);
         if (res != NULL) break;
         scope = scope->Parent();
      }
      if (res != NULL && st::isa<st::Alias>(res))
      {
         res = st::cast<st::Alias>(res)->Aliased();
      }
   }

   return res;
}

TupleType*
getTupleType (Symbol* scope, TypeVector tys)
{
   st::Symbol* child = NULL;
   Symbol::SymbolCollectionIterator i;

   for (i = scope->Children().begin(); i != scope->Children().end(); ++i)
   {
      child = i->second;
      if (st::isa<st::TupleType>(child))
      {
         if (st::cast<st::TupleType>(child)->hasTypes(tys))
         {
            return st::cast<st::TupleType>(child);
         }
      }
   }

   // TupleType is not found, create it
   st::TupleType* tuple_ty = new st::TupleType();
   tuple_ty->addTypes(tys);
   scope->addChild(tuple_ty);

   return tuple_ty;
}

ArrayType*
getSizedArrayType (Type* item_ty, int size)
{
   if (item_ty != NULL && item_ty->Parent() != NULL)
   {
      std::stringstream arr_ty_name;
      arr_ty_name << "[" << item_ty->Name() << "," << size << "]";
      Symbol* sym = item_ty->Parent()->getChild(arr_ty_name.str());

      if (sym == NULL)
      {
         st::ArrayType* ty = new ArrayType();
         ty->setItemType(item_ty);
         ty->setName(arr_ty_name.str());
         ty->setArrayLength(size);
         item_ty->Parent()->addChild(ty);

         return ty;
      }
      else
      {
         return st::cast<st::ArrayType>(sym);
      }
      DEBUG_UNREACHABLE();
   }
   return NULL;

}

ArrayType*
getUnsizedArrayType (ArrayType* sized_array)
{
   return getUnsizedArrayType(sized_array->ItemType());
}

ArrayType*
getUnsizedArrayType (Type* base_ty)
{
   if (base_ty != NULL)
   {
      std::stringstream arr_ty_name;
      arr_ty_name << "[" << base_ty->Name() << "]";
      Symbol* sym = base_ty->Parent()->getChild(arr_ty_name.str());

      if (sym == NULL)
      {
         st::ArrayType* ty = new ArrayType();
         ty->setItemType(base_ty);
         ty->setName(arr_ty_name.str());
         ty->setArrayLength(-1);
         base_ty->Parent()->addChild(ty);

         return ty;
      }
      else
      {
         return st::cast<st::ArrayType>(sym);
      }
      DEBUG_UNREACHABLE();
   }
   return NULL;
}

bool
isFunctorType (Symbol* s)
{
   if (s != NULL && st::isa<st::PointerType>(s))
   {
      Type* pointed_ty = st::cast<st::PointerType>(s)->getNonPointerParent();
      if (st::isa<st::FunctionType>(pointed_ty)) return true;
   }
   return false;
}

ArrayType*
lookupArrayType (Symbol* scope, std::string base_ty_name, int size)
{
   ArrayType* arr_ty = NULL;
   Symbol* base_ty = util::lookupSymbol(scope, base_ty_name);

   if (base_ty != NULL && st::isa<st::Type>(base_ty))
   {
      std::stringstream str;
      str << "[";
      str << base_ty->Name();
      str << ",";
      str << size;
      str << "]";

      arr_ty = new ArrayType();
      arr_ty->setItemType(st::cast<st::Type>(base_ty));
      arr_ty->setName(str.str());
      arr_ty->setArrayLength(size);

      base_ty->Parent()->addChild(arr_ty);
   }

   return arr_ty;
}

Class*
lookupClass (Symbol* scope, std::string cls_name)
{
   Symbol* cls = util::lookupSymbol(scope, cls_name);
   if (cls != NULL && st::isa<st::Class>(cls))
   {
      return st::cast<st::Class>(cls);
   }
   return NULL;
}

Func*
lookupFunction (Symbol* scope, std::string func_name)
{
   Symbol* func = util::lookupSymbol(scope, func_name);
   if (func != NULL && st::isa<st::Func>(func))
   {
      return st::cast<Func>(func);
   }
   return NULL;
}

Symbol*
lookupMember (Symbol* scope, std::string symbol_name)
{
   Symbol* res = NULL;

   while (scope != NULL)
   {
      res = scope->getChild(symbol_name);
      if (res != NULL) return res;
      scope = st::cast<st::Class>(scope)->ParentType();
   }

   return NULL;
}

Symbol*
lookupSymbol (Symbol* scope, std::string symbol_name)
{
   Symbol* res = NULL;

   if (scope != NULL && symbol_name.size() != 0)
   {
      res = getSymbol(scope, symbol_name);

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

      if (res != NULL && st::isa<st::Alias>(res))
      {
         res = st::cast<st::Alias>(res)->Aliased();
      }
   }

   return res;
}

Symbol*
lookupSymbol (Symbol* scope, std::vector<std::string> parts)
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
      cur_scope = cur_scope->Parent();
   }

   return NULL;
}

st::PointerType*
lookupPointer(Symbol* scope, Type* base_ty)
{
   st::Symbol* parent = base_ty->Parent();
   if (parent != NULL && st::isa<st::Alias>(parent))
   {
      parent = st::cast<st::Alias>(parent)->Aliased();
   }
   st::Symbol* ptr = parent->getChild(base_ty->Name() + "*");

   if (ptr == NULL)
   {
      st::PointerType* ptr_ty = new PointerType();
      ptr_ty->setName(base_ty->Name() + "*");
      ptr_ty->setPointedType(base_ty);
      parent->addChild(ptr_ty);

      return ptr_ty;
   }
   else if (st::isa<st::PointerType>(ptr))
   {
      return st::cast<st::PointerType>(ptr);
   }

   return NULL;
}

st::PointerType*
lookupPointer (Symbol* scope, std::string base_ty_name, size_t ptr_level)
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
         cur_sym = st::cast<st::Type>(lookupSymbol(scope, base_ty_name));
         if (cur_sym == NULL) break;
      }
      else
      {
         tmp_ptr = st::cast<st::PointerType>(getSymbol(scope, cur_ptr_name));

         if (tmp_ptr != NULL)
         {
            cur_sym = tmp_ptr;
         }
         else
         {
            // Create the pointer type
            PointerType* ptr_symb = new PointerType();
            ptr_symb->setName(cur_ptr_name);
            ptr_symb->setPointedType(cur_sym);

            // Add the pointer at the same level as the base type
            IF_DEBUG
            {
               if (cur_sym->Parent() == NULL)
               {
                  DEBUG_PRINTF("Symbol <%s>(%d) must have a parent",
                     cur_sym->Name().c_str(), cur_sym->Kind());
               }
               assert(cur_sym->Parent() != NULL);
            }

            cur_sym->Parent()->addChild(ptr_symb);
            cur_sym = ptr_symb;
         }
      }
      cur_ptr_name += "*";
   }

   DEBUG_ENSURE(cur_sym == NULL || st::isa<st::PointerType>(cur_sym));

   return st::cast<st::PointerType>(cur_sym);
}

bool
parseArrayTypeName (std::string name, std::string& base_ty_name,
   int& array_len)
{
   base_ty_name = "";
   array_len = -1;

   if (name[0] == ']' && name[name.size()-1] == ']')
   {
      size_t comma_pos = name.find_first_of(',');
      if (comma_pos != std::string::npos)
      {
         //base_ty_name = name[1, comma_pos];
         // FIXME This may fail badly
         array_len = atoi(name.substr(comma_pos+1,name.size()-2).c_str());
      }
      else
      {
         //base_ty_name = name[1, name.size()-2];
      }
      return true;
   }
   return false;
}

void
registerType (SymbolTable* st, Symbol* scope, Type* ty)
{
   scope->addChild(ty);
   st->_types[ty->gQualifiedName()] = ty;
}

void
setupBool (SymbolTable& st, CoreTypes& core_types)
{
   util::registerType(&st, st.System(), core_types.BoolTy());

   st::Var* symTrue = new st::Var("true", core_types.BoolTy());
   symTrue->setIsConstant(true);

   st::Var* symFalse = new st::Var("false", core_types.BoolTy());
   symFalse->setIsConstant(true);

   st.System()->addChild(symTrue);
   st.System()->addChild(symFalse);
}

void
setupBugType (SymbolTable& st, CoreTypes& core_types)
{
   core_types._bug_type = new st::PrimitiveType();
   core_types._bug_type->setName("$BadType");
   util::registerType(&st, st.System(), core_types._bug_type);
}

void
setupInts (SymbolTable& st, CoreTypes& core_types)
{
   util::registerType(&st, st.System(), core_types.CharTy());
   util::registerType(&st, st.System(), core_types.UCharTy());
   util::registerType(&st, st.System(), core_types.ShortTy());
   util::registerType(&st, st.System(), core_types.UShortTy());
   util::registerType(&st, st.System(), core_types.IntTy());
   util::registerType(&st, st.System(), core_types.UIntTy());
   util::registerType(&st, st.System(), core_types.LongTy());
   util::registerType(&st, st.System(), core_types.ULongTy());
   util::registerType(&st, st.System(), core_types.Int8Ty());
   util::registerType(&st, st.System(), core_types.Int16Ty());
   util::registerType(&st, st.System(), core_types.Int32Ty());
   util::registerType(&st, st.System(), core_types.Int64Ty());
   util::registerType(&st, st.System(), core_types.UInt8Ty());
   util::registerType(&st, st.System(), core_types.UInt16Ty());
   util::registerType(&st, st.System(), core_types.UInt32Ty());
   util::registerType(&st, st.System(), core_types.UInt64Ty());
}

void
setupVoid (SymbolTable& st, CoreTypes& core_types)
{
   util::registerType(&st, st.System(), core_types.VoidTy());

   core_types._null = new st::Null();
   core_types._null->setType(getPointerType(core_types.VoidTy()));

   st.System()->addChild(core_types._null);
}

std::vector<std::string>
splitQualifiedName (std::string name)
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

} } }
