#include "mem/ast/visitor/CoherenceChecker.hpp"


namespace mem { namespace ast { namespace visitor {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

CoherenceChecker::CoherenceChecker ()
{
   _name = "ast.CoherenceChecker";
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
CoherenceChecker::visit (node::Node* node)
{
   assert (node != NULL);

   std::vector<std::string> errors;

   node::Node* nodeChild = NULL;
   for (size_t i = 0; i < node->ChildCount(); ++i)
   {
      nodeChild = node->getChild(i);

      if (nodeChild != NULL && nodeChild->Parent() != node)
      {
         DEBUG_PRINTF("node.parent %s, node %s, child.parent %s, child%s\n",
            node->Parent()->StringRep().c_str(),
            node->StringRep().c_str(),
            nodeChild->Parent()->StringRep().c_str(),
            nodeChild->StringRep().c_str());
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
      err->formatMessage("Invalid node %s", node->StringRep().c_str());
      err->setSecondaryText(desc);
      log(err);
   }

   return true;
}

} } }
