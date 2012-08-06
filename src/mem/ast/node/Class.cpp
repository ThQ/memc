#include "mem/ast/node/Class.hpp"


namespace mem { namespace ast { namespace node {


Class::Class ()
{
   _type = Kind::CLASS;
}

Node*
Class::gParentTypeNode ()
{
   for (size_t i = 0 ; i < ChildCount() ; ++i)
   {
      assert (getChild(i) != NULL);

      if (!getChild(i)->isFieldNode() && !getChild(i)->isFuncNode())
      {
         return getChild(i);
      }
   }
   return NULL;
}

} } }
