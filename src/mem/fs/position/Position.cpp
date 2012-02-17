#include "mem/fs/position/Position.hpp"

namespace mem { namespace fs { namespace position {

Position::~Position()
{
}

Position*
Position::copy ()
{
   Position* pos = new Position();
   pos->_file = this->_file;
   return pos;
}

PositionType
Position::get_type_at (int column)
{
   return NOTHING;
}


} } }
