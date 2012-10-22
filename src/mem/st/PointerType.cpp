#include "mem/st/PointerType.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------
PointerType::PointerType ()
{
   _pointed_type = NULL;
   _kind = PointerType::kTYPE;
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
   if (st::isa<st::PointerType>(dest_ty))
   {
      PointerType* dest_ptr_ty = st::cast<st::PointerType>(dest_ty);
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
   while (parent != NULL && st::isa<st::PointerType>(parent))
   {
      parent = st::cast<st::PointerType>(parent)->PointedType();
   }

   if (!st::isa<st::PointerType>(parent))
   {
      return parent;
   }
   return NULL;
}

} }
