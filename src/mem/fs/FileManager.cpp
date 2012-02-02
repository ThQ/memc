#include "mem/fs/FileManager.hpp"

namespace mem { namespace fs {


FileManager::~FileManager ()
{
   std::map<std::string,File*>::iterator it = this->_files.begin();
   for (; it != this->_files.end(); it++ )
   {
      delete it->second;
   }
}

std::string
FileManager::get_line_of (std::string file_path, unsigned int lineno)
{
   std::string line;
   std::map<std::string, File*>::iterator file_it;
   if ((file_it = this->_files.find(file_path)) != this->_files.end())
   {
      if (file_it->second->_lines.size() > lineno)
      {
         line.assign(file_it->second->_lines[lineno - 1]->c_str());
      }
   }
   return line;
}

File*
FileManager::open_file (std::string file_path)
{
   File* file = new File();
   if (file->open(file_path))
   {
      this->_files[file_path] = file;
      return file;
   }
   delete file;
   return NULL;
}


} }
