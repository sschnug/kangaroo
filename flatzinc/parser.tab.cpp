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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 50 "parser.yxx"

#define YYPARSE_PARAM parm
#define YYLEX_PARAM static_cast<FlatZinc::ParserState*>(parm)->yyscanner

#include <iostream>
#include <fstream>
#include <sstream>

//#include "cbls/globals/idx.hh"
//#include "cbls/structs/idx.hh"

#include "flatzinc.hpp"
#include "parser.hpp"

using namespace std;

int yyparse(void*);
int yylex(YYSTYPE*, void* scanner);
int yylex_init (void** scanner);
int yylex_destroy (void* scanner);
int yyget_lineno (void* scanner);
void yyset_extra (void* user_defined ,void* yyscanner );

extern int yydebug;

using namespace FlatZinc;

void yyerror(void* parm, const char *str) {
	ParserState* pp = static_cast<ParserState*>(parm);
	pp->err << "Error: " << str
			<< " in line no. " << yyget_lineno(pp->yyscanner)
			<< std::endl;
	pp->hadError = true;
}

void yyassert(FlatZinc::ParserState* pp, bool cond, const char* str) {
	if (!cond) {
		pp->err << "Error: " << str
				<< " in line no. " << yyget_lineno(pp->yyscanner)
				<< std::endl;
		pp->hadError = true;
	}
}


/*
 * The main program
 *
 */

namespace FlatZinc {

	FlatZincModel *parse(const std::string& filename, std::ostream& err,
						 unsigned int rndSeed, FlatZincModel *fzs) {
		std::ifstream file;
		file.open(filename.c_str());
		if (!file.is_open()) {
			err << "Cannot open file " << filename << endl;
			return NULL;
		}
		std::string s = string(istreambuf_iterator<char>(file),istreambuf_iterator<char>());

		if (fzs == NULL) {
			fzs = new FlatZincModel();
		}
		if ( rndSeed ) fzs->setRandomSeed(rndSeed);

		ParserState pp(s, err, fzs);

		yylex_init(&pp.yyscanner);
		yyset_extra(&pp, pp.yyscanner);
		// yydebug = 1;
		std::cout << "Parse file: " << filename << "\n" << std::flush;
		yyparse(&pp);

		if (pp.yyscanner)
			yylex_destroy(pp.yyscanner);
		return pp.hadError ? NULL : pp.fzm;
	}

	FlatZincModel* parse(std::istream& is, std::ostream& err,
						 unsigned int rndSeed, FlatZincModel* fzs) {

		std::string s = string(istreambuf_iterator<char>(is), istreambuf_iterator<char>());

		if (fzs == NULL) {
			fzs = new FlatZincModel();
		}
		if ( rndSeed ) fzs->setRandomSeed(rndSeed);

		ParserState pp(s, err, fzs);

		yylex_init(&pp.yyscanner);
		yyset_extra(&pp, pp.yyscanner);
		// yydebug = 1;
		yyparse(&pp);

		if (pp.yyscanner)
			yylex_destroy(pp.yyscanner);
		return pp.hadError ? NULL : pp.fzm;
	}

}



