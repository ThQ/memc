%{
#include <string.h>
#include <stdio.h>
#include <ios>
#include "mem/parser/Bison.hpp"

int yycolumn = 0;

mem::fs::File* yyfile = NULL;
#define YY_USER_ACTION yylloc._line = yylineno; \
    yylloc._column_start = yycolumn; \
    yylloc._column_end = yycolumn + yyleng - 1; \
    yylloc._file = yyfile; \
    yycolumn += yyleng;

#define NEW_LINE ((0));


int i = T_ID;

char* INDENT_UNIT = NULL;
unsigned int INDENT_UNIT_LEN = 0;
unsigned int INDENT_LEVEL = 0;
unsigned int ML_COMMENT_DEPTH = 0;
//define lexical_error(line, msg, args...) printf("[??:%d] TokenizerError: ", line); printf(msg, args)

char* str_sub(const char* source, size_t start, size_t end)
{
   char* sub = new char[end - start + 2];
   sub[end - start ] = '\n';
   for (size_t i = start, j = 0 ; i <= end ; ++i, ++j)
   {
      sub[j] = source[i];
   }
   return sub;
}

void reset_lexer ()
{
   if (INDENT_UNIT != NULL)
   {
      delete[] INDENT_UNIT;
   }
   yycolumn = 0;
   yylloc._column_start = yylloc._column_end = 0;
   INDENT_UNIT = NULL;
   INDENT_UNIT_LEN = 0;
   INDENT_LEVEL = 0;
   ML_COMMENT_DEPTH = 0;
}
%}


KW_DEF def
KW_USE use
KW_IF if
KW_ELSE else

ID                   [a-zA-Z_][a-zA-Z_0-9]*
ID_SEP               ::
ID_FULL              {ID}(\.{ID})*
WHITE_SPACES         [ \t]+
OPT_WHITE_SPACES     [ \t]*
EOL                  [\r\n]|"\r\n"

VAL_INT              [0-9]+
VAL_FLOAT            [0-9]*\.[0-9]+
VAL_HEX              \\x[0-9]+

BINARY_OPERATOR           [+/*^-]|"&&"|"||"
UNARY_OPERATOR             "++"|"--"|[:]
ASSIGNMENT_OPERATOR        "+="|"-="|"*="|"^="|"/="
OPERATOR                 {BINARY_OPERATOR}|{UNARY_OPERATOR}|{ASSIGNMENT_OPERATOR}

PONCTUATION          [,;]

NS_SEP ::
NS_PART_NAME [a-zA-Z_][a-zA-Z_0-9]*

NS_FULL_NAME {NS_PART_NAME}({NS_SEP}{NS_PART_NAME})*

CLASS_BASE_NAME [a-zA-Z_][a-zA-Z_0-9]*
CLASS_FULL_NAME ({NS_FULL_NAME}::)?{CLASS_BASE_NAME}

VAR_BASE_NAME [a-zA-Z_][a-zA-Z_0-9]*

FUNC_BASE_NAME [a-zA-Z_][a-zA-Z_0-9]*

ST_END      (\n|\r|"\n\r"|;|$)
ST_USE      {KW_USE}[ ]+{NS_PART_NAME}
%option yylineno

%x FUNC_CLOSE_PARAMS
%x FUNC_NAME
%x FUNC_OPEN_PARENTHESIS
%x FUNC_PARAM_NAME
%x FUNC_PARAM_TYPE
%x FUNC_PARAM_TYPE_NAME
%x FUNC_PARAM_TYPE_OP
%x FUNC_PARAM_COMA
%x FUNC_RETURN_TYPE_OP
%x FUNC_RETURN_TYPE_NAME

%x FUNC_CALL_PARAM
%x FUNC_CALL_PARAM_COMA

%x DQ_STRING
%x USE_END
%x USE_NAME
%x ID_ACTION
%x INDENT_OR_DEDENT
%x INDENT
%x DEDENT
%x ML_COMMENT
%x EOF_DEDENT

%%
"@" {
   return T_AROBASE;
}
"use" {
   return T_USE;
}

"class" {
   return T_CLASS;
}

"object" {
   return T_OBJECT;
}

"primitive" {
   return T_PRIMITIVE;
}

"interface" {
   return T_INTERFACE;
}

"patch" {
   return T_PATCH;
}

"pass" {
   return T_PASS;
}

"new" {
   return T_NEW;
}

"if" {
   return T_IF;
}

"else" {
   return T_ELSE;
}

"while" {
   return T_WHILE;
}

":" {
   return T_SEMICOLON;
}
"," {
   return T_COMMA;
}

"+" {
   return T_PLUS;
}

"." {
   return T_DOT;
}

"++" {
   return T_PLUS_PLUS;
}

"-" {
   return T_MINUS;
}

"--" {
   return T_MINUS_MINUS;
}

"!" {
   return T_BANG;
}

"*" {
   return T_MUL;
}

"/" {
   return T_DIV;
}

"**" {
   return T_MUL_MUL;
}


"%" {
   return T_MODULO;
}

"=" {
   return T_EQ;
}

"==" {
   return T_EQ_EQ;
}

">=" {
   return T_RARR_EQ;
}

">" {
   return T_RARR;
}

"<" {
   return T_LARR;
}

"<=" {
   return T_LARR_EQ;
}


{ID} {
   yylval.text = strdup(yytext);
   return T_ID;
}

"(" {
   return T_OP;
}

")" {
   return T_CP;
}

"[" {
   return T_LBRACKET;
}

"]" {
   return T_RBRACKET;
}
"/*" {
   BEGIN(ML_COMMENT);
   ML_COMMENT_DEPTH ++;
}

<<EOF>> {
   //printf("At EOF indent = %d\n", INDENT_LEVEL);
   if (INDENT_LEVEL != 0)
   {
      for (unsigned int i = 0 ; i < INDENT_LEVEL ; ++i)
      {
         unput('<');
      }
      BEGIN(EOF_DEDENT);
   }
   else
   {
      yyterminate();
   }
}

<EOF_DEDENT>"<" {
   INDENT_LEVEL --;
   return T_DEDENT;
}

<ML_COMMENT>"/*" {
   ML_COMMENT_DEPTH ++;
}

<ML_COMMENT>"*/" {
   ML_COMMENT_DEPTH --;
   if (ML_COMMENT_DEPTH == 0)
   {
      BEGIN(0);
   }
}

