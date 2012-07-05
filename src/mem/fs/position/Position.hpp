#ifndef _MEM__FS__POSITION__POSITION__HPP_
#define _MEM__FS__POSITION__POSITION__HPP_


#include "mem/fs/File.hpp"


namespace mem { namespace fs { namespace position {


typedef enum {NOTHING=0, CURSOR=1, RANGE=2} PositionType;

class Position
{

   //--------------------------------------------------------------------------
   // PUBLIC PROPERTIES
   //--------------------------------------------------------------------------

   public: File* _file;
   public: inline File* gFile() const {return this->_file;}
   public: inline void sFile (File* file) { this->_file = file; }

   public: int _line;
   public: inline int gLine() const {return this->_line;}
   public: inline void sLine (int line) { this->_line = line; }


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Destructor.
    */
   virtual
   ~Position();
   public: virtual Position* copy ();
   public: virtual PositionType getTypeAt (int column);

};


} } }

#endif