/* Line 268 of yacc.c  */
#line 178 "parser.tab.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FZ_INT_CONST = 258,
     FZ_BOOL_CONST = 259,
     FZ_FLOAT_CONST = 260,
     FZ_STRING_CONST = 261,
     FZ_ID = 262,
     FZ_U_ID = 263,
     FZ_ANNOTATION = 264,
     FZ_ANY = 265,
     FZ_ARRAY = 266,
     FZ_BOOL = 267,
     FZ_CASE = 268,
     FZ_COLONCOLON = 269,
     FZ_CONSTRAINT = 270,
     FZ_DIFF = 271,
     FZ_DIV = 272,
     FZ_DOTDOT = 273,
     FZ_ELSE = 274,
     FZ_ELSEIF = 275,
     FZ_ENDIF = 276,
     FZ_ENUM = 277,
     FZ_FLOAT = 278,
     FZ_FUNCTION = 279,
     FZ_IF = 280,
     FZ_IN = 281,
     FZ_INCLUDE = 282,
     FZ_INT = 283,
     FZ_INTERSECT = 284,
     FZ_LET = 285,
     FZ_LIST = 286,
     FZ_MAXIMIZE = 287,
     FZ_MINIMIZE = 288,
     FZ_MOD = 289,
     FZ_NOT = 290,
     FZ_OF = 291,
     FZ_SATISFY = 292,
     FZ_SUBSET = 293,
     FZ_SUPERSET = 294,
     FZ_OUTPUT = 295,
     FZ_PAR = 296,
     FZ_PREDICATE = 297,
     FZ_RECORD = 298,
     FZ_SEMICOLON = 299,
     FZ_SET = 300,
     FZ_SHOW = 301,
     FZ_SHOWCOND = 302,
     FZ_SOLVE = 303,
     FZ_STRING = 304,
     FZ_SYMDIFF = 305,
     FZ_TEST = 306,
     FZ_THEN = 307,
     FZ_TUPLE = 308,
     FZ_TYPE = 309,
     FZ_UNION = 310,
     FZ_VARIANT_RECORD = 311,
     FZ_VAR = 312,
     FZ_WHERE = 313,
     FZ_XOR = 314
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 156 "parser.yxx"
 bool bValue; double dValue; int iValue; char* sValue;
	std::string*                              stValue;
	emu::b1<kangaroo::Int,xmm>*          		iPair;
	emu::b1<kangaroo::Flt,xmm>*          		fPair;
	emu::b1<kangaroo::Int,xmm>*          		iList;
	FlatZinc::ExprSpec*                       exprSpec;
	FlatZinc::TypeSpec*                       typeSpec;
	FlatZinc::AnnSpec*                        annSpec;
	FlatZinc::Annotations*                    anns;



