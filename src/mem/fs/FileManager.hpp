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
   public: std::map<std::string, File*> _files;
   public: std::vector<std::string> _path;

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
    * Appends the include path.
    */
   inline void
   appendPath (std::string dir_path) {_path.push_back(dir_path);}

   /**
    * Returns the Nth line in a given previously opened file.
    */
   std::string
   getLineOf (std::string file_path, unsigned int line);

   /**
    * Opens a file.
    */
   File*
   openFile (std::string file_path);

   /**
    * Tries to open a file.
    */
   File*
   tryOpenFile (std::string file_path, std::vector<std::string>& paths_tried);
};


} }

#endif
