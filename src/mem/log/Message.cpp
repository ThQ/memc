#include "mem/log/Message.hpp"

namespace mem { namespace log {


Message::~Message ()
{
   if (this->_position != NULL)
   {
      delete this->_position;
   }
}

void
Message::format_message (const char* format, ...)
{
   va_list args;
   va_start(args, format);
   char message [256] = "\0";
   vsprintf(message, format, args);
   va_end(args);
   this->_message = message;
}

void
Message::format_description (const char* format, ...)
{
   va_list args;
   va_start(args, format);
   char desc [300] = "\0";
   if (vsprintf(desc, format, args) >= 0)
   {
      this->_description.assign(desc);
   }
   else
   {
      this->_description.assign("[[INTERNAL_ERROR]]");
   }
   va_end(args);
}

void
Message::set_description (const char* desc)
{
   this->_description.assign(desc);
}

void
Message::set_level (MessageLevel level)
{
   this->_level = level;
}

void
Message::set_message (const char* message)
{
   this->_message.assign(message);
}

void
Message::set_position (fs::position::Position* position)
{
   this->_position = position;
}


} }
