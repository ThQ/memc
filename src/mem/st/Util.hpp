#ifndef _MEM__ST__UTIL__HPP_
#define _MEM__ST__UTIL__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/st/Array.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/st/Primitive.hpp"
#include "mem/st/Ptr.hpp"
#include "mem/st/Type.hpp"
#include "mem/st/Var.hpp"


namespace mem { namespace st {


class Util
{
   public:

   static st::Namespace*
   createNamespace (Symbol* scope, std::vector<std::string> ns_name_parts);

   static Type*
   getPointerBaseType(Ptr* ptr);

   static Symbol*
   getSymbol (Symbol* scope, std::string symbol_name);

   static size_t
   getIndirectionCount (std::string type_name);

   static Array*
   lookupArrayType (Symbol* scope, std::string base_ty_name, int size);

   static Class*
   lookupClass (Symbol* scope, std::string cls_name);

   static Func*
   lookupFunction (Symbol* scope, std::string func_name);

   static Ptr*
   lookupPointer(Symbol* scope, std::string base_ty_name, size_t ptr_level);

   static Ptr*
   lookupPointer (Symbol* scope, Type* base_ty);

   static Symbol*
   lookupMember (Symbol* scope, std::string symbol_name);

   static Symbol*
   lookupSymbol (Symbol* scope, std::string symbol_name);

   static bool
   parseArrayTypeName (std::string name, std::string& base_ty_name, int& array_len);

   static void
   registerType (SymbolTable* st, Symbol* scope, Type* ty);

   static void
   setupBool (SymbolTable& st, CoreTypes& core_types);

   static void
   setupInts (SymbolTable& st, CoreTypes& core_types);

   static void
   setupVoid (SymbolTable& st, CoreTypes& core_types);
};


} }

#endif
