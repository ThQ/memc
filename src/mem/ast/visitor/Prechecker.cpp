#include "mem/ast/visitor/Prechecker.hpp"


namespace mem { namespace ast { namespace visitor {


Prechecker::Prechecker ()
{
   _name = "ast.Prechecker";
}

bool
Prechecker::visit (node::Node* node)
{
   if (node->gPosition() == NULL && node->isRootNode() && node->isFileNode())
   {
      log::Message* warn = new log::Warning();
      warn->formatMessage("Node (%s) has no position.",
         node::Node::get_type_name(node->_type));
      _logger->log(warn);
   }

   if (node->gType() == 0)
   {
      _logger->warning("Node has an unknown type", "");
   }

   if (!node->isRootNode() && node->gParent() == NULL)
   {
      _logger->warning("Node(%s) has no parent",
         node::Node::get_type_name(node->gType()));
   }
   return true;
}


} } }
