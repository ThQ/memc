#include "mem/st/Array.hpp"


namespace mem { namespace st {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Array::Array ()
{
   _kind = ARRAY;
   _array_length = -1;
}


//-----------------------------------------------------------------------------
// PROTECTED FUNCTIONS
//-----------------------------------------------------------------------------

void
Array::_computeByteSize ()
{
   if (_array_length != -1 && _base_type != NULL
      && _base_type->ByteSize() != -1)
   {
      _byte_size = _array_length * _base_type->ByteSize();
   }
   else
   {
      _byte_size = -1;
   }
}


} }
