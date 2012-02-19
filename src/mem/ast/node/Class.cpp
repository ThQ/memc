#include "mem/ast/node/Class.hpp"


namespace mem { namespace ast { namespace node {


Class::Class ()
{
   this->_type = MEM_NODE_CLASS;
}

Text*
Class::g_parent_type_node ()
{
   for (int i = 0 ; i < this->_child_count ; ++i)
   {
      assert (this->getChild(i) != NULL);

      if (this->getChild(i)->isType(MEM_NODE_ID))
      {
         return static_cast<Text*>(this->getChild(i));
      }
   }
   return NULL;
}

} } }
