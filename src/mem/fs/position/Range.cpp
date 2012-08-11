#include "mem/fs/position/Range.hpp"


namespace mem { namespace fs { namespace position {

Range::Range ()
{
   _file = NULL;
   _line_start = 0;
   _line_end = 0;
   _column_start = 0;
   _column_end = 0;
}

Range::Range (Range pos_start, Range pos_end)
{
   _file = pos_start._file;
   _line_start = pos_start._line_start;
   _line_end = pos_end._line_end;
   _column_start = pos_start._column_start;
   _column_end = pos_end._column_end;
}

void
Range::append (Range r)
{
   _column_end = r.ColumnEnd();
   _line_end = r.LineEnd();
}

Position*
Range::copy ()
{
   Range* rnge = new Range();
   rnge->_file = _file;
   rnge->_line_start = _line_start;
   rnge->_line_end = _line_end;
   rnge->_column_start = _column_start;
   rnge->_column_end = _column_end;
   return rnge;
}

Range*
Range::copy_range ()
{
   return static_cast<Range*>(copy());
}

void
Range::import (Range r)
{
   _line_start = r.LineStart();
   _line_end = r.LineEnd();
   _column_start = r.ColumnStart();
   _column_end = r.ColumnEnd();
}

PositionType
Range::getTypeAt (int column)
{
   // @FIXME : does not work on multi-lines
   if (column == _column_start)
   {
      return CURSOR;
   }
   else if (column >= _column_start && column <= _column_end)
   {
      return RANGE;
   }
   return NOTHING;
}

} } }
