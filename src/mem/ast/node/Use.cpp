#include "mem/ast/node/Use.hpp"


namespace mem { namespace ast { namespace node {


Use::Use ()
{
   _type = MEM_NODE_USE;
}


bool
Use::isValid ()
{
   if (!Node::isValid()) return false;
   if (gChildCount() != 0) return false;

   return true;
}


} } }
