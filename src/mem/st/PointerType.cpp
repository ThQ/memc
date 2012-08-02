#include "mem/st/PointerType.hpp"


namespace mem { namespace st {


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