<ML_COMMENT>. {}

\n[ \t]*\n {
   unput('\n');
}

\n[ ]* {
   //printf("FIRST LEVEL INDENT\n");
   yylloc._column_start = 0;
   yylloc._column_end = yycolumn = yyleng;

   if (INDENT_UNIT == NULL)
   {
      if (yyleng > 1)
      {
         INDENT_UNIT_LEN = yyleng - 1; //strlen(yytext - 1);
         INDENT_UNIT = str_sub(yytext, 1, INDENT_UNIT_LEN);
         //printf("INIT_INDENT=[%s](%d)\n", INDENT_UNIT, INDENT_UNIT_LEN);
         //printf(">>`%s`(%d)\n", yytext, strlen(yytext));
         unput('>');
         BEGIN(INDENT);
      }
   }
   else
   {
      unsigned int indent_len = yyleng - 1;
      unsigned int indent_level = 0;

      if (indent_len % INDENT_UNIT_LEN == 0)
      {
         indent_level = indent_len / INDENT_UNIT_LEN;
         //printf("INDENTATION|LEN=%d|UNIT_LEN=%d|LEVEL_FOUND=%d|CUR_LEVEL=%d\n", indent_len, INDENT_UNIT_LEN, indent_level, INDENT_LEVEL);
      }
      else
      {
         printf("Indentation unit is %d spaces long, but got %d spaces.\n>>`", INDENT_UNIT_LEN, indent_len);
         for (size_t i = 0 ; i < INDENT_UNIT_LEN ; ++ i)
         {
            printf("%c", INDENT_UNIT[i]);
         }
         printf("`\n");
      }

      if (indent_level != INDENT_LEVEL)
      {
         //printf("THERE IN/DE.DENTATION\n");
         if (indent_level < INDENT_LEVEL)
         {
            unput('\n');
            //INDENT_LEVEL = indent_level;
            for (int i = INDENT_LEVEL - indent_level ; i > 0; --i)
            {
               //printf("unput %d\n", i);
               unput('<');
            }
            //printf("STARTING DEDENT=(%d)\n", yyleng);
            BEGIN(DEDENT);
         }
         else
         {
            unput('>');
            //printf("STARTING INDENT\n");
            BEGIN(INDENT);
         }
         //INDENT_LEVEL = indent_level;
      }
   }
   return T_NEWLINE;
}

<INDENT>">" {
   yycolumn --;
   BEGIN(0);
   INDENT_LEVEL ++;
   return T_INDENT;
}


<DEDENT>"<" {
   yycolumn --;
   if (INDENT_LEVEL > 0)
   {
      INDENT_LEVEL --;
      //printf("DEDENT=[%s]%d\n", yytext, yyleng);
      return T_DEDENT;
   }
   else
   {
      printf("ERROR HERE\n");
   }
}
<DEDENT>"\n" {
   yycolumn --;
   NEW_LINE;
   BEGIN(0);
}

"\"".*"\"" {
   yylval.text = strdup(yytext);
   return T_STRING;
}

{WHITE_SPACES} {
}

{VAL_INT} {
   yylval.text = strdup(yytext);
   return T_LITERAL_INT;
}

{VAL_FLOAT} {
   return T_LITERAL_FLOAT;
}

{VAL_HEX} {
   return T_LITERAL_HEX;
}

. {
   printf("Bad input character '%s'\n", yytext);
}

%%

int yywrap() { return 1; }
