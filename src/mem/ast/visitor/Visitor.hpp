#ifndef _MEM__AST__VISITOR__VISITOR__HPP_
#define _MEM__AST__VISITOR__VISITOR__HPP_


#include <string>
#include "mem/ast/node/Node.hpp"
#include "mem/log/errors.hpp"
#include "mem/log/Logger.hpp"
#include "mem/st/SymbolTable.hpp"


namespace mem { namespace ast { namespace visitor {


class Visitor
{
   public: log::Logger* _logger;
   public: std::string _name;
   public: st::SymbolTable* _symbols;
   public: st::CoreTypes* _core_types;

   //--------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   //--------------------------------------------------------------------------
   public:

   void SymbolTable (st::SymbolTable* st) { _symbols = st; _core_types=&(st->gCoreTypes()); }

   void Logger (log::Logger* logger) { _logger = logger; }

   //--------------------------------------------------------------------------
   // CONSTRUCTORS/DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   virtual ~Visitor ();

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual bool
   setup (st::SymbolTable* symbols, log::Logger* logger);

   inline void
   log (log::Message* msg) {this->_logger->log(msg);}

   virtual bool
   tearDown();

   virtual bool
   visit (node::Node* node);

   virtual void
   visit_preorder (node::Node* node);
};


} } }


#endif