/* Line 293 of yacc.c  */
#line 286 "parser.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 298 "parser.tab.cpp"

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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   128

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNRULES -- Number of states.  */
#define YYNSTATES  128

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      65,    66,     2,     2,    62,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    67,     2,
       2,    68,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    63,     2,    64,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,     2,    61,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     7,     8,    10,    12,    15,    16,    18,
      20,    23,    27,    31,    35,    37,    41,    47,    49,    51,
      53,    57,    60,    63,    66,    71,    74,    77,    80,    83,
      86,    89,    94,    99,   103,   107,   111,   115,   119,   123,
     129,   135,   137,   139,   141,   143,   145,   147,   149,   151,
     153,   158,   160,   165,   167,   170,   174,   176,   180,   186,
     194,   202,   207,   213,   219,   221,   226,   227,   229,   232,
     236,   238
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      70,     0,    -1,    71,    73,    88,    -1,    -1,    72,    -1,
      86,    -1,    72,    86,    -1,    -1,    74,    -1,    87,    -1,
      74,    87,    -1,     5,    18,     5,    -1,     3,    18,     3,
      -1,    60,    78,    61,    -1,     3,    -1,    78,    62,     3,
      -1,    11,    63,    76,    64,    36,    -1,    12,    -1,    23,
      -1,    28,    -1,    45,    36,    28,    -1,    79,    12,    -1,
      79,    23,    -1,    79,    28,    -1,    79,    45,    36,    28,
      -1,    57,    12,    -1,    57,    23,    -1,    57,    75,    -1,
      57,    28,    -1,    57,    76,    -1,    57,    77,    -1,    57,
      45,    36,    76,    -1,    57,    45,    36,    77,    -1,    79,
      57,    12,    -1,    79,    57,    23,    -1,    79,    57,    75,
      -1,    79,    57,    28,    -1,    79,    57,    76,    -1,    79,
      57,    77,    -1,    79,    57,    45,    36,    76,    -1,    79,
      57,    45,    36,    77,    -1,     7,    -1,     7,    -1,     8,
      -1,     4,    -1,     5,    -1,     3,    -1,    76,    -1,    77,
      -1,    82,    -1,    82,    63,     3,    64,    -1,    84,    -1,
      81,    65,    85,    66,    -1,     6,    -1,    63,    64,    -1,
      63,    85,    64,    -1,    83,    -1,    85,    62,    83,    -1,
      80,    67,    82,    90,    44,    -1,    80,    67,    82,    90,
      68,    83,    44,    -1,    15,    81,    65,    85,    66,    90,
      44,    -1,    48,    90,    37,    44,    -1,    48,    90,    33,
      89,    44,    -1,    48,    90,    32,    89,    44,    -1,    82,
      -1,    82,    63,     3,    64,    -1,    -1,    91,    -1,    14,
      92,    -1,    91,    14,    92,    -1,    81,    -1,    81,    65,
      85,    66,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   250,   250,   264,   266,   269,   270,   273,   275,   278,
     279,   367,   376,   385,   391,   396,   411,   429,   433,   437,
     441,   446,   451,   456,   461,   485,   489,   493,   498,   502,
     507,   513,   519,   525,   530,   535,   540,   545,   550,   556,
     562,   578,   587,   591,   610,   615,   620,   625,   630,   639,
     645,   651,   656,   662,   673,   678,   685,   690,   710,   725,
     756,   780,   786,   792,   803,   808,   823,   826,   832,   837,
     849,   854
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FZ_INT_CONST", "FZ_BOOL_CONST",
  "FZ_FLOAT_CONST", "FZ_STRING_CONST", "FZ_ID", "FZ_U_ID", "FZ_ANNOTATION",
  "FZ_ANY", "FZ_ARRAY", "FZ_BOOL", "FZ_CASE", "FZ_COLONCOLON",
  "FZ_CONSTRAINT", "FZ_DIFF", "FZ_DIV", "FZ_DOTDOT", "FZ_ELSE",
  "FZ_ELSEIF", "FZ_ENDIF", "FZ_ENUM", "FZ_FLOAT", "FZ_FUNCTION", "FZ_IF",
  "FZ_IN", "FZ_INCLUDE", "FZ_INT", "FZ_INTERSECT", "FZ_LET", "FZ_LIST",
  "FZ_MAXIMIZE", "FZ_MINIMIZE", "FZ_MOD", "FZ_NOT", "FZ_OF", "FZ_SATISFY",
  "FZ_SUBSET", "FZ_SUPERSET", "FZ_OUTPUT", "FZ_PAR", "FZ_PREDICATE",
  "FZ_RECORD", "FZ_SEMICOLON", "FZ_SET", "FZ_SHOW", "FZ_SHOWCOND",
  "FZ_SOLVE", "FZ_STRING", "FZ_SYMDIFF", "FZ_TEST", "FZ_THEN", "FZ_TUPLE",
  "FZ_TYPE", "FZ_UNION", "FZ_VARIANT_RECORD", "FZ_VAR", "FZ_WHERE",
  "FZ_XOR", "'{'", "'}'", "','", "'['", "']'", "'('", "')'", "':'", "'='",
  "$accept", "model", "param_var_decl_list", "param_var_decl_list_head",
  "constraint_list", "constraint_list_head", "float_range", "int_range",
  "int_set", "int_list", "array_range", "par_var_type", "pred_ann_id",
  "var_par_id", "expr", "array_expr", "expr_list", "param_var_decl",
  "constraint", "solve_goal", "objfn", "annotations", "annotation_list",
  "annotation", 0
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
     123,   125,    44,    91,    93,    40,    41,    58,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    71,    71,    72,    72,    73,    73,    74,
      74,    75,    76,    77,    78,    78,    79,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    81,    82,    82,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    84,    84,    85,    85,    86,    86,
      87,    88,    88,    88,    89,    89,    90,    90,    91,    91,
      92,    92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     1,     1,     2,     0,     1,     1,
       2,     3,     3,     3,     1,     3,     5,     1,     1,     1,
       3,     2,     2,     2,     4,     2,     2,     2,     2,     2,
       2,     4,     4,     3,     3,     3,     3,     3,     3,     5,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     4,     1,     2,     3,     1,     3,     5,     7,
       7,     4,     5,     5,     1,     4,     0,     1,     2,     3,
       1,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    17,    18,    19,     0,     0,     0,     7,     4,
       0,     0,     5,     0,     0,     0,     0,    25,    26,    28,
       0,     0,    27,    29,    30,     1,     0,     0,     8,     9,
       6,    21,    22,    23,     0,     0,     0,     0,    20,     0,
       0,     0,    14,     0,    41,     0,    66,     2,    10,     0,
      33,    34,    36,     0,    35,    37,    38,    42,    43,    66,
       0,    12,    11,    31,    32,    13,     0,     0,     0,     0,
      67,    24,     0,     0,    16,    15,    46,    44,    45,    53,
      42,     0,    47,    48,     0,    49,    56,    51,     0,    70,
      68,     0,     0,     0,     0,    39,    40,    58,     0,    54,
       0,     0,     0,     0,    66,     0,    64,     0,     0,    61,
      69,     0,    55,     0,     0,    57,     0,     0,     0,    63,
      62,    59,    52,    50,    60,    71,     0,    65
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     7,     8,     9,    27,    28,    22,    82,    83,    43,
      10,    11,    84,    85,    86,    87,    88,    12,    29,    47,
     107,    69,    70,    90
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -93
static const yytype_int8 yypact[] =
{
      60,   -29,   -93,   -93,   -93,    -8,    32,    26,    25,    60,
      63,   -24,   -93,    59,    35,    62,    64,   -93,   -93,   -93,
      42,    81,   -93,   -93,   -93,   -93,    78,    39,    25,   -93,
     -93,   -93,   -93,   -93,    53,    36,    46,    29,   -93,    87,
      89,     1,   -93,     4,   -93,    30,    83,   -93,   -93,    70,
     -93,   -93,   -93,    65,   -93,   -93,   -93,   -93,   -93,    83,
      66,   -93,   -93,   -93,   -93,   -93,    96,    16,    78,    14,
      86,   -93,     1,   -35,   -93,   -93,    62,   -93,   -93,   -93,
      38,    10,   -93,   -93,    41,    44,   -93,   -93,   -37,    45,
     -93,    46,    46,    67,    78,   -93,   -93,   -93,    16,   -93,
     -52,    16,   101,    16,    83,    16,    49,    69,    71,   -93,
     -93,    72,   -93,   -17,    50,   -93,    74,   -10,   106,   -93,
     -93,   -93,   -93,   -93,   -93,   -93,    55,   -93
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -93,   -93,   -93,   -93,   -93,   -93,    88,    -5,    -3,   -93,
     -93,   -93,   -26,   -34,   -92,   -93,   -74,   112,    94,   -93,
      33,   -54,   -93,    34
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -42
static const yytype_int8 yytable[] =
{
      45,    23,    59,    24,    15,    73,   111,   100,    37,    97,
     103,   115,   112,    76,    77,    78,    79,    80,    58,    76,
      77,    78,    79,    80,    58,   103,    25,   113,    14,   104,
      55,   117,    56,    98,    13,    15,    63,    16,    64,    15,
      26,    16,    89,    36,    17,   103,    91,    92,    50,   122,
     116,    93,   103,    57,    58,    18,   125,   106,   106,    51,
      19,    21,    15,    38,    52,    65,    66,    95,    89,    96,
      21,     1,     2,    81,    99,    31,    21,    20,    41,    81,
      39,    53,    40,     3,    42,    44,    32,    46,     4,    49,
      61,    33,    21,    60,    62,    67,    21,    68,    71,    75,
      94,    72,    74,   -41,   114,     5,   101,   102,    34,   126,
     105,   109,   118,   119,   123,   120,   121,     6,   124,   127,
      35,    30,    48,    54,     0,   108,     0,     0,   110
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-93))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      26,     6,    36,     6,     3,    59,    98,    81,    13,    44,
      62,   103,    64,     3,     4,     5,     6,     7,     8,     3,
       4,     5,     6,     7,     8,    62,     0,   101,    36,    66,
      35,   105,    35,    68,    63,     3,    41,     5,    41,     3,
      15,     5,    68,    67,    12,    62,    32,    33,    12,    66,
     104,    37,    62,     7,     8,    23,    66,    91,    92,    23,
      28,    60,     3,    28,    28,    61,    62,    72,    94,    72,
      60,    11,    12,    63,    64,    12,    60,    45,    36,    63,
      18,    45,    18,    23,     3,     7,    23,    48,    28,    36,
       3,    28,    60,    64,     5,    65,    60,    14,    28,     3,
      14,    36,    36,    65,     3,    45,    65,    63,    45,     3,
      65,    44,    63,    44,    64,    44,    44,    57,    44,    64,
      57,     9,    28,    35,    -1,    92,    -1,    -1,    94
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    12,    23,    28,    45,    57,    70,    71,    72,
      79,    80,    86,    63,    36,     3,     5,    12,    23,    28,
      45,    60,    75,    76,    77,     0,    15,    73,    74,    87,
      86,    12,    23,    28,    45,    57,    67,    76,    28,    18,
      18,    36,     3,    78,     7,    81,    48,    88,    87,    36,
      12,    23,    28,    45,    75,    76,    77,     7,     8,    82,
      64,     3,     5,    76,    77,    61,    62,    65,    14,    90,
      91,    28,    36,    90,    36,     3,     3,     4,     5,     6,
       7,    63,    76,    77,    81,    82,    83,    84,    85,    81,
      92,    32,    33,    37,    14,    76,    77,    44,    68,    64,
      85,    65,    63,    62,    66,    65,    82,    89,    89,    44,
      92,    83,    64,    85,     3,    83,    90,    85,    63,    44,
      44,    44,    66,    64,    44,    66,     3,    64
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
      yyerror (parm, YY_("syntax error: cannot back up")); \
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
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
		  Type, Value, parm); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *parm)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, parm)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void *parm;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (parm);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *parm)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, parm)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void *parm;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parm);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, void *parm)
