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

   node::Node* child_n = node->getChild(0);
   for (; child_n != NULL; child_n = child_n->_next)
   {
      if (child_n->Parent() != node)
      {
         errors.push_back("Node parent declared differently between parent and child");
      }

      if (child_n->_prev != NULL && child_n->_prev->_next != child_n)
      {
         errors.push_back("Left sibling has not node as right sibling");

         if (child_n->_prev->Parent() != child_n->Parent())
         {
            errors.push_back("Left sibling has not the same parent");
         }
      }

      if (child_n->_next != NULL && child_n->_next->_prev != child_n)
      {
         errors.push_back("Right sibling has not node as left sibling");

         if (child_n->_next->Parent() != child_n->Parent())
         {
            errors.push_back("Right sibling has not the same parent");
         }
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
