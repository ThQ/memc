#define YYDEBUG 1
#define YYPRINT 1

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#include <stdio.h>
#include "mem/tokenizer/Flex.hpp"
#include "mem/parser/Bison.hpp"


int main (int argc, char** argv )
{
   int token;
   while ((token = yylex()))
   {
      printf("TOKEN[%d]\n", (unsigned int)token);
   }
   return 0;
}
