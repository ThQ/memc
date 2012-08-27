#include "mem/ast/visitor/FindClasses.hpp"


namespace mem { namespace ast { namespace visitor {


FindClasses::FindClasses ()
{
   _name = "ast.FindClasses";
}

bool
FindClasses::visit (node::Node* node)
{
   assert (node != NULL);

   if (node::isa<node::Class>(node))
   {
      node::Class* cls_node = node::cast<node::Class>(node);
      visitClassDecl(cls_node);
   }

   return true;
}

void
FindClasses::visitClassDecl (node::Class* cls_node)
{
   assert(cls_node != NULL);

   node::File* file_node = util::getFileNode(cls_node);
   assert(file_node != NULL);
   st::Namespace* file_sym = static_cast<st::Namespace*>(file_node->BoundSymbol());
   assert(file_sym != NULL);

   st::Class* cls = new st::Class();
   cls->setName(cls_node->Value());
   cls_node->setBoundSymbol(cls);

   st::util::registerType(_symbols, file_sym, cls);
}

} } }
