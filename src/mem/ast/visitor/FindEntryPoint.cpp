#include "mem/ast/visitor/FindEntryPoint.hpp"


namespace mem { namespace ast { namespace visitor {


FindEntryPoint::FindEntryPoint ()
{
   _name = "ast.FindEntryPoint";
   _entry_point = NULL;
}

bool
FindEntryPoint::tearDown ()
{
   if (_entry_point == NULL)
   {
      log::EntryPointNotFound* err = new log::EntryPointNotFound();
      err->format();
      _logger->log(err);
      return true;
   }
   return false;
}

bool
FindEntryPoint::visit (node::Node* node)
{
   if (node->isFuncNode())
   {
      st::Func* func = static_cast<st::Func*>(node->BoundSymbol());
      if (func->Name() == "main")
      {
         _entry_point = func;
         func->setIsEntryPoint(true);
      }
   }
   return true;
}


} } }
