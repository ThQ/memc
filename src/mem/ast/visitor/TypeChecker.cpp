#include "mem/ast/visitor/TypeChecker.hpp"

namespace mem { namespace ast { namespace visitor {

bool
TypeChecker::checkAssignment (node::Node* source, st::Type* dest_ty)
{
   bool is_valid = false;
   st::Type* src_ty = source->ExprType();

   if (src_ty == dest_ty)
   {
      is_valid = true;
   }
   else if (src_ty->isIntType() && dest_ty->isIntType())
   {
      // Safe integer cast
      if (src_ty->ByteSize() < dest_ty->ByteSize())
      {
         is_valid = true;
      }
   }

   if (!is_valid)
   {
      log::CannotAssign* err = new log::CannotAssign();
      err->sTypeName(src_ty->Name());
      err->sExpectedTypeName(dest_ty->Name());
      err->format();
      log(err);
   }
   return is_valid;
}

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
TypeChecker::ensureSizedExprType (node::Node* expr)
{
   st::Type* ty = expr->ExprType();
   ensureSymbolIsType(expr, ty);

   if (ty != NULL && !ty->hasByteSize())
   {
      std::string fix_str;

      if (ty->isArrayType() && !static_cast<st::ArrayType*>(ty)->hasLength())
      {
         fix_str += "> [" + static_cast<st::ArrayType*>(ty)->ItemType()->Name() + ",1i]\n";
         fix_str += "> [" + static_cast<st::ArrayType*>(ty)->ItemType()->Name() + "]*\n";
      }
      std::string desc;
      if (fix_str.size() != 0)
      {
         desc += "Did you mean :\n" + fix_str;
      }

      log::UnsizedType* err = new log::UnsizedType();
      err->sTypeName(ty->Name());
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

   if (!sym->isAnyType())
   {
      log::TypeExpected* err = new log::TypeExpected();
      err->sSymbolName(sym->gQualifiedName());
      //err->setPosition(node->copyPosition());
      err->format();
      log(err);
      return false;
   }
   return true;
}

void
TypeChecker::logSymbolNotFound (st::Symbol* scope, std::string symbol_name)
{
   log::SymbolNotFound* err = new log::SymbolNotFound();
   err->sSymbolName(symbol_name);
   err->sScopeName(scope->Name());
   err->format();
   //err->setPosition(right_node->copyPosition());
   log(err);
}

} } }
