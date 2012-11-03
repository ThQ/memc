#ifndef _MEM__FS__POSITION__POSITION__HPP_
#define _MEM__FS__POSITION__POSITION__HPP_


#include "mem/fs/File.hpp"


namespace mem { namespace fs { namespace position {


typedef enum {NOTHING=0, CURSOR=1, RANGE=2} PositionType;

class Position
{
   //==========================================================================
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   // Destructor.
   virtual
   ~Position();


   //==========================================================================
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // File
   inline File*
   File() const {return _file;}

   inline void
   setFile (class File* file) { _file = file; }

   // Line
   inline int
   Line() const {return _line;}

   inline void
   setLine (int line) { _line = line; }


   //==========================================================================
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   virtual Position*
   copy ();

   virtual PositionType
   getTypeAt (int column) const;


   //==========================================================================
   // FILES
   //--------------------------------------------------------------------------
   protected:

   class File* _file;
   int _line;
};


} } }

#endif
