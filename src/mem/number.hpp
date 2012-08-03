#ifndef _MEM__NUMBER__HPP_
#define _MEM__NUMBER__HPP_


#include <limits.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


namespace mem { namespace number {


char parseIntNumber (std::string str, int& nb);
int getIntStringLength (double nb);
bool getCharFromString (const char* nb, int& c_out);
bool getIntFromString (const char* nb, int& i_out);
bool getShortFromString (const char* nb, int& s_out);


} }

#endif
