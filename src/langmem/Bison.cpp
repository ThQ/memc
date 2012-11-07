/* A Bison parser, made by GNU Bison 2.6.4.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.6.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */

/* Line 358 of yacc.c  */
#line 68 "/home/thomas/code/memc/src/langmem/Bison.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "Bison.hpp".  */
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
/* Line 374 of yacc.c  */
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


/* Line 374 of yacc.c  */
#line 181 "/home/thomas/code/memc/src/langmem/Bison.cpp"

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
/* Line 374 of yacc.c  */
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


/* Line 374 of yacc.c  */
#line 357 "/home/thomas/code/memc/src/langmem/Bison.cpp"
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

/* Copy the second part of user declarations.  */

/* Line 377 of yacc.c  */
#line 398 "/home/thomas/code/memc/src/langmem/Bison.cpp"
/* Unqualified %code blocks.  */
/* Line 378 of yacc.c  */
#line 90 "/home/thomas/code/memc/src/langmem/Bison.ypp"

   langmem::Tokenizer gTOKENIZER;

   int yylex()
   {
      langmem::Token t = gTOKENIZER.getNextToken();

      switch (t.Kind())
      {
         case T_ID:
         case T_OP:
         case T_STRING:
         case T_LITERAL_NUMBER:
            std::string* str = new std::string();
            str->assign(t.Value());
            yylval.text = str;
            break;
      }
      yylloc = t.Location();
      return t.Kind();
   }

   void yyerror(ast::node::Node* ast,
      mem::st::SymbolTable* symbols,
      ::mem::log::Logger* logger, // Type ambiguity for gcc-c++ 4.2.1 on FreeBSD
      fs::File* file,
      const char *s)
   {
      fs::position::Position* pos = new fs::position::Position();
      pos->setFile(file);

      log::Message* msg = new log::Error();
      msg->setId("syntax-error");
      msg->setPrimaryText("Syntax error");
      msg->setSecondaryText(s);
      msg->setPosition(pos);
      logger->log(msg);
   }


