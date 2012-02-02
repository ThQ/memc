#ifndef _MEM__LOG__FORMATTER__HPP_
#define _MEM__LOG__FORMATTER__HPP_


#include <string>
#include <string.h>
#include "mem/log/Message.hpp"


namespace mem { namespace log {


class Formatter
{
   public: virtual ~Formatter();
   public: virtual std::string format (Message* msg);
   public: virtual const char* format_string (const char* message);
};


} }

#endif
