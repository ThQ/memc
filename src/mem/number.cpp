#include "mem/number.hpp"


namespace mem { namespace number {

char
parseIntNumber (std::string str, int& nb)
{
   nb = 0;
   // FIXME This is so ugly it hurts...
   if (getCharFromString(str.c_str(), nb))
   {
      return 'c';
   }
   else if (getShortFromString(str.c_str(), nb))
   {
      return 's';
   }
   else if (getIntFromString(str.c_str(), nb))
   {
      return 'i';
   }
   return '\0';
}

int
getIntStringLength (double nb)
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
getCharFromString (const char* nb, int& c_out)
{
   int char_max_len = number::getIntStringLength(CHAR_MAX);
   int nb_len = strlen(nb);
   c_out = 0;
   if (nb_len <= char_max_len)
   {
      int i = atoi(nb);
      if (i <= CHAR_MAX)
      {
         c_out = atoi(nb);
         return true;
      }
   }

   return false;
}

bool
getIntFromString (const char* nb, int& i_out)
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
getShortFromString (const char* nb, int& s_out)
{
   int short_max_len = number::getIntStringLength(SHRT_MAX);
   int nb_len = strlen(nb);
   s_out = 0;

   // FIXME Only works when the nb lenght is < to SHRT_MAX length
   if (nb_len <= short_max_len)
   {
      int i = atoi(nb);
      if (i <= SHRT_MAX)
      {
         s_out = i;
         return true;
      }
   }

   return false;
}



} }
