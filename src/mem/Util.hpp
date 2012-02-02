#ifndef _MEM__UTIL__HPP_
#define _MEM__UTIL__HPP_


#include <string>


namespace mem
{
   class Util
   {
      public: static void namespace_to_path (std::string& path);
      public: static void partition_full_type_name (std::string full_type_name, std::string& ns, std::string& type_name);
      public: static void path_to_namespace (std::string& path);
   };
}

#endif
