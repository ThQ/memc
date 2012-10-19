#include "mem/fs/FileManager.hpp"


namespace mem { namespace fs {


FileManager::~FileManager ()
{
   std::map<std::string,File*>::iterator it = _files.begin();
   for (; it != _files.end(); ++it )
   {
      DEBUG_PRINTF("Delete FILE %s\n", it->second->gPath().c_str());
      delete it->second;
   }
}

std::string
FileManager::getLineOf (std::string file_path, unsigned int lineno)
{
   std::string line;
   std::map<std::string, File*>::iterator file_it;
   if ((file_it = _files.find(file_path)) != _files.end())
   {
      if (file_it->second->_lines.size() > lineno)
      {
         line.assign(file_it->second->_lines[lineno - 1]->c_str());
      }
   }
   return line;
}

File*
FileManager::openFile (std::string file_path)
{
   File* file = new File();
   if (file->open(file_path))
   {
      _files[file_path] = file;
      return file;
   }
   delete file;
   return NULL;
}

File*
FileManager::tryOpenFile (std::string file_path,
   std::vector<std::string>& paths_tried)
{
   File* res = openFile(file_path);
   paths_tried.push_back(file_path);

   if (res == NULL)
   {
      std::string try_file_path;

      std::vector<std::string>::size_type i;
      for (i=0; res==NULL && i < _path.size(); ++i)
      {
         try_file_path = _path[i] + "/" + file_path;
         DEBUG_PRINTF("Trying to open %s\n", try_file_path.c_str());
         paths_tried.push_back(try_file_path);

         res = openFile(try_file_path);

         if (res != NULL)
         {
            res->_include_path = _path[i];
            break;
         }
      }
   }

   return res;
}


} }
