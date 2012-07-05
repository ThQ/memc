#include "mem/ast/node/New.hpp"

namespace mem { namespace ast { namespace node {


New::New ()
{
   _type = MEM_NODE_NEW;
}


bool
New::isValid ()
{

   if (!Node::isValid()) return false;
   if (gChildCount() != 1) return false;
   if (gExprType() == NULL) return false;

   if (gChildCount() == 1)
   {
      if(getChild(0)->gExprType() == NULL) return false;
   }

   return true;
}


} } }