/* Line 378 of yacc.c  */
#line 443 "/home/thomas/code/memc/src/langmem/Bison.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   669

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNRULES -- Number of states.  */
#define YYNSTATES  190

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   327

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    23,    24,
      27,    28,    30,    32,    35,    40,    42,    49,    51,    54,
      57,    65,    67,    71,    72,    74,    78,    79,    82,    83,
      87,    89,    93,    97,   103,   107,   113,   117,   119,   121,
     123,   125,   127,   135,   138,   141,   143,   144,   146,   149,
     151,   153,   155,   157,   159,   161,   164,   168,   172,   177,
     182,   189,   193,   195,   197,   199,   202,   206,   212,   214,
     216,   218,   222,   223,   225,   227,   229,   231,   233,   235,
     237,   241,   245,   247,   249,   251,   253,   255,   258,   261,
     264,   268,   273,   275,   279,   281,   283,   285,   287,   289,
     291,   293,   295,   297,   299,   301,   303,   305,   307,   309,
     311,   313,   315,   317,   319,   321,   325,   327,   331,   335,
     340,   342
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      74,     0,    -1,    -1,    74,   102,    -1,    74,    75,    -1,
      74,    80,    -1,    74,    83,    -1,     8,   106,    76,    35,
      77,     9,    -1,    -1,    57,   106,    -1,    -1,    78,    -1,
      79,    -1,    78,    79,    -1,   106,    10,   107,    44,    -1,
      83,    -1,    17,   106,    76,    35,    81,     9,    -1,    82,
      -1,    81,    82,    -1,   106,    44,    -1,   106,    88,    34,
      85,    12,    87,   105,    -1,    86,    -1,    84,    11,    86,
      -1,    -1,    84,    -1,   106,    10,   107,    -1,    -1,    42,
     107,    -1,    -1,    25,    89,    41,    -1,   106,    -1,    89,
      11,   106,    -1,    34,   108,    12,    -1,    34,   109,    12,
      42,   107,    -1,    21,   113,   105,    -1,    21,   113,   105,
      16,   105,    -1,    53,   113,   105,    -1,   104,    -1,   103,
      -1,   113,    -1,   103,    -1,   113,    -1,    19,    94,    44,
     113,    44,    95,   105,    -1,   113,    44,    -1,   100,    44,
      -1,    99,    -1,    -1,    97,    -1,    98,    97,    -1,    92,
      -1,    93,    -1,    96,    -1,   104,    -1,   103,    -1,   101,
      -1,    43,   113,    -1,    51,   111,    44,    -1,   113,   110,
     113,    -1,    52,   106,    10,   107,    -1,    52,   106,    18,
     113,    -1,    52,   106,    10,   107,    18,   113,    -1,    35,
      98,     9,    -1,    22,    -1,   106,    -1,   111,    -1,   107,
      48,    -1,    25,   107,    41,    -1,    25,   107,    11,   113,
      41,    -1,    90,    -1,    91,    -1,   107,    -1,   108,    11,
     107,    -1,    -1,   108,    -1,    18,    -1,    40,    -1,    31,
      -1,    46,    -1,    49,    -1,   106,    -1,   111,    14,   106,
      -1,   113,    14,   106,    -1,   122,    -1,   112,    -1,   119,
      -1,   111,    -1,   121,    -1,     3,   113,    -1,     4,   113,
      -1,    32,   107,    -1,   113,    10,   107,    -1,   113,    25,
     113,    41,    -1,   114,    -1,    34,   120,    12,    -1,     5,
      -1,    36,    -1,    60,    -1,    57,    -1,    56,    -1,    59,
      -1,    58,    -1,     7,    -1,    61,    -1,    62,    -1,    48,
      -1,    63,    -1,    67,    -1,    68,    -1,    66,    -1,    65,
      -1,    64,    -1,    69,    -1,   115,    -1,   116,    -1,   117,
      -1,   113,   118,   113,    -1,   113,    -1,   120,    11,   113,
      -1,   113,    34,    12,    -1,   113,    34,   120,    12,    -1,
      30,    -1,    50,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   262,   262,   264,   268,   272,   276,   287,   301,   304,
     311,   314,   320,   325,   333,   342,   353,   376,   381,   389,
     402,   437,   443,   451,   454,   460,   470,   473,   480,   483,
     489,   494,   505,   511,   530,   539,   555,   569,   570,   571,
     574,   575,   578,   596,   600,   604,   611,   614,   620,   627,
     628,   632,   635,   636,   637,   640,   648,   659,   670,   679,
     694,   710,   717,   727,   731,   739,   747,   756,   765,   769,
     775,   781,   789,   792,   795,   795,   795,   795,   795,   799,
     808,   825,   835,   839,   843,   848,   852,   858,   867,   876,
     885,   895,   902,   905,   928,   933,   941,   947,   953,   959,
     965,   971,   979,   984,   989,   994,   999,  1004,  1009,  1014,
    1019,  1024,  1031,  1031,  1031,  1034,  1044,  1050,  1058,  1068,
    1079,  1139
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_AMPERSAND", "T_AROBASE", "T_AND",
  "T_BANG", "T_BANG_EQ", "T_CLASS", "T_CLOSE_BRACE", "T_COLON", "T_COMMA",
  "T_CP", "T_DEDENT", "T_DOT", "T_DOTDOTDOT", "T_ELSE", "T_ENUM", "T_EQ",
  "T_FOR", "T_HASH", "T_IF", "T_ID", "T_INDENT", "T_INTERFACE",
  "T_LBRACKET", "T_LEFT_BINARY_OP", "T_LITERAL_FLOAT", "T_LITERAL_HEX",
  "T_LITERAL_INT", "T_LITERAL_NUMBER", "T_MINUS_EQ", "T_NEW", "T_NEWLINE",
  "T_OP", "T_OPEN_BRACE", "T_OR", "T_PASS", "T_OBJECT", "T_QUOTE",
  "T_PLUS_EQ", "T_RBRACKET", "T_RARR", "T_RETURN", "T_SEMICOLON",
  "T_SINGLE_LINE_COMMENT", "T_SLASH_EQ", "T_SPACE", "T_STAR", "T_STAR_EQ",
  "T_STRING", "T_USE", "T_VAR", "T_WHILE", "T_WHITESPACE", "T_BANQ_EQ",
  "T_LT_EQ", "T_LT", "T_GT_EQ", "T_GT", "T_EQ_EQ", "T_PLUS", "T_MINUS",
  "T_DIV", "T_XOR", "T_BIT_AND", "T_BIT_OR", "T_GT_GT", "T_LT_LT",
  "T_MODULO", "T_MUL_MUL", "T_PLUS_PLUS", "T_MINUS_MINUS", "$accept",
  "File", "Class", "ClassParent_", "ClassMembers_", "ClassMembers",
  "ClassMember", "Enum", "EnumFields", "EnumField", "FunctionDeclaration",
  "ArgumentList", "ArgumentList_", "Argument", "ReturnType_",
  "TemplateArguments_", "SimpleIdList", "TupleType", "FunctionType", "If",
  "While", "ForInitialization", "ForIteration", "For", "Statement",
  "Statements", "CompoundStatement", "SimpleStatement", "Return", "Use",
  "VariableAssignment", "VariableDeclaration", "Block", "SimpleId", "Id",
  "TypeList", "TypeList_", "AssignmentOperator", "QualifiedId", "DotExpr",
  "Expr", "TupleExpr", "BoolOperator", "CompOperator", "MathOperator",
  "BinaryOperator", "BinaryExpr", "ExprList", "Call", "Literal", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    74,    74,    74,    74,    75,    76,    76,
      77,    77,    78,    78,    79,    79,    80,    81,    81,    82,
      83,    84,    84,    85,    85,    86,    87,    87,    88,    88,
      89,    89,    90,    91,    92,    92,    93,    94,    94,    94,
      95,    95,    96,    97,    97,    97,    98,    98,    98,    99,
      99,    99,   100,   100,   100,   101,   102,   103,   104,   104,
     104,   105,   106,   107,   107,   107,   107,   107,   107,   107,
     108,   108,   109,   109,   110,   110,   110,   110,   110,   111,
     111,   112,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   114,   115,   115,   116,   116,   116,   116,
     116,   116,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   118,   118,   118,   119,   120,   120,   121,   121,
     122,   122
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     6,     0,     2,
       0,     1,     1,     2,     4,     1,     6,     1,     2,     2,
       7,     1,     3,     0,     1,     3,     0,     2,     0,     3,
       1,     3,     3,     5,     3,     5,     3,     1,     1,     1,
       1,     1,     7,     2,     2,     1,     0,     1,     2,     1,
       1,     1,     1,     1,     1,     2,     3,     3,     4,     4,
       6,     3,     1,     1,     1,     2,     3,     5,     1,     1,
       1,     3,     0,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1,     2,     2,     2,
       3,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     3,     4,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    62,     0,     4,     5,     6,
       3,    28,     8,     8,    79,     0,     0,     0,     0,     0,
       0,     0,    56,     0,    30,    23,     9,    10,     0,    80,
       0,    29,    24,     0,    21,     0,     0,    11,    12,    15,
      28,     0,    17,     0,    31,     0,    26,     0,     7,    13,
       0,    16,    18,    19,    22,     0,     0,     0,    72,    68,
      69,    63,    25,    64,     0,    27,    46,    20,     0,    70,
       0,     0,    65,    14,     0,     0,     0,     0,   120,     0,
       0,     0,   121,     0,     0,    49,    50,    51,    47,     0,
      45,     0,    54,    53,    52,    85,    83,     0,    92,    84,
      86,    82,     0,    66,     0,    32,     0,    87,    88,     0,
      38,    37,    39,     0,    89,   116,     0,    55,     0,     0,
      61,    48,    44,    94,   101,     0,     0,    74,     0,    76,
       0,    95,    75,    43,    77,   104,    78,    98,    97,   100,
      99,    96,   102,   103,   105,   110,   109,   108,   106,   107,
     111,     0,   112,   113,   114,     0,     0,    71,     0,     0,
      34,     0,    93,     0,     0,    36,    90,    81,     0,   118,
       0,    57,   115,    67,    33,     0,     0,   117,    58,    59,
      91,   119,     0,    35,     0,     0,    40,    41,    60,    42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     7,    19,    36,    37,    38,     8,    41,    42,
      39,    32,    33,    34,    56,    17,    23,    59,    60,    85,
      86,   109,   185,    87,    88,    89,    90,    91,    92,    10,
      93,    94,    67,    14,    62,    70,    71,   151,    95,    96,
      97,    98,   152,   153,   154,   155,    99,   116,   100,   101
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -106
static const yytype_int16 yypact[] =
{
    -106,    13,  -106,    -6,    -6,  -106,    -6,  -106,  -106,  -106,
    -106,     9,     6,     6,  -106,    -7,    -6,    17,    -6,    35,
      41,    -6,  -106,    32,  -106,    -6,  -106,    -6,    -6,  -106,
      -6,  -106,    70,    71,  -106,    75,    83,    -6,  -106,  -106,
       0,    -3,  -106,    49,  -106,    -6,    53,    50,  -106,  -106,
      50,  -106,  -106,  -106,  -106,    50,    62,    50,    50,  -106,
    -106,  -106,    54,    90,   -16,    54,   616,  -106,     7,    54,
      11,    93,  -106,  -106,   134,   134,    64,   134,  -106,    50,
     134,   134,  -106,    -6,   134,  -106,  -106,  -106,  -106,   602,
    -106,    63,  -106,  -106,  -106,    90,  -106,   145,  -106,  -106,
    -106,  -106,   134,  -106,    50,  -106,    66,   535,    31,    74,
    -106,  -106,   210,   275,    54,   535,    77,   535,    21,   275,
    -106,  -106,  -106,  -106,  -106,    50,    -6,  -106,   134,  -106,
      97,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,   134,  -106,  -106,  -106,   134,   340,    54,    50,   134,
      94,   134,  -106,    50,   134,  -106,    54,  -106,   405,  -106,
      79,   535,   535,  -106,    54,   470,    62,   535,    29,   535,
    -106,  -106,   134,  -106,   134,    62,  -106,   210,   535,  -106
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -106,  -106,  -106,   108,  -106,  -106,    69,  -106,  -106,    81,
     122,  -106,  -106,    85,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,    37,  -106,  -106,  -106,  -106,  -106,
     -71,    52,  -105,    -1,   -46,  -106,  -106,  -106,    -5,  -106,
     -15,  -106,  -106,  -106,  -106,  -106,  -106,     2,  -106,  -106
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      11,    15,    12,    13,    64,   110,    51,    21,   160,    65,
      50,    68,    69,     2,   165,    24,     5,    26,   102,     5,
      29,     3,   104,   105,    35,    16,    40,    43,    73,    44,
       4,   163,    72,   114,    16,     5,    40,    22,   124,   164,
      43,   125,    63,    30,    35,    63,    61,   184,   103,    61,
      63,    25,    63,    63,    61,    72,    61,    61,   157,   107,
     108,   112,   113,    18,     6,   115,   117,    74,    75,   119,
      27,   183,     5,    31,    63,    57,    28,    72,    61,   166,
     189,    45,   118,    46,    58,    47,     5,   156,   161,   162,
     161,   181,    48,    53,    78,    55,    79,    66,    80,    63,
      74,    75,    72,    61,    21,   106,    49,   122,   158,   169,
     176,   186,   174,   168,    82,   115,    83,   178,   159,     5,
      63,    20,    52,     9,    61,   167,   121,    78,   111,    79,
      54,    80,   170,     0,     0,     0,   171,    74,    75,     0,
     172,     0,     0,     0,   175,     0,   177,    82,     0,   179,
     123,     0,   124,    63,     0,   125,     5,    61,    63,   126,
       0,     0,    61,   127,    78,     0,    79,   187,    80,   188,
     128,     0,     0,     0,     0,     0,   129,     0,     0,   130,
       0,   131,     0,     0,    82,   132,     0,     0,     0,   133,
       0,   134,     0,   135,   136,     0,     0,     0,     0,     0,
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   123,     0,   124,     0,     0,
     125,     0,     0,     0,   126,     0,     0,     0,   127,     0,
       0,     0,     0,     0,     0,   128,     0,     0,     0,     0,
       0,   129,     0,     0,   130,     0,   131,     0,     0,     0,
     132,     0,     0,     0,     0,     0,   134,     0,   135,   136,
       0,     0,     0,     0,     0,     0,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     123,     0,   124,     0,     0,   125,     0,     0,     0,   126,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     128,     0,     0,     0,     0,     0,     0,     0,     0,   130,
      66,   131,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,     0,     0,     0,     0,     0,     0,
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   123,     0,   124,     0,     0,
     125,     0,     0,     0,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,     0,     0,     0,     0,
       0,     0,     0,     0,   130,     0,   131,     0,     0,     0,
       0,   173,     0,     0,     0,     0,     0,     0,   135,     0,
       0,     0,     0,     0,     0,     0,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     123,     0,   124,     0,     0,   125,     0,     0,     0,   126,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     128,     0,     0,     0,     0,     0,     0,     0,     0,   130,
       0,   131,     0,     0,     0,     0,   180,     0,     0,     0,
       0,     0,     0,   135,     0,     0,     0,     0,     0,     0,
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   123,     0,   124,     0,     0,
     125,     0,     0,     0,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,     0,     0,     0,     0,
       0,     0,     0,     0,   130,     0,   131,     0,     0,     0,
       0,     0,     0,     0,   182,     0,     0,     0,   135,     0,
       0,     0,     0,     0,     0,     0,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     123,     0,   124,     0,     0,   125,     0,     0,     0,   126,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     128,     0,     0,     0,     0,     0,     0,     0,     0,   130,
       0,   131,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,     0,     0,     0,     0,     0,     0,
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,    74,    75,     0,     0,     0,
       0,   120,     0,     0,     0,     0,     0,     0,     0,    74,
      75,    76,     0,    77,     5,     0,     0,     0,     0,     0,
       0,     0,    78,     0,    79,    76,    80,    77,     5,     0,
       0,     0,     0,     0,     0,    81,    78,     0,    79,     0,
      80,     0,    82,     0,    83,    84,     0,     0,     0,    81,
       0,     0,     0,     0,     0,     0,    82,     0,    83,    84
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-106)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,     6,     3,     4,    50,    76,     9,    14,   113,    55,
      10,    57,    58,     0,   119,    16,    22,    18,    11,    22,
      21,     8,    11,    12,    25,    25,    27,    28,    44,    30,
      17,    10,    48,    79,    25,    22,    37,    44,     7,    18,
      41,    10,    47,    11,    45,    50,    47,    18,    41,    50,
      55,    34,    57,    58,    55,    48,    57,    58,   104,    74,
      75,    76,    77,    57,    51,    80,    81,     3,     4,    84,
      35,   176,    22,    41,    79,    25,    35,    48,    79,   125,
     185,    11,    83,    12,    34,    10,    22,   102,    11,    12,
      11,    12,     9,    44,    30,    42,    32,    35,    34,   104,
       3,     4,    48,   104,    14,    12,    37,    44,    42,    12,
      16,   182,   158,   128,    50,   130,    52,   163,    44,    22,
     125,    13,    41,     1,   125,   126,    89,    30,    76,    32,
      45,    34,   130,    -1,    -1,    -1,   151,     3,     4,    -1,
     155,    -1,    -1,    -1,   159,    -1,   161,    50,    -1,   164,
       5,    -1,     7,   158,    -1,    10,    22,   158,   163,    14,
      -1,    -1,   163,    18,    30,    -1,    32,   182,    34,   184,
      25,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    34,
      -1,    36,    -1,    -1,    50,    40,    -1,    -1,    -1,    44,
      -1,    46,    -1,    48,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,     5,    -1,     7,    -1,    -1,
      10,    -1,    -1,    -1,    14,    -1,    -1,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    46,    -1,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       5,    -1,     7,    -1,    -1,    10,    -1,    -1,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,     5,    -1,     7,    -1,    -1,
      10,    -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       5,    -1,     7,    -1,    -1,    10,    -1,    -1,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    36,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,     5,    -1,     7,    -1,    -1,
      10,    -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       5,    -1,     7,    -1,    -1,    10,    -1,    -1,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,     3,     4,    -1,    -1,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,    19,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    32,    19,    34,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    30,    -1,    32,    -1,
      34,    -1,    50,    -1,    52,    53,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    52,    53
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    74,     0,     8,    17,    22,    51,    75,    80,    83,
     102,   106,   106,   106,   106,   111,    25,    88,    57,    76,
      76,    14,    44,    89,   106,    34,   106,    35,    35,   106,
      11,    41,    84,    85,    86,   106,    77,    78,    79,    83,
     106,    81,    82,   106,   106,    11,    12,    10,     9,    79,
      10,     9,    82,    44,    86,    42,    87,    25,    34,    90,
      91,   106,   107,   111,   107,   107,    35,   105,   107,   107,
     108,   109,    48,    44,     3,     4,    19,    21,    30,    32,
      34,    43,    50,    52,    53,    92,    93,    96,    97,    98,
      99,   100,   101,   103,   104,   111,   112,   113,   114,   119,
     121,   122,    11,    41,    11,    12,    12,   113,   113,    94,
     103,   104,   113,   113,   107,   113,   120,   113,   106,   113,
       9,    97,    44,     5,     7,    10,    14,    18,    25,    31,
      34,    36,    40,    44,    46,    48,    49,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,   110,   115,   116,   117,   118,   113,   107,    42,    44,
     105,    11,    12,    10,    18,   105,   107,   106,   113,    12,
     120,   113,   113,    41,   107,   113,    16,   113,   107,   113,
      41,    12,    44,   105,    18,    95,   103,   113,   113,   105
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (ast, symbols, logger, file, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])



