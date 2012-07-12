#ifndef _MEM__NUMBER__HPP_
#define _MEM__NUMBER__HPP_


#include <limits.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


namespace mem {


class number
{
   public: static int getIntStringLength (double nb);
   public: static bool getCharFromString (const char* nb, char& c_out);
   public: static bool getIntFromString (const char* nb, int& i_out);
   public: static bool getShortFromString (const char* nb, short& s_out);
};


}

#endif
