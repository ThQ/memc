#include "mem/ast/visitor/CoherenceChecker.hpp"


namespace mem { namespace ast { namespace visitor {


CoherenceChecker::CoherenceChecker ()
{
   _name = "ast.CoherenceChecker";
}

bool
CoherenceChecker::visit (node::Node* node)
{
   assert (node != NULL);

   std::vector<std::string> errors;

   node::Node* child_n = NULL;
   for (size_t i = 0; i < node->ChildCount(); ++i)
   {
      child_n = node->getChild(i);

      if (child_n != NULL && child_n->Parent() != node)
      {
         errors.push_back("Node parent declared differently between parent and child");
      }
   }

   std::string desc;
   for (size_t i = 0; i < errors.size(); ++i)
   {
      desc += "* " + errors[i] + "\n";
   }

   if (desc.size() != 0)
   {
      log::Message* err = new log::FatalError();
      err->formatMessage("Invalid node (Kind {ID:%d, NAME:%s})",
         node->Kind(),
         node::Node::get_type_name(node->Kind()));
      err->setSecondaryText(desc);
      log(err);
   }

   return true;
}

} } }
