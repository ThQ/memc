#ifndef _MEM__ST__UTIL__HPP_
#define _MEM__ST__UTIL__HPP_


#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/st/Function.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/st/Var.hpp"

namespace mem { namespace st {


class Util
{
   public: static Class* lookup_class (Symbol* scope, std::string cls_name);
   public: static Function* lookup_function (Symbol* scope, std::string func_name);
   public: static Symbol* lookup_member (Symbol* scope, std::string symbol_name);
   public: static Symbol* lookup_symbol (Symbol* scope, std::string symbol_name);
   public: static Symbol* get_eval_type (Symbol* symbol);
   public: static Function* get_function (SymbolTable* st, ast::node::Node* func);
   public: static std::string get_function_path (SymbolTable* st, ast::node::Node* func);
};


} }

#endif
