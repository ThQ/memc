#ifndef _MEM__UTIL__HPP_
#define _MEM__UTIL__HPP_


#include <limits.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>


namespace mem {


class Util
{
   public:

   static void
   partition_full_type_name (std::string full_type_name, std::string& ns, std::string& type_name);

   static std::string
   getPathFromNamespace (std::string sNamespace);

   static std::string
   getNamespaceFromPath (std::string sPath);

   public: static std::string stripFileExtension (std::string file_path);
   public: static std::vector<std::string>split (std::string qualified_name, char separator);

   public: static int getIntStringLength (double nb);
   public: static bool getIntFromString (const char* nb, int& i_out);
};


}

#endif
