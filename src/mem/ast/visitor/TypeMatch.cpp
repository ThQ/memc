#include "mem/ast/visitor/TypeMatch.hpp"


namespace mem { namespace ast { namespace visitor {


TypeMatch::TypeMatch ()
{
   this->_name = "TypeMatch";
}

bool
TypeMatch::visit (node::Node* node)
{
   switch (node->_type)
   {
      case MEM_NODE_VARIABLE_DECLARATION:
         if (node->gChildCount() == 3)
         {
            this->visitVarDecl(static_cast<node::VarDecl*>(node));
         }
         return false;
   }
   return true;
}

void
TypeMatch::visitVarDecl (node::VarDecl* var_decl_node)
{
   node::Node* value_node = var_decl_node->gValueNode();
   node::Node* type_node = var_decl_node->gTypeNode();

   st::Symbol* var_type = var_decl_node->gExprType();
   st::Symbol* value_type = value_node->gExprType();

   if (var_type != NULL && value_type != NULL
      && !static_cast<st::Type*>(value_type)->isSubclass(static_cast<st::Type*>(var_type))
      && value_node != NULL && type_node != NULL)
   {
      assert (type_node->gPosition() != NULL);
      assert (value_node->gPosition() != NULL);

      log::Message* err = new log::Error();
      err->formatMessage("Types mismatch in %s variable assignment",
         var_decl_node->gNameCstr());
      err->formatDescription("Variable expects value of type %s, but got %s instead",
         var_decl_node->gExprType()->gQualifiedNameCstr(),
         var_decl_node->gValueNode()->gExprType()->gQualifiedNameCstr()
      );

      fs::position::Composite* pos = new fs::position::Composite();
      pos->addChild(type_node->copyPosition());
      pos->addChild(value_node->copyPosition());
      err->sPosition(pos);

      this->log(err);
   }
}


} } }
