#ifndef _MEM__AST__VISITOR__VISITOR__HPP_
#define _MEM__AST__VISITOR__VISITOR__HPP_


#include <string>
#include "mem/ast/node/Node.hpp"
#include "mem/log/errors.hpp"
#include "mem/log/Logger.hpp"
#include "mem/st/SymbolTable.hpp"


namespace mem { namespace ast { namespace node {
class Node;
} } }


namespace mem { namespace ast { namespace visitor {


// A base class for all AST visitors.
class Visitor
{
   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   virtual ~Visitor ();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   void SymbolTable (st::SymbolTable* st) { _symbols = st; _core_types=&(st->gCoreTypes()); }

   void Logger (log::Logger* logger) { _logger = logger; }


   GETTER (BugType, st::Type*) {return _symbols->_core_types._bug_type;}


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual bool
   setup (){return true;};

   inline void
   log (log::Message* msg) {this->_logger->log(msg);}

   virtual bool
   tearDown() {return true;};

   // Return: true if we should visit child nodes
   virtual bool
   visit (node::Node* node);

   virtual void
   visit_preorder (node::Node* node);


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   st::CoreTypes* _core_types;
   log::Logger* _logger;
   std::string _name;
   st::SymbolTable* _symbols;
};


} } }


#endif
