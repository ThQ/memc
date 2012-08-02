#include "mem/st/ArrayType.hpp"


namespace mem { namespace st {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

ArrayType::ArrayType ()
{
   _kind = ARRAY;
   _array_length = -1;
   _item_type = NULL;
}


//-----------------------------------------------------------------------------
// PROTECTED FUNCTIONS
//-----------------------------------------------------------------------------

void
ArrayType::_computeByteSize ()
{
   if (_array_length != -1 && _item_type != NULL
      && _item_type->ByteSize() != -1)
   {
      _byte_size = _array_length * _item_type->ByteSize();
   }
   else
   {
      _byte_size = -1;
   }
}


} }