#else
static void
yy_reduce_print (yyvsp, yyrule, parm)
    YYSTYPE *yyvsp;
    int yyrule;
    void *parm;
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
		       		       , parm);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, parm); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *parm)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, parm)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    void *parm;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (parm);

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
int yyparse (void *parm);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


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
yyparse (void *parm)
#else
int
yyparse (parm)
    void *parm;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 11:

/* Line 1806 of yacc.c  */
#line 368 "parser.yxx"
    {
			(yyval.fPair) = new emu::b1<kangaroo::Flt,xmm>(2);
			(yyval.fPair)->append((yyvsp[(1) - (3)].dValue));
			(yyval.fPair)->append((yyvsp[(3) - (3)].dValue));
		}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 377 "parser.yxx"
    {
			(yyval.iPair) = new emu::b1<kangaroo::Int,xmm>(2);
			(yyval.iPair)->append((yyvsp[(1) - (3)].iValue));
			(yyval.iPair)->append((yyvsp[(3) - (3)].iValue));
		}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 386 "parser.yxx"
    {
			(yyval.iList) = (yyvsp[(2) - (3)].iList);
		}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 392 "parser.yxx"
    {
			(yyval.iList) = new emu::b1<kangaroo::Int,xmm>(1);
			(yyval.iList)->annex((yyvsp[(1) - (1)].iValue));
		}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 397 "parser.yxx"
    {
			(yyval.iList) = (yyvsp[(1) - (3)].iList);
			(yyval.iList)->annex((yyvsp[(3) - (3)].iValue));
		}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 412 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			yyassert(pp, (yyvsp[(3) - (5)].iPair)->item(0) == 1, "An array index_set has to start with 1.");
			(yyval.iPair) = (yyvsp[(3) - (5)].iPair);
		}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 430 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::BoolTypeSpec(FlatZinc::KFZ_PAR);
		}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 434 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::FloatTypeSpec(FlatZinc::KFZ_PAR);
		}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 438 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::IntTypeSpec(FlatZinc::KFZ_PAR);
		}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 442 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			yyerror(pp, "Not yet supported:: par_type: set of int.");
		}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 447 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::BoolTypeSpec(FlatZinc::KFZ_PAR, (yyvsp[(1) - (2)].iPair));
			delete (yyvsp[(1) - (2)].iPair);
		}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 452 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::FloatTypeSpec(FlatZinc::KFZ_PAR, (yyvsp[(1) - (2)].iPair));
			delete (yyvsp[(1) - (2)].iPair);
		}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 457 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::IntTypeSpec(FlatZinc::KFZ_PAR, (yyvsp[(1) - (2)].iPair));
			delete (yyvsp[(1) - (2)].iPair);
		}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 462 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			yyerror(pp, "Not yet supported:: par_type: array of set of int.");
			delete (yyvsp[(1) - (4)].iPair);
		}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 486 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::BoolTypeSpec(FlatZinc::KFZ_VAR);
		}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 490 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::FloatTypeSpec(FlatZinc::KFZ_VAR);
		}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 494 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::FloatTypeSpec(FlatZinc::KFZ_VAR, (yyvsp[(2) - (2)].fPair)->item(0), (yyvsp[(2) - (2)].fPair)->item(1));
			delete (yyvsp[(2) - (2)].fPair);
		}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 499 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::IntTypeSpec(FlatZinc::KFZ_VAR);
		}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 503 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::IntTypeSpec(FlatZinc::KFZ_VAR, (yyvsp[(2) - (2)].iPair)->item(0), (yyvsp[(2) - (2)].iPair)->item(1));
			delete (yyvsp[(2) - (2)].iPair);
		}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 508 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			yyerror(pp, "Not yet supported:: var_type: {int_const, ...}.");
			delete (yyvsp[(2) - (2)].iList);
		}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 514 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			yyerror(pp, "Not yet supported:: var_type: set of int_const..int_const.");
			delete (yyvsp[(4) - (4)].iPair);
		}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 520 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			yyerror(pp, "Not yet supported:: var_type: set of {int_const, ...}.");
			delete (yyvsp[(4) - (4)].iList);
		}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 526 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::BoolTypeSpec(FlatZinc::KFZ_VAR, (yyvsp[(1) - (3)].iPair));
			delete (yyvsp[(1) - (3)].iPair);
		}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 531 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::FloatTypeSpec(FlatZinc::KFZ_VAR, (yyvsp[(1) - (3)].iPair));
			delete (yyvsp[(1) - (3)].iPair);
		}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 536 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::FloatTypeSpec(FlatZinc::KFZ_VAR, (yyvsp[(1) - (3)].iPair), (yyvsp[(3) - (3)].fPair)->item(0), (yyvsp[(3) - (3)].fPair)->item(1));
			delete (yyvsp[(1) - (3)].iPair);	delete (yyvsp[(3) - (3)].fPair);
		}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 541 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::IntTypeSpec(FlatZinc::KFZ_VAR, (yyvsp[(1) - (3)].iPair));
			delete (yyvsp[(1) - (3)].iPair);
		}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 546 "parser.yxx"
    {
			(yyval.typeSpec) = new FlatZinc::IntTypeSpec(FlatZinc::KFZ_VAR, (yyvsp[(1) - (3)].iPair), (yyvsp[(3) - (3)].iPair)->item(0), (yyvsp[(3) - (3)].iPair)->item(1));
			delete (yyvsp[(1) - (3)].iPair);	delete (yyvsp[(3) - (3)].iPair);
		}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 551 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			yyerror(pp, "Not yet supported:: var_type: array of {int_const, ...}.");
			delete (yyvsp[(1) - (3)].iPair);	delete (yyvsp[(3) - (3)].iList);
		}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 557 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			yyerror(pp, "Not yet supported:: var_type: array of set of int_const..int_const.");
			delete (yyvsp[(1) - (5)].iPair);	delete (yyvsp[(5) - (5)].iPair);
		}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 563 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			yyerror(pp, "Not yet supported:: var_type: array of set of {int_const, ...}.");
			delete (yyvsp[(1) - (5)].iPair);	delete (yyvsp[(5) - (5)].iList);
		}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 579 "parser.yxx"
    {
			(yyval.sValue) = (yyvsp[(1) - (1)].sValue);
		}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 588 "parser.yxx"
    {
			(yyval.sValue) = (yyvsp[(1) - (1)].sValue);
		}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 592 "parser.yxx"
    {
			(yyval.sValue) = (yyvsp[(1) - (1)].sValue);
		}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 611 "parser.yxx"
    {
			(yyval.exprSpec) = new FlatZinc::ExprSpec();
			(yyval.exprSpec)->setBoolVal((yyvsp[(1) - (1)].iValue));
		}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 616 "parser.yxx"
    {
			(yyval.exprSpec) = new FlatZinc::ExprSpec();
			(yyval.exprSpec)->setFloatVal((yyvsp[(1) - (1)].dValue));
		}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 621 "parser.yxx"
    {
			(yyval.exprSpec) = new FlatZinc::ExprSpec();
			(yyval.exprSpec)->setIntVal((yyvsp[(1) - (1)].iValue));
		}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 626 "parser.yxx"
    {
			(yyval.exprSpec) = new FlatZinc::ExprSpec();
			(yyval.exprSpec)->setIntRange((yyvsp[(1) - (1)].iPair));
		}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 631 "parser.yxx"
    {
			(yyval.exprSpec) = new FlatZinc::ExprSpec();
			(yyval.exprSpec)->setIntSet((yyvsp[(1) - (1)].iList));
		}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 640 "parser.yxx"
    {
			(yyval.exprSpec) = new FlatZinc::ExprSpec();
			(yyval.exprSpec)->setIdVal((yyvsp[(1) - (1)].sValue));
			free((yyvsp[(1) - (1)].sValue));
		}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 646 "parser.yxx"
    {
			(yyval.exprSpec) = new FlatZinc::ExprSpec();
			(yyval.exprSpec)->setIdVal( FlatZinc::elem_id((yyvsp[(1) - (4)].sValue), (yyvsp[(3) - (4)].iValue)) );
			free((yyvsp[(1) - (4)].sValue));
		}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 652 "parser.yxx"
    {
			(yyval.exprSpec) = (yyvsp[(1) - (1)].exprSpec);
		}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 657 "parser.yxx"
    {
			(yyval.exprSpec) = new FlatZinc::ExprSpec();
			(yyval.exprSpec)->setAnnVal( new AnnSpec((yyvsp[(1) - (4)].sValue), (yyvsp[(3) - (4)].exprSpec)) );
			free((yyvsp[(1) - (4)].sValue));
		}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 663 "parser.yxx"
    {
			(yyval.exprSpec) = new FlatZinc::ExprSpec();
			(yyval.exprSpec)->setStringVal((yyvsp[(1) - (1)].sValue));
			free((yyvsp[(1) - (1)].sValue));
		}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 674 "parser.yxx"
    {
			(yyval.exprSpec) = new FlatZinc::ExprSpec();
			(yyval.exprSpec)->setArrayEmptyVal();
		}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 679 "parser.yxx"
    {
			(yyval.exprSpec) = (yyvsp[(2) - (3)].exprSpec);
		}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 686 "parser.yxx"
    {
			(yyval.exprSpec) = new FlatZinc::ExprSpec();
			(yyval.exprSpec)->setArrayFirstVal((yyvsp[(1) - (1)].exprSpec));
		}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 691 "parser.yxx"
    {
			(yyvsp[(1) - (3)].exprSpec)->setArrayNextVal((yyvsp[(3) - (3)].exprSpec));
			(yyval.exprSpec) = (yyvsp[(1) - (3)].exprSpec);
		}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 711 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			if ( (yyvsp[(1) - (5)].typeSpec)->objType == FlatZinc::KFZ_VAR ) {
#if ! defined(NDEBUG)
				cerr << "variable '" << (yyvsp[(3) - (5)].sValue) <<  "'" << endl;
#endif
				if ( !pp->hadError ) {
					pp->fzm->declVariable((yyvsp[(3) - (5)].sValue), (yyvsp[(1) - (5)].typeSpec), (yyvsp[(4) - (5)].anns));
				}
			} else if ( (yyvsp[(1) - (5)].typeSpec)->objType == FlatZinc::KFZ_PAR ) {
				yyerror(pp, "A parameter must have a default value!");
			}
			delete (yyvsp[(1) - (5)].typeSpec);	free((yyvsp[(3) - (5)].sValue));	delete (yyvsp[(4) - (5)].anns);
		}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 726 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			if ( (yyvsp[(1) - (7)].typeSpec)->objType == FlatZinc::KFZ_VAR ) {
#if ! defined(NDEBUG)
				cerr << "variable '" << (yyvsp[(3) - (7)].sValue) <<  "'" << " with expr = " << (yyvsp[(6) - (7)].exprSpec) << endl;
#endif
				if ( !pp->hadError ) {
					pp->fzm->declVariable((yyvsp[(3) - (7)].sValue), (yyvsp[(1) - (7)].typeSpec), (yyvsp[(4) - (7)].anns), (yyvsp[(6) - (7)].exprSpec));
				}
			} else if ( (yyvsp[(1) - (7)].typeSpec)->objType == FlatZinc::KFZ_PAR ) {
#if ! defined(NDEBUG)
				cerr << "param '" << (yyvsp[(3) - (7)].sValue) << "'" << endl;
#endif
				yyassert(pp, (yyvsp[(4) - (7)].anns)->empty(), "A parameter cannot have annotation(s)!");
				if ( !pp->hadError ) {
					pp->fzm->declConstant((yyvsp[(3) - (7)].sValue), (yyvsp[(1) - (7)].typeSpec), (yyvsp[(6) - (7)].exprSpec));
				}
			}
			delete (yyvsp[(1) - (7)].typeSpec);	free((yyvsp[(3) - (7)].sValue));	delete (yyvsp[(4) - (7)].anns);	//delete $6; // $6 (expr) will be deleted by flatzinc.cpp
		}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 757 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
