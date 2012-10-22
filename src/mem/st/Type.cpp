#include "mem/st/Type.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Type::Type ()
{
   _byte_size = -1;
   _kind = Type::kTYPE;
   _parent_type = NULL;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
Type::isSubclass (Type* possible_parent)
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
