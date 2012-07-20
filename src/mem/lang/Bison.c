/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */


/* Line 268 of yacc.c  */
#line 71 "src/mem/lang/Bison.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 288 of yacc.c  */
#line 7 "Bison.y"

#define PASS (0);
#include <stdio.h>
#include <string.h>
#include "mem/ast/node/BinaryExpression.hpp"
#include "mem/ast/node/BinaryOp.hpp"
#include "mem/ast/node/Block.hpp"
#include "mem/ast/node/Call.hpp"
#include "mem/ast/node/Class.hpp"
#include "mem/ast/node/Dot.hpp"
#include "mem/ast/node/Field.hpp"
#include "mem/ast/node/FinalId.hpp"
#include "mem/ast/node/New.hpp"
#include "mem/ast/node/Primitive.hpp"
#include "mem/ast/node/Root.hpp"
#include "mem/ast/node/Text.hpp"
#include "mem/ast/node/Use.hpp"
#include "mem/ast/node/VarAssign.hpp"
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


/* Line 288 of yacc.c  */
#line 85 "Bison.y"




/* Line 288 of yacc.c  */
#line 162 "src/mem/lang/Bison.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_AMPERSAND = 258,
     T_AROBASE = 259,
     T_AND = 260,
     T_CLASS = 261,
     T_COMMA = 262,
     T_CP = 263,
     T_DEDENT = 264,
     T_DOT = 265,
     T_ELSE = 266,
     T_EQ = 267,
     T_IF = 268,
     T_ID = 269,
     T_INDENT = 270,
     T_INTERFACE = 271,
     T_LBRACKET = 272,
     T_LITERAL_FLOAT = 273,
     T_LITERAL_HEX = 274,
     T_LITERAL_INT = 275,
     T_LITERAL_NUMBER = 276,
     T_NEW = 277,
     T_NEWLINE = 278,
     T_OP = 279,
     T_OR = 280,
     T_PASS = 281,
     T_PATCH = 282,
     T_PRIMITIVE = 283,
     T_OBJECT = 284,
     T_RBRACKET = 285,
     T_RARR = 286,
     T_STRING = 287,
     T_USE = 288,
     T_WHITESPACE = 289,
     T_LEFT_BINARY_OP = 290,
     T_RETURN = 291,
     T_SEMICOLON = 292,
     T_WHILE = 293,
     T_SELF = 294,
     T_BANG = 295,
     T_HASH = 296,
     T_DOTDOTDOT = 297,
     T_LARR_EQ = 298,
     T_LT = 299,
     T_RARR_EQ = 300,
     T_GT = 301,
     T_EQ_EQ = 302,
     T_PLUS = 303,
     T_MINUS = 304,
     T_DIV = 305,
     T_MUL = 306,
     T_MODULO = 307,
     T_MUL_MUL = 308,
     T_PLUS_PLUS = 309,
     T_MINUS_MINUS = 310
   };
#endif
/* Tokens.  */
#define T_AMPERSAND 258
#define T_AROBASE 259
#define T_AND 260
#define T_CLASS 261
#define T_COMMA 262
#define T_CP 263
#define T_DEDENT 264
#define T_DOT 265
#define T_ELSE 266
#define T_EQ 267
#define T_IF 268
#define T_ID 269
#define T_INDENT 270
#define T_INTERFACE 271
#define T_LBRACKET 272
#define T_LITERAL_FLOAT 273
#define T_LITERAL_HEX 274
#define T_LITERAL_INT 275
#define T_LITERAL_NUMBER 276
#define T_NEW 277
#define T_NEWLINE 278
#define T_OP 279
#define T_OR 280
#define T_PASS 281
#define T_PATCH 282
#define T_PRIMITIVE 283
#define T_OBJECT 284
#define T_RBRACKET 285
#define T_RARR 286
#define T_STRING 287
#define T_USE 288
#define T_WHITESPACE 289
#define T_LEFT_BINARY_OP 290
#define T_RETURN 291
#define T_SEMICOLON 292
#define T_WHILE 293
#define T_SELF 294
#define T_BANG 295
#define T_HASH 296
#define T_DOTDOTDOT 297
#define T_LARR_EQ 298
#define T_LT 299
#define T_RARR_EQ 300
#define T_GT 301
#define T_EQ_EQ 302
#define T_PLUS 303
#define T_MINUS 304
#define T_DIV 305
#define T_MUL 306
#define T_MODULO 307
#define T_MUL_MUL 308
#define T_PLUS_PLUS 309
#define T_MINUS_MINUS 310




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 88 "Bison.y"

   int integer;
   char* text;
   ast::node::Node* binary_node;
   ast::node::Node* node;
   ast::node::Text* text_node;