#if ! defined(NDEBUG)
			cerr << "constraint '" << (yyvsp[(2) - (7)].sValue) <<  "' :: " << (yyvsp[(4) - (7)].exprSpec) << endl;
#endif
			if ( !pp->hadError ) {
				pp->fzm->postConstraint((yyvsp[(2) - (7)].sValue), (yyvsp[(4) - (7)].exprSpec), (yyvsp[(6) - (7)].anns));
			}
			free((yyvsp[(2) - (7)].sValue));	delete (yyvsp[(6) - (7)].anns);	/* memory deallocation of $4 is handled in postConstraint() */
		}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 781 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			pp->fzm->postSolver(KFZ_SAT, NULL, (yyvsp[(2) - (4)].anns));
			delete (yyvsp[(2) - (4)].anns);
		}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 787 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			pp->fzm->postSolver(KFZ_MIN, (yyvsp[(4) - (5)].stValue), (yyvsp[(2) - (5)].anns));
			delete (yyvsp[(2) - (5)].anns);	delete (yyvsp[(4) - (5)].stValue);
		}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 793 "parser.yxx"
    {
			ParserState* pp = static_cast<ParserState*>(parm);
			pp->fzm->postSolver(KFZ_MAX, (yyvsp[(4) - (5)].stValue), (yyvsp[(2) - (5)].anns));
			delete (yyvsp[(2) - (5)].anns);	delete (yyvsp[(4) - (5)].stValue);
		}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 804 "parser.yxx"
    {
			(yyval.stValue) = new std::string((yyvsp[(1) - (1)].sValue));
			free((yyvsp[(1) - (1)].sValue));
		}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 809 "parser.yxx"
    {
			(yyval.stValue) = FlatZinc::elem_id((yyvsp[(1) - (4)].sValue), (yyvsp[(3) - (4)].iValue));
			free((yyvsp[(1) - (4)].sValue));
		}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 823 "parser.yxx"
    {
			(yyval.anns) = new FlatZinc::Annotations();
		}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 827 "parser.yxx"
    {
			(yyval.anns) = (yyvsp[(1) - (1)].anns);
		}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 833 "parser.yxx"
    {
			(yyval.anns) = new FlatZinc::Annotations();
			(yyval.anns)->addAnn((yyvsp[(2) - (2)].annSpec));
		}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 838 "parser.yxx"
    {
			(yyval.anns) = (yyvsp[(1) - (3)].anns);
			(yyval.anns)->addAnn((yyvsp[(3) - (3)].annSpec));
		}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 850 "parser.yxx"
    {
			(yyval.annSpec) = new FlatZinc::AnnSpec((yyvsp[(1) - (1)].sValue));
			free((yyvsp[(1) - (1)].sValue));
		}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 855 "parser.yxx"
    {
			(yyval.annSpec) = new FlatZinc::AnnSpec((yyvsp[(1) - (4)].sValue), (yyvsp[(3) - (4)].exprSpec));
			free((yyvsp[(1) - (4)].sValue));
		}
    break;



/* Line 1806 of yacc.c  */
#line 2301 "parser.tab.cpp"
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
      yyerror (parm, YY_("syntax error"));
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
        yyerror (parm, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
		      yytoken, &yylval, parm);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, parm);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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
  yyerror (parm, YY_("memory exhausted"));
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
                  yytoken, &yylval, parm);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, parm);
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



