#include "mem/fs/position/Range.hpp"


namespace mem { namespace fs { namespace position {

Range::Range ()
{
   this->_file = NULL;
   this->_line = 0;
   this->_line_end = 0;
   this->_column_start = 0;
   this->_column_end = 0;
}

Range::Range(Range pos_start, Range pos_end)
{
   this->_file = pos_start._file;
   this->_line = pos_start._line;
   this->_line_end = pos_end._line;
   this->_column_start = pos_start._column_start;
   this->_column_end = pos_end._column_end;
}

Position*
Range::copy ()
{
   Range* rnge = new Range();
   rnge->_file = this->_file;
   rnge->_line = this->_line;
   rnge->_line_end = this->_line_end;
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
Range::getTypeAt (int column)
{
   // @FIXME : does not work on multi-lines
   if (column >= this->_column_start && column <= this->_column_end)
   {
      return RANGE;
   }
   return NOTHING;
}

} } }