/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, ast, symbols, logger, file); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, mem::ast::node::File* ast, mem::st::SymbolTable* symbols, mem::log::Logger* logger, mem::fs::File* file)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, ast, symbols, logger, file)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    mem::ast::node::File* ast;
    mem::st::SymbolTable* symbols;
    mem::log::Logger* logger;
    mem::fs::File* file;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (ast);
  YYUSE (symbols);
  YYUSE (logger);
  YYUSE (file);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, mem::ast::node::File* ast, mem::st::SymbolTable* symbols, mem::log::Logger* logger, mem::fs::File* file)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, ast, symbols, logger, file)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    mem::ast::node::File* ast;
    mem::st::SymbolTable* symbols;
    mem::log::Logger* logger;
    mem::fs::File* file;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, ast, symbols, logger, file);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, mem::ast::node::File* ast, mem::st::SymbolTable* symbols, mem::log::Logger* logger, mem::fs::File* file)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, ast, symbols, logger, file)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    mem::ast::node::File* ast;
    mem::st::SymbolTable* symbols;
    mem::log::Logger* logger;
    mem::fs::File* file;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , ast, symbols, logger, file);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, ast, symbols, logger, file); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, mem::ast::node::File* ast, mem::st::SymbolTable* symbols, mem::log::Logger* logger, mem::fs::File* file)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, ast, symbols, logger, file)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    mem::ast::node::File* ast;
    mem::st::SymbolTable* symbols;
    mem::log::Logger* logger;
    mem::fs::File* file;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (ast);
  YYUSE (symbols);
  YYUSE (logger);
  YYUSE (file);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YYLVAL_INITIALIZE
