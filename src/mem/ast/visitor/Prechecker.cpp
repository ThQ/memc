#include "mem/ast/visitor/Prechecker.hpp"


namespace mem { namespace ast { namespace visitor {


Prechecker::Prechecker ()
{
   _name = "ast.Prechecker";
}

bool
Prechecker::visit (node::Node* node)
{
   if (node->Position() == NULL && node::isa<node::Root>(node) && node::isa<node::File>(node))
   {
      log::Message* warn = new log::Warning();
      warn->formatMessage("Node (%s) has no position.",
         node::Node::get_type_name(node->Kind()));
      _logger->log(warn);
   }

   if (node->Kind() == node::MetaKind::UNKNOWN)
   {
      _logger->warning("Node has an unknown type {kind: %d, name: %s}",
         node->Kind(),
         node->KindName().c_str());
   }

   if (!node::isa<node::Root>(node) && node->Parent() == NULL)
   {
      _logger->warning("Node(%s) has no parent",node->KindName().c_str());
   }
   return true;
}


} } }
