#include "mem/fs/position/Composite.hpp"

namespace mem { namespace fs { namespace position {


Composite::~Composite ()
{
   for (size_t i = 0; i < _children.size() ; ++i)
   {
      delete _children[i];
   }
}

void
Composite::addChild (Position* child)
{
   _file = child->_file;
   _line = child->_line;
   _children.push_back(child);
}

PositionType
Composite::getTypeAt (int column)
{
   PositionType i_type = NOTHING;
   PositionType cur_type = NOTHING;

   for (size_t i = 0 ; i < _children.size() ; ++i)
   {
      cur_type = _children[i]->getTypeAt(column);
      if (cur_type > i_type)
      {
         i_type = cur_type;
      }
   }
   return i_type;
}


} } }
