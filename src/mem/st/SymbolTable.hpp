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

// The class that manages all the symbols used.
class SymbolTable
{
   //public: inline Namespace* gRoot () {return _root;}
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

   // Default constructor.
   SymbolTable ();

   // Destructor.
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

   // The `home' namespace
   GETTER(Home, Namespace*) {return _home;}

   // The `system' namespace
   GETTER(System, Namespace*) {return _system;}

   // The top level namespace
   GETTER(Root, Namespace*) {return _root;}


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:
#if 0
   Class* create_class (std::string full_class_name);
   bool create_type (Type* anonymous_type, std::string full_type_name);
   Namespace* create_namespace (std::string name);
   Namespace* get_namespace (std::string ns_name);
   Symbol* get_symbol (std::string name);
   bool has_class (std::string class_name);
   bool has_namespace (std::string ns_name);
   //Func* register_function (std::string func_full_name);
   bool register_symbol (std::string path, Symbol* sym);
#endif

   // True if the symbol is the void type.
   inline bool
   isVoidType (st::Symbol* s) {assert(_core_types._void != NULL);return s == _core_types._void;}

   // Lookup a symbol from a given scope.
   //
   // It starts from the home namespace, then switches to the system namespace.
   st::Symbol*
   lookupSymbol (st::Symbol* scope, std::string symbol_id);

   // Lookup a symbol in a scope until a top scope is reached.
   st::Symbol*
   lookupSymbolUntil (st::Symbol* cur_scope, std::string symbol_id, st::Symbol* top_scope);

   // Add a function to the function linked list.
   void
   registerFunction (Func* func);


   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   // The root namespace.
   //
   // Every symbol created must be added to this namespace, directly or
   // indirectly.
   Namespace* _root;

   // The home namespace.
   //
   // Symbols created by the user must be added to this namespace.
   Namespace* _home;

   // The system namespace.
   //
   // Symbols created at start up must be added to this namespace. The user
   // should never add anything to this.
   Namespace* _system;
};


} }

#endif
