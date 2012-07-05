#ifndef _MEM__FS__FILE__HPP_
#define _MEM__FS__FILE__HPP_


#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


namespace mem { namespace fs {


class File
{
   public: std::vector<std::string*> _lines;
   public: std::string _path;
   public: std::string gPath() const {return this->_path;}

   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   File ();

   /**
    * Destructor.
    */
   ~File ();

   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   /**
    * Dumps the file contents to stdout.
    */
   void
   dump ();

   /**
    * Returns the Nth line of the file.
    */
   std::string*
   getLine (size_t n) const;

   /**
    * Returns the Nth line of the file as a C string.
    */
   inline const char*
   getLineCstr(size_t i) const {return this->getLine(i)->c_str();}

   /**
    * Returns true if the i is a valid line.
    */
   bool
   isLineInFile(size_t i) const { return i < this->_lines.size();}

   /**
    * Reads all the lines in the file.
    */
   bool
   open (std::string name);
};


} }


#endif
