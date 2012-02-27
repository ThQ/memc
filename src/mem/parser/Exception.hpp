#ifndef MEM_PARSER_EXCEPTION_HPP
#define MEM_PARSER_EXCEPTION_HPP

#include <stdio.h>
#include "mem/parser/SourceLocation.hpp"

/**
namespace mem { namespace parser {

   class Exception
   {
      public: enum LEVEL {UNKNOWN=0, WARNING, ERROR};

      protected: unsigned char _hint_count;
      protected: unsigned char _hint_cursor;
      protected: char** _hints;
      protected: const char* _message;
      protected: Exception::LEVEL _level;
      protected: SourceLocation* _location;

      public: Exception ();
      public: const char* message ();
      public: LEVEL level ();
      public: SourceLocation* location ();
      public: void print ();
      public: void push_hint(char* hint);
      public: void set_message (const char* message);
      public: void set_level (LEVEL level);
      public: void set_location (SourceLocation* location);
      public: void size_hints (unsigned char size);
   };

} }
*/

#endif
