#ifndef _MEM__AST__VISITOR__TYPE_MATCH__HPP_
#define _MEM__AST__VISITOR__TYPE_MATCH__HPP_


#include "mem/ast/node/Node.hpp"
#include "mem/ast/node/VarDecl.hpp"
#include "mem/ast/visitor/Visitor.hpp"
#include "mem/fs/position/Composite.hpp"
#include "mem/log/Logger.hpp"
#include "mem/st/SymbolTable.hpp"

namespace mem { namespace ast { namespace visitor {


class TypeMatch : public Visitor
{
   public: log::Logger* _logger;
   public: st::SymbolTable* _symbols;

   public: TypeMatch (st::SymbolTable* symbols, log::Logger* logger);
   public: virtual bool visit (node::Node* node);
   public: void visit_var_decl (node::VarDecl* var_decl_node);
};


} } }

#endif
