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

   public: ~FileManager();
   public: inline void appendPath (std::string dir_path) {_path.push_back(dir_path);}
   public: std::string getLineOf (std::string file_path, unsigned int line);
   public: File* openFile (std::string file_path);
};


} }

#endif
