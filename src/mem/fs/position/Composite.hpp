#ifndef _MEM__FS__POSITION__COMPOSITE__HPP_
#define _MEM__FS__POSITION__COMPOSITE__HPP_


#include <vector>

#include "mem/fs/position/Position.hpp"


namespace mem { namespace fs { namespace position {


class Composite : public Position
{
   public : std::vector<Position*> _children;


   public: ~Composite ();

   public: void addChild (Position* child);
   public: virtual PositionType getTypeAt (int column);
};


} } }

#endif
