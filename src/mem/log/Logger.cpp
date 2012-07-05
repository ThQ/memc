#include "mem/log/Logger.hpp"


namespace mem { namespace log {

Logger::Logger()
{
   this->_n_errors = 0;
   this->_n_warnings = 0;
   this->_n_fatal_errors = 0;
}

Logger::~Logger()
{
   if (this->_formatter != NULL)
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
Logger::fatalError (const char* format, ...)
{
   va_list vargs;
   va_start(vargs, format);
   this->log(FATAL_ERROR, format, vargs);
}

void
Logger::fatalError (const char* message)
{
   this->log(FATAL_ERROR, message);
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
   assert(this->_formatter != NULL);

   if (msg != NULL)
   {
      switch (msg->_level)
      {
         case ERROR: _n_errors++; break;
         case WARNING: _n_warnings++; break;
         case FATAL_ERROR: _n_fatal_errors++; break;
         default:break; // Keep that, or clang will complain
      }

      if (msg->gLevel() >= _level)
      {
         std::string log_msg = _formatter->format(msg);
         this->write(log_msg);
      }
      delete msg;
   }
}

void
Logger::log (MessageLevel level, const char* message)
{
   Message* msg = new Message(level);
   msg->sMessage(message);
   this->log(msg);
}

void
Logger::log (MessageLevel level, const char* format, va_list varg)
{
   char* fmsg = new char[300];
   vsprintf(fmsg, format, varg);

   Message* msg = new Message(level);
   msg->sMessage(fmsg);
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
