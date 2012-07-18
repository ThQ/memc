#ifndef _MEM__LOG__LOGGER__HPP_
#define _MEM__LOG__LOGGER__HPP_


#include <stdarg.h>
#include <stdio.h>
#include "mem/log/Formatter.hpp"
#include "mem/log/Message.hpp"
#include "mem/log/MessageLevel.hpp"
#include "mem/ss.hpp"

namespace mem { namespace log {


class Logger
{
   protected:

   Formatter* _formatter;
   int _level;
   int _n_errors;
   int _n_warnings;
   int _n_fatal_errors;


   //--------------------------------------------------------------------------
   // PROPERTIES
   //--------------------------------------------------------------------------
   public:

   // ErrorCount
   GETTER(ErrorCount, int) {return _n_errors;}

   // FatalErrorCount
   GETTER(FatalErrorCount, int) {return _n_fatal_errors;}

   // Formatter
   SETTER(Formatter, Formatter*) {_formatter = val;}

   // Level
   SETTER(Level, int) {_level = val;}

   // WarningCount
   GETTER(WarningCount, int) {return _n_warnings;}


   //--------------------------------------------------------------------------
   // CONSTRUCTORS / DESTRUCTOR
   //--------------------------------------------------------------------------
   public:

   /**
    * Default constructor.
    */
   Logger();

   /**
    * Destructor.
    */
   virtual
   ~Logger();


   //--------------------------------------------------------------------------
   // PUBLIC FUNCTIONS
   //--------------------------------------------------------------------------
   public:

   void
   error (const char* message);

   void
   error (const char* format, ...);

   void
   fatalError (const char* message);

   void
   fatalError (const char* format, ...);

   void
   log (Message* msg);

   void
   log (MessageLevel level, const char* message);

   void
   log (MessageLevel level, const char* format, va_list arg);

   void
   info (const char* message);

   void
   info (const char* format, ...);

   void
   debug (const char* message);

   void
   debug (const char* format, ...);

   void
   warning (const char* message);

   void
   warning (const char* format, ...);

   virtual void
   write (std::string str){}
};


} }


#endif
