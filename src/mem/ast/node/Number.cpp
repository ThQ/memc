#include "mem/ast/node/Number.hpp"


namespace mem { namespace ast { namespace node {


Number::Number ()
{
   _type = Kind::NUMBER;
   _format = ' ';
   _val = 0;
}

int
Number::getInt ()
{
   return (int)_val;
}

unsigned int
Number::getUInt ()
{
   return 0;
}

short
Number::getShort ()
{
   return (short)_val;
}

void
Number::setInt (int i)
{
   _format = 'i';
   _val = i;
}

void
Number::setShort (short s)
{
   _format = 's';
   _val = s;
}

std::string
Number::getStringFromVal ()
{
   std::ostringstream s;

   switch (_format)
   {
      case 'i':
         s << (int)_val;
         break;

      case 's':
         s << (short)_val;
         break;

      case 'c':
         s << (char)_val;
         break;

      default:
         DEBUG_PRINTF("Unknown number format `%c'\n", _format);
   }

   return s.str();
}

void
Number::isValid (NodeValidator* v)
{
   Node::isValid(v);
   v->ensure(ChildCount() == 0, "Number cannot have children");
}

} } }
