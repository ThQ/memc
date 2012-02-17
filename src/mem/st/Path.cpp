#include "mem/st/Path.hpp"


namespace mem { namespace st {


Path::Path (std::string path)
{
   this->assign(path);
   this->_last_dot_pos = 0;
}

std::string
Path::next_name ()
{
   std::string name="";
   for (size_t i = this->_last_dot_pos ; i < this->length() ; ++i)
   {
      if (this->data()[i] == '.')
      {
         name = this->substr(this->_last_dot_pos, i-this->_last_dot_pos);
         this->_last_dot_pos = i + 1;
         break;
      }
      else if (i == this->length() - 1)
      {
         name = this->substr(this->_last_dot_pos, i-this->_last_dot_pos+1);
         this->_last_dot_pos = i + 1;
         break;
      }
   }
   return name;
}

void
Path::reset ()
{
   this->_last_dot_pos = 0;
}


} }
