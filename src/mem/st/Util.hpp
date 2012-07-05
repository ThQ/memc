#ifndef _MEM__ST__UTIL__HPP_
#define _MEM__ST__UTIL__HPP_


#include <string>
#include <vector>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/st/Primitive.hpp"
#include "mem/st/Ptr.hpp"
#include "mem/st/Type.hpp"
#include "mem/st/Var.hpp"

namespace mem { namespace st {


class Util
{
   public: static st::Namespace* createNamespace (Symbol* scope, std::vector<std::string> ns_name_parts);
   //public: static std::vector<st::FunctionSignature*> listFuncSigns(st::Class* cls_sym, std::string func_name);
   //public: static st::FunctionSignature* lookupFunctionSignature(Symbol* scope, Func* func, std::vector<st::Symbol*> params);
   public: static Class* lookupClass (Symbol* scope, std::string cls_name);
   public: static Func* lookupFunction (Symbol* scope, std::string func_name);
   public: static Symbol* lookupMember (Symbol* scope, std::string symbol_name);
   public: static Symbol* lookupSymbol (Symbol* scope, std::string symbol_name);
   public: static void registerType (SymbolTable* st, Symbol* scope, Type* ty);
   public: static void setupBool (SymbolTable& st, CoreTypes& core_types);
   public: static void setupInts (SymbolTable& st, CoreTypes& core_types);
   public: static void setupVoid (SymbolTable& st, CoreTypes& core_types);
};


} }

#endif
