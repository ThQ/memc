/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* "%code requires" blocks.  */

/* Line 2068 of yacc.c  */
#line 7 "src/mem/lang/Bison.ypp"

#define PASS (0);
#include <stdio.h>
#include <string.h>
#include "mem/ast/node/BinaryExpression.hpp"
#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Call.hpp"
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Field.hpp"
#include "mem/ast/node/LeftUnary.hpp"
#include "mem/ast/node/New.hpp"
#include "mem/ast/node/Primitive.hpp"
#include "mem/ast/node/Root.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Use.hpp"
#include "mem/ast/node/VarDecl.hpp"
#include "mem/ast/node/While.hpp"
#include "mem/fs/File.hpp"
#include "mem/fs/FileManager.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/log/Logger.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/Compiler.hpp"
#include "mem/number.hpp"

using namespace mem;

#ifndef YYERROR_VERBOSE
#define YYERROR_VERBOSE 1
#endif

#define YYLTYPE fs::position::Range
#define YYLTYPE_IS_DECLARED 1

#define YYLLOC_DEFAULT(Current, Rhs, N) \
   do \
   { \
      if (YYID (N)) \
      { \
         (Current).sLine(YYRHSLOC (Rhs, 1)._line); \
         (Current).sLineEnd(YYRHSLOC (Rhs, 1)._line_end); \
         (Current).sColStart(YYRHSLOC (Rhs, 1)._column_start); \
         (Current).sColEnd(YYRHSLOC (Rhs, N)._column_end); \
         (Current).sFile(YYRHSLOC(Rhs, 1)._file); \
      } \
      else \
      { \
         (Current).sLine(YYRHSLOC (Rhs, 0)._line); \
         (Current).sLineEnd(YYRHSLOC (Rhs, 0)._line_end); \
         (Current).sColStart(YYRHSLOC (Rhs, 0)._column_end); \
         (Current).sColEnd(YYRHSLOC (Rhs, 0)._column_end); \
         (Current).sFile(NULL); \
      } \
   } \
   while (YYID (0))


/* Line 2068 of yacc.c  */
#line 81 "src/mem/lang/Bison.ypp"




/* Line 2068 of yacc.c  */
#line 102 "src/mem/lang/Bison.hpp"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_AROBASE = 258,
     T_AND = 259,
     T_CLASS = 260,
     T_COMMA = 261,
     T_CP = 262,
     T_DEDENT = 263,
     T_DOT = 264,
     T_ELSE = 265,
     T_EQ = 266,
     T_IF = 267,
     T_ID = 268,
     T_INDENT = 269,
     T_INTERFACE = 270,
     T_LBRACKET = 271,
     T_LITERAL_FLOAT = 272,
     T_LITERAL_HEX = 273,
     T_LITERAL_INT = 274,
     T_LITERAL_NUMBER = 275,
     T_NEW = 276,
     T_NEWLINE = 277,
     T_OP = 278,
     T_OR = 279,
     T_PASS = 280,
     T_PATCH = 281,
     T_PRIMITIVE = 282,
     T_OBJECT = 283,
     T_RBRACKET = 284,
     T_RARR = 285,
     T_STRING = 286,
     T_USE = 287,
     T_WHITESPACE = 288,
     T_LEFT_BINARY_OP = 289,
     T_RETURN = 290,
     T_SEMICOLON = 291,
     T_WHILE = 292,
     T_SELF = 293,
     T_BANG = 294,
     T_LARR_EQ = 295,
     T_LT = 296,
     T_RARR_EQ = 297,
     T_GT = 298,
     T_EQ_EQ = 299,
     T_PLUS = 300,
     T_MINUS = 301,
     T_DIV = 302,
     T_MUL = 303,
     T_MODULO = 304,
     T_MUL_MUL = 305,
     T_PLUS_PLUS = 306,
     T_MINUS_MINUS = 307
   };
#endif
/* Tokens.  */
#define T_AROBASE 258
#define T_AND 259
#define T_CLASS 260
#define T_COMMA 261
#define T_CP 262
#define T_DEDENT 263
#define T_DOT 264
#define T_ELSE 265
#define T_EQ 266
#define T_IF 267
#define T_ID 268
#define T_INDENT 269
#define T_INTERFACE 270
#define T_LBRACKET 271
#define T_LITERAL_FLOAT 272
#define T_LITERAL_HEX 273
#define T_LITERAL_INT 274
#define T_LITERAL_NUMBER 275
#define T_NEW 276
#define T_NEWLINE 277
#define T_OP 278
#define T_OR 279
#define T_PASS 280
#define T_PATCH 281
#define T_PRIMITIVE 282
#define T_OBJECT 283
#define T_RBRACKET 284
#define T_RARR 285
#define T_STRING 286
#define T_USE 287
#define T_WHITESPACE 288
#define T_LEFT_BINARY_OP 289
#define T_RETURN 290
#define T_SEMICOLON 291
#define T_WHILE 292
#define T_SELF 293
#define T_BANG 294
#define T_LARR_EQ 295
#define T_LT 296
#define T_RARR_EQ 297
#define T_GT 298
#define T_EQ_EQ 299
#define T_PLUS 300
#define T_MINUS 301
#define T_DIV 302
#define T_MUL 303
#define T_MODULO 304
#define T_MUL_MUL 305
#define T_PLUS_PLUS 306
#define T_MINUS_MINUS 307




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 84 "src/mem/lang/Bison.ypp"

   int integer;
   char* text;
   ast::node::Node* binary_node;
   ast::node::Node* node;
   ast::node::Text* text_node;



/* Line 2068 of yacc.c  */
#line 233 "src/mem/lang/Bison.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;