# define YYLVAL_INITIALIZE()
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (mem::ast::node::File* ast, mem::st::SymbolTable* symbols, mem::log::Logger* logger, mem::fs::File* file)
#else
int
yyparse (ast, symbols, logger, file)
    mem::ast::node::File* ast;
    mem::st::SymbolTable* symbols;
    mem::log::Logger* logger;
    mem::fs::File* file;
#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

  YYLVAL_INITIALIZE ();
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
/* Line 1813 of yacc.c  */
#line 265 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      ast->addChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 4:
/* Line 1813 of yacc.c  */
#line 269 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      ast->addChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 5:
/* Line 1813 of yacc.c  */
#line 273 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      ast->addChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 6:
/* Line 1813 of yacc.c  */
#line 277 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      ast->addChild((yyvsp[(2) - (2)].nodeFunc));
   }
    break;

  case 7:
/* Line 1813 of yacc.c  */
#line 288 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::Class* cls = new mem::ast::node::Class();
      cls->setValue((yyvsp[(2) - (6)].nodeFinalId)->Value());
      cls->setNameNode((yyvsp[(2) - (6)].nodeFinalId));
      cls->setParentTypeNode((yyvsp[(3) - (6)].node));
      cls->setMembersNode((yyvsp[(5) - (6)].nodeList));
      cls->setPosition(new fs::position::Range((yyloc)));

      (yyval.node) = cls;
   }
    break;

  case 8:
/* Line 1813 of yacc.c  */
#line 301 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = NULL;
   }
    break;

  case 9:
/* Line 1813 of yacc.c  */
#line 305 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = (yyvsp[(2) - (2)].nodeFinalId);
   }
    break;

  case 10:
/* Line 1813 of yacc.c  */
#line 311 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList) = new mem::ast::node::NodeList();
   }
    break;

  case 11:
/* Line 1813 of yacc.c  */
#line 315 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList) = (yyvsp[(1) - (1)].nodeList);
   }
    break;

  case 12:
/* Line 1813 of yacc.c  */
#line 321 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList) = new mem::ast::node::NodeList();
      (yyval.nodeList)->addChild((yyvsp[(1) - (1)].node));
   }
    break;

  case 13:
/* Line 1813 of yacc.c  */
#line 326 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      assert ((yyvsp[(1) - (2)].nodeList) != NULL);
      (yyval.nodeList)->addChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 14:
/* Line 1813 of yacc.c  */
#line 334 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::Field* field = new mem::ast::node::Field();
      field->setPosition((yyloc).copy_range());
      field->setNameNode((yyvsp[(1) - (4)].nodeFinalId));
      field->setTypeNode((yyvsp[(3) - (4)].nodeId));

      (yyval.node) = (ast::node::Node*)field;
   }
    break;

  case 15:
/* Line 1813 of yacc.c  */
#line 343 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = (yyvsp[(1) - (1)].nodeFunc);
   }
    break;

  case 16:
/* Line 1813 of yacc.c  */
#line 354 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {

      mem::ast::node::EnumType* e = new mem::ast::node::EnumType();
      e->setNameNode((yyvsp[(2) - (6)].nodeFinalId));
      e->setValue((yyvsp[(2) - (6)].nodeFinalId)->Value());
      if ((yyvsp[(3) - (6)].node) == NULL)
      {
         // FIXME Not sure if it belongs here, maybe in TopTypesChecker ?
         mem::ast::node::FinalId* enum_ty = new mem::ast::node::FinalId();
         enum_ty->setValue("int");
         e->setParentTypeNode(enum_ty);
      }
      else
      {
         e->setParentTypeNode((yyvsp[(3) - (6)].node));
      }
      e->setMembersNode((yyvsp[(5) - (6)].nodeList));

      (yyval.node) = e;
   }
    break;

  case 17:
/* Line 1813 of yacc.c  */
#line 377 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList) = new mem::ast::node::NodeList();
      (yyval.nodeList)->addChild((yyvsp[(1) - (1)].nodeVarDecl));
   }
    break;

  case 18:
/* Line 1813 of yacc.c  */
#line 382 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      assert((yyvsp[(2) - (2)].nodeVarDecl) != NULL);
      (yyval.nodeList) = (yyvsp[(1) - (2)].nodeList);
      (yyval.nodeList)->addChild((yyvsp[(2) - (2)].nodeVarDecl));
   }
    break;

  case 19:
/* Line 1813 of yacc.c  */
#line 390 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeVarDecl) = new mem::ast::node::VarDecl();
      (yyval.nodeVarDecl)->setNameNode((yyvsp[(1) - (2)].nodeFinalId));
   }
    break;

  case 20:
/* Line 1813 of yacc.c  */
#line 403 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeFunc) = new mem::ast::node::Func();
      (yyval.nodeFunc)->setNameNode((yyvsp[(1) - (7)].nodeFinalId));
      (yyval.nodeFunc)->setValue((yyvsp[(1) - (7)].nodeFinalId)->Value());

      // Argument list
      if ((yyvsp[(4) - (7)].nodeList) != NULL)
      {
         (yyval.nodeFunc)->setParamsNode((yyvsp[(4) - (7)].nodeList));
      }

      // Return type
      if ((yyvsp[(6) - (7)].node) != NULL)
      {
         (yyval.nodeFunc)->setReturnTypeNode(mem::ast::node::cast<mem::ast::node::Id>((yyvsp[(6) - (7)].node)));
      }
      else
      {
         mem::ast::node::FinalId* void_ty = new mem::ast::node::FinalId();
         void_ty->setValue("void");
         (yyval.nodeFunc)->setReturnTypeNode(void_ty);
      }

      // Body block
      if ((yyvsp[(7) - (7)].nodeBlock) != NULL)
      {
         (yyval.nodeFunc)->setBodyNode(mem::ast::node::cast<mem::ast::node::Block>((yyvsp[(7) - (7)].nodeBlock)));
      }

      (yyval.nodeFunc)->setPosition((yyloc).copy_range());
   }
    break;

  case 21:
/* Line 1813 of yacc.c  */
#line 438 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList) = new mem::ast::node::NodeList();
      (yyval.nodeList)->addChild((yyvsp[(1) - (1)].nodeVarDecl));
      (yyval.nodeList)->setPosition((yylsp[(1) - (1)]).copy_range());
   }
    break;

  case 22:
/* Line 1813 of yacc.c  */
#line 444 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList)->addChild((yyvsp[(3) - (3)].nodeVarDecl));
      (yyval.nodeList)->Position()->append((yylsp[(3) - (3)]));
   }
    break;

  case 23:
/* Line 1813 of yacc.c  */
#line 451 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList) = new mem::ast::node::NodeList();
   }
    break;

  case 24:
/* Line 1813 of yacc.c  */
#line 455 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList) = (yyvsp[(1) - (1)].nodeList);
   }
    break;

  case 25:
/* Line 1813 of yacc.c  */
#line 461 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeVarDecl) = new mem::ast::node::VarDecl();
      (yyval.nodeVarDecl)->setNameNode((yyvsp[(1) - (3)].nodeFinalId));
      (yyval.nodeVarDecl)->setTypeNode((yyvsp[(3) - (3)].nodeId));
      (yyval.nodeVarDecl)->setPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(3) - (3)])));
   }
    break;

  case 26:
/* Line 1813 of yacc.c  */
#line 470 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = NULL;
   }
    break;

  case 27:
/* Line 1813 of yacc.c  */
#line 474 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = (yyvsp[(2) - (2)].nodeId);
   }
    break;

  case 28:
/* Line 1813 of yacc.c  */
#line 480 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList) = NULL;
   }
    break;

  case 29:
/* Line 1813 of yacc.c  */
#line 484 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList) = new mem::ast::node::NodeList();
   }
    break;

  case 30:
/* Line 1813 of yacc.c  */
#line 490 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList) = new mem::ast::node::NodeList();
      (yyval.nodeList)->addChild((yyvsp[(1) - (1)].nodeFinalId));
   }
    break;

  case 31:
/* Line 1813 of yacc.c  */
#line 495 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyvsp[(1) - (3)].nodeList)->addChild((yyvsp[(3) - (3)].nodeFinalId));
   }
    break;

  case 32:
/* Line 1813 of yacc.c  */
#line 506 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = (yyvsp[(2) - (3)].nodeId);
   }
    break;

  case 33:
/* Line 1813 of yacc.c  */
#line 512 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::FuncType* nodeFunc = new mem::ast::node::FuncType();
      nodeFunc->setParamsNode((yyvsp[(2) - (5)].nodeId));

      (yyval.node) = nodeFunc;
   }
    break;

  case 34:
/* Line 1813 of yacc.c  */
#line 531 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::If* n = new mem::ast::node::If();
      n->setConditionNode((yyvsp[(2) - (3)].node));
      n->setIfBlockNode((yyvsp[(3) - (3)].nodeBlock));
      n->setPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(2) - (3)])));
      (yyval.node) = n;
   }
    break;

  case 35:
/* Line 1813 of yacc.c  */
#line 540 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::If* n = new mem::ast::node::If();
      n->setConditionNode((yyvsp[(2) - (5)].node));
      n->setIfBlockNode((yyvsp[(3) - (5)].nodeBlock));
      n->setElseBlockNode((yyvsp[(5) - (5)].nodeBlock));
      n->setPosition(new fs::position::Range((yylsp[(1) - (5)]), (yylsp[(5) - (5)])));
      (yyval.node) = n;
   }
    break;

  case 36:
/* Line 1813 of yacc.c  */
#line 556 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeWhile) = new mem::ast::node::While();
      (yyval.nodeWhile)->setConditionNode((yyvsp[(2) - (3)].node));
      (yyval.nodeWhile)->setBlockNode((yyvsp[(3) - (3)].nodeBlock));
      (yyval.nodeWhile)->setPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(3) - (3)])));
   }
    break;

  case 42:
/* Line 1813 of yacc.c  */
#line 579 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::For* n = new mem::ast::node::For();
      n->setInitializationNode((yyvsp[(2) - (7)].node));
      n->setConditionNode((yyvsp[(4) - (7)].node));
      n->setIterationNode((yyvsp[(6) - (7)].node));
      n->setBlockNode(mem::ast::node::cast<mem::ast::node::Block>((yyvsp[(7) - (7)].nodeBlock)));
      n->setPosition((yyloc).copy_range());

      (yyval.node) = n;
   }
    break;

  case 43:
/* Line 1813 of yacc.c  */
#line 597 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = (yyvsp[(1) - (2)].node);
   }
    break;

  case 44:
/* Line 1813 of yacc.c  */
#line 601 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = (yyvsp[(1) - (2)].node);
   }
    break;

  case 45:
/* Line 1813 of yacc.c  */
#line 605 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
   }
    break;

  case 46:
/* Line 1813 of yacc.c  */
#line 611 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBlock) = new mem::ast::node::Block();
   }
    break;

  case 47:
/* Line 1813 of yacc.c  */
#line 615 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      assert ((yyvsp[(1) - (1)].node) != NULL);
      (yyval.nodeBlock) = new mem::ast::node::Block();
      (yyval.nodeBlock)->addChild((yyvsp[(1) - (1)].node));
   }
    break;

  case 48:
/* Line 1813 of yacc.c  */
#line 621 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      assert ((yyval.nodeBlock) != NULL);
      (yyval.nodeBlock)->addChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 50:
/* Line 1813 of yacc.c  */
#line 629 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = (yyvsp[(1) - (1)].nodeWhile);
   }
    break;

  case 55:
/* Line 1813 of yacc.c  */
#line 641 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::Return* n = new mem::ast::node::Return();
      n->setValueNode((yyvsp[(2) - (2)].node));
      (yyval.node) = n;
   }
    break;

  case 56:
/* Line 1813 of yacc.c  */
#line 649 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::Use* nodeUse = new mem::ast::node::Use();
      nodeUse->setValue((yyvsp[(2) - (3)].node)->Value());
      nodeUse->setPosition((yyloc).copy_range());
      nodeUse->setIdNode(mem::ast::node::cast<mem::ast::node::FinalId>((yyvsp[(2) - (3)].node)));

      (yyval.node) = nodeUse;
   }
    break;

  case 57:
/* Line 1813 of yacc.c  */
#line 660 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::VarAssign* n = new mem::ast::node::VarAssign();
      n->setPosition((yyloc).copy_range());
      n->setNameNode((yyvsp[(1) - (3)].node));
      n->setValueNode((yyvsp[(3) - (3)].node));
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 58:
/* Line 1813 of yacc.c  */
#line 671 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::VarDecl* n = new mem::ast::node::VarDecl();
      n->setNameNode((yyvsp[(2) - (4)].nodeFinalId));
      n->setTypeNode((yyvsp[(4) - (4)].nodeId));
      n->setPosition((yyloc).copy_range());
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 59:
/* Line 1813 of yacc.c  */
#line 680 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::Node* nodeTypePlaceHolder = new mem::ast::node::Node();
      nodeTypePlaceHolder->setKind(ast::node::MetaKind::PLACE_HOLDER);
      nodeTypePlaceHolder->setPosition((yylsp[(4) - (4)]).copy_range());

      mem::ast::node::VarDecl* nodeVarDecl = new mem::ast::node::VarDecl();
      nodeVarDecl->setNameNode((yyvsp[(2) - (4)].nodeFinalId));
      nodeVarDecl->setTypeNode(nodeTypePlaceHolder);
      nodeVarDecl->setValueNode((yyvsp[(4) - (4)].node));
      nodeVarDecl->setPosition((yyloc).copy_range());

      (yyval.node) = (ast::node::Node*)nodeVarDecl;
   }
    break;

  case 60:
/* Line 1813 of yacc.c  */
#line 695 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::VarDecl* n = new mem::ast::node::VarDecl();
      n->setNameNode((yyvsp[(2) - (6)].nodeFinalId));
      n->setTypeNode((yyvsp[(4) - (6)].nodeId));
      n->setValueNode((yyvsp[(6) - (6)].node));
      n->setPosition((yyloc).copy_range());
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 61:
/* Line 1813 of yacc.c  */
#line 711 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBlock) = mem::ast::node::cast<mem::ast::node::Block>((yyvsp[(2) - (3)].nodeBlock));
      (yyval.nodeBlock)->setPosition((yyloc).copy_range());
   }
    break;

  case 62:
/* Line 1813 of yacc.c  */
#line 718 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeFinalId) = new mem::ast::node::FinalId();
      (yyval.nodeFinalId)->setPosition(new fs::position::Range((yyloc)));
      (yyval.nodeFinalId)->setValue((yyvsp[(1) - (1)].text)->c_str());

      delete (yyvsp[(1) - (1)].text);
   }
    break;

  case 63:
/* Line 1813 of yacc.c  */
#line 728 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeId) = (yyvsp[(1) - (1)].nodeFinalId);
   }
    break;

  case 64:
/* Line 1813 of yacc.c  */
#line 732 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeId) = new ast::node::Id();
      (yyval.nodeId)->setValue((yyvsp[(1) - (1)].node)->Value());
      (yyval.nodeId)->setPosition((yyloc).copy_range());
      delete (yyvsp[(1) - (1)].node);
   }
    break;

  case 65:
/* Line 1813 of yacc.c  */
#line 740 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::PointerType* ptr = new mem::ast::node::PointerType();
      ptr->setTypeNode((yyvsp[(1) - (2)].nodeId));
      (yyval.nodeId) = ptr;
      (yyval.nodeId)->setPosition((yyloc).copy_range());
   }
    break;

  case 66:
/* Line 1813 of yacc.c  */
#line 748 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::ArrayType* arr = new mem::ast::node::ArrayType();
      arr->setTypeNode((yyvsp[(2) - (3)].nodeId));

      (yyval.nodeId) = arr;
      (yyval.nodeId)->setPosition((yyloc).copy_range());
   }
    break;

  case 67:
/* Line 1813 of yacc.c  */
#line 757 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::ArrayType* arr = new mem::ast::node::ArrayType();
      arr->setTypeNode((yyvsp[(2) - (5)].nodeId));
      arr->setLengthNode((yyvsp[(4) - (5)].node));

      (yyval.nodeId) = arr;
      (yyval.nodeId)->setPosition((yyloc).copy_range());
   }
    break;

  case 68:
/* Line 1813 of yacc.c  */
#line 766 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeId) = mem::ast::node::cast<mem::ast::node::Id>((yyvsp[(1) - (1)].node));
   }
    break;

  case 69:
/* Line 1813 of yacc.c  */
#line 770 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeId) = mem::ast::node::cast<mem::ast::node::Id>((yyvsp[(1) - (1)].node));
   }
    break;

  case 70:
/* Line 1813 of yacc.c  */
#line 776 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::TupleType* t = new mem::ast::node::TupleType();
      t->addChild((yyvsp[(1) - (1)].nodeId));
      (yyval.nodeId) = t;
   }
    break;

  case 71:
/* Line 1813 of yacc.c  */
#line 782 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      assert ((yyvsp[(1) - (3)].nodeId) != NULL);
      mem::ast::node::cast<mem::ast::node::TupleType>((yyval.nodeId))->addChild((yyvsp[(3) - (3)].nodeId));
   }
    break;

  case 72:
/* Line 1813 of yacc.c  */
#line 789 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeId) = new mem::ast::node::TupleType();
   }
    break;

  case 79:
/* Line 1813 of yacc.c  */
#line 800 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::FinalId* n = new mem::ast::node::FinalId();
      n->setValue((yyvsp[(1) - (1)].nodeFinalId)->Value());
      n->setPosition((yyloc).copy_range());
      delete (yyvsp[(1) - (1)].nodeFinalId);
      (yyval.node) = ast::node::cast<ast::node::Text>(n);
      assert((yyval.node)->Position() != NULL);
   }
    break;

  case 80:
/* Line 1813 of yacc.c  */
#line 809 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::Dot* n = new mem::ast::node::Dot();
      n->setLeftNode((yyvsp[(1) - (3)].node));
      n->setRightNode((yyvsp[(3) - (3)].nodeFinalId));
      if (n->Position() != NULL)
      {
         n->Position()->append((yyloc));
      }
      else
      {
         n->setPosition((yyloc).copy_range());
      }
      (yyval.node) = n;
   }
    break;

  case 81:
/* Line 1813 of yacc.c  */
#line 826 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::Dot* n = new mem::ast::node::Dot();
      n->setPosition((yyloc).copy_range());
      n->setLeftNode((yyvsp[(1) - (3)].node));
      n->setRightNode((yyvsp[(3) - (3)].nodeFinalId));
      (yyval.node) = n;
   }
    break;

  case 82:
/* Line 1813 of yacc.c  */
#line 836 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
   }
    break;

  case 83:
/* Line 1813 of yacc.c  */
#line 840 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
   }
    break;

  case 84:
/* Line 1813 of yacc.c  */
#line 844 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = (ast::node::Node*)(yyvsp[(1) - (1)].nodeBinaryOp);
   }
    break;

  case 85:
/* Line 1813 of yacc.c  */
#line 849 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = ast::node::cast<ast::node::Node>((yyvsp[(1) - (1)].node));
   }
    break;

  case 86:
/* Line 1813 of yacc.c  */
#line 853 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.node) = ast::node::cast<ast::node::Node>((yyvsp[(1) - (1)].node));
   }
    break;

  case 87:
/* Line 1813 of yacc.c  */
#line 859 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::UnaryOp* n = new mem::ast::node::UnaryOp();
      n->setKind(ast::node::MetaKind::AMPERSAND);
      n->setValueNode((yyvsp[(2) - (2)].node));
      (yyval.node) = n;
   }
    break;

  case 88:
/* Line 1813 of yacc.c  */
#line 868 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::UnaryOp* n = new mem::ast::node::UnaryOp();
      n->setKind(ast::node::MetaKind::DEREF);
      n->setValueNode((yyvsp[(2) - (2)].node));
      n->setPosition((yyloc).copy_range());
      (yyval.node) = n;
   }
    break;

  case 89:
/* Line 1813 of yacc.c  */
#line 877 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::New* n = new mem::ast::node::New();
      n->setTypeNode((yyvsp[(2) - (2)].nodeId));
      (yyval.node) = n;
      (yyval.node)->setPosition((yyloc).copy_range());
   }
    break;

  case 90:
/* Line 1813 of yacc.c  */
#line 886 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::CastOp* n = new mem::ast::node::CastOp();
      n->setValueNode((yyvsp[(1) - (3)].node));
      n->setTypeNode((yyvsp[(3) - (3)].nodeId));

      (yyval.node) = n;
      (yyval.node)->setPosition((yyloc).copy_range());
   }
    break;

  case 91:
/* Line 1813 of yacc.c  */
#line 896 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::BracketOp* n = new mem::ast::node::BracketOp();
      n->setValueNode((yyvsp[(1) - (4)].node));
      n->setIndexNode((yyvsp[(3) - (4)].node));
      (yyval.node) = n;
   }
    break;

  case 93:
/* Line 1813 of yacc.c  */
#line 906 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      if ((yyvsp[(2) - (3)].nodeList)->ChildCount() == 1)
      {
         (yyval.node) = (yyvsp[(2) - (3)].nodeList)->getChild(0);
         (yyval.node)->setParent(NULL);
         // For some reason, we get a segfault if we delete $2
         //delete $2;
      }
      else
      {
         DEBUG_PRINT("Tuple with several expr\n");
         mem::ast::node::Tuple* nodeTuple = new mem::ast::node::Tuple();
         nodeTuple->eat((yyvsp[(2) - (3)].nodeList));
         nodeTuple->setPosition((yyloc).copy_range());
         (yyval.node) = nodeTuple;

         // See before
         //delete $2;
      }
   }
    break;

  case 94:
/* Line 1813 of yacc.c  */
#line 929 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_AND);
   }
    break;

  case 95:
