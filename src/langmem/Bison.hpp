/* A Bison parser, made by GNU Bison 2.6.4.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_HOME_THOMAS_CODE_MEMC_SRC_LANGMEM_BISON_HPP_INCLUDED
# define YY_YY_HOME_THOMAS_CODE_MEMC_SRC_LANGMEM_BISON_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
/* Line 2077 of yacc.c  */
#line 10 "/home/thomas/code/memc/src/langmem/Bison.ypp"


#define PASS (0);
#include <stdio.h>
#include <string.h>
#ifndef INCLUDED_BISON_HPP
#define INCLUDED_BISON_HPP
#include "langmem/Bison.hpp"
#endif
#include "langmem/Tokenizer.hpp"
#include "mem/ast/node/ArrayType.hpp"
#include "mem/ast/node/BinaryOp.hpp"
#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/BracketOp.hpp"
#include "mem/ast/node/Call.hpp"
#include "mem/ast/node/CastOp.hpp"
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Decorator.hpp"
#include "mem/ast/node/Dot.hpp"
#include "mem/ast/node/EnumType.hpp"
#include "mem/ast/node/Field.hpp"
#include "mem/ast/node/File.hpp"
#include "mem/ast/node/FinalId.hpp"
#include "mem/ast/node/For.hpp"
#include "mem/ast/node/Func.hpp"
#include "mem/ast/node/FuncType.hpp"
#include "mem/ast/node/If.hpp"
#include "mem/ast/node/New.hpp"
#include "mem/ast/node/Number.hpp"
#include "mem/ast/node/PointerType.hpp"
#include "mem/ast/node/Return.hpp"
#include "mem/ast/node/Root.hpp"
#include "mem/ast/node/String.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Tuple.hpp"
#include "mem/ast/node/TupleType.hpp"
#include "mem/ast/node/UnaryOp.hpp"
#include "mem/ast/node/Use.hpp"
#include "mem/ast/node/VarAssign.hpp"
#include "mem/ast/node/VarDecl.hpp"
#include "mem/ast/node/While.hpp"
#include "mem/fs/File.hpp"
#include "mem/fs/FileManager.hpp"
#include "mem/fs/position/Range.hpp"
#include "mem/log/Logger.hpp"
#include "mem/st/SymbolTable.hpp"
#include "mem/st/util.hpp"
#include "mem/number.hpp"

using namespace mem;


#define YYLTYPE fs::position::Range
#define YYLTYPE_IS_DECLARED 1

#define YYLLOC_DEFAULT(Current, Rhs, N) \
   do \
   { \
      if (YYID (N)) \
      { \
         (Current).setLineStart(YYRHSLOC (Rhs, 1).LineStart()); \
         (Current).setLineEnd(YYRHSLOC (Rhs, 1).LineEnd()); \
         (Current).setColumnStart(YYRHSLOC (Rhs, 1).ColumnStart()); \
         (Current).setColumnEnd(YYRHSLOC (Rhs, N).ColumnEnd()); \
         (Current).setFile(YYRHSLOC(Rhs, 1).File()); \
      } \
      else \
      { \
         (Current).setLineStart(YYRHSLOC (Rhs, 0).LineStart()); \
         (Current).setLineEnd(YYRHSLOC (Rhs, 0).LineEnd()); \
         (Current).setColumnStart(YYRHSLOC (Rhs, 0).ColumnEnd()); \
         (Current).setColumnEnd(YYRHSLOC (Rhs, 0).ColumnEnd()); \
         (Current).setFile(NULL); \
      } \
   } \
   while (YYID (0))

extern langmem::Tokenizer gTOKENIZER;


