#include "mem/ast/visitor/TypeChecker.hpp"

namespace mem { namespace ast { namespace visitor {

bool
TypeChecker::ensureBoolExpr (node::Node* expr)
{
   return this->ensureExprType(expr, this->_symbols->_glob_bool_cls);
}

bool
TypeChecker::ensureExprType (node::Node* expr, st::Symbol* expr_type)
{
   if (expr->gExprType() != expr_type)
   {
      // @FIXME Prints the same types, why ?
      log::Message* err = new log::Error();
      err->formatMessage("Expression of type {id:%s} expected, but got {id:%s} instead",
         expr->gExprType()->gQualifiedNameCstr(),
         expr_type->gQualifiedNameCstr());
      err->sPosition(expr->copyPosition());
      this->log(err);
      return false;
   }
   return true;
}

bool
TypeChecker::ensureSymbolIsType (node::Node* node, st::Symbol* sym)
{
   if (!sym->isTypeSymbol())
   {
      log::Message* err = new log::Error();
      err->formatMessage("%s is not a type", sym->gNameCstr());
      err->sPosition(node->copyPosition());
      this->log(err);
      return false;
   }
   return true;
}

} } }
