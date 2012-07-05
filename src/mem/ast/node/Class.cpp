#include "mem/ast/node/Class.hpp"


namespace mem { namespace ast { namespace node {


Class::Class ()
{
   _type = MEM_NODE_CLASS;
}

Text*
Class::gParentTypeNode ()
{
   for (size_t i = 0 ; i < gChildCount() ; ++i)
   {
      assert (getChild(i) != NULL);

      if (getChild(i)->isIdNode())
      {
         return static_cast<Text*>(getChild(i));
      }
   }
   return NULL;
}

} } }
