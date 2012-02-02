#ifndef _MEM__AST__VISITOR__VARIABLE_TYPES_CHECKER__HPP_
#define _MEM__AST__VISITOR__VARIABLE_TYPES_CHECKER__HPP_


#include <vector>
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Type.hpp"
#include "mem/ast/visitor/Visitor.hpp"
#include "mem/log/Logger.hpp"
#include "mem/st/SymbolTable.hpp"


namespace mem { namespace ast { namespace visitor {


class VariableTypesChecker : public Visitor
{
   public: log::Logger* _logger;
   public: st::SymbolTable* _symbols;

   public: VariableTypesChecker (st::SymbolTable* symbols, log::Logger* logger);
   public: virtual bool visit (node::Node* node);
};


} } }

#endif
