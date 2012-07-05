#include "mem/ast/node/While.hpp"

namespace mem { namespace ast { namespace node {

While::While ()
{
   _type = MEM_NODE_WHILE;
}

bool
While::isValid ()
{
   if (!Node::isValid()) return false;
   if (gChildCount() != 2) return false;

   return true;
}

} } }
