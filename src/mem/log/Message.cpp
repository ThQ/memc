#include "mem/log/Message.hpp"

namespace mem { namespace log {

Message::Message ()
{
   _id = "unknown";
   _level = UNKNOWN;
   _position = NULL;
}

Message::Message (MessageLevel level)
{
   _position = NULL;
   _level = level;
}

Message::~Message ()
{
   delete _position;
}

void
Message::formatMessage (const char* format, ...)
{
   va_list args;
   va_start(args, format);
   char message [256] = "\0";
   vsprintf(message, format, args);
   va_end(args);
   _message = message;
}

void
Message::formatDescription (const char* format, ...)
{
   va_list args;
   va_start(args, format);
   char desc [300] = "\0";
   if (vsprintf(desc, format, args) >= 0)
   {
      _description.assign(desc);
   }
   else
   {
      _description.assign("[[INTERNAL_ERROR]]");
   }
   va_end(args);
}


} }
