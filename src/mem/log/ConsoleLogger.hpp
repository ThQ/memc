#ifndef _MEM__LOG__CONSOLER_LOGGER__H_
#define _MEM__LOG__CONSOLER_LOGGER__H_ __FILE__


#include <iostream>
#include "mem/log/Logger.hpp"


namespace mem { namespace log {


class ConsoleLogger : public Logger
{
   protected: virtual void write(std::string str);
};


} }

#endif
