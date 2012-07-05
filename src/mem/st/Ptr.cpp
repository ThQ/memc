#include "mem/st/Ptr.hpp"


namespace mem { namespace st {


Ptr::Ptr ()
{
   _base_type = NULL;
   _kind = POINTER;
   _ptr_level = 0;
}

Ptr::~Ptr ()
{
}


} }
