#include "mem/ast/visitor/TypeChecker.hpp"

namespace mem { namespace ast { namespace visitor {


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
TypeChecker::checkAssignment (node::Node* nodeSource, st::Type* symDestType)
{
   DEBUG_REQUIRE (nodeSource != NULL);
   DEBUG_REQUIRE (symDestType != NULL);

   bool bIsSafeCast = false;
   DEBUG_PRINT("Check assign\n");
   if (nodeSource->hasExprType())
   {
      st::Type* symSourceType = nodeSource->ExprType();

      if (symSourceType != BugType() && symDestType != BugType())
      {
         bIsSafeCast = symSourceType->canCastTo(symDestType);

         DEBUG_PRINTF(" is casting safe ? %s -> %s = %d\n",
            symSourceType->Name().c_str(),
            symDestType->Name().c_str(),
            bIsSafeCast);

         if (!bIsSafeCast)
         {
            log::CannotAssign* err = new log::CannotAssign();
            err->setTypeName(symSourceType->Name());
            err->setExpectedTypeName(symDestType->Name());
            err->setPosition(nodeSource->Position()->copy());
            err->format();
            log(err);
         }
      }
   }

   return bIsSafeCast;
}

bool
TypeChecker::ensureBoolExpr (node::Node* expr)
{
   assert (expr != NULL);
   return ensureExprType(expr, _core_types->BoolTy());
}

bool
TypeChecker::ensureClassType (node::Node* expr)
{
   bool is_class_ty = false;

   if (expr->hasBoundSymbol() && st::isa<st::Class>(expr->BoundSymbol()))
   {
      is_class_ty = true;
   }
   else
   {
      log::ExpectedClassType* err = new log::ExpectedClassType();
      err->setType(expr->BoundSymbol());
      err->format();
      log(err);
   }


   return is_class_ty;
}

bool
TypeChecker::ensureConstantExpr (node::Node* expr)
{
   if (expr == NULL || !expr->hasBoundSymbol() || !st::isa<st::Constant>(expr->BoundSymbol()))
   {
      log::ExpectedConstant* err = new log::ExpectedConstant();
      err->format();
      log(err);
      return false;
   }
   return true;
}

bool
TypeChecker::ensureExprType (node::Node* expr, st::Symbol* expr_type)
{
   if (expr->hasExprType() && expr->ExprType() != expr_type)
   {
      // @FIXME Prints the same types, why ?
      log::SpecificTypeExpected* err = new log::SpecificTypeExpected();
      err->setTypeName(expr->ExprType()->gQualifiedName());
      err->setExpectedTypeName(expr_type->gQualifiedName());
      err->setPosition(expr->copyPosition());
      err->format();
      log(err);
      return false;
   }
   return true;
}

bool
TypeChecker::ensureSizedExprType (node::Node* expr)
{
   st::Type* ty = expr->ExprType();
   ensureSymbolIsType(expr, ty);

   if (ty != NULL && ty != BugType() && !ty->hasByteSize())
   {
      std::string fix_str;

      if (st::isa<st::ArrayType>(ty) && !st::cast<st::ArrayType>(ty)->hasLength())
      {
         fix_str += "> [" + st::cast<st::ArrayType>(ty)->ItemType()->Name() + ",1i]\n";
         fix_str += "> [" + st::cast<st::ArrayType>(ty)->ItemType()->Name() + "]*\n";
      }
      std::string desc;
      if (fix_str.size() != 0)
      {
         desc += "Did you mean :\n" + fix_str;
      }

      log::UnsizedType* err = new log::UnsizedType();
      err->setTypeName(ty->Name());
      if (desc.size() != 0)
      {
         err->setSecondaryText(desc);
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

   if (!st::isa<st::Type>(sym))
   {
      log::TypeExpected* err = new log::TypeExpected();
      err->setSymbolName(sym->gQualifiedName());
      err->setPosition(node->copyPosition());
      err->format();
      log(err);
      return false;
   }
   return true;
}

void
TypeChecker::logSymbolNotFound (st::Symbol* scope, node::Node* node, std::string symbol_name)
{
   log::SymbolNotFound* err = new log::SymbolNotFound();
   err->setSymbolName(symbol_name);
   err->setScopeName(scope->gQualifiedName());
   err->format();
   err->setPosition(node->copyPosition());
   log(err);
}

} } }
