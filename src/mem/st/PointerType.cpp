#include "mem/st/PointerType.hpp"


namespace mem { namespace st {


PointerType::PointerType ()
{
   _base_type = NULL;
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
   st::Type* parent = _base_type;
   while (parent != NULL && parent->isPtrSymbol())
   {
      parent = static_cast<st::PointerType*>(parent)->BaseType();
   }

   if (!parent->isPtrSymbol())
   {
      return parent;
   }
   return NULL;
}

} }
