#include "mem/Metadata.hpp"


namespace mem {


bool
Metadata::set (std::string md_name, std::string md_value)
{
   _md[md_name] = md_value;
   return true;
}


}
