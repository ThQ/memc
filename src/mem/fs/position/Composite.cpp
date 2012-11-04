#include "mem/fs/position/Composite.hpp"


namespace mem { namespace fs { namespace position {


//=============================================================================
// CONSTRUCTORS / DESTRUCTOR
//-----------------------------------------------------------------------------

Composite::~Composite ()
{
   for (size_t i = 0; i < _children.size() ; ++i)
   {
      delete _children[i];
   }
}


//=============================================================================
// PUBLIC FUNCTIONS
//-----------------------------------------------------------------------------

void
Composite::addChild (Position* child)
{
   _file = child->File();
   _line = child->Line();
   _children.push_back(child);
}

PositionType
Composite::getTypeAt (int column) const
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
