#ifndef _MEM__ST__SYMBOL_TABLE__HPP_
#define _MEM__ST__SYMBOL_TABLE__HPP_


#include <assert.h>
#include <map>
#include <stdlib.h>
#include <string>
#include "mem/st/Class.hpp"
#include "mem/st/CoreTypes.hpp"
#include "mem/st/Func.hpp"
#include "mem/st/Macro.hpp"
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
   public:

   Func* _func_ll_head;
   Func* _func_ll_tail;

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
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // FunctionLinkedListHead
   GETTER(FunctionLinkedListHead, Func*) {return _func_ll_head;}
   SETTER(FunctionLinkedListHead, Func*) {_func_ll_head = val;}

   // FunctionLinkedListTail
   GETTER(FunctionLinkedListTail, Func*) {return _func_ll_tail;}
   SETTER(FunctionLinkedListTail, Func*) {_func_ll_tail = val;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   Class* create_class (std::string full_class_name);
   bool create_type (Type* anonymous_type, std::string full_type_name);
   Namespace* create_namespace (std::string name);
   Namespace* get_namespace (std::string ns_name);
   Symbol* get_symbol (std::string name);
   bool has_class (std::string class_name);
   bool has_namespace (std::string ns_name);
   //Func* register_function (std::string func_full_name);
   bool register_symbol (std::string path, Symbol* sym);

   /**
    * Add a function to the function linked list.
    */
   void
   registerFunction (Func* func);
};


} }

#endif
