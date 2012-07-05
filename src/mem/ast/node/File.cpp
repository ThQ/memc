#include "mem/ast/node/File.hpp"

namespace mem { namespace ast { namespace node {

File::File ()
{
   _type = MEM_NODE_FILE;
}

bool
File::isValid ()
{
   Node* child = NULL;

   if (!Node::isValid()) return false;

   for (size_t i = 0 ; i < gChildCount(); ++i)
   {
      child = getChild(i);

      if (!child->isUseNode() && !child->isClassNode() && !child->isFuncNode()) return false;
   }

   return true;
}

} } }
