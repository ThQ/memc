#include "mem/st/ArrayType.hpp"


namespace mem { namespace st {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

ArrayType::ArrayType ()
{
   _kind = ARRAY;
   _array_length = -1;
}


//-----------------------------------------------------------------------------
// PROTECTED FUNCTIONS
//-----------------------------------------------------------------------------

void
ArrayType::_computeByteSize ()
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
