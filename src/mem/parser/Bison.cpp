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
#line 71 "src/mem/parser/Bison.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
# define YYTOKEN_TABLE 1
#endif

/* "%code requires" blocks.  */

/* Line 288 of yacc.c  */
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
#line 76 "src/mem/grammar/mem.y"




/* Line 288 of yacc.c  */
#line 154 "src/mem/parser/Bison.cpp"

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

/* Line 293 of yacc.c  */
#line 79 "src/mem/grammar/mem.y"

   int integer;
   char* text;
   ast::node::Node* binary_node;
   ast::node::Node* node;
   ast::node::Text* text_node;



/* Line 293 of yacc.c  */
#line 230 "src/mem/parser/Bison.cpp"
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
#line 255 "src/mem/parser/Bison.cpp"
/* Unqualified %code blocks.  */

/* Line 344 of yacc.c  */
#line 59 "src/mem/grammar/mem.y"

extern int yylex();

void yyerror(fs::FileManager& fm, ast::node::Node* ast, st::SymbolTable& symbols, log::Logger& logger, fs::File* file, const char *s)
{
   fs::position::Position* pos = new fs::position::Position();
   pos->sFile(file);

   log::Message* msg = new log::Error();
   msg->sMessage("Syntax error");
   msg->sDescription(s);
   msg->sPosition(pos);
   logger.log(msg);
}


/* Line 344 of yacc.c  */
#line 87 "src/mem/grammar/mem.y"




