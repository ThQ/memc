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

   public: Message ();
   public: Message (MessageLevel level);
   public: ~Message();

   public: void formatDescription(const char* format, ...);
   public: void formatMessage (const char* format, ...);
   public: void sDescription(const char* desc);
   public: inline void sDescription (std::string desc) { this->_description.assign(desc); }
   public: void sLevel (MessageLevel level);
   public: void sMessage (const char* message);
   public: void sPosition (fs::position::Position* position);
};


} }
#endif
