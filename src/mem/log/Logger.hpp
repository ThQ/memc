#ifndef _MEM__LOG__LOGGER__HPP_
#define _MEM__LOG__LOGGER__HPP_


#include <stdarg.h>
#include <stdio.h>
#include "check.h"
#include "macro.h"
#include "mem/log/Formatter.hpp"
#include "mem/log/Message.hpp"
#include "mem/log/MessageLevel.hpp"


namespace mem { namespace log {

   class Logger
   {
      public: Formatter* _formatter;
      public: MessageLevel _level;

      public: virtual ~Logger();
      public: void error (const char* message);
      public: void error (const char* format, ...);
      public: void log (Message* msg);
      public: void log (MessageLevel level, const char* message);
      public: void log (MessageLevel level, const char* format, va_list arg);
      public: void info (const char* message);
      public: void info (const char* format, ...);
      public: void debug (const char* message);
      public: void debug (const char* format, ...);
      public: void warning (const char* message);
      public: void warning (const char* format, ...);

      //protected: void _printf(const char* message, ...);
      protected: virtual void write (std::string str){}
   };

} }

#endif
