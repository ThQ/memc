#ifndef _MEM__AST__VISITOR__TYPE_CHECKER__HPP_
#define _MEM__AST__VISITOR__TYPE_CHECKER__HPP_


#include "mem/ast/visitor/Visitor.hpp"
#include "mem/log/Message.hpp"
#include "mem/st/ArrayType.hpp"
#include "mem/st/Symbol.hpp"


namespace mem { namespace ast { namespace node {
class Node;
} } }

namespace mem { namespace ast { namespace visitor {


class TypeChecker : public Visitor
{
   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   bool
   checkAssignment (node::Node* src, st::Type* dest_ty);

   bool
   ensureBoolExpr (node::Node* expr);

   bool
   ensureClassType (node::Node* expr);

   bool
   ensureConstantExpr (node::Node* expr);

   bool
   ensureExprType (node::Node* expr, st::Symbol* expr_type);

   bool
   ensureSizedExprType (node::Node* expr);

   bool
   ensureSymbolIsType (node::Node* node, st::Symbol* sym);

   void
   logSymbolNotFound (st::Symbol* scope, node::Node* node, std::string symbol_name);
};


} } }


#endif
