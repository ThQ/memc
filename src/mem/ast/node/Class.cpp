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
      assert (this->get_child(i) != NULL);

      if (this->get_child(i)->_type == MEM_NODE_ID)
      {
         return (Text*)this->get_child(i);
      }
   }
   return NULL;
}

} } }
