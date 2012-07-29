#include "mem/log/ConsoleLogger.hpp"

namespace mem { namespace log {

void
ConsoleLogger::begin ()
{
   if (_formatter != NULL)
   {
      printf("%s", _formatter->formatStart().c_str());
   }
}

void
ConsoleLogger::finish ()
{
   if (_formatter != NULL)
   {
      printf("%s", _formatter->formatEnd().c_str());
   }
}

void
ConsoleLogger::write(std::string str)
{
   printf("%s", str.c_str());
}


} }
