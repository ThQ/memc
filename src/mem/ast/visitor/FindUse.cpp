#include "mem/ast/visitor/FindUse.hpp"


namespace mem { namespace ast { namespace visitor {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

FindUse::FindUse ()
{
   _name = "FindUse";
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
FindUse::visit (node::Node* node)
{
   assert (node != NULL);

   if (node::isa<node::File>(node))
   {
      visitFile (node::cast<node::File>(node));
      return false;
   }
   return true;
}

void
FindUse::visitFile (node::File* nodeFile)
{
   node::Use* nodeUse = NULL;
   for (size_t i = 0; i < nodeFile->ChildCount(); ++i)
   {
      if (node::isa<node::Use>(nodeFile->getChild(i)))
      {
         nodeUse = node::cast<node::Use>(nodeFile->getChild(i));
         DEBUG_PRINTF("Found use `%s` in file `%s'\n",
            nodeUse->Value().c_str(),
            nodeFile->Path().c_str());
         _uses.push_back(nodeUse);
      }
   }
}

} } }
