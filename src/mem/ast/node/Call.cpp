#include "mem/ast/node/Call.hpp"

namespace mem { namespace ast { namespace node {

Call::Call ()
{
   _type = MEM_NODE_CALL;
}

bool
Call::isValid ()
{
   if (!Node::isValid()) return false;
   if (gChildCount() > 2) return false;
   if (gExprType() == NULL) return false;

   return true;
}

} } }
