#include "mem/fs/position/Range.hpp"


namespace mem { namespace fs { namespace position {

Range::Range ()
{
   this->_file = NULL;
   this->_line = 0;
   this->_column_start = 0;
   this->_column_end = 0;
}

Position*
Range::copy ()
{
   Range* rnge = new Range();
   rnge->_file = this->_file;
   rnge->_line = this->_line;
   rnge->_column_start = this->_column_start;
   rnge->_column_end = this->_column_end;
   return rnge;
}

Range*
Range::copy_range ()
{
   return static_cast<Range*>(this->copy());
}

PositionType
Range::get_type_at (int column)
{
   if (column >= this->_column_start && column <= this->_column_end)
   {
      return RANGE;
   }
   return NOTHING;
}

} } }
