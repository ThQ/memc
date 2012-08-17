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


std::string
Util::getNamespaceNameFromPath (std::string path)
{
   std::string ns_name = stripFileExtension(path);

   while (ns_name[0] == '/' || ns_name[0] == '.')
   {
      ns_name = ns_name.substr(1, ns_name.size());
   }

   for (size_t i = 0 ; i < ns_name.size() ; ++i)
   {
      if (ns_name[i] == '/')
      {
         ns_name[i] = '.';
      }
   }

   return ns_name;
}

std::string
Util::stripFileExtension(std::string path)
{
   size_t last_dot_pos = path.find_last_of('.');
   std::string stripped_path = "";

   if (last_dot_pos != 0)
   {
      stripped_path = path.substr(0, last_dot_pos);
   }

   return stripped_path;
}

std::vector<std::string>
Util::split (std::string qualified_name, char separator)
{
   std::vector<std::string> parts;
   std::string buffer = "";

   for (size_t i=0; i < qualified_name.size(); ++i)
   {
      if (qualified_name[i] != separator)
      {
         buffer += qualified_name[i];
      }
      else
      {
         parts.push_back(buffer);
         buffer = "";
      }
   }
   if (buffer != "")
   {
      parts.push_back(buffer);
   }
   return parts;
}

int
Util::getIntStringLength (double nb)
{
   int max_int_len = 1;

   while (max_int_len++)
   {
      if (nb < pow(static_cast<double>(10), max_int_len))
      {
         break;
      }
   }
   return max_int_len;
}

bool
Util::getIntFromString (const char* nb, int& i_out)
{
   int int_max_len = Util::getIntStringLength(INT_MAX);
   int nb_len = strlen(nb);
   i_out = 0;

   // FIXME Only works when the nb lenght is < to INT_MAX len
   if (nb_len < int_max_len)
   {
      i_out = atoi(nb);
      return true;
   }

   return false;
}



}
