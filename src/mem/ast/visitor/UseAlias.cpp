#include "mem/ast/visitor/UseAlias.hpp"


namespace mem { namespace ast { namespace visitor {


UseAlias::UseAlias ()
{
   _name = "ast.UseAlias";
}

bool
UseAlias::visit (node::Node* node)
{
   switch (node->Kind())
   {
      case node::Kind::USE:
         visitUse(static_cast<node::Use*>(node));
         return false;
   }
   return true;
}

void
UseAlias::visitUse (node::Use* node)
{
   std::string file_ns_name = static_cast<node::Use*>(node)->gValue();
   std::vector<std::string> file_ns_parts = st::util::splitQualifiedName(file_ns_name);
   st::Symbol* file_sym = st::util::lookupSymbol(_symbols->Home(), file_ns_parts);
   if (file_sym == NULL)
   {
      file_sym = st::util::lookupSymbol(_symbols->System(), file_ns_parts);
   }

   if (file_sym != NULL)
   {
      st::Alias* alias = new st::Alias();
      alias->setName(file_sym->Name());
      alias->setAliased(static_cast<st::Namespace*>(file_sym));
      node->setBoundSymbol(file_sym);
      node->Parent()->BoundSymbol()->addChild(alias);
   }
}


} } }
