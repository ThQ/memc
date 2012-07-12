#include "mem/ast/node/Number.hpp"


namespace mem { namespace ast { namespace node {


Number::Number ()
{
   _type = MEM_NODE_NUMBER;
   _format = ' ';
   _sval = 0;
   _ival = 0;
   _lval = 0;
}

int
Number::getInt ()
{
   return _ival;
}

unsigned int
Number::getUInt ()
{
   return 0;
}

short
Number::getShort ()
{
   return _sval;
}

void
Number::setInt (int i)
{
   _format = 'i';
   _ival = i;
}

void
Number::setShort (short s)
{
   _format = 's';
   _sval = s;
}

std::string
Number::getStringFromVal ()
{
   std::ostringstream s;

   switch (_format)
   {
      case 'i':
         s << (int)_ival;
         break;
      case 's':
         s << (short)_sval;
         break;
      case 'c':
         s << (short)_cval;
         break;
   }

   return s.str();
}

bool
Number::isValid ()
{
   if (!Node::isValid()) return false;
   if (gChildCount() != 0) return false;

   return true;
}

} } }
