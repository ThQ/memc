#include "mem/fs/position/Position.hpp"


namespace mem { namespace fs { namespace position {


Position::~Position()
{
}

Position*
Position::copy ()
{
   Position* pos = new Position();
   pos->_file = _file;
   return pos;
}

PositionType
Position::getTypeAt (int column)
{
   return NOTHING;
}


} } }
