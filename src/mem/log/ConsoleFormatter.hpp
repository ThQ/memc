#ifndef _MEM__LOG__CONSOLE_FORMATTER__HPP_
#define _MEM__LOG__CONSOLE_FORMATTER__HPP_


#include <sstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "macro.h"
#include "mem/fs/position/Position.hpp"
#include "mem/log/Formatter.hpp"


namespace mem { namespace log {

   typedef const char* (*TagFunctor)();
   class ConsoleFormatter : public Formatter
   {
      public: std::map<std::string, log::TagFunctor> _tags;
      public: struct StackElement
      {
         size_t start;
         size_t end;
         std::string name;
      };



      public: ConsoleFormatter ();
      public: virtual ~ConsoleFormatter ();
      public: void add_tag(std::string tag_name, log::TagFunctor fptr_start, log::TagFunctor fptr_end);
      public: virtual std::string format (Message* msg);
      public: void format_description (std::ostringstream& str, Message* msg);
      public: void format_level_name (std::ostringstream& str, MessageLevel level);
      public: void format_message (std::ostringstream& str, Message* msg);
      public: void format_position (std::ostringstream& str, fs::position::Position* pos);
      public: virtual const char* format_string (const char* message);
      public: static const char* format_type_start ();
      public: static const char* format_type_end ();
      public: log::TagFunctor get_tag_functor (std::string name);
   };

} }

#endif
