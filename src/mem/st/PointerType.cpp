#include "mem/st/PointerType.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------
PointerType::PointerType ()
{
   _pointed_type = NULL;
   _kind = POINTER;
   _ptr_level = 1;
   _byte_size = sizeof(void*);
}

PointerType::~PointerType ()
{
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
PointerType::canCastTo (Type* dest_ty) const
{
   if (dest_ty->isPointerType())
   {
      PointerType* dest_ptr_ty = static_cast<PointerType*>(dest_ty);
      if (IndirectionLevel() == dest_ptr_ty->IndirectionLevel())
      {
         return _pointed_type->canCastTo(dest_ptr_ty->PointedType());
      }
   }
   return false;
}

Type*
PointerType::getNonPointerParent ()
{
   st::Type* parent = _pointed_type;
   while (parent != NULL && parent->isPointerType())
   {
      parent = static_cast<st::PointerType*>(parent)->PointedType();
   }

   if (!parent->isPointerType())
   {
      return parent;
   }
   return NULL;
}

} }