/* Line 344 of yacc.c  */
#line 283 "src/mem/parser/Bison.cpp"

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
#define YYLAST   231

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

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
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    14,    17,    20,    24,
      29,    31,    35,    41,    45,    51,    55,    60,    62,    65,
      68,    70,    72,    74,    76,    78,    80,    83,    85,    87,
      90,    92,    95,    97,    99,   106,   114,   121,   129,   134,
     136,   140,   144,   146,   151,   157,   164,   166,   168,   172,
     176,   178,   180,   182,   184,   188,   190,   192,   194,   196,
     198,   200,   202,   204,   206,   208,   210,   212,   214,   216,
     218,   220,   224,   227,   229,   233,   237,   242
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    -1,    51,    20,    -1,    51,     7,    -1,
      51,    30,    20,    -1,    51,    52,    -1,    51,    54,    -1,
      29,    12,    20,    -1,    20,    13,    65,     7,    -1,    55,
      -1,     4,    73,    53,    -1,     4,    73,    38,    73,    53,
      -1,    11,    76,    58,    -1,    11,    76,    58,     9,    58,
      -1,    34,    76,    58,    -1,    20,    13,    59,     7,    -1,
      60,    -1,    59,    60,    -1,    76,    20,    -1,    62,    -1,
      61,    -1,    56,    -1,    57,    -1,    72,    -1,    63,    -1,
      32,    76,    -1,    68,    -1,    67,    -1,    22,    20,    -1,
      64,    -1,    65,    64,    -1,    12,    -1,    28,    -1,    66,
      21,     6,    27,    71,    20,    -1,    66,    21,    69,     6,
      27,    71,    20,    -1,    66,    21,     6,    27,    71,    58,
      -1,    66,    21,    69,     6,    27,    71,    58,    -1,    73,
      33,    71,    20,    -1,    70,    -1,    69,     5,    70,    -1,
      73,    33,    71,    -1,    74,    -1,    73,    33,    71,    20,
      -1,    73,    33,    10,    76,    20,    -1,    73,    33,    71,
      10,    76,    20,    -1,    12,    -1,    73,    -1,    74,     8,
      73,    -1,    76,     8,    73,    -1,    83,    -1,    75,    -1,
      79,    -1,    80,    -1,    21,    76,     6,    -1,    74,    -1,
      82,    -1,    44,    -1,    41,    -1,    38,    -1,    37,    -1,
      43,    -1,    46,    -1,    45,    -1,    47,    -1,    42,    -1,
      40,    -1,    39,    -1,    36,    -1,    49,    -1,    48,    -1,
      76,    77,    76,    -1,    78,    76,    -1,    76,    -1,    81,
       5,    76,    -1,    76,    21,     6,    -1,    76,    21,    81,
       6,    -1,    18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   170,   170,   172,   173,   174,   175,   179,   186,   200,
     208,   211,   222,   242,   248,   256,   264,   273,   278,   288,
     292,   296,   302,   303,   306,   307,   310,   317,   318,   319,
     325,   330,   336,   337,   342,   354,   369,   380,   396,   406,
     411,   417,   425,   432,   440,   450,   459,   469,   473,   481,
     489,   493,   497,   501,   506,   511,   515,   521,   526,   531,
     536,   541,   546,   551,   556,   561,   566,   571,   578,   583,
     588,   595,   605,   615,   620,   631,   638,   647
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_AROBASE", "T_CLASS", "T_COMMA",
  "T_CP", "T_DEDENT", "T_DOT", "T_ELSE", "T_EQ", "T_IF", "T_ID",
  "T_INDENT", "T_INTERFACE", "T_LBRACKET", "T_LITERAL_FLOAT",
  "T_LITERAL_HEX", "T_LITERAL_INT", "T_NEW", "T_NEWLINE", "T_OP", "T_PASS",
  "T_PATCH", "T_PRIMITIVE", "T_OBJECT", "T_RBRACKET", "T_RARR", "T_STRING",
  "T_USE", "T_WHITESPACE", "T_LEFT_BINARY_OP", "T_RETURN", "T_SEMICOLON",
  "T_WHILE", "T_SELF", "T_BANG", "T_LARR_EQ", "T_LT", "T_RARR_EQ", "T_GT",
  "T_EQ_EQ", "T_PLUS", "T_MINUS", "T_DIV", "T_MUL", "T_MODULO",
  "T_MUL_MUL", "T_PLUS_PLUS", "T_MINUS_MINUS", "$accept", "input", "use",
  "type_block", "type_declaration", "class_declaration", "if", "while",
  "block", "statements", "statement", "compound_statement",
  "simple_statement", "return_statement", "top_level_statement",
  "top_level_statements", "function_name", "function_declaration",
  "member_declaration", "function_declaration_parameter_list",
  "function_declaration_parameter", "type_name", "variable_declaration",
  "id", "qualified_id", "dot_expr", "expr", "binary_operator",
  "left_unary_operator", "binary_expr", "left_unary_expr", "expr_list",
  "call", "literal", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    51,    51,    51,    51,    51,    52,    53,
      54,    55,    55,    56,    56,    57,    58,    59,    59,    60,
      60,    60,    61,    61,    62,    62,    63,    64,    64,    64,
      65,    65,    66,    66,    67,    67,    67,    67,    68,    69,
      69,    70,    71,    72,    72,    72,    73,    74,    74,    75,
      76,    76,    76,    76,    76,    76,    76,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    78,    78,
      78,    79,    80,    81,    81,    82,    82,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     3,     2,     2,     3,     4,
       1,     3,     5,     3,     5,     3,     4,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     2,
       1,     2,     1,     1,     6,     7,     6,     7,     4,     1,
       3,     3,     1,     4,     5,     6,     1,     1,     3,     3,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     1,     3,     3,     4,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     4,     3,     0,     0,     6,     7,
      10,    46,     0,     0,     5,     0,     0,    11,     8,     0,
       0,    32,     0,    33,    30,     0,     0,    28,    27,     0,
      12,    29,     9,    31,     0,     0,     0,     0,    39,     0,
       0,    47,    42,     0,     0,     0,     0,    38,     0,     0,
      40,     0,    41,    48,    34,    36,     0,     0,    35,    37,
       0,    77,     0,     0,     0,    68,    70,    69,    22,    23,
       0,    17,    21,    20,    25,    24,    47,    55,    51,     0,
       0,    52,    53,    56,    50,     0,     0,    26,     0,    16,
      18,     0,     0,    19,     0,    60,    59,    67,    66,    58,
      65,    61,    57,    63,    62,    64,     0,    72,     0,    13,
      54,    15,     0,     0,    49,    75,    73,     0,    71,     0,
       0,     0,    43,     0,    76,    14,    44,     0,    74,    45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     8,    17,     9,    10,    68,    69,    55,    70,
      71,    72,    73,    74,    24,    25,    26,    27,    28,    37,
      38,    40,    75,    41,    77,    78,    79,   106,    80,    81,
      82,   117,    83,    84
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -60
static const yytype_int16 yypact[] =
{
     -60,     8,   -60,   -10,   -60,   -60,    -6,     3,   -60,   -60,
     -60,   -60,    52,     7,   -60,    33,   -10,   -60,   -60,    70,
      23,   -23,    31,   -60,   -60,    22,    55,   -60,   -60,    47,
     -60,   -60,   -60,   -60,    20,   -10,    64,    69,   -60,    66,
      77,   -60,   118,   -10,   -10,   100,   -10,   -60,   -10,   108,
     -60,   -10,   -60,   -60,   116,   -60,   110,   182,   116,   -60,
      37,   -60,    37,    37,    37,   -60,   -60,   -60,   -60,   -60,
      45,   -60,   -60,   -60,   -60,   -60,    98,   118,   -60,    75,
      37,   -60,   -60,   -60,   -60,   103,    63,   145,   103,   -60,
     -60,    30,   -10,   -60,    12,   -60,   -60,   -60,   -60,   -60,
     -60,   -60,   -60,   -60,   -60,   -60,    37,   145,   116,   123,
     -60,   -60,    37,    58,   -60,   -60,   145,    82,   145,   113,
     117,    37,   -60,    37,   -60,   -60,   -60,   131,   145,   -60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -60,   -60,   -60,   114,   -60,   -60,   -60,   -60,   -49,   -60,
      65,   -60,   -60,   -60,   111,   -60,   -60,   -60,   -60,   -60,
     121,   -32,   -60,    -3,   -26,   -60,   -59,   -60,   -60,   -60,
     -60,   -60,   -60,   -60
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -47
static const yytype_int16 yytable[] =
{
      12,    85,    11,    86,    87,    88,    13,    59,     2,    42,
     -46,    49,     3,    20,    52,     4,    29,    42,   115,    56,
      42,   107,    29,    14,    11,    42,    36,    18,     5,    32,
      61,    39,    11,    62,    21,   116,   109,     6,     7,   111,
     112,    39,    11,    15,    22,    53,    19,   118,    65,    11,
      23,    31,    89,   120,    76,    61,    60,    11,    62,   113,
      66,    67,   127,    61,   128,    42,    62,    76,   121,   110,
     125,    92,    15,    65,    44,    45,    34,    63,   122,    64,
      35,    65,    21,    92,    94,    66,    67,   123,   124,   114,
      16,    43,    22,    66,    67,    93,    94,    47,    23,    46,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,    92,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   108,    94,    92,    48,    51,    54,    57,
      58,    91,   119,   108,    30,    90,    33,   126,    94,    92,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   129,    94,    92,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,    50,    94,     0,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,     0,
       0,     0,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,    60,    11,     0,     0,     0,     0,     0,
      61,     0,     0,    62,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    63,     0,    64,     0,    65,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      66,    67
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-60))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       3,    60,    12,    62,    63,    64,    12,    56,     0,    35,
      33,    43,     4,    16,    46,     7,    19,    43,     6,    51,
      46,    80,    25,    20,    12,    51,     6,    20,    20,     7,
      18,    34,    12,    21,    12,    94,    85,    29,    30,    88,
      10,    44,    12,    20,    22,    48,    13,   106,    36,    12,
      28,    20,     7,   112,    57,    18,    11,    12,    21,    91,
      48,    49,   121,    18,   123,    91,    21,    70,    10,     6,
     119,     8,    20,    36,     5,     6,    21,    32,    20,    34,
      33,    36,    12,     8,    21,    48,    49,     5,     6,    92,
      38,    27,    22,    48,    49,    20,    21,    20,    28,    33,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,     8,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    20,    21,     8,     8,    27,    20,    13,
      20,    33,     9,    20,    20,    70,    25,    20,    21,     8,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    20,    21,     8,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    44,    21,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    11,    12,    -1,    -1,    -1,    -1,    -1,
      18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    34,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    51,     0,     4,     7,    20,    29,    30,    52,    54,
      55,    12,    73,    12,    20,    20,    38,    53,    20,    13,
      73,    12,    22,    28,    64,    65,    66,    67,    68,    73,
      53,    20,     7,    64,    21,    33,     6,    69,    70,    73,
      71,    73,    74,    27,     5,     6,    33,    20,     8,    71,
      70,    27,    71,    73,    20,    58,    71,    13,    20,    58,
      11,    18,    21,    32,    34,    36,    48,    49,    56,    57,
      59,    60,    61,    62,    63,    72,    73,    74,    75,    76,
      78,    79,    80,    82,    83,    76,    76,    76,    76,     7,
      60,    33,     8,    20,    21,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    77,    76,    20,    58,
       6,    58,    10,    71,    73,     6,    76,    81,    76,     9,
      76,    10,    20,     5,     6,    58,    20,    76,    76,    20
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger& logger, mem::fs::File* file)
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
    mem::log::Logger& logger;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger& logger, mem::fs::File* file)
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
    mem::log::Logger& logger;
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger& logger, mem::fs::File* file)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, fm, ast, symbols, logger, file)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    mem::fs::FileManager& fm;
    mem::ast::node::Node* ast;
    mem::st::SymbolTable& symbols;
    mem::log::Logger& logger;
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger& logger, mem::fs::File* file)
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
    mem::log::Logger& logger;
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
int yyparse (mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger& logger, mem::fs::File* file);
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
yyparse (mem::fs::FileManager& fm, mem::ast::node::Node* ast, mem::st::SymbolTable& symbols, mem::log::Logger& logger, mem::fs::File* file)
#else
int
yyparse (fm, ast, symbols, logger, file)
    mem::fs::FileManager& fm;
    mem::ast::node::Node* ast;
    mem::st::SymbolTable& symbols;
    mem::log::Logger& logger;
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
#line 176 "src/mem/grammar/mem.y"
    {
      ast->pushChild((yyvsp[(2) - (2)].text_node));
   }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 180 "src/mem/grammar/mem.y"
    {
      ast->pushChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 187 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Use();
      (yyval.text_node)->sValue((yyvsp[(2) - (3)].text), strlen((yyvsp[(2) - (3)].text)));
      (yyval.text_node)->sPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(3) - (3)])));
      free((yyvsp[(2) - (3)].text));
   }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 201 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Block();
      (yyval.node)->eat((yyvsp[(3) - (4)].node));
      delete (yyvsp[(3) - (4)].node);
   }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 212 "src/mem/grammar/mem.y"
    {
      ast::node::Class* cls = new ast::node::Class();

      cls->sValue((yyvsp[(2) - (3)].text_node)->_value);
      cls->eat((yyvsp[(3) - (3)].node));
      cls->sPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(3) - (3)])));
      delete (yyvsp[(2) - (3)].text_node);
      delete (yyvsp[(3) - (3)].node);
      (yyval.node) = cls;
   }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 223 "src/mem/grammar/mem.y"
    {
      ast::node::Class* cls = new ast::node::Class();

      cls->sValue((yyvsp[(2) - (5)].text_node)->_value);
      cls->eat((yyvsp[(5) - (5)].node));
      cls->pushChild((yyvsp[(4) - (5)].text_node));
      cls->sPosition(new fs::position::Range((yylsp[(1) - (5)]), (yylsp[(3) - (5)])));
      delete (yyvsp[(2) - (5)].text_node);
      delete (yyvsp[(5) - (5)].node);
      (yyval.node) = cls;
   }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 243 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Node(MEM_NODE_IF);
      (yyval.node)->pushChildren((yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));
      (yyval.node)->sPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(2) - (3)])));
   }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 249 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Node(MEM_NODE_IF_ELSE);
      (yyval.node)->pushChildren((yyvsp[(2) - (5)].node), (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
      (yyval.node)->sPosition(new fs::position::Range((yylsp[(1) - (5)]), (yylsp[(5) - (5)])));
   }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 257 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Node(MEM_NODE_WHILE);
      (yyval.node)->pushChildren((yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));
      (yyval.node)->sPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(3) - (3)])));
   }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 265 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Block();
      (yyval.node)->sPosition(new fs::position::Range((yylsp[(3) - (4)]), (yylsp[(3) - (4)])));
      (yyval.node)->eat((yyvsp[(3) - (4)].node));
      delete (yyvsp[(3) - (4)].node);
   }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 274 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Node();
      (yyval.node)->pushChild((yyvsp[(1) - (1)].node));
   }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 279 "src/mem/grammar/mem.y"
    {
      if ((yyval.node) == 0)
      {
         (yyval.node) = new ast::node::Node();
      }
      (yyval.node)->pushChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 289 "src/mem/grammar/mem.y"
    {
      (yyval.node) = (yyvsp[(1) - (2)].node);
   }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 293 "src/mem/grammar/mem.y"
    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
   }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 297 "src/mem/grammar/mem.y"
    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
   }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 311 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Node(MEM_NODE_RETURN);
      (yyval.node)->pushChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 320 "src/mem/grammar/mem.y"
    {
      (yyval.node) = NULL;
   }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 326 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Node();
      (yyval.node)->pushChild((yyvsp[(1) - (1)].node));
   }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 331 "src/mem/grammar/mem.y"
    {
      (yyval.node)->pushChild((yyvsp[(2) - (2)].node));
   }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 343 "src/mem/grammar/mem.y"
    {
      ast::node::Func* n = new ast::node::Func();
      n->sValue((yyvsp[(1) - (6)].text), strlen((yyvsp[(1) - (6)].text)));
      n->pushChild((yyvsp[(5) - (6)].node));
      n->sPosition((yyloc).copy_range());
      (yyval.node) = (ast::node::Node*)n;

      free((yyvsp[(1) - (6)].text));
   }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 355 "src/mem/grammar/mem.y"
    {
      (yyvsp[(3) - (7)].node)->sPosition(new fs::position::Range(
         *((yyvsp[(3) - (7)].node)->getChild(0)->_position),
         *((yyvsp[(3) - (7)].node)->getChild((yyvsp[(3) - (7)].node)->_child_count-1)->_position)));

      ast::node::Func* n = new ast::node::Func();
      n->sValue((yyvsp[(1) - (7)].text), strlen((yyvsp[(1) - (7)].text)));
      n->pushChildren((yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node));
      n->sPosition((yyloc).copy_range());
      (yyval.node) = (ast::node::Node*)n;

      free((yyvsp[(1) - (7)].text));
   }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 370 "src/mem/grammar/mem.y"
    {
      ast::node::Func* n = new ast::node::Func();
      n->sValue((yyvsp[(1) - (6)].text), strlen((yyvsp[(1) - (6)].text)));
      n->pushChildren((yyvsp[(5) - (6)].node), (yyvsp[(6) - (6)].node));
      n->sPosition((yyloc).copy_range());
      (yyval.node) = (ast::node::Node*)n;

      free((yyvsp[(1) - (6)].text));
   }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 381 "src/mem/grammar/mem.y"
    {
      (yyvsp[(3) - (7)].node)->sPosition(new fs::position::Range(
         *((yyvsp[(3) - (7)].node)->getChild(0)->_position),
         *((yyvsp[(3) - (7)].node)->getChild((yyvsp[(3) - (7)].node)->_child_count-1)->_position)));
      ast::node::Func* n = new ast::node::Func();
      n->sValue((yyvsp[(1) - (7)].text), strlen((yyvsp[(1) - (7)].text)));
      n->pushChildren((yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node), (yyvsp[(7) - (7)].node));
      n->sPosition((yyloc).copy_range());
      (yyval.node) = (ast::node::Node*)n;

      free((yyvsp[(1) - (7)].text));
   }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 397 "src/mem/grammar/mem.y"
    {
      ast::node::Field* field = new ast::node::Field();
      field->sPosition((yyloc).copy_range());
      field->pushChildren((yyvsp[(1) - (4)].text_node), (yyvsp[(3) - (4)].node));

      (yyval.node) = (ast::node::Node*)field;
   }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 407 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Node(MEM_NODE_FUNCTION_PARAMETERS);
      (yyval.node)->pushChild((yyvsp[(1) - (1)].node));
   }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 412 "src/mem/grammar/mem.y"
    {
      (yyval.node)->pushChild((yyvsp[(3) - (3)].node));
   }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 418 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Node(MEM_NODE_FUNCTION_PARAMETER);
      (yyval.node)->pushChildren((yyvsp[(1) - (3)].text_node), (yyvsp[(3) - (3)].node));
      (yyval.node)->sPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(3) - (3)])));
   }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 426 "src/mem/grammar/mem.y"
    {
      (yyval.node) = static_cast<ast::node::Node*>((yyvsp[(1) - (1)].binary_node));
   }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 433 "src/mem/grammar/mem.y"
    {
      ast::node::VarDecl* n = new ast::node::VarDecl();
      n->sPosition((yyloc).copy_range());
      n->pushChildren((yyvsp[(1) - (4)].text_node), (yyvsp[(3) - (4)].node));
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 441 "src/mem/grammar/mem.y"
    {
      ast::node::Text* type = new ast::node::Text(MEM_NODE_ID);
      type->sValue("$AUTO");

      ast::node::VarDecl* n = new ast::node::VarDecl();
      n->pushChildren((yyvsp[(1) - (5)].text_node), type, (yyvsp[(4) - (5)].node));
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 451 "src/mem/grammar/mem.y"
    {
      ast::node::VarDecl* n = new ast::node::VarDecl();
      n->sPosition((yyloc).copy_range());
      n->pushChildren((yyvsp[(1) - (6)].text_node), (yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].node));
      (yyval.node) = (ast::node::Node*)n;
   }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 460 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text(MEM_NODE_ID);
      (yyval.text_node)->sPosition((yyloc).copy_range());
      (yyval.text_node)->sValue((yyvsp[(1) - (1)].text), strlen((yyvsp[(1) - (1)].text)));

      free((yyvsp[(1) - (1)].text));
   }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 470 "src/mem/grammar/mem.y"
    {
      (yyval.binary_node)->_type = MEM_NODE_FINAL_ID;
   }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 474 "src/mem/grammar/mem.y"
    {
      (yyval.binary_node) = new ast::node::Text(MEM_NODE_DOT);
      (yyval.binary_node)->pushChildren((yyvsp[(1) - (3)].binary_node), (yyvsp[(3) - (3)].text_node));
      (yyval.binary_node)->sPosition((yyloc).copy_range());
   }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 482 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Node(MEM_NODE_DOT);
      (yyval.node)->sPosition((yyloc).copy_range());
      (yyval.node)->pushChildren((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].text_node));
   }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 490 "src/mem/grammar/mem.y"
    {
      (yyval.node) = (yyvsp[(1) - (1)].text_node);
   }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 494 "src/mem/grammar/mem.y"
    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
   }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 498 "src/mem/grammar/mem.y"
    {
      (yyval.node) = (ast::node::Node*)(yyvsp[(1) - (1)].node);
   }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 502 "src/mem/grammar/mem.y"
    {
      (yyval.node) = (ast::node::Node*)(yyvsp[(1) - (1)].text_node);
   }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 507 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Node(MEM_NODE_GROUP);
      (yyval.node)->pushChild((yyvsp[(2) - (3)].node));
   }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 512 "src/mem/grammar/mem.y"
    {
      (yyval.node) = static_cast<ast::node::Node*>((yyvsp[(1) - (1)].binary_node));
   }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 516 "src/mem/grammar/mem.y"
    {
      (yyval.node) = (ast::node::Node*)(yyvsp[(1) - (1)].node);
   }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 522 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->sValue("__div__", 7);
   }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 527 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->sValue("__equals__", 10);
   }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 532 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->sValue("__lt__", 6);
   }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 537 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->sValue("__lte__", 7);
   }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 542 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->sValue("__minus__", 9);
   }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 547 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->sValue("__modulo__", 10);
   }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 552 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->sValue("__mul__", 7);
   }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 557 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->sValue("__pow__", 7);
   }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 562 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text(MEM_NODE_ID);
      (yyval.text_node)->sValue("__plus__", 8);
   }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 567 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->sValue("__gt__", 6);
   }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 572 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text();
      (yyval.text_node)->sValue("__gte__", 7);
   }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 579 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text(MEM_NODE_ID);
      (yyval.text_node)->sValue("__bang__");
   }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 584 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text(MEM_NODE_ID);
      (yyval.text_node)->sValue("__minus_minus__");
   }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 589 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text(MEM_NODE_ID);
      (yyval.text_node)->sValue("__plus_plus__");
   }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 596 "src/mem/grammar/mem.y"
    {
      ast::node::Node* func = new ast::node::Node(MEM_NODE_DOT);
      func->pushChildren((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].text_node));

      (yyval.node) = new ast::node::Text(MEM_NODE_CALL);
      (yyval.node)->pushChildren(func, (yyvsp[(3) - (3)].node));
   }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 606 "src/mem/grammar/mem.y"
    {
      ast::node::Node* func = new ast::node::Node(MEM_NODE_DOT);
      func->pushChild ((yyvsp[(2) - (2)].node));

      (yyval.text_node) = new ast::node::Text(MEM_NODE_CALL);
      (yyval.text_node)->pushChild(func);
   }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 616 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Node(MEM_NODE_EXPR_LIST);
      (yyval.node)->pushChild((yyvsp[(1) - (1)].node));
   }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 621 "src/mem/grammar/mem.y"
    {
      if ((yyval.node) == 0)
      {
         (yyval.node) = new ast::node::Node(MEM_NODE_EXPR_LIST);
      }
      (yyval.node)->pushChild((yyvsp[(3) - (3)].node));
   }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 632 "src/mem/grammar/mem.y"
    {
      (yyval.node) = new ast::node::Node(MEM_NODE_CALL);
      (yyval.node)->sPosition(new fs::position::Range((yylsp[(1) - (3)]), (yylsp[(3) - (3)])));
      (yyval.node)->pushChild((yyvsp[(1) - (3)].node));
   }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 639 "src/mem/grammar/mem.y"
    {
      (yyvsp[(3) - (4)].node)->sPosition((yylsp[(3) - (4)]).copy_range());
      (yyval.node) = new ast::node::Node(MEM_NODE_CALL);
      (yyval.node)->sPosition(new fs::position::Range((yylsp[(1) - (4)]), (yylsp[(4) - (4)])));
      (yyval.node)->pushChildren((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
   }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 648 "src/mem/grammar/mem.y"
    {
      (yyval.text_node) = new ast::node::Text(MEM_NODE_LITERAL_INT);
      (yyval.text_node)->sPosition((yylsp[(1) - (1)]).copy_range());
      (yyval.text_node)->sValue((yyvsp[(1) - (1)].text));

      free((yyvsp[(1) - (1)].text));
   }
    break;



/* Line 1806 of yacc.c  */
#line 2434 "src/mem/parser/Bison.cpp"
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
#line 655 "src/mem/grammar/mem.y"


#include "mem/ast/node/Node.hpp"

