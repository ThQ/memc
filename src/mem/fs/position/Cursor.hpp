#ifndef _MEM__FS__POSITION__CURSOR__HPP_
#define _MEM__FS__POSITION__CURSOR__HPP_


#include "mem/fs/position/Position.hpp"


namespace mem { namespace fs { namespace position {


class Cursor : public Position
{
   public: int _column;

   public: Cursor();
   public: Cursor (int line, int column);
   public: Cursor (fs::File* file, int line, int column);

   public: virtual Position* copy ();
   public: virtual PositionType getTypeAt (int column);
};

} } }

#endif
