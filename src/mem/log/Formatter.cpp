#include "mem/log/Formatter.hpp"

namespace mem { namespace log {


Formatter::~Formatter()
{
}

std::string
Formatter::format (Message* msg)
{
   std::string res = "";
   return res;
}

const char*
Formatter::format_string (const char* message)
{
   return 0;
}


} }
