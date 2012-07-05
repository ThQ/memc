#include "mem/ast/visitor/CheckValidity.hpp"


namespace mem { namespace ast { namespace visitor {


CheckValidity::CheckValidity ()
{
   _name = "ast.CheckValidity";
}

bool
CheckValidity::visit (node::Node* node)
{
   if (!node->isValid())
   {
      log::FatalError* err = new log::FatalError();
      err->formatMessage("[BUG] Invalid node : %s",
         node::Node::get_type_name(node->gType()));
      if (node->gPosition() != NULL)
      {
         err->sPosition(node->copyPosition());
      }
      log(err);
   }
   return true;
}


} } }
