#ifndef _MEM__AST__VISITOR__TYPE_CHECKER__HPP_
#define _MEM__AST__VISITOR__TYPE_CHECKER__HPP_


#include "mem/ast/node/Node.hpp"
#include "mem/ast/visitor/Visitor.hpp"
#include "mem/log/Message.hpp"
#include "mem/st/Symbol.hpp"


namespace mem { namespace ast { namespace visitor {


class TypeChecker : public Visitor
{
   public: bool ensureBoolExpr (node::Node* expr);
   public: bool ensureExprType (node::Node* expr, st::Symbol* expr_type);
   public: bool ensureSymbolIsType (node::Node* node, st::Symbol* sym);
};


} } }

#endif
