#ifndef _MEM__FS__POSITION__RANGE__HPP_
#define _MEM__FS__POSITION__RANGE__HPP_


#include <iostream>
#include "mem/fs/position/Position.hpp"


namespace mem { namespace fs { namespace position {


class Range : public Position
{
   public: int _column_start;
   public: inline void s_col_start(int col_start)
   {
      this->_column_start = col_start;
   }
   public: int _column_end;
   public: inline void s_col_end (int col_end)
   {
      this->_column_end = col_end;
   }

   public: int _line_end;
   public: inline void s_line_end (int line)
   {
      this->_line_end = line;
   }

   public: Range ();
   public: Range (Range pos_start, Range pos_end);
   public: virtual Position* copy ();
   public: virtual Range* copy_range();
   public: virtual PositionType get_type_at (int column);
};


} } }

#endif
