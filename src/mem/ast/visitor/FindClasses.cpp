#include "mem/ast/visitor/FindClasses.hpp"


namespace mem { namespace ast { namespace visitor {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

FindClasses::FindClasses ()
{
   _name = "ast.FindClasses";
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
FindClasses::visit (node::Node* node)
{
   assert (node != NULL);

   if (node::isa<node::Class>(node))
   {
      node::Class* nodeClass = node::cast<node::Class>(node);
      visitClassDecl(nodeClass);
   }

   return true;
}

void
FindClasses::visitClassDecl (node::Class* nodeClass)
{
   DEBUG_REQUIRE (nodeClass != NULL);

   //-------------------
   // Create class type
   //-------------------
   st::Class* symClass = new st::Class();
   symClass->setName(nodeClass->Value());


   //--------------------------------
   // Register class in symbol table
   //--------------------------------
   node::File* nodeFile = util::getFileNode(nodeClass);
   st::Namespace* symFile = st::cast<st::Namespace>(nodeFile->BoundSymbol());
   st::util::registerType(_symbols, symFile, symClass);

   nodeClass->setBoundSymbol(symClass);

   DEBUG_PRINTF("Found class type `%s'(%p), associated with node `%s' (%p)\n",
      symClass->gQualifiedNameCstr(), symClass,
      nodeClass->KindNameCstr(), nodeClass);
}

} } }
