#ifndef _MEM__FS__POSITION__CURSOR__HPP_
#define _MEM__FS__POSITION__CURSOR__HPP_


#include "mem/fs/position/Position.hpp"


namespace mem { namespace fs { namespace position {


class Cursor : public Position
{
   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   Cursor();

   Cursor (int line, int column);

   Cursor (fs::File* file, int line, int column);

   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Position*
   copy ();

   virtual PositionType
   getTypeAt (int column) const;


   //==========================================================================
   // FIELDS
   //--------------------------------------------------------------------------
   protected:

   int _column;
};

} } }

#endif
