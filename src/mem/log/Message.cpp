#include "mem/log/Message.hpp"

namespace mem { namespace log {

Message::Message ()
{
   this->_position = NULL;
}

Message::Message (MessageLevel level)
{
   this->_position = NULL;
   this->_level = level;
}

Message::~Message ()
{
   if (this->_position != NULL)
   {
      delete this->_position;
   }
}

void
Message::formatMessage (const char* format, ...)
{
   va_list args;
   va_start(args, format);
   char message [256] = "\0";
   vsprintf(message, format, args);
   va_end(args);
   this->_message = message;
}

void
Message::formatDescription (const char* format, ...)
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
Message::sDescription (const char* desc)
{
   this->_description.assign(desc);
}

void
Message::sLevel (MessageLevel level)
{
   this->_level = level;
}

void
Message::sMessage (const char* message)
{
   this->_message.assign(message);
}

void
Message::sPosition (fs::position::Position* position)
{
   this->_position = position;
}


} }
