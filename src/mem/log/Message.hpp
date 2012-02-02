#ifndef _MEM__LOG__MESSAGE__HPP_
#define _MEM__LOG__MESSAGE__HPP_


#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <string.h>

#include "macro.h"
#include "mem/fs/position/Position.hpp"
#include "mem/log/MessageLevel.hpp"


namespace mem { namespace log {


class Message
{
   public: std::string _description;
   public: std::string _file_path;
   public: MessageLevel _level;
   public: std::string _message;
   public: fs::position::Position* _position;
   public: std::string _source_line;

   public: inline Message ()
   {
      this->_position = NULL;
   }

   public: inline Message (MessageLevel level)
   {
      this->_position = NULL;
      this->set_level(level);
   }

   public: ~Message();

   public: void format_description(const char* format, ...);
   public: void format_message (const char* format, ...);
   public: void set_description(const char* desc);
   public: inline void set_description (std::string desc)
   {
      this->_description.assign(desc);
   }

   public: void set_level (MessageLevel level);
   public: void set_message (const char* message);
   public: void set_position (fs::position::Position* position);
};


} }
#endif
