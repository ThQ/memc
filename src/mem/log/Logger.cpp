#include "mem/log/Logger.hpp"


namespace mem { namespace log {


Logger::~Logger()
{
   if (this->_formatter!= NULL)
   {
      delete this->_formatter;
   }
}

void
Logger::debug (const char* message)
{
   this->log(DEBUG, message);
}

void
Logger::debug (const char* format, ...)
{
   va_list vargs;
   va_start(vargs, format);
   this->log(DEBUG, format, vargs);
}

void
Logger::error (const char* format, ...)
{
   va_list vargs;
   va_start(vargs, format);
   this->log(ERROR, format, vargs);
}

void
Logger::error (const char* message)
{
   this->log(ERROR, message);
}

void
Logger::info (const char* message)
{
   this->log(INFO, message);
}

void
Logger::info (const char* format, ...)
{
   va_list vargs;
   va_start(vargs, format);
   this->log(INFO, format, vargs);
}

void
Logger::log (Message* msg)
{
   ASSERT_NOT_NULL(this->_formatter);

   if (msg != NULL)
   {
      if (msg->_level >= this->_level)
      {
         std::string log_msg = this->_formatter->format(msg);
         this->write(log_msg);
      }
      delete msg;
   }
}

void
Logger::log (MessageLevel level, const char* message)
{
   Message* msg = new Message(level);
   msg->set_message(message);
   this->log(msg);
}

void
Logger::log (MessageLevel level, const char* format, va_list varg)
{
   char* fmsg = new char[300];
   vsprintf(fmsg, format, varg);

   Message* msg = new Message(level);
   msg->set_message(fmsg);
   this->log(msg);

   delete[] fmsg;
}

void
Logger::warning (const char* message)
{
   this->log(WARNING, message);
}

void
Logger::warning (const char* format, ...)
{
   va_list vargs;
   va_start(vargs, format);
   this->log(WARNING, format, vargs);
}


} }
