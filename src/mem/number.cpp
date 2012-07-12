#include "mem/number.hpp"


namespace mem {


int
number::getIntStringLength (double nb)
{
   int max_int_len = 1;

   while (max_int_len++)
   {
      if (nb < pow(10, max_int_len))
      {
         break;
      }
   }
   return max_int_len;
}

bool
number::getCharFromString (const char* nb, char& c_out)
{
   int char_max_len = number::getIntStringLength(CHAR_MAX);
   int nb_len = strlen(nb);
   c_out = 0;

   // FIXME Only works when the nb lenght is < to INT_MAX length
   if (nb_len < char_max_len)
   {
      c_out = static_cast<char>(atoi(nb));
      return true;
   }

   return false;
}

bool
number::getIntFromString (const char* nb, int& i_out)
{
   int int_max_len = number::getIntStringLength(INT_MAX);
   int nb_len = strlen(nb);
   i_out = 0;

   // FIXME Only works when the nb lenght is < to INT_MAX length
   if (nb_len < int_max_len)
   {
      i_out = atoi(nb);
      return true;
   }

   return false;
}

bool
number::getShortFromString (const char* nb, short& s_out)
{
   int short_max_len = number::getIntStringLength(SHRT_MAX);
   int nb_len = strlen(nb);
   s_out = 0;

   // FIXME Only works when the nb lenght is < to SHRT_MAX length
   if (nb_len < short_max_len)
   {
      s_out = atoi(nb);
      return true;
   }

   return false;
}



}
