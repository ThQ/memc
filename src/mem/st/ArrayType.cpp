#include "mem/st/ArrayType.hpp"


namespace mem { namespace st {

//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

ArrayType::ArrayType ()
{
   _kind = ArrayType::kTYPE;
   _array_length = -1;
   _item_type = NULL;
}


//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

bool
ArrayType::canCastTo (Type* dest_ty) const
{
  if (st::isa<st::ArrayType>(dest_ty))
  {
      ArrayType* arr_ty = st::cast<ArrayType>(dest_ty);
      return arr_ty->ItemType() == _item_type && arr_ty->ArrayLength() == _array_length;
  }
  return false;
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
