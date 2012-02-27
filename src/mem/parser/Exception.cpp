#include "mem/parser/Exception.hpp"
/*
namespace mem { namespace parser {


Exception::Exception ()
{
   this->_level = UNKNOWN;
   this->_location = 0;
   this->_hints = 0;
   this->_hint_cursor = 0;
   this->_hint_count = 0;
}

Exception::LEVEL
Exception::level ()
{
   return this->_level;
}

SourceLocation*
Exception::location ()
{
   return this->_location;
}

const char*
Exception::message ()
{
   return this->_message;
}

void
Exception::print ()
{
   switch(this->_level)
   {
      case WARNING:
         printf("[\033[01;31mWarning\033[0m]");
         break;
      case ERROR:
         printf("[Error]");
         break;
      default:
         printf("[Unknown]");
         break;
   }
   printf(" %s\n", this->_message);
   printf("| ---------------------------------------------------------------\n");
   if (this->_location != 0)
   {
      printf("| @ <stdin>:%d,%d\n",
         this->_location->_line,
         this->_location->_column);
   }
   if (this->_hint_count > 0)
   {
      for (unsigned char i = 0 ; i < this->_hint_count ; ++ i)
      {
         printf("| * %s\n", this->_hints[i]);
      }
   }
}

void
Exception::push_hint (char* hint)
{
   this->_hints[this->_hint_cursor] = hint;
   ++ this->_hint_cursor;
}

void
Exception::set_level (LEVEL level)
{
   this->_level = level;
}

void
Exception::set_location (SourceLocation* location)
{
   this->_location = location;
}

void
Exception::set_message (const char* message)
{
   this->_message = message;
}

void
Exception::size_hints (unsigned char size)
{
   this->_hint_cursor = 0;
   this->_hint_count = size;
   this->_hints = new char*[size];
}

} }

*/
