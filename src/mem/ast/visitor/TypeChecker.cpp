#include "mem/ast/visitor/TypeChecker.hpp"

namespace mem { namespace ast { namespace visitor {

bool
TypeChecker::ensureBoolExpr (node::Node* expr)
{
   return ensureExprType(expr, _core_types->gBoolTy());
}

bool
TypeChecker::ensureExprType (node::Node* expr, st::Symbol* expr_type)
{
   if (expr->hasExprType() && expr->gExprType() != expr_type)
   {
      // @FIXME Prints the same types, why ?
      log::SpecificTypeExpected* err = new log::SpecificTypeExpected();
      err->sExpectedTypeName(expr->gExprType()->gQualifiedName());
      err->sTypeName(expr_type->gQualifiedName());
      err->sPosition(expr->copyPosition());
      err->format();
      log(err);
      return false;
   }
   return true;
}

bool
TypeChecker::ensureSymbolIsType (node::Node* node, st::Symbol* sym)
{
   if (!sym->isTypeSymbol())
   {
      log::TypeExpected* err = new log::TypeExpected();
      err->sSymbolName(sym->gName());
      err->sPosition(node->copyPosition());
      err->format();
      log(err);
      return false;
   }
   return true;
}

} } }
