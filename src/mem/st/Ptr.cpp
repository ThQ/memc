#include "mem/st/Ptr.hpp"


namespace mem { namespace st {


Ptr::Ptr ()
{
   _base_type = NULL;
   _kind = POINTER;
   _ptr_level = 1;
   _byte_size = sizeof(void*);
}

Ptr::~Ptr ()
{
}

Type*
Ptr::getNonPointerParent ()
{
   st::Type* parent = _base_type;
   while (parent != NULL && parent->isPtrSymbol())
   {
      parent = static_cast<st::Ptr*>(parent)->_base_type;
   }

   if (!parent->isPtrSymbol())
   {
      return parent;
   }
   return NULL;
}

} }
