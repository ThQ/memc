#include "mem/ast/visitor/TypeMatch.hpp"


namespace mem { namespace ast { namespace visitor {


TypeMatch::TypeMatch ()
{
   _name = "ast.TypeMatch";
}

bool
TypeMatch::visit (node::Node* node)
{
   switch (node->Kind())
   {
      case node::MetaKind::VARIABLE_DECLARATION:
         if (node->ChildCount() == 3)
         {
            visitVarDecl(node::cast<node::VarDecl>(node));
         }
         return false;
   }
   return true;
}

void
TypeMatch::visitVarDecl (node::VarDecl* var_decl_node)
{
   node::Node* value_node = var_decl_node->ValueNode();
   st::Type* value_ty = st::cast<st::Type>(value_node->ExprType());

   node::Node* type_node = var_decl_node->TypeNode();
   st::Type* var_ty = st::cast<st::Type>(type_node->BoundSymbol());

   if (value_ty != NULL && !value_ty->isSubclass(var_ty))
   {

      fs::position::Composite* pos = new fs::position::Composite();
      //pos->addChild(type_node->copyPosition());
      //pos->addChild(value_node->copyPosition());

      log::InvalidTypeInVarAssignment* err = new log::InvalidTypeInVarAssignment();
      err->setVariableName(var_decl_node->Name());
      err->setExpectedTypeName(var_ty->gQualifiedName());
      err->setTypeName(value_ty->gQualifiedName());
      err->format();
      err->setPosition(pos);

      log(err);
   }
}


} } }