/* Line 293 of yacc.c  */
#line 299 "src/mem/lang/Bison.c"
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


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 324 "src/mem/lang/Bison.c"
/* Unqualified %code blocks.  */

/* Line 344 of yacc.c  */
#line 67 "Bison.y"

extern int yylex();

void yyerror(fs::FileManager& fm, ast::node::Node* ast,
   st::SymbolTable& symbols, log::Logger* logger, fs::File* file,
   const char *s)
{
   fs::position::Position* pos = new fs::position::Position();
   pos->sFile(file);

   log::Message* msg = new log::Error();
   msg->sMessage("Syntax error");
   msg->sDescription(s);
   msg->sPosition(pos);
   logger->log(msg);
}


/* Line 344 of yacc.c  */
#line 96 "Bison.y"




/* Line 344 of yacc.c  */
#line 354 "src/mem/lang/Bison.c"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   273

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNRULES -- Number of states.  */
#define YYNSTATES  139

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

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
      55
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    14,    17,    20,    23,
      26,    28,    32,    36,    40,    46,    51,    53,    56,    63,
      71,    78,    86,    88,    92,    97,   101,   105,   111,   115,
     120,   122,   125,   128,   130,   132,   134,   136,   138,   140,
     142,   146,   148,   151,   156,   158,   163,   168,   174,   181,
     183,   185,   189,   195,   197,   199,   201,   205,   207,   209,
     212,   215,   217,   219,   221,   223,   225,   227,   229,   231,
     233,   235,   237,   239,   241,   245,   247,   251,   255,   260
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    -1,    57,    23,    -1,    57,     9,    -1,
      57,    34,    23,    -1,    57,    58,    -1,    57,    61,    -1,
      57,    64,    -1,    33,    59,    -1,    14,    -1,    59,    10,
      14,    -1,    41,    14,    23,    -1,     6,    80,    62,    -1,
       6,    80,    44,    80,    62,    -1,    23,    15,    75,     9,
      -1,    14,    -1,    60,    14,    -1,    63,    24,     8,    31,
      77,    23,    -1,    63,    24,    65,     8,    31,    77,    23,
      -1,    63,    24,     8,    31,    77,    69,    -1,    63,    24,
      65,     8,    31,    77,    69,    -1,    66,    -1,    65,     7,
      66,    -1,    65,     7,    42,    66,    -1,    80,    37,    77,
      -1,    13,    83,    69,    -1,    13,    83,    69,    11,    69,
      -1,    38,    83,    69,    -1,    23,    15,    70,     9,    -1,
      71,    -1,    70,    71,    -1,    83,    23,    -1,    73,    -1,
      72,    -1,    67,    -1,    68,    -1,    79,    -1,    78,    -1,
      74,    -1,    36,    83,    23,    -1,    76,    -1,    75,    76,
      -1,    80,    37,    77,    23,    -1,    81,    -1,    83,    12,
      83,    23,    -1,    80,    37,    77,    23,    -1,    80,    37,
      12,    83,    23,    -1,    80,    37,    77,    12,    83,    23,
      -1,    14,    -1,    80,    -1,    81,    10,    80,    -1,    24,
      83,     8,    10,    80,    -1,    91,    -1,    82,    -1,    88,
      -1,    24,    83,     8,    -1,    81,    -1,    90,    -1,     3,
      83,    -1,    22,    77,    -1,     5,    -1,    25,    -1,    47,
      -1,    44,    -1,    43,    -1,    46,    -1,    45,    -1,    48,
      -1,    49,    -1,    51,    -1,    84,    -1,    85,    -1,    86,
      -1,    83,    87,    83,    -1,    83,    -1,    89,     7,    83,
      -1,    81,    24,     8,    -1,    81,    24,    89,     8,    -1,
      21,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   188,   188,   190,   191,   192,   193,   197,   201,   208,
     217,   222,   228,   239,   250,   264,   278,   286,   306,   315,
     331,   339,   353,   359,   363,   369,   385,   394,   402,   410,
     419,   425,   435,   439,   443,   449,   450,   453,   454,   455,
     458,   466,   471,   478,   488,   494,   504,   512,   524,   533,
     544,   551,   559,   567,   571,   575,   580,   586,   590,   594,
     600,   608,   613,   621,   629,   634,   639,   644,   651,   656,
     661,   668,   668,   668,   671,   680,   686,   698,   705,   714
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_AMPERSAND", "T_AROBASE", "T_AND",
  "T_CLASS", "T_COMMA", "T_CP", "T_DEDENT", "T_DOT", "T_ELSE", "T_EQ",
  "T_IF", "T_ID", "T_INDENT", "T_INTERFACE", "T_LBRACKET",
  "T_LITERAL_FLOAT", "T_LITERAL_HEX", "T_LITERAL_INT", "T_LITERAL_NUMBER",
  "T_NEW", "T_NEWLINE", "T_OP", "T_OR", "T_PASS", "T_PATCH", "T_PRIMITIVE",
  "T_OBJECT", "T_RBRACKET", "T_RARR", "T_STRING", "T_USE", "T_WHITESPACE",
  "T_LEFT_BINARY_OP", "T_RETURN", "T_SEMICOLON", "T_WHILE", "T_SELF",
  "T_BANG", "T_HASH", "T_DOTDOTDOT", "T_LARR_EQ", "T_LT", "T_RARR_EQ",
  "T_GT", "T_EQ_EQ", "T_PLUS", "T_MINUS", "T_DIV", "T_MUL", "T_MODULO",
  "T_MUL_MUL", "T_PLUS_PLUS", "T_MINUS_MINUS", "$accept", "input", "use",
  "use_file", "metadata", "class_declaration", "class_members",
  "function_name", "function_declaration",
  "function_declaration_parameter_list", "function_declaration_parameter",
  "if", "while", "block", "statements", "statement", "compound_statement",
  "simple_statement", "return_statement", "members_declarations",
  "member_declaration", "type_name", "variable_assignment",
  "variable_declaration", "id", "qualified_id", "dot_expr", "expr",
  "bool_operator", "comp_operator", "math_operator", "binary_operator",
  "binary_expr", "expr_list", "call", "literal", 0
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
     305,   306,   307,   308,   309,   310
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    57,    57,    57,    57,    57,    57,    58,
      59,    59,    60,    61,    61,    62,    63,    63,    64,    64,
      64,    64,    65,    65,    65,    66,    67,    67,    68,    69,
      70,    70,    71,    71,    71,    72,    72,    73,    73,    73,
      74,    75,    75,    76,    77,    78,    79,    79,    79,    80,
      81,    81,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    84,    84,    85,    85,    85,    85,    85,    86,    86,
      86,    87,    87,    87,    88,    89,    89,    90,    90,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     3,     2,     2,     2,     2,
       1,     3,     3,     3,     5,     4,     1,     2,     6,     7,
       6,     7,     1,     3,     4,     3,     3,     5,     3,     4,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     2,     4,     1,     4,     4,     5,     6,     1,
       1,     3,     5,     1,     1,     1,     3,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     3,     4,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     4,    16,     3,     0,     0,     0,
       6,     0,     7,     0,     8,    49,     0,    10,     9,     5,
       0,    17,     0,     0,     0,    13,     0,    12,     0,     0,
      22,     0,     0,     0,    11,     0,     0,     0,     0,     0,
      41,     0,    14,     0,    50,    44,     0,    23,     0,    25,
      15,    42,     0,    18,    20,     0,    24,     0,     0,     0,
      51,    19,    21,    43,     0,     0,    79,     0,     0,     0,
       0,    35,    36,     0,    30,    34,    33,    39,    38,    37,
      50,    57,    54,     0,    55,    58,    53,    59,     0,    60,
       0,     0,     0,    29,    31,     0,     0,    61,     0,    32,
      62,    65,    64,    67,    66,    63,    68,    69,    70,    71,
      72,    73,     0,     0,    26,    56,    40,    28,     0,     0,
      77,    75,     0,     0,    74,     0,     0,     0,     0,    46,
       0,    78,    45,    27,    52,    47,     0,    76,    48
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    10,    18,    11,    12,    25,    13,    14,    29,
      30,    71,    72,    54,    73,    74,    75,    76,    77,    39,
      40,    43,    78,    79,    44,    81,    82,    83,   109,   110,
     111,   112,    84,   122,    85,    86
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -55
static const yytype_int16 yypact[] =
{
     -55,   214,   -55,    -8,   -55,   -55,   -55,    -5,   -18,    14,
     -55,    21,   -55,    23,   -55,   -55,   -21,   -55,    43,   -55,
      32,   -55,    37,    50,    -8,   -55,    54,   -55,    26,    42,
     -55,    27,    -8,    46,   -55,    -8,   -10,    44,    -8,    17,
     -55,    40,   -55,    65,   -55,    63,    -8,   -55,    -8,   -55,
     -55,   -55,    -8,    76,   -55,    -8,   -55,    79,    80,   222,
     -55,    76,   -55,   -55,    87,    87,   -55,    -8,    87,    87,
      87,   -55,   -55,   218,   -55,   -55,   -55,   -55,   -55,   -55,
      67,    -2,   -55,    36,   -55,   -55,   -55,   164,    49,   -55,
      81,    94,    49,   -55,   -55,    28,   249,   -55,    87,   -55,
     -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,
     -55,   -55,    87,    76,    96,    95,   -55,   -55,    87,     2,
     -55,   164,    55,   108,   164,    89,    -8,   139,    87,   -55,
      87,   -55,   -55,   -55,   -55,   -55,   153,   164,   -55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -55,   -55,   -55,   -55,   -55,   -55,    77,   -55,   -55,   -55,
      -9,   -55,   -55,   -54,   -55,    41,   -55,   -55,   -55,   -55,
      82,   -37,   -55,   -55,    -3,   -28,   -55,   -52,   -55,   -55,
     -55,   -55,   -55,   -55,   -55,   -55
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      16,    49,    23,    62,    15,    19,    15,    45,    55,    17,
      45,    57,    87,    88,   128,    58,    90,    91,    92,    31,
      45,    33,    96,    24,    45,   129,    50,    47,    20,    41,
      89,    15,    46,    31,   114,    21,    41,    56,   117,    45,
     118,    97,    15,    31,   121,    28,   123,    22,    98,    36,
      37,    15,    60,    26,    97,    27,    80,    35,   119,    99,
     124,   100,   130,   131,    38,    32,   127,    45,    34,    23,
      80,   133,   113,    55,   100,    48,   136,    52,   137,   101,
     102,   103,   104,   105,   106,   107,    97,   108,    53,   115,
      64,    59,   101,   102,   103,   104,   105,   106,   107,    97,
     108,    15,    61,    63,    95,   126,   100,   125,    66,    67,
      42,    68,   113,    97,    94,     0,     0,   116,     0,   100,
       0,    51,     0,   134,   101,   102,   103,   104,   105,   106,
     107,   132,   108,   100,     0,     0,     0,   101,   102,   103,
     104,   105,   106,   107,    97,   108,     0,     0,     0,     0,
       0,   101,   102,   103,   104,   105,   106,   107,    97,   108,
       0,     0,   135,     0,   100,     0,     0,     0,     0,    97,
       0,     0,     0,     0,     0,     0,   138,     0,   100,     0,
       0,     0,   101,   102,   103,   104,   105,   106,   107,   100,
     108,     0,     0,     0,     0,     0,   101,   102,   103,   104,
     105,   106,   107,     0,   108,     0,     0,   101,   102,   103,
     104,   105,   106,   107,     2,   108,     0,     0,     0,     0,
       3,    64,     0,     4,     0,    64,     0,    93,     5,     0,
       0,    65,    15,     0,     0,    65,    15,     6,     0,    66,
      67,     0,    68,    66,    67,     0,    68,     7,     8,     0,
       0,     0,    64,     0,    69,     9,    70,   120,    69,     0,
      70,     0,     0,    15,     0,     0,     0,     0,     0,     0,
      66,    67,     0,    68
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-55))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       3,    38,    23,    57,    14,    23,    14,    35,    10,    14,
      38,    48,    64,    65,    12,    52,    68,    69,    70,    22,
      48,    24,    24,    44,    52,    23,     9,    36,    14,    32,
      67,    14,    42,    36,    88,    14,    39,    46,    92,    67,
      12,     5,    14,    46,    96,     8,    98,    24,    12,     7,
       8,    14,    55,    10,     5,    23,    59,    31,    95,    23,
     112,    25,     7,     8,    37,    15,   118,    95,    14,    23,
      73,   125,    23,    10,    25,    31,   128,    37,   130,    43,
      44,    45,    46,    47,    48,    49,     5,    51,    23,     8,
       3,    15,    43,    44,    45,    46,    47,    48,    49,     5,
      51,    14,    23,    23,    37,    10,    25,    11,    21,    22,
      33,    24,    23,     5,    73,    -1,    -1,    23,    -1,    25,
      -1,    39,    -1,   126,    43,    44,    45,    46,    47,    48,
      49,    23,    51,    25,    -1,    -1,    -1,    43,    44,    45,
      46,    47,    48,    49,     5,    51,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    47,    48,    49,     5,    51,
      -1,    -1,    23,    -1,    25,    -1,    -1,    -1,    -1,     5,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    25,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    48,    49,    25,
      51,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,
      47,    48,    49,    -1,    51,    -1,    -1,    43,    44,    45,
      46,    47,    48,    49,     0,    51,    -1,    -1,    -1,    -1,
       6,     3,    -1,     9,    -1,     3,    -1,     9,    14,    -1,
      -1,    13,    14,    -1,    -1,    13,    14,    23,    -1,    21,
      22,    -1,    24,    21,    22,    -1,    24,    33,    34,    -1,
      -1,    -1,     3,    -1,    36,    41,    38,     8,    36,    -1,
      38,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    22,    -1,    24
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    57,     0,     6,     9,    14,    23,    33,    34,    41,
      58,    60,    61,    63,    64,    14,    80,    14,    59,    23,
      14,    14,    24,    23,    44,    62,    10,    23,     8,    65,
      66,    80,    15,    80,    14,    31,     7,     8,    37,    75,
      76,    80,    62,    77,    80,    81,    42,    66,    31,    77,
       9,    76,    37,    23,    69,    10,    66,    77,    77,    15,
      80,    23,    69,    23,     3,    13,    21,    22,    24,    36,
      38,    67,    68,    70,    71,    72,    73,    74,    78,    79,
      80,    81,    82,    83,    88,    90,    91,    83,    83,    77,
      83,    83,    83,     9,    71,    37,    24,     5,    12,    23,
      25,    43,    44,    45,    46,    47,    48,    49,    51,    84,
      85,    86,    87,    23,    69,     8,    23,    69,    12,    77,
       8,    83,    89,    83,    83,    11,    10,    83,    12,    23,
       7,     8,    23,    69,    80,    23,    83,    83,    23
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (fm, ast, symbols, logger, file, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


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
		  Type, Value, Location, fm, ast, symbols, logger, file); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger* logger, mem::fs::File* file)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, fm, ast, symbols, logger, file)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    mem::fs::FileManager& fm;
    mem::ast::node::Node* ast;
    mem::st::SymbolTable& symbols;
    mem::log::Logger* logger;
    mem::fs::File* file;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (fm);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger* logger, mem::fs::File* file)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, fm, ast, symbols, logger, file)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    mem::fs::FileManager& fm;
    mem::ast::node::Node* ast;
    mem::st::SymbolTable& symbols;
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
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, fm, ast, symbols, logger, file);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger* logger, mem::fs::File* file)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, fm, ast, symbols, logger, file)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    mem::fs::FileManager& fm;
    mem::ast::node::Node* ast;
    mem::st::SymbolTable& symbols;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , fm, ast, symbols, logger, file);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, fm, ast, symbols, logger, file); \
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger* logger, mem::fs::File* file)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, fm, ast, symbols, logger, file)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    mem::fs::FileManager& fm;
    mem::ast::node::Node* ast;
    mem::st::SymbolTable& symbols;
    mem::log::Logger* logger;
    mem::fs::File* file;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (fm);
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


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger* logger, mem::fs::File* file);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

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
yyparse (mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger* logger, mem::fs::File* file)
#else
int
yyparse (fm, ast, symbols, logger, file)
    mem::fs::FileManager& fm;
    mem::ast::node::Node* ast;
    mem::st::SymbolTable& symbols;
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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
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
  *++yyvsp = yylval;
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
        case 6:

