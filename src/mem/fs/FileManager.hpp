#ifndef _MEM__FS__FILE_MANAGER__HPP_
#define _MEM__FS__FILE_MANAGER__HPP_


#include <assert.h>
#include <map>
#include <string>
#include <vector>
#include "mem/fs/File.hpp"


namespace mem { namespace fs {


class FileManager
{
   //--------------------------------------------------------------------------
   // FIELDS
   //--------------------------------------------------------------------------
   public:

   std::map<std::string, File*> _files;
   std::vector<std::string> _path;


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   /**
    * Destructor.
    */
   ~FileManager();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   /**
    * Append the include path.
    */
   inline void
   appendPath (std::string dir_path) {_path.push_back(dir_path);}

   /**
    * Return the Nth line in a given previously opened file.
    */
   std::string
   getLineOf (std::string file_path, unsigned int line);

   /**
    * Open a file.
    */
   File*
   openFile (std::string file_path);

   /**
    * Try to open a file.
    */
   File*
   tryOpenFile (std::string file_path, std::vector<std::string>& paths_tried);
};


} }

#endif
