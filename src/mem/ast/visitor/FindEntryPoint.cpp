#include "mem/ast/visitor/FindEntryPoint.hpp"


namespace mem { namespace ast { namespace visitor {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

FindEntryPoint::FindEntryPoint ()
{
   _name = "ast.FindEntryPoint";
   _entry_point = NULL;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

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
   if (node::isa<node::Func>(node))
   {
      st::Func* symFunc = st::cast<st::Func>(node->BoundSymbol());
      if (symFunc->Name() == "main")
      {
         if (_entry_point == NULL)
         {
            _entry_point = symFunc;
            symFunc->setIsEntryPoint(true);
         }
         else
         {
            mem::log::MultipleMainDefinitions* err = new mem::log::MultipleMainDefinitions();
            err->setPosition(node->copyPosition());
            log(err);
         }
      }
   }
   return true;
}


} } }
