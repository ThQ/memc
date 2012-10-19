#ifndef _MEM__FS__FILE__HPP_
#define _MEM__FS__FILE__HPP_


#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "mem/ss.hpp"

namespace mem { namespace fs {


class File
{
   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   std::vector<std::string*> _lines;
   std::string _path;
   std::string _include_path;

   std::string gPath() const {return this->_path;}

   std::string
   gPathWithoutInclude () {return _path.substr(_include_path.size(), _path.size() - _include_path.size() + 1);}


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
   // PROPERTIES
   //--------------------------------------------------------------------------


   //--------------------------------------------------------------------------
   // FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   /**
    * Dump the file contents to stdout.
    */
   void
   dump ();

   /**
    * Return the Nth line of the file.
    */
   std::string
   getLine (size_t n) const;

   /**
    * Return the Nth line of the file as a C string.
    */
   inline const char*
   getLineCstr(size_t i) const {return this->getLine(i).c_str();}

   /**
    * Return true if the i is a valid line.
    */
   bool
   isLineInFile(size_t i) const { return i < this->_lines.size();}

   /**
    * Read all the lines in the file.
    */
   bool
   open (std::string name);
};


} }


#endif
