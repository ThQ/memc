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
Type::isSubTypeOf (Type* symPossibleParentType) const
{
   DEBUG_PRINTF("is %s subtype of %s\n", _name.c_str(), symPossibleParentType->gQualifiedNameCstr());
   if (symPossibleParentType == this)
   {
      return true;
   }
   else
   {
      Type* symParentType = this->ParentType();

      while (symParentType != NULL)
      {
         if (symParentType == symPossibleParentType)
         {
            return true;
         }
         symParentType = symParentType->ParentType();
      }
      return false;
   }
}


} }
