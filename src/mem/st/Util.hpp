#ifndef _MEM__ST__UTIL__HPP_
#define _MEM__ST__UTIL__HPP_


#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/st/Var.hpp"

namespace mem { namespace st {


class Util
{
   public: static Class* lookupClass (Symbol* scope, std::string cls_name);
   public: static Func* lookupFunction (Symbol* scope, std::string func_name);
   public: static Symbol* lookupMember (Symbol* scope, std::string symbol_name);
   public: static Symbol* lookupSymbol (Symbol* scope, std::string symbol_name);
};


} }

#endif
