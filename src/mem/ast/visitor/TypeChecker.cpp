#include "mem/ast/visitor/TypeChecker.hpp"

namespace mem { namespace ast { namespace visitor {

bool
TypeChecker::ensureBoolExpr (node::Node* expr)
{
   assert (expr != NULL);
   return ensureExprType(expr, _core_types->gBoolTy());
}

bool
TypeChecker::ensureExprType (node::Node* expr, st::Symbol* expr_type)
{
   if (expr->hasExprType() && expr->ExprType() != expr_type)
   {
      // @FIXME Prints the same types, why ?
      log::SpecificTypeExpected* err = new log::SpecificTypeExpected();
      err->sExpectedTypeName(expr->ExprType()->gQualifiedName());
      err->sTypeName(expr_type->gQualifiedName());
      if (expr->Position() != NULL)
      {
         err->setPosition(expr->copyPosition());
      }
      err->format();
      log(err);
      return false;
   }
   return true;
}

bool
TypeChecker::ensureSymbolIsType (node::Node* node, st::Symbol* sym)
{
   assert (node != NULL);
   assert (sym != NULL);

   if (!sym->isTypeSymbol())
   {
      log::TypeExpected* err = new log::TypeExpected();
      err->sSymbolName(sym->Name());
      //err->setPosition(node->copyPosition());
      err->format();
      log(err);
      return false;
   }
   return true;
}

} } }
