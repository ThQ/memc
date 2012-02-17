#include "mem/fs/position/Composite.hpp"

namespace mem { namespace fs { namespace position {


Composite::~Composite ()
{
   for (unsigned int i = 0; i < this->_children.size() ; ++i)
   {
      if (this->_children[i] != NULL)
      {
         delete this->_children[i];
      }
   }
}

void
Composite::add_child (Position* child)
{
   this->_file = child->_file;
   this->_line = child->_line;
   this->_children.push_back(child);
}

PositionType
Composite::get_type_at (int column)
{
   PositionType i_type = NOTHING;
   PositionType cur_type = NOTHING;
   for (unsigned int i = 0 ; i < this->_children.size() ; ++i)
   {
      cur_type = this->_children[i]->get_type_at(column);
      if (cur_type > i_type)
      {
         i_type = cur_type;
      }
   }
   return i_type;
}


} } }
