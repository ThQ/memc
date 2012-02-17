#ifndef _MEM__ST__SYMBOL_TABLE__HPP_
#define _MEM__ST__SYMBOL_TABLE__HPP_


#include <assert.h>
#include <stdlib.h>
#include <string>
#include "check.h"
#include "mem/st/Class.hpp"
#include "mem/st/Function.hpp"
#include "mem/st/Namespace.hpp"
#include "mem/st/Path.hpp"
#include "mem/st/Var.hpp"
#include "mem/Util.hpp"


namespace mem { namespace st {


class SymbolTable
{
   public: st::Class* _glob_bool_cls;
   public: Namespace* _root;

   public: SymbolTable ();
   public: ~SymbolTable ();
   public: Class* create_class (std::string full_class_name);
   public: bool create_type (Type* anonymous_type, std::string full_type_name);
   public: Namespace* create_namespace (std::string name);
   //public: void dump ();
   public: Namespace* get_namespace (std::string ns_name);
   public: Symbol* get_symbol (std::string name);
   public: bool has_class (std::string class_name);
   public: bool has_namespace (std::string ns_name);
   public: Function* register_function (std::string func_full_name);
   public: bool register_symbol (std::string path, Symbol* sym);
   public: void setup ();
   public: void setup_bool ();
   public: void setup_ints ();
};


} }

#endif
