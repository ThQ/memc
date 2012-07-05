#include "mem/ast/visitor/FindEntryPoint.hpp"


namespace mem { namespace ast { namespace visitor {


FindEntryPoint::FindEntryPoint ()
{
   _name = "ast.FindEntryPoint";
   _entry_point = NULL;
}

void
FindEntryPoint::tearDown ()
{
   if (_entry_point == NULL)
   {
      log::EntryPointNotFound* err = new log::EntryPointNotFound();
      err->format();
      _logger->log(err);
   }
}

bool
FindEntryPoint::visit (node::Node* node)
{
   if (node->isFuncNode())
   {
      st::Func* func = static_cast<st::Func*>(node->gBoundSymbol());
      if (func->gName() == "main")
      {
         _entry_point = func;
         func->sIsEntryPoint(true);
      }
   }
   return true;
}


} } }
