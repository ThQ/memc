#include "mem/ast/visitor/Visitor.hpp"

namespace mem { namespace ast { namespace visitor {


Visitor::~Visitor ()
{
}

bool
Visitor::visit (node::Node* node)
{
   return false;
}

void
Visitor::visit_preorder (node::Node* node)
{

   if (node != NULL)
   {
#if 0
      DEBUG_PRINTF("visit node [@%p, %s], parent[@%p, %s]\n",
         node, node->KindNameCstr(),
         node->Parent(), node->Parent() != NULL ? node->Parent()->KindNameCstr() : "");
#endif

      if(visit(node))
      {
         for (size_t i = 0; i < node->ChildCount(); ++i)
         {
            visit_preorder(node->getChild(i));
         }
      }
   }
}


} } }
