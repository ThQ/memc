#include "mem/ast/visitor/VariableTypesChecker.hpp"

namespace mem { namespace ast { namespace visitor {


VariableTypesChecker::VariableTypesChecker ()
{
   this->_name = "VariableTypesChecker";
}

bool
VariableTypesChecker::visit (node::Node* node)
{
   assert(node != NULL);

   if (node->isType(MEM_NODE_VARIABLE_DECLARATION))
   {
      assert(node->getChild(0) != NULL);
      assert(node->getChild(1) != NULL);

      node::Text* type_node = static_cast<node::Text*>(node->getChild(1));
      std::string class_name(type_node->_value);

      // @TODO Is this obsolete ?
      if (class_name[0]!='$')
      {
         st::Symbol* var_st_type = this->_symbols->get_symbol(class_name);
         if (var_st_type != NULL)
         {
            node->sExprType(static_cast<st::Class*>(var_st_type));
            node->getChild(1)->sExprType(node->gExprType());
         }
      }
   }

   return true;
}


} } }
