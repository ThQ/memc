#ifndef _MEM__FS__POSITION__COMPOSITE__HPP_
#define _MEM__FS__POSITION__COMPOSITE__HPP_


#include <vector>

#include "mem/fs/position/Position.hpp"


namespace mem { namespace fs { namespace position {


class Composite : public Position
{
   public : std::vector<Position*> _children;

   public: void add_child (Position* child);
   public: virtual PositionType get_type_at (int column);
};


} } }

#endif
