#include "mem/st/Type.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Type::Type ()
{
   _parent_type = NULL;
   _byte_size = -1;
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

//-----------------------------------------------------------------------------
// STATIC FUNCTIONS
//-----------------------------------------------------------------------------

st::Type*
castToType (Symbol* s)
{
   assert (s != NULL);
   assert (s->isAnyType());
   return static_cast<Type*>(s);
}

} }
