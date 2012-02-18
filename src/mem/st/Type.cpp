#include "mem/st/Type.hpp"

namespace mem { namespace st {

Type::Type ()
{
   this->_parent_type = NULL;
}

bool
Type::is_subclass (Type* possible_parent)
{
   Type* direct_parent = this;

   while (direct_parent != NULL)
   {
      if (direct_parent == possible_parent)
      {
         return true;
      }
      direct_parent = direct_parent->_parent_type;
   }
   return false;
}


} }