/* Line 2077 of yacc.c  */
#line 127 "/home/thomas/code/memc/src/langmem/Bison.hpp"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_AMPERSAND = 258,
     T_AROBASE = 259,
     T_AND = 260,
     T_BANG = 261,
     T_BANG_EQ = 262,
     T_CLASS = 263,
     T_CLOSE_BRACE = 264,
     T_COLON = 265,
     T_COMMA = 266,
     T_CP = 267,
     T_DEDENT = 268,
     T_DOT = 269,
     T_DOTDOTDOT = 270,
     T_ELSE = 271,
     T_ENUM = 272,
     T_EQ = 273,
     T_FOR = 274,
     T_HASH = 275,
     T_IF = 276,
     T_ID = 277,
     T_INDENT = 278,
     T_INTERFACE = 279,
     T_LBRACKET = 280,
     T_LEFT_BINARY_OP = 281,
     T_LITERAL_FLOAT = 282,
     T_LITERAL_HEX = 283,
     T_LITERAL_INT = 284,
     T_LITERAL_NUMBER = 285,
     T_MINUS_EQ = 286,
     T_NEW = 287,
     T_NEWLINE = 288,
     T_OP = 289,
     T_OPEN_BRACE = 290,
     T_OR = 291,
     T_PASS = 292,
     T_OBJECT = 293,
     T_QUOTE = 294,
     T_PLUS_EQ = 295,
     T_RBRACKET = 296,
     T_RARR = 297,
     T_RETURN = 298,
     T_SEMICOLON = 299,
     T_SINGLE_LINE_COMMENT = 300,
     T_SLASH_EQ = 301,
     T_SPACE = 302,
     T_STAR = 303,
     T_STAR_EQ = 304,
     T_STRING = 305,
     T_USE = 306,
     T_VAR = 307,
     T_WHILE = 308,
     T_WHITESPACE = 309,
     T_BANQ_EQ = 310,
     T_LT_EQ = 311,
     T_LT = 312,
     T_GT_EQ = 313,
     T_GT = 314,
     T_EQ_EQ = 315,
     T_PLUS = 316,
     T_MINUS = 317,
     T_DIV = 318,
     T_XOR = 319,
     T_BIT_AND = 320,
     T_BIT_OR = 321,
     T_GT_GT = 322,
     T_LT_LT = 323,
     T_MODULO = 324,
     T_MUL_MUL = 325,
     T_PLUS_PLUS = 326,
     T_MINUS_MINUS = 327
   };
#endif
/* Tokens.  */
#define T_AMPERSAND 258
#define T_AROBASE 259
#define T_AND 260
#define T_BANG 261
#define T_BANG_EQ 262
#define T_CLASS 263
#define T_CLOSE_BRACE 264
#define T_COLON 265
#define T_COMMA 266
#define T_CP 267
#define T_DEDENT 268
#define T_DOT 269
#define T_DOTDOTDOT 270
#define T_ELSE 271
#define T_ENUM 272
#define T_EQ 273
#define T_FOR 274
#define T_HASH 275
#define T_IF 276
#define T_ID 277
#define T_INDENT 278
#define T_INTERFACE 279
#define T_LBRACKET 280
#define T_LEFT_BINARY_OP 281
#define T_LITERAL_FLOAT 282
#define T_LITERAL_HEX 283
#define T_LITERAL_INT 284
#define T_LITERAL_NUMBER 285
#define T_MINUS_EQ 286
#define T_NEW 287
#define T_NEWLINE 288
#define T_OP 289
#define T_OPEN_BRACE 290
#define T_OR 291
#define T_PASS 292
#define T_OBJECT 293
#define T_QUOTE 294
#define T_PLUS_EQ 295
#define T_RBRACKET 296
#define T_RARR 297
#define T_RETURN 298
#define T_SEMICOLON 299
#define T_SINGLE_LINE_COMMENT 300
#define T_SLASH_EQ 301
#define T_SPACE 302
#define T_STAR 303
#define T_STAR_EQ 304
#define T_STRING 305
#define T_USE 306
#define T_VAR 307
#define T_WHILE 308
#define T_WHITESPACE 309
#define T_BANQ_EQ 310
#define T_LT_EQ 311
#define T_LT 312
#define T_GT_EQ 313
#define T_GT 314
#define T_EQ_EQ 315
#define T_PLUS 316
#define T_MINUS 317
#define T_DIV 318
#define T_XOR 319
#define T_BIT_AND 320
#define T_BIT_OR 321
#define T_GT_GT 322
#define T_LT_LT 323
#define T_MODULO 324
#define T_MUL_MUL 325
#define T_PLUS_PLUS 326
#define T_MINUS_MINUS 327



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2077 of yacc.c  */
#line 131 "/home/thomas/code/memc/src/langmem/Bison.ypp"

   std::string* text;
   mem::ast::node::Node* node;
   mem::ast::node::Text* nodeText;
   mem::ast::node::Id* nodeId;
   mem::ast::node::BinaryOp* nodeBinaryOp;
   mem::ast::node::Block* nodeBlock;
   mem::ast::node::Decorator* nodeDecorator;
   mem::ast::node::FinalId* nodeFinalId;
   mem::ast::node::Func* nodeFunc;
   mem::ast::node::NodeList* nodeList;
   mem::ast::node::Type* nodeType;
   mem::ast::node::VarDecl* nodeVarDecl;
   mem::ast::node::While* nodeWhile;


/* Line 2077 of yacc.c  */
#line 303 "/home/thomas/code/memc/src/langmem/Bison.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

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

extern YYSTYPE yylval;
extern YYLTYPE yylloc;
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (mem::ast::node::File* ast, mem::st::SymbolTable* symbols, mem::log::Logger* logger, mem::fs::File* file);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_HOME_THOMAS_CODE_MEMC_SRC_LANGMEM_BISON_HPP_INCLUDED  */
