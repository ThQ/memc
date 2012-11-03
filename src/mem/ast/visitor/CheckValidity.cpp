#include "mem/ast/visitor/CheckValidity.hpp"


namespace mem { namespace ast { namespace visitor {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------
CheckValidity::CheckValidity ()
{
   _name = "ast.CheckValidity";
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
CheckValidity::visit (node::Node* node)
{
   DEBUG_REQUIRE (node != NULL);

   _node_vld.setup();
   assert (_node_vld._is_valid == true);

   node->isValid(&_node_vld);

   if (!_node_vld._is_valid)
   {
      std::string description = "";
      for (size_t i = 0; i < _node_vld._messages.size(); ++i)
      {
         description += "* " + _node_vld._messages[i] + "\n";
      }

      log::FatalError* err = new log::FatalError();
      err->formatMessage("[BUG] Invalid node : %s", node->KindName().c_str());
      err->setSecondaryText(description);
      if (node->Position() != NULL)
      {
         err->setPosition(node->copyPosition());
      }
      log(err);
   }
   return true;
}


} } }
