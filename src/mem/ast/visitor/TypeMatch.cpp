#include "mem/ast/visitor/TypeMatch.hpp"


namespace mem { namespace ast { namespace visitor {


TypeMatch::TypeMatch ()
{
   _name = "ast.TypeMatch";
}

bool
TypeMatch::visit (node::Node* node)
{
   switch (node->gType())
   {
      case MEM_NODE_VARIABLE_DECLARATION:
         if (node->gChildCount() == 3)
         {
            visitVarDecl(static_cast<node::VarDecl*>(node));
         }
         return false;
   }
   return true;
}

void
TypeMatch::visitVarDecl (node::VarDecl* var_decl_node)
{
   node::Node* value_node = var_decl_node->ValueNode();
   st::Type* value_ty = static_cast<st::Type*>(value_node->gExprType());

   node::Node* type_node = var_decl_node->TypeNode();
   st::Type* var_ty = static_cast<st::Type*>(type_node->gBoundSymbol());

   /*
   if (var_type != NULL && value_type != NULL
      && !static_cast<st::Type*>(value_type)->isSubclass(static_cast<st::Type*>(var_type))
      && value_node != NULL && type_node != NULL)
   */
   //assert(value_ty != NULL);
   //assert(var_ty != NULL);

   if (value_ty != NULL && !value_ty->isSubclass(var_ty))
   {
      assert (type_node->gPosition() != NULL);
      assert (value_node->gPosition() != NULL);

      fs::position::Composite* pos = new fs::position::Composite();
      pos->addChild(type_node->copyPosition());
      pos->addChild(value_node->copyPosition());

      log::InvalidTypeInVarAssignment* err = new log::InvalidTypeInVarAssignment();
      err->sVariableName(var_decl_node->gName());
      err->sExpectedTypeName(var_ty->gQualifiedName());
      err->sTypeName(value_ty->gQualifiedName());
      err->format();
      err->sPosition(pos);

      log(err);
   }
}


} } }
