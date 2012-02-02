#include "mem/fs/position/Cursor.hpp"

namespace mem { namespace fs { namespace position {


Cursor::Cursor ()
{
   this->_file = NULL;
   this->_line = 0;
   this->_column = 0;
}

Cursor::Cursor (int line, int column)
{
   this->_file = NULL;
   this->_line = line;
   this->_column = column;
}

Cursor::Cursor (fs::File* file, int line, int column)
{
   this->_column = column;
   this->_file = file;
   this->_line = line;
}

Position*
Cursor::copy ()
{
   Cursor* cur = new Cursor();
   cur->_file = this->_file;
   cur->_line = this->_line;
   cur->_column = this->_column;

   return cur;
}

PositionType
Cursor::get_type_at (int column)
{
   if (column == this->_column)
   {
      return CURSOR;
   }
   return NOTHING;
}

} } }
