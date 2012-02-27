#ifndef _MEM__AST__VISITOR__VISITOR__HPP_
#define _MEM__AST__VISITOR__VISITOR__HPP_


#include <string>
#include "macro.h"
#include "mem/ast/node/Node.hpp"
#include "mem/log/Logger.hpp"
#include "mem/st/SymbolTable.hpp"


namespace mem { namespace ast { namespace visitor {


class Visitor
{
   public: log::Logger* _logger;
   public: std::string _name;
   public: st::SymbolTable* _symbols;

   public: virtual ~Visitor ();
   public: virtual void init (st::SymbolTable* symbols, log::Logger* logger);
   public: inline void log (log::Message* msg) {this->_logger->log(msg);}
   public: virtual bool visit (node::Node* node);
   public: virtual void visit_preorder (node::Node* node);
};


} } }

#endif
