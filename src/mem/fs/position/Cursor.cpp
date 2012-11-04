#include "mem/fs/position/Cursor.hpp"


namespace mem { namespace fs { namespace position {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------
Cursor::Cursor ()
{
   _file = NULL;
   _line = 0;
   _column = 0;
}

Cursor::Cursor (int line, int column)
{
   _file = NULL;
   _line = line;
   _column = column;
}

Cursor::Cursor (fs::File* file, int line, int column)
{
   _column = column;
   _file = file;
   _line = line;
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

Position*
Cursor::copy ()
{
   Cursor* cur = new Cursor();
   cur->_file = _file;
   cur->_line = _line;
   cur->_column = _column;

   return cur;
}

PositionType
Cursor::getTypeAt (int column) const
{
   if (column == _column)
   {
      return CURSOR;
   }
   return NOTHING;
}


} } }
