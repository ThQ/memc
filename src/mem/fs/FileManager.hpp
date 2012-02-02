#ifndef _MEM__FS__FILE_MANAGER__HPP_
#define _MEM__FS__FILE_MANAGER__HPP_


#include <assert.h>
#include <map>
#include <string>
#include <vector>
#include "macro.h"
#include "mem/fs/File.hpp"


namespace mem { namespace fs {


class FileManager
{
   public: std::map<std::string, File*> _files;
   public: std::vector<std::string> _path;

   public: ~FileManager();
   public: std::string get_line_of (std::string file_path, unsigned int line);
   public: File* open_file (std::string file_path);
};


} }

#endif
