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
#line 7 "src/mem/grammar/mem.y"

#define PASS (0);
#include <stdio.h>
#include <string.h>
#include "mem/ast/node/BinaryExpression.hpp"
#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Field.hpp"
#include "mem/ast/node/LeftUnary.hpp"
#include "mem/ast/node/Primitive.hpp"
#include "mem/ast/node/Root.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Use.hpp"
#include "mem/ast/node/VarDecl.hpp"
#include "mem/fs/File.hpp"
#include "mem/fs/FileManager.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/log/Logger.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/Compiler.hpp"
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
         (Current).s_line(YYRHSLOC (Rhs, 1)._line); \
         (Current).s_line_end(YYRHSLOC (Rhs, 1)._line_end); \
         (Current).s_col_start(YYRHSLOC (Rhs, 1)._column_start); \
         (Current).s_col_end(YYRHSLOC (Rhs, N)._column_end); \
         (Current)._file = YYRHSLOC(Rhs, 1)._file; \
      } \
      else \
      { \
         (Current).s_line(YYRHSLOC (Rhs, 0)._line); \
         (Current).s_line_end(YYRHSLOC (Rhs, 0)._line_end); \
         (Current).s_col_start(YYRHSLOC (Rhs, 0)._column_end); \
         (Current).s_col_end(YYRHSLOC (Rhs, 0)._column_end); \
         (Current)._file = NULL; \
      } \
   } \
   while (YYID (0))


/* Line 2068 of yacc.c  */
#line 76 "src/mem/grammar/mem.y"




/* Line 2068 of yacc.c  */
#line 97 "src/mem/parser/Bison.hpp"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_AROBASE = 258,
     T_CLASS = 259,
     T_COMMA = 260,
     T_CP = 261,
     T_DEDENT = 262,
     T_DOT = 263,
     T_ELSE = 264,
     T_EQ = 265,
     T_IF = 266,
     T_ID = 267,
     T_INDENT = 268,
     T_INTERFACE = 269,
     T_LBRACKET = 270,
     T_LITERAL_FLOAT = 271,
     T_LITERAL_HEX = 272,
     T_LITERAL_INT = 273,
     T_NEW = 274,
     T_NEWLINE = 275,
     T_OP = 276,
     T_PASS = 277,
     T_PATCH = 278,
     T_PRIMITIVE = 279,
     T_OBJECT = 280,
     T_RBRACKET = 281,
     T_RARR = 282,
     T_STRING = 283,
     T_USE = 284,
     T_WHITESPACE = 285,
     T_LEFT_BINARY_OP = 286,
     T_RETURN = 287,
     T_SEMICOLON = 288,
     T_WHILE = 289,
     T_SELF = 290,
     T_BANG = 291,
     T_LARR_EQ = 292,
     T_LT = 293,
     T_RARR_EQ = 294,
     T_GT = 295,
     T_EQ_EQ = 296,
     T_PLUS = 297,
     T_MINUS = 298,
     T_DIV = 299,
     T_MUL = 300,
     T_MODULO = 301,
     T_MUL_MUL = 302,
     T_PLUS_PLUS = 303,
     T_MINUS_MINUS = 304
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 79 "src/mem/grammar/mem.y"

   int integer;
   char* text;
   ast::node::Node* binary_node;
   ast::node::Node* node;
   ast::node::Text* text_node;



/* Line 2068 of yacc.c  */
#line 173 "src/mem/parser/Bison.hpp"
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

