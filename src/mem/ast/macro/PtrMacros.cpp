#include "mem/ast/macro/PtrMacros.hpp"

namespace mem { namespace ast { namespace macro {

st::Macro*
PtrMacros::getSymbol ()
{
   st::Macro* macro = new st::Macro();
   macro->setName("malloc");
   macro->setMacroExpander((void*)this);
   return macro;
}

node::Node*
PtrMacros::expand (node::Call* n)
{
   node::New* str = new node::New();
   if (n->ParamsNode()->ChildCount() == 2)
   {
      node::ArrayType* arr_node = new node::ArrayType();
      arr_node->setTypeNode(n->ParamsNode()->getChild(0));
      arr_node->setLengthNode(n->ParamsNode()->getChild(1));
      str->setTypeNode(arr_node);
   }
   else if (n->ParamsNode()->ChildCount() == 1)
   {
      str->setTypeNode(n->ParamsNode()->getChild(0));
   }
   return str;
}

} } }
