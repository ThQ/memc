#ifndef _MEM__ST__SYMBOL_TABLE__HPP_
#define _MEM__ST__SYMBOL_TABLE__HPP_


#include <assert.h>
#include <map>
#include <stdlib.h>
#include <string>
#include "mem/st/Class.hpp"
#include "mem/st/CoreTypes.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/Namespace.hpp"
#include "mem/st/Path.hpp"
#include "mem/st/Var.hpp"
#include "mem/Util.hpp"


namespace mem { namespace st {


class SymbolTable
{
   public: Namespace* _root;
   public: inline Namespace* gRoot () {return _root;}
   public: std::map<std::string, st::Type*> _types;
   public: std::map<std::string, st::Type*> gTypes (){return _types;}

   public: st::CoreTypes _core_types;
   public: inline st::CoreTypes& gCoreTypes(){return _core_types;}

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   SymbolTable ();

   /**
    * Destructor.
    */
   ~SymbolTable ();

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------

   public: Class* create_class (std::string full_class_name);
   public: bool create_type (Type* anonymous_type, std::string full_type_name);
   public: Namespace* create_namespace (std::string name);
   //public: void dump ();
   public: Namespace* get_namespace (std::string ns_name);
   public: Symbol* get_symbol (std::string name);
   public: bool has_class (std::string class_name);
   public: bool has_namespace (std::string ns_name);
   public: Func* register_function (std::string func_full_name);
   public: bool register_symbol (std::string path, Symbol* sym);
};


} }

#endif
