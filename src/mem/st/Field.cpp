#include "mem/st/Field.hpp"


namespace mem { namespace st {


//-----------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Field::Field ()
{
   _field_index = 0;
   _kind = FIELD;
   _virtual_function = NULL;
}

} }