/* Line 1813 of yacc.c  */
#line 934 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_OR);
   }
    break;

  case 96:
/* Line 1813 of yacc.c  */
#line 942 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_EQ_EQ);
   }
    break;

  case 97:
/* Line 1813 of yacc.c  */
#line 948 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_LT);
   }
    break;

  case 98:
/* Line 1813 of yacc.c  */
#line 954 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_LTE);
   }
    break;

  case 99:
/* Line 1813 of yacc.c  */
#line 960 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_GT);
   }
    break;

  case 100:
/* Line 1813 of yacc.c  */
#line 966 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_GTE);
   }
    break;

  case 101:
/* Line 1813 of yacc.c  */
#line 972 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_NE);
   }
    break;

  case 102:
/* Line 1813 of yacc.c  */
#line 980 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_PLUS);
   }
    break;

  case 103:
/* Line 1813 of yacc.c  */
#line 985 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_MINUS);
   }
    break;

  case 104:
/* Line 1813 of yacc.c  */
#line 990 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_MUL);
   }
    break;

  case 105:
/* Line 1813 of yacc.c  */
#line 995 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_DIV);
   }
    break;

  case 106:
/* Line 1813 of yacc.c  */
#line 1000 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_RSHIFT);
   }
    break;

  case 107:
/* Line 1813 of yacc.c  */
#line 1005 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_LSHIFT);
   }
    break;

  case 108:
/* Line 1813 of yacc.c  */
#line 1010 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_BIT_OR);
   }
    break;

  case 109:
/* Line 1813 of yacc.c  */
#line 1015 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_BIT_AND);
   }
    break;

  case 110:
/* Line 1813 of yacc.c  */
#line 1020 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_XOR);
   }
    break;

  case 111:
/* Line 1813 of yacc.c  */
#line 1025 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeBinaryOp) = new mem::ast::node::BinaryOp();
      (yyval.nodeBinaryOp)->setKind(ast::node::MetaKind::OP_MODULO);
   }
    break;

  case 115:
/* Line 1813 of yacc.c  */
#line 1035 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::BinaryOp* n = (yyvsp[(2) - (3)].nodeBinaryOp);
      n->setLeftNode((yyvsp[(1) - (3)].node));
      n->setRightNode((yyvsp[(3) - (3)].node));
      n->setPosition((yyloc).copy_range());
      (yyval.nodeBinaryOp) = n;
   }
    break;

  case 116:
/* Line 1813 of yacc.c  */
#line 1045 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList) = new mem::ast::node::NodeList();
      (yyval.nodeList)->addChild((yyvsp[(1) - (1)].node));
      (yyval.nodeList)->setPosition((yyloc).copy_range());
   }
    break;

  case 117:
/* Line 1813 of yacc.c  */
#line 1051 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      (yyval.nodeList)->addChild((yyvsp[(3) - (3)].node));
      (yyval.nodeList)->Position()->append((yylsp[(3) - (3)]));
   }
    break;

  case 118:
/* Line 1813 of yacc.c  */
#line 1059 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::Call* n = new mem::ast::node::Call();
      n->setCallerNode((yyvsp[(1) - (3)].node));
      n->setParamsNode(new mem::ast::node::NodeList());

      (yyval.node) = n;
      (yyval.node)->setPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(3) - (3)])));
   }
    break;

  case 119:
/* Line 1813 of yacc.c  */
#line 1069 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::Call* n = new mem::ast::node::Call();
      n->setCallerNode((yyvsp[(1) - (4)].node));
      n->setParamsNode((yyvsp[(3) - (4)].nodeList));

      (yyval.node) = n;
      (yyval.node)->setPosition(new fs::position::Range((yylsp[(1) - (4)]), (yylsp[(4) - (4)])));
   }
    break;

  case 120:
/* Line 1813 of yacc.c  */
#line 1080 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      int i = 0;
      number::parseIntNumber(*(yyvsp[(1) - (1)].text), i);
#if 0

      switch (nb_format)
      {
         case 'c':
         {
            mem::st::IntConstant* ic = mem::st::util::getNativeCharConstant(symbols->System(), (char)i);
            ic->setType(symbols->_core_types.CharTy());

            mem::ast::node::Number* c_node = new mem::ast::node::Number();
            c_node->setBoundSymbol(ic);
            c_node->setExprType(symbols->_core_types.CharTy());
            (yyval.node) = c_node;
            break;
         }
         case 's':
         {
            mem::st::IntConstant* ic = mem::st::util::getNativeShortConstant(symbols->System(), (short)i);
            ic->setType(symbols->_core_types.ShortTy());

            mem::ast::node::Number* s_node = new mem::ast::node::Number();
            s_node->setBoundSymbol(ic);
            s_node->setExprType(symbols->_core_types.ShortTy());
            (yyval.node) = s_node;
            break;
         }
         case 'i':
         {
#endif
            mem::st::IntConstant* ic = mem::st::util::getNativeShortConstant(symbols->System(), i);
            ic->setType(symbols->_core_types.IntTy());

            mem::ast::node::Number* i_node = new mem::ast::node::Number();
            i_node->setBoundSymbol(ic);
            i_node->setExprType(symbols->_core_types.IntTy());
            (yyval.node) = i_node;
#if 0
            break;
         }
      }
#endif

      assert ((yyval.node) != NULL);

      if ((yyval.node) != NULL)
      {
         (yyval.node)->setPosition((yylsp[(1) - (1)]).copy_range());
      }
      else
      {
         assert(false);
         //FIXME Couldnt fit this value into a numeric type, so should fail
      }

      delete (yyvsp[(1) - (1)].text);
   }
    break;

  case 121:
/* Line 1813 of yacc.c  */
#line 1140 "/home/thomas/code/memc/src/langmem/Bison.ypp"
    {
      mem::ast::node::String* str = new mem::ast::node::String();
      str->setValue((yyvsp[(1) - (1)].text)->c_str());
      str->setPosition((yylsp[(1) - (1)]).copy_range());

      (yyval.node) = str;

      delete (yyvsp[(1) - (1)].text);
   }
    break;


/* Line 1813 of yacc.c  */
#line 3128 "/home/thomas/code/memc/src/langmem/Bison.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (ast, symbols, logger, file, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (ast, symbols, logger, file, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc, ast, symbols, logger, file);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, ast, symbols, logger, file);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (ast, symbols, logger, file, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, ast, symbols, logger, file);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, ast, symbols, logger, file);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2076 of yacc.c  */
#line 1149 "/home/thomas/code/memc/src/langmem/Bison.ypp"


#include "mem/ast/node/Node.hpp"
