#include "mem/ast/node/New.hpp"

namespace mem { namespace ast { namespace node {


New::New ()
{
   _type = MEM_NODE_NEW;
}


void
New::isValid (NodeValidator* v)
{

   Node::isValid(v);
   v->ensure(gChildCount() == 1, "New must have exactly 1 child");
   v->ensure(hasExprType() == NULL, "New must have an expression type");

   if (gChildCount() == 1)
   {
      v->ensure(getChild(0)->hasExprType() == NULL,
         "New : first child must have an expression type");
   }
}


} } }
