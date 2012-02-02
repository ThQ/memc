#include "mem/Util.hpp"

namespace mem {


void
Util::namespace_to_path (std::string& path)
{
   for (size_t i = 0 ; i < path.size() ; ++i)
   {
      if (path[i] == '.')
      {
         path[i] = '/';
      }
   }
}

void
Util::partition_full_type_name (std::string full_type_name, std::string& ns,
   std::string& type_name)
{
   size_t last_dot_pos = full_type_name.rfind('.');
   if (last_dot_pos == std::string::npos)
   {
      ns.assign("");
      type_name.assign(full_type_name);
   }
   else
   {
      ns.assign(full_type_name.substr(0, last_dot_pos));
      type_name.assign(full_type_name.substr(last_dot_pos + 1));
   }
}

void
Util::path_to_namespace (std::string& path)
{
   for (size_t i = 0 ; i < path.size() ; ++i)
   {
      if (path[i] == '/')
      {
         path[i] = '.';
      }
   }
   if (path.compare(path.size() - 4, 4, ".mem", 4) == 0)
   {
      path.erase(path.size() - 4, 4);
   }
}


}