/* Line 1806 of yacc.c  */
#line 194 "Bison.y"
    {
      ast->pushChild((yyvsp[(2) - (2)].text_node));
   }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 198 "Bison.y"
    {
      ast->pushChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 202 "Bison.y"
    {
      ast->pushChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 209 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Use();
      (yyval.text_node)->sValue((yyvsp[(2) - (2)].text_node)->gValue());
      (yyval.text_node)->setPosition(new fs::position::Range((yylsp[(1) - (2)]), (yylsp[(2) - (2)])));
      delete (yyvsp[(2) - (2)].text_node);
   }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 218 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->sValue((yyvsp[(1) - (1)].text));
   }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 223 "Bison.y"
    {
      (yyval.text_node)->sValue((yyval.text_node)->gValue() + '.' + (yyvsp[(3) - (3)].text));
   }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 229 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->sValue((yyvsp[(2) - (3)].text), strlen((yyvsp[(2) - (3)].text)));
   }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 240 "Bison.y"
    {
      ast::node::Class* cls = new ast::node::Class();

      cls->sValue((yyvsp[(2) - (3)].text_node)->_value);
      cls->eat((yyvsp[(3) - (3)].node));
      cls->setPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(3) - (3)])));
      delete (yyvsp[(2) - (3)].text_node);
      delete (yyvsp[(3) - (3)].node);
      (yyval.node) = cls;
   }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 251 "Bison.y"
    {
      ast::node::Class* cls = new ast::node::Class();

      cls->sValue((yyvsp[(2) - (5)].text_node)->_value);
      cls->eat((yyvsp[(5) - (5)].node));
      cls->pushChild((yyvsp[(4) - (5)].text_node));
      cls->setPosition(new fs::position::Range((yylsp[(1) - (5)]), (yylsp[(3) - (5)])));
      delete (yyvsp[(2) - (5)].text_node);
      delete (yyvsp[(5) - (5)].node);
      (yyval.node) = cls;
   }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 265 "Bison.y"
    {
      (yyval.node) = new ast::node::Block();
      (yyval.node)->setPosition(new fs::position::Range((yylsp[(3) - (4)]), (yylsp[(3) - (4)])));
      (yyval.node)->eat((yyvsp[(3) - (4)].node));
      delete (yyvsp[(3) - (4)].node);
   }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 279 "Bison.y"
    {
      ast::node::Func* func = new ast::node::Func();
      func->sValue((yyvsp[(1) - (1)].text), strlen((yyvsp[(1) - (1)].text)));
      (yyval.node) = func;

      free((yyvsp[(1) - (1)].text));
   }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 287 "Bison.y"
    {
      Metadata* md = new Metadata();
      md->set((yyvsp[(1) - (2)].text_node)->gValue(), "");

      ast::node::Func* func = new ast::node::Func();
      func->sValue((yyvsp[(2) - (2)].text), strlen((yyvsp[(2) - (2)].text)));
      func->setMetadata(md);
      (yyval.node) = func;

      delete (yyvsp[(1) - (2)].text_node);
   }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 307 "Bison.y"
    {
      ast::node::Func* n = static_cast<ast::node::Func*>((yyvsp[(1) - (6)].node));
      n->pushChild((yyvsp[(5) - (6)].node));
      n->setPosition((yyloc).copy_range());
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 316 "Bison.y"
    {
      (yyvsp[(3) - (7)].node)->setPosition(new fs::position::Range(
         *((yyvsp[(3) - (7)].node)->getChild(0)->_position),
         *((yyvsp[(3) - (7)].node)->getChild((yyvsp[(3) - (7)].node)->_child_count-1)->_position)));

      ast::node::Func* n = static_cast<ast::node::Func*>((yyvsp[(1) - (7)].node));
      n->pushChildren((yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node));
      n->setPosition((yyloc).copy_range());
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 332 "Bison.y"
    {
      ast::node::Func* n = static_cast<ast::node::Func*>((yyvsp[(1) - (6)].node));
      n->pushChildren((yyvsp[(5) - (6)].node), (yyvsp[(6) - (6)].node));
      n->setPosition((yyloc).copy_range());
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 340 "Bison.y"
    {
      (yyvsp[(3) - (7)].node)->setPosition(new fs::position::Range(
         *((yyvsp[(3) - (7)].node)->getChild(0)->_position),
         *((yyvsp[(3) - (7)].node)->getChild((yyvsp[(3) - (7)].node)->_child_count-1)->_position)));

      ast::node::Func* n = static_cast<ast::node::Func*>((yyvsp[(1) - (7)].node));
      n->pushChildren((yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node), (yyvsp[(7) - (7)].node));
      n->setPosition((yyloc).copy_range());
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 354 "Bison.y"
    {
      (yyval.node) = new ast::node::Node();
      (yyval.node)->setKind(ast::node::Kind::FUNCTION_PARAMETERS);
      (yyval.node)->pushChild((yyvsp[(1) - (1)].node));
   }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 360 "Bison.y"
    {
      (yyval.node)->pushChild((yyvsp[(3) - (3)].node));
   }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 364 "Bison.y"
    {
      (yyval.node)->pushChild((yyvsp[(4) - (4)].node));
   }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 370 "Bison.y"
    {
      (yyval.node) = new ast::node::Node();
      (yyval.node)->setKind(ast::node::Kind::FUNCTION_PARAMETERS);
      (yyval.node)->pushChildren((yyvsp[(1) - (3)].text_node), (yyvsp[(3) - (3)].node));
      (yyval.node)->setPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(3) - (3)])));
   }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 386 "Bison.y"
    {
      (yyval.node) = new ast::node::If();
      (yyval.node)->pushChildren((yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));
      (yyval.node)->setPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(2) - (3)])));
   }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 395 "Bison.y"
    {
      (yyval.node) = new ast::node::If();
      (yyval.node)->pushChildren((yyvsp[(2) - (5)].node), (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
      (yyval.node)->setPosition(new fs::position::Range((yylsp[(1) - (5)]), (yylsp[(5) - (5)])));
   }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 403 "Bison.y"
    {
      (yyval.node) = new ast::node::While();
      (yyval.node)->pushChildren((yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));
      (yyval.node)->setPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(3) - (3)])));
   }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 411 "Bison.y"
    {
      (yyval.node) = new ast::node::Block();
      (yyval.node)->setPosition(new fs::position::Range((yylsp[(3) - (4)]), (yylsp[(3) - (4)])));
      (yyval.node)->eat((yyvsp[(3) - (4)].node));
      delete (yyvsp[(3) - (4)].node);
   }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 420 "Bison.y"
    {
      assert ((yyvsp[(1) - (1)].node) != NULL);
      (yyval.node) = new ast::node::Node();
      (yyval.node)->pushChild((yyvsp[(1) - (1)].node));
   }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 426 "Bison.y"
    {
      if ((yyval.node) == 0)
      {
         (yyval.node) = new ast::node::Node();
      }
      (yyval.node)->pushChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 436 "Bison.y"
    {
      (yyval.node) = (yyvsp[(1) - (2)].node);
   }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 440 "Bison.y"
    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
   }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 444 "Bison.y"
    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
   }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 459 "Bison.y"
    {
      (yyval.node) = new ast::node::Return();
      (yyval.node)->pushChild((yyvsp[(2) - (3)].node));
   }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 467 "Bison.y"
    {
      (yyval.node) = new ast::node::Node();
      (yyval.node)->pushChild((yyvsp[(1) - (1)].node));
   }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 472 "Bison.y"
    {
      (yyval.node)->pushChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 479 "Bison.y"
    {
      ast::node::Field* field = new ast::node::Field();
      field->setPosition((yyloc).copy_range());
      field->pushChildren((yyvsp[(1) - (4)].text_node), (yyvsp[(3) - (4)].node));

      (yyval.node) = (ast::node::Node*)field;
   }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 489 "Bison.y"
    {
      (yyval.node) = static_cast<ast::node::Node*>((yyvsp[(1) - (1)].node));
   }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 495 "Bison.y"
    {
      ast::node::VarAssign* n = new ast::node::VarAssign();
      n->setPosition((yyloc).copy_range());
      n->pushChildren((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 505 "Bison.y"
    {
      ast::node::VarDecl* n = new ast::node::VarDecl();
      n->setPosition((yyloc).copy_range());
      n->pushChildren((yyvsp[(1) - (4)].text_node), (yyvsp[(3) - (4)].node));
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 513 "Bison.y"
    {
      ast::node::Node* ty_place_holder = new ast::node::Node();
      ty_place_holder->setKind(ast::node::Kind::PLACE_HOLDER);
      ty_place_holder->setPosition((yylsp[(3) - (5)]).copy_range());

      ast::node::VarDecl* n = new ast::node::VarDecl();
      n->pushChildren((yyvsp[(1) - (5)].text_node), ty_place_holder, (yyvsp[(4) - (5)].node));
      n->setPosition((yyloc).copy_range());
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 525 "Bison.y"
    {
      ast::node::VarDecl* n = new ast::node::VarDecl();
      n->setPosition((yyloc).copy_range());
      n->pushChildren((yyvsp[(1) - (6)].text_node), (yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].node));
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 534 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->setKind(ast::node::Kind::ID);
      (yyval.text_node)->setPosition((yyloc).copy_range());
      (yyval.text_node)->sValue((yyvsp[(1) - (1)].text), strlen((yyvsp[(1) - (1)].text)));

      free((yyvsp[(1) - (1)].text));
   }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 545 "Bison.y"
    {
      ast::node::FinalId* n = new ast::node::FinalId();
      n->sValue((yyvsp[(1) - (1)].text_node)->gValue());
      delete (yyvsp[(1) - (1)].text_node);
      (yyval.node) = static_cast<ast::node::Text*>(n);
   }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 552 "Bison.y"
    {
      (yyval.node) = new ast::node::Dot();
      (yyval.node)->pushChildren((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].text_node));
      (yyval.node)->setPosition((yyloc).copy_range());
   }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 560 "Bison.y"
    {
      (yyval.node) = new ast::node::Dot();
      (yyval.node)->setPosition((yyloc).copy_range());
      (yyval.node)->pushChildren((yyvsp[(2) - (5)].node), (yyvsp[(5) - (5)].text_node));
   }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 568 "Bison.y"
    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
   }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 572 "Bison.y"
    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
   }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 576 "Bison.y"
    {
      (yyval.node) = (ast::node::Node*)(yyvsp[(1) - (1)].node);
   }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 581 "Bison.y"
    {
      (yyval.node) = new ast::node::Node();
      (yyval.node)->setKind(ast::node::Kind::GROUP);
      (yyval.node)->pushChild((yyvsp[(2) - (3)].node));
   }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 587 "Bison.y"
    {
      (yyval.node) = static_cast<ast::node::Node*>((yyvsp[(1) - (1)].node));
   }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 591 "Bison.y"
    {
      (yyval.node) = (ast::node::Node*)(yyvsp[(1) - (1)].node);
   }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 595 "Bison.y"
    {
      (yyval.node) = new ast::node::Node();
      (yyval.node)->setKind(ast::node::Kind::AMPERSAND);
      (yyval.node)->pushChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 601 "Bison.y"
    {
      (yyval.node) = new ast::node::New();
      (yyval.node)->setPosition((yyloc).copy_range());
      (yyval.node)->pushChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 609 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->setKind(ast::node::Kind::OP_AND);
   }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 614 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->setKind(ast::node::Kind::OP_OR);
   }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 622 "Bison.y"
    {
      ast::node::BinaryOp* op = new ast::node::BinaryOp();
      op->setKind(ast::node::Kind::OP_EQ_EQ);
      (yyval.text_node) = static_cast<ast::node::Text*>(op);

   }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 630 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Text();
   }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 635 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Text();
   }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 640 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Text();
   }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 645 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Text();
   }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 652 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->setKind(ast::node::Kind::OP_PLUS);
   }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 657 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->setKind(ast::node::Kind::OP_MINUS);
   }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 662 "Bison.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->setKind(ast::node::Kind::OP_MUL);
   }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 672 "Bison.y"
    {
      (yyvsp[(2) - (3)].text_node)->pushChildren((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      (yyvsp[(2) - (3)].text_node)->setPosition((yyloc).copy_range());
      (yyval.node) = (yyvsp[(2) - (3)].text_node);
   }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 681 "Bison.y"
    {
      (yyval.node) = new ast::node::Node();
      (yyval.node)->setKind(ast::node::Kind::EXPRESSION_LIST);
      (yyval.node)->pushChild((yyvsp[(1) - (1)].node));
   }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 687 "Bison.y"
    {
      if ((yyval.node) == 0)
      {
         (yyval.node) = new ast::node::Node();
         (yyval.node)->setKind(ast::node::Kind::EXPRESSION_LIST);
      }
      (yyval.node)->pushChild((yyvsp[(3) - (3)].node));
   }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 699 "Bison.y"
    {
      (yyval.node) = new ast::node::Call();
      (yyval.node)->setPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(3) - (3)])));
      (yyval.node)->pushChild((yyvsp[(1) - (3)].node));
   }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 706 "Bison.y"
    {
      (yyvsp[(3) - (4)].node)->setPosition((yylsp[(3) - (4)]).copy_range());
      (yyval.node) = new ast::node::Call();
      (yyval.node)->setPosition(new fs::position::Range((yylsp[(1) - (4)]), (yylsp[(4) - (4)])));
      (yyval.node)->pushChildren((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
   }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 715 "Bison.y"
    {
      char c_val = 0;
      short s_val = 0;
      int i_val = 0;

      size_t nb_len = strlen((yyvsp[(1) - (1)].text));
      char int_ty = (yyvsp[(1) - (1)].text)[nb_len-1];
      char sign_ty = (yyvsp[(1) - (1)].text)[nb_len-2];
      if (sign_ty != 'u') nb_len--;

      char* nb = static_cast<char*>(malloc(sizeof(char) * nb_len + 1));
      strncpy(nb, (yyvsp[(1) - (1)].text), nb_len);
      nb[nb_len] = '\0';

      switch (int_ty)
      {
         case 'c':
            if (mem::number::getCharFromString(nb, c_val))
            {
               ast::node::Number* s_node = new ast::node::Number();
               s_node->setChar(c_val);
               s_node->setExprType(symbols._core_types.gCharTy());
               (yyval.node) = s_node;
            }
            break;

         case 's':
            if (mem::number::getShortFromString(nb, s_val))
            {
               ast::node::Number* s_node = new ast::node::Number();
               s_node->setShort(s_val);
               s_node->setExprType(symbols._core_types.gShortTy());
               (yyval.node) = s_node;
            }
            break;

         case 'i':
            if (mem::number::getIntFromString(nb, i_val))
            {
               ast::node::Number* i_node = new ast::node::Number();
               i_node->setInt(i_val);
               i_node->setExprType(symbols._core_types.gIntTy());
               (yyval.node) = i_node;
            }
            break;

         defaut:
            printf("Strange number in source");
            assert(false);
      }

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
      free(nb);
      free((yyvsp[(1) - (1)].text));
   }
    break;



/* Line 1806 of yacc.c  */
#line 2617 "src/mem/lang/Bison.c"
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
      yyerror (fm, ast, symbols, logger, file, YY_("syntax error"));
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
        yyerror (fm, ast, symbols, logger, file, yymsgp);
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
		      yytoken, &yylval, &yylloc, fm, ast, symbols, logger, file);
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
		  yystos[yystate], yyvsp, yylsp, fm, ast, symbols, logger, file);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (fm, ast, symbols, logger, file, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, fm, ast, symbols, logger, file);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, fm, ast, symbols, logger, file);
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



/* Line 2067 of yacc.c  */
#line 780 "Bison.y"


#include "mem/ast/node/Node.hpp"

