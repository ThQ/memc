#include "mem/fs/File.hpp"

namespace mem { namespace fs {


File::File ()
{
}

File::~File ()
{
   for (size_t i = 0; i < _lines.size(); ++i)
   {
      delete _lines[i];
   }
}

void
File::dump ()
{
   for (size_t i = 0; i < _lines.size(); ++ i)
   {
      printf("#%d. %s\n", i + 1, _lines[i]->c_str());
   }
}

std::string*
File::getLine (size_t i) const
{
   assert(i < _lines.size() && "Line out of file");
   return _lines[i];
}

bool
File::open (std::string name)
{
   _path = name;
   std::ifstream is;
   is.open(name.c_str(), std::ios::in);

   if (is.good())
   {
      char* buffer = new char[6];
      for (unsigned int i = 0; i < 6 ; ++i)
      {
         buffer[i] = 0;
      }

      size_t buffer_len = 0;
      std::string* cur_line = new std::string();
      bool eol_found = false;
      size_t j = 0;
      size_t i = 0;

      while (!is.eof() && !is.fail())
      {
         j = 0;
         is.read(buffer, 5);
         buffer_len = is.gcount();
         for (i = 0; i < buffer_len; ++i)
         {
            if (buffer[i] == '\n')
            {
               eol_found = true;
               cur_line->append(buffer, j, i - j);
               _lines.push_back(cur_line);
               cur_line = new std::string();
               j = i + 1;
            }
         }
         if (!eol_found)
         {
            cur_line->append(buffer, 0, buffer_len);
         }
         else
         {
            cur_line->append(buffer, j, buffer_len - j);
         }
         eol_found = false;
      }

      if (buffer_len != 0)
      {
         cur_line->append(buffer, j, buffer_len - 1);
         _lines.push_back(cur_line);
      }

      delete[] buffer;
      return true;
   }
   return false;
}


} }
