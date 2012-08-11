#ifndef _MEM__FS__POSITION__RANGE__HPP_
#define _MEM__FS__POSITION__RANGE__HPP_


#include <iostream>
#include "mem/fs/position/Position.hpp"


namespace mem { namespace fs { namespace position {


class Range : public Position
{
   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   Range ();
   Range (Range pos_start, Range pos_end);

   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   GETTER(ColumnStart, int) {return _column_start;}
   SETTER(ColumnStart, int) {_column_start = val;}

   GETTER(ColumnEnd, int) {return _column_end;}
   SETTER(ColumnEnd, int) {_column_end = val;}


   GETTER(LineStart, int) {return _line_start;}
   SETTER(LineStart, int) {_line_start = val;}

   GETTER(LineEnd, int) {return _line_end;}
   SETTER(LineEnd, int) {_line_end = val;}

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   void
   append(fs::position::Range r);

   virtual Position*
   copy ();

   virtual Range*
   copy_range();

   void
   import (Range r);

   virtual PositionType
   getTypeAt (int column);

   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   protected:
   int _column_start;
   int _column_end;
   int _line_end;
   int _line_start;
};


} } }

#endif
