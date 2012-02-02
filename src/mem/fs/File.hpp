#ifndef _MEM__FS__FILE__HPP_
#define _MEM__FS__FILE__HPP_


#include <fstream>
#include <iostream>
#include <string>
#include <vector>


namespace mem { namespace fs
{
   class File
   {
      public: std::vector<std::string*> _lines;
      public: std::string _path;

      public: File ();
      public: ~File ();
      public: void dump ();
      public: bool open (std::string name);
   };
}
}

#endif
