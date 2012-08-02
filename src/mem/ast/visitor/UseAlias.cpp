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
         std::string file_ns_name = static_cast<node::Use*>(node)->gValue();
         st::Symbol* file_sym = st::util::lookupSymbol(_symbols->gRoot(), st::util::splitQualifiedName(file_ns_name));

         if (file_sym != NULL)
         {
            st::Alias* alias = new st::Alias();
            alias->setName(file_sym->Name());
            alias->setAliased(static_cast<st::Namespace*>(file_sym));
            node->setBoundSymbol(file_sym);
            node->Parent()->BoundSymbol()->addChild(alias);
         }
         return false;
   }
   return true;
}


} } }
