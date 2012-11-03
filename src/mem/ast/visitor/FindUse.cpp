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
   }
   return false;
}

void
FindUse::visitFile (node::File* nodeFile)
{
   for (size_t i = 0; i < nodeFile->ChildCount(); ++i)
   {
      if (node::isa<node::Use>(nodeFile->getChild(i)))
      {
         node::Text* nodeText = node::cast<node::Text>(nodeFile);
         _uses.push_back(nodeText->Value());
      }
   }
}

} } }
