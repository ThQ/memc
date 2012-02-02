#include "mem/log/ConsoleLogger.hpp"

namespace mem { namespace log {


void
ConsoleLogger::write(std::string str)
{
   printf("%s", str.c_str());
}


} }
