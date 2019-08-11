/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include <stdio.h>
#include <list>
#include "program.hh"
#include "procedure.hh"
#include "ast.hh"
#include "symbol-table.hh"
extern "C" void yyerror(char *s);
extern int yylex(void);
extern int yylineno;	
list<pair<string,int> > vars;
Symbol_Table *gtab;
Procedure *curProc;
int isGlob=1;

#line 82 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER_NUMBER = 258,
    DOUBLE_NUMBER = 259,
    INTEGER = 260,
    FLOAT = 261,
    RETURN = 262,
    VOID = 263,
    ASSIGN = 264,
    IF = 265,
    ELSE = 266,
    DO = 267,
    WHILE = 268,
    EQ = 269,
    NEQ = 270,
    LT = 271,
    LTE = 272,
    GT = 273,
    GTE = 274,
    AND = 275,
    OR = 276,
    NOT = 277,
    PRINT = 278,
    NAME = 279,
    UMINUS = 280
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "parser.y" /* yacc.c:355  */
 
    int integer_value;
	double double_value;
	std::string * string_value;
	list<Ast *> * ast_list;
	Ast * ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	Basic_Block * basic_block;
	Procedure * procedure;

#line 160 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 177 "parser.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   248

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      32,    33,    29,    27,    35,    28,     2,    30,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,    34,
       2,     2,     2,    25,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    55,    55,    58,    70,    77,    87,    88,    91,   107,
     125,   145,   158,   174,   182,   190,   202,   203,   206,   216,
     241,   268,   273,   281,   285,   293,   317,   321,   325,   331,
     335,   342,   345,   352,   357,   361,   365,   369,   373,   385,
     390,   395,   402,   409,   419,   422,   428,   435,   442,   451,
     457,   463,   467,   473,   501,   518,   521,   524,   527,   532,
     535,   540,   551,   565,   570,   578,   584,   592,   602,   608,
     614,   620,   626,   632,   636,   640,   645,   652
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER_NUMBER", "DOUBLE_NUMBER",
  "INTEGER", "FLOAT", "RETURN", "VOID", "ASSIGN", "IF", "ELSE", "DO",
  "WHILE", "EQ", "NEQ", "LT", "LTE", "GT", "GTE", "AND", "OR", "NOT",
  "PRINT", "NAME", "'?'", "':'", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "'('", "')'", "';'", "','", "'{'", "'}'", "$accept", "program",
  "var_proc_decl_list", "var_proc_decl", "proc_declaration", "type_list",
  "argument_list", "argument", "procedure_definition_list",
  "procedure_definition", "procedure_name",
  "optional_variable_declaration_list", "variable_declaration_list",
  "variable_declaration", "data_type", "variable_list", "statement_list",
  "statement", "if_else_stmt", "body", "else", "do_while_stmt",
  "while_stmt", "cond_expression", "relational_expression", "less_greater",
  "equal_not_equal", "FunCall", "exprList", "assignment_statement",
  "expression", "variable", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    63,    58,    43,    45,    42,
      47,   280,    40,    41,    59,    44,   123,   125
};
# endif

#define YYPACT_NINF -120

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-120)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     151,  -120,  -120,  -120,     5,   151,  -120,  -120,   151,  -120,
      -4,  -120,   -16,  -120,  -120,   151,  -120,    25,   151,     3,
     -17,    26,  -120,   151,  -120,    41,    17,  -120,    45,    38,
      75,  -120,  -120,    43,    24,    40,  -120,    57,  -120,  -120,
      94,    57,    52,    65,    -3,    69,    66,    85,  -120,  -120,
    -120,  -120,  -120,  -120,    97,  -120,   114,  -120,   108,   151,
     109,   151,  -120,  -120,  -120,  -120,   112,  -120,   112,   112,
    -120,    89,  -120,   136,  -120,   112,  -120,   133,   112,   113,
     100,    82,  -120,   117,  -120,  -120,  -120,  -120,  -120,   204,
    -120,    27,   178,   112,   112,   112,  -120,  -120,  -120,  -120,
    -120,  -120,   112,   112,   112,   112,  -120,   112,   112,    58,
     116,   105,  -120,  -120,   102,   204,  -120,   124,   157,  -120,
    -120,  -120,   140,   198,    78,    78,  -120,  -120,   204,   204,
      -3,   112,    -3,  -120,   112,  -120,  -120,   112,   150,   215,
    -120,   204,   204,    -3,  -120,   128,  -120,  -120
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    26,    27,    28,     0,     0,     4,     7,     3,    16,
       0,     6,     0,     1,     5,     2,    17,     0,    21,    30,
       0,     0,    31,    22,    23,     0,     0,    25,     0,     0,
       0,    24,    30,    19,     0,     0,    14,    12,    29,    19,
       0,     0,     0,     0,     0,     0,     0,    77,    31,    18,
      32,    35,    37,    36,     0,    34,     0,     8,     0,     0,
      20,     0,    15,    20,    75,    76,     0,    77,     0,     0,
      39,     0,    51,     0,    74,     0,    43,     0,     0,     0,
       0,     0,    41,     0,    10,    11,     9,    13,    48,     0,
      67,     0,     0,     0,     0,     0,    59,    60,    55,    56,
      57,    58,     0,     0,     0,     0,    40,     0,     0,     0,
       0,     0,    33,    62,     0,    64,    38,     0,     0,    52,
      73,    49,    50,     0,    68,    69,    70,    71,    53,    54,
       0,     0,     0,    61,     0,    66,    65,     0,    44,     0,
      47,    63,    72,     0,    42,     0,    45,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -120,  -120,  -120,   162,  -120,  -120,   139,   118,   164,    30,
    -120,  -120,  -120,    18,    11,  -120,   129,   -28,  -120,  -119,
    -120,  -120,  -120,   -63,  -120,  -120,  -120,    95,  -120,  -120,
     -41,   -30
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    34,    35,    36,     8,     9,
      10,    22,    23,    11,    12,    20,    30,    76,    51,    77,
     144,    52,    53,    71,    72,   107,   108,    54,   114,    55,
      89,    74
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      56,    73,    50,    88,    42,    13,    91,    43,    19,    44,
      45,   138,   109,   140,    56,   111,    79,    27,    28,    17,
      46,    47,     1,     2,   146,     3,    17,    90,    92,    25,
     121,   122,    18,    48,    25,    26,    24,    37,    16,   115,
      41,    31,   118,     1,     2,    16,     3,    93,    94,    21,
      33,    56,    95,    50,   123,    64,    65,    58,    29,    59,
     119,   124,   125,   126,   127,    32,   128,   129,   139,    38,
      85,    39,    41,    60,    66,    61,    67,    57,    93,    94,
      68,    62,    42,    95,    69,    43,    70,    44,    45,    42,
      67,   130,    43,   141,    44,    45,   142,    75,    46,    47,
      56,    78,    56,    64,    65,    46,    47,   104,   105,    93,
      94,    48,    49,    56,    95,    64,    65,    80,    48,   116,
      64,    65,    66,    83,    67,    93,    94,    63,    68,    61,
      95,    82,    69,   113,    66,   133,    67,   134,   132,    66,
      68,    47,    84,    86,    69,    68,   110,   112,   131,    69,
      96,    97,    98,    99,   100,   101,     1,     2,   135,     3,
      93,   143,   147,   102,   103,   104,   105,    14,    40,    15,
     106,    96,    97,    98,    99,   100,   101,    81,   117,    87,
       0,     0,     0,     0,   102,   103,   104,   105,     0,     0,
       0,   136,    96,    97,    98,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,     0,
       0,   120,    96,    97,    98,    99,   100,   101,    96,    97,
      98,    99,   100,   101,   137,   102,   103,   104,   105,     0,
       0,   102,   103,   104,   105,    93,    94,     0,     0,     0,
      95,     0,     0,     0,     0,     0,     0,     0,   145
};

static const yytype_int16 yycheck[] =
{
      30,    42,    30,    66,     7,     0,    69,    10,    24,    12,
      13,   130,    75,   132,    44,    78,    46,    34,    35,     8,
      23,    24,     5,     6,   143,     8,    15,    68,    69,    18,
      93,    94,    36,    36,    23,    32,    18,    26,     8,    80,
      29,    23,    83,     5,     6,    15,     8,    20,    21,    24,
      33,    81,    25,    81,    95,     3,     4,    33,    32,    35,
      33,   102,   103,   104,   105,    24,   107,   108,   131,    24,
      59,    33,    61,    33,    22,    35,    24,    34,    20,    21,
      28,    24,     7,    25,    32,    10,    34,    12,    13,     7,
      24,    33,    10,   134,    12,    13,   137,    32,    23,    24,
     130,    32,   132,     3,     4,    23,    24,    29,    30,    20,
      21,    36,    37,   143,    25,     3,     4,    32,    36,    37,
       3,     4,    22,     9,    24,    20,    21,    33,    28,    35,
      25,    34,    32,    33,    22,    33,    24,    35,    33,    22,
      28,    24,    34,    34,    32,    28,    13,    34,    32,    32,
      14,    15,    16,    17,    18,    19,     5,     6,    34,     8,
      20,    11,    34,    27,    28,    29,    30,     5,    29,     5,
      34,    14,    15,    16,    17,    18,    19,    48,    83,    61,
      -1,    -1,    -1,    -1,    27,    28,    29,    30,    -1,    -1,
      -1,    34,    14,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    29,    30,    -1,
      -1,    33,    14,    15,    16,    17,    18,    19,    14,    15,
      16,    17,    18,    19,    26,    27,    28,    29,    30,    -1,
      -1,    27,    28,    29,    30,    20,    21,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,     8,    39,    40,    41,    42,    46,    47,
      48,    51,    52,     0,    41,    46,    47,    52,    36,    24,
      53,    24,    49,    50,    51,    52,    32,    34,    35,    32,
      54,    51,    24,    33,    43,    44,    45,    52,    24,    33,
      44,    52,     7,    10,    12,    13,    23,    24,    36,    37,
      55,    56,    59,    60,    65,    67,    69,    34,    33,    35,
      33,    35,    24,    33,     3,     4,    22,    24,    28,    32,
      34,    61,    62,    68,    69,    32,    55,    57,    32,    69,
      32,    54,    34,     9,    34,    52,    34,    45,    61,    68,
      68,    61,    68,    20,    21,    25,    14,    15,    16,    17,
      18,    19,    27,    28,    29,    30,    34,    63,    64,    61,
      13,    61,    34,    33,    66,    68,    37,    65,    68,    33,
      33,    61,    61,    68,    68,    68,    68,    68,    68,    68,
      33,    32,    33,    33,    35,    34,    34,    26,    57,    61,
      57,    68,    68,    11,    58,    33,    57,    34
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    42,    42,
      42,    43,    43,    44,    44,    45,    46,    46,    47,    48,
      48,    49,    49,    50,    50,    51,    52,    52,    52,    53,
      53,    54,    54,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    56,    57,    58,    58,    59,    60,    61,    61,
      61,    61,    61,    62,    62,    63,    63,    63,    63,    64,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     2,     1,     1,     5,     6,
       6,     3,     1,     3,     1,     2,     1,     2,     5,     4,
       5,     0,     1,     1,     2,     3,     1,     1,     1,     3,
       1,     0,     2,     3,     1,     1,     1,     1,     3,     2,
       3,     2,     6,     1,     0,     2,     7,     5,     2,     3,
       3,     1,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     4,     3,     3,     1,     4,     4,     2,     3,     3,
       3,     3,     5,     3,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
      yychar = yylex ();
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 71 "parser.y" /* yacc.c:1646  */
    {
								(yyval.symbol_table)=(yyvsp[0].symbol_table); 
								(yyval.symbol_table)->set_table_scope(global);
								gtab=(yyval.symbol_table);
								program_object.set_global_table(*(yyval.symbol_table));
							}
#line 1382 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 78 "parser.y" /* yacc.c:1646  */
    {
								(yyvsp[-1].symbol_table)->append_list(*(yyvsp[0].symbol_table),yylineno);
								(yyval.symbol_table)=(yyvsp[-1].symbol_table);
								(yyval.symbol_table)->set_table_scope(global);
								gtab=(yyval.symbol_table);
								program_object.set_global_table(*(yyval.symbol_table));
							}
#line 1394 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 87 "parser.y" /* yacc.c:1646  */
    {(yyval.symbol_table)=(yyvsp[0].symbol_table);}
#line 1400 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 88 "parser.y" /* yacc.c:1646  */
    {(yyval.symbol_table)=(yyvsp[0].symbol_table);}
#line 1406 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 92 "parser.y" /* yacc.c:1646  */
    {
								(yyval.symbol_table) = new Symbol_Table();
								Data_Type varType;
								if((yyvsp[-4].integer_value)==263)
									varType=int_data_type;
								else if((yyvsp[-4].integer_value)==264)
									varType=double_data_type;
								else if((yyvsp[-4].integer_value)==265)
									varType=void_data_type;
								if(program_object.variable_in_symbol_list_check(*(yyvsp[-3].string_value)))
									yyerror("proc name cant be same to global var");
								
								Procedure *proc = new Procedure(varType,*(yyvsp[-3].string_value),yylineno);
								program_object.set_proc_to_map(*(yyvsp[-3].string_value),proc);
							}
#line 1426 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 108 "parser.y" /* yacc.c:1646  */
    {
								(yyval.symbol_table) = new Symbol_Table();
								Data_Type varType;
								if((yyvsp[-5].integer_value)==263)
									varType=int_data_type;
								else if((yyvsp[-5].integer_value)==264)
									varType=double_data_type;
								else if((yyvsp[-5].integer_value)==265)
									varType=void_data_type;
								if(program_object.variable_in_symbol_list_check(*(yyvsp[-4].string_value)))
									yyerror("proc name cant be same to global var");
								
								Procedure *proc = new Procedure(varType,*(yyvsp[-4].string_value),yylineno);
								(yyvsp[-2].symbol_table)->set_table_scope(formal);
								proc->set_formal_param_list(*(yyvsp[-2].symbol_table));
								program_object.set_proc_to_map(*(yyvsp[-4].string_value),proc);
							}
#line 1448 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 126 "parser.y" /* yacc.c:1646  */
    {
								(yyval.symbol_table) = new Symbol_Table();
								Data_Type varType;
								if((yyvsp[-5].integer_value)==263)
									varType=int_data_type;
								else if((yyvsp[-5].integer_value)==264)
									varType=double_data_type;
								else if((yyvsp[-5].integer_value)==265)
									varType=void_data_type;
								if(program_object.variable_in_symbol_list_check(*(yyvsp[-4].string_value)))
									yyerror("proc name cant be same to global var");
								
								Procedure *proc = new Procedure(varType,*(yyvsp[-4].string_value),yylineno);
								(yyvsp[-2].symbol_table)->set_table_scope(formal);
								proc->set_formal_param_list(*(yyvsp[-2].symbol_table));
								program_object.set_proc_to_map(*(yyvsp[-4].string_value),proc);
							}
#line 1470 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 146 "parser.y" /* yacc.c:1646  */
    {	
								if((yyvsp[0].integer_value)==265) yyerror("void variable type not allowed");
								Data_Type varType;
								if((yyvsp[0].integer_value)==263)
									varType=int_data_type;
								else
									varType=double_data_type;
								string s="";
								Symbol_Table_Entry *e= new Symbol_Table_Entry(s,varType,yylineno);
								(yyvsp[-2].symbol_table)->push_symbol(e);
								(yyval.symbol_table)=(yyvsp[-2].symbol_table);
							}
#line 1487 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 159 "parser.y" /* yacc.c:1646  */
    {
								if((yyvsp[0].integer_value)==265) yyerror("void variable type not allowed");
								Symbol_Table *symtab = new Symbol_Table();
								Data_Type varType;
								if((yyvsp[0].integer_value)==263)
									varType=int_data_type;
								else
									varType=double_data_type;
								string s="";
								Symbol_Table_Entry *e= new Symbol_Table_Entry(s,varType,yylineno);
								symtab->push_symbol(e);
								(yyval.symbol_table) = symtab;
							}
#line 1505 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 175 "parser.y" /* yacc.c:1646  */
    {
								if(!(yyvsp[-2].symbol_table)->variable_in_symbol_list_check((yyvsp[0].symbol_entry)->get_variable_name()))
									(yyvsp[-2].symbol_table)->push_symbol((yyvsp[0].symbol_entry));
								else
									yyerror("Variable is declared twice");
								(yyval.symbol_table)=(yyvsp[-2].symbol_table);
							}
#line 1517 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 183 "parser.y" /* yacc.c:1646  */
    {
								Symbol_Table *symtab = new Symbol_Table();
								symtab->push_symbol((yyvsp[0].symbol_entry));
								(yyval.symbol_table) = symtab;
							}
#line 1527 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 191 "parser.y" /* yacc.c:1646  */
    {
								if((yyvsp[-1].integer_value)==265) yyerror("void variable type not allowed");
								Data_Type varType;
								if((yyvsp[-1].integer_value)==263)
									varType=int_data_type;
								else
									varType=double_data_type;
								(yyval.symbol_entry) = new Symbol_Table_Entry(*(yyvsp[0].string_value), varType, yylineno);
							}
#line 1541 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 211 "parser.y" /* yacc.c:1646  */
    {
								(yyvsp[-4].procedure)->set_ast_list(*(yyvsp[-1].ast_list));
							}
#line 1549 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 217 "parser.y" /* yacc.c:1646  */
    {
								Data_Type varType;
								if((yyvsp[-3].integer_value)==263)
									varType=int_data_type;
								else if((yyvsp[-3].integer_value)==264)
									varType=double_data_type;
								else if((yyvsp[-3].integer_value)==265)
									varType=void_data_type;
								if(program_object.variable_in_symbol_list_check(*(yyvsp[-2].string_value)))
									yyerror("proc name cant be same to global var");
								
								if(program_object.variable_in_proc_map_check(*(yyvsp[-2].string_value))){
									Procedure *temp = program_object.get_procedure_prototype(*(yyvsp[-2].string_value));
									if(temp->is_proc_defined())
										yyerror("multiple proc definition");
								}
		
								Procedure *proc = new Procedure(varType,*(yyvsp[-2].string_value),yylineno);
								// proc->set_formal_param_list(*$4);
								proc->set_proc_is_defined();
								program_object.set_proc_to_map(*(yyvsp[-2].string_value),proc);
								curProc = proc;
								(yyval.procedure) = proc;
							}
#line 1578 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 242 "parser.y" /* yacc.c:1646  */
    {
								Data_Type varType;
								if((yyvsp[-4].integer_value)==263)
									varType=int_data_type;
								else if((yyvsp[-4].integer_value)==264)
									varType=double_data_type;
								else if((yyvsp[-4].integer_value)==265)
									varType=void_data_type;
								if(program_object.variable_in_symbol_list_check(*(yyvsp[-3].string_value)))
									yyerror("proc name cant be same to global var");
								
								if(program_object.variable_in_proc_map_check(*(yyvsp[-3].string_value))){
									Procedure *temp = program_object.get_procedure_prototype(*(yyvsp[-3].string_value));
									if(temp->is_proc_defined())
										yyerror("multiple proc definition");
								}
								Procedure *proc = new Procedure(varType,*(yyvsp[-3].string_value),yylineno);
								proc->set_formal_param_list(*(yyvsp[-1].symbol_table));
								proc->set_proc_is_defined();
								program_object.set_proc_to_map(*(yyvsp[-3].string_value),proc);
								curProc = proc;
								(yyval.procedure) = proc;
							}
#line 1606 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 268 "parser.y" /* yacc.c:1646  */
    {
								(yyval.symbol_table) = new Symbol_Table();
								(yyval.symbol_table)->set_table_scope(local);
								curProc->set_local_list(*(yyval.symbol_table));
							}
#line 1616 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 274 "parser.y" /* yacc.c:1646  */
    {
								(yyvsp[0].symbol_table)->set_table_scope(local);
								curProc->set_local_list(*(yyvsp[0].symbol_table));
								(yyval.symbol_table) = (yyvsp[0].symbol_table);
							}
#line 1626 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 282 "parser.y" /* yacc.c:1646  */
    {
								(yyval.symbol_table)=(yyvsp[0].symbol_table);
							}
#line 1634 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 287 "parser.y" /* yacc.c:1646  */
    {
								(yyvsp[-1].symbol_table)->append_list(*(yyvsp[0].symbol_table),yylineno);
								(yyval.symbol_table)=(yyvsp[-1].symbol_table);
							}
#line 1643 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 294 "parser.y" /* yacc.c:1646  */
    {
								if((yyvsp[-2].integer_value)==265) yyerror("void variable type not allowed");
								Symbol_Table *symtab = new Symbol_Table();
								while(!vars.empty()){
									pair<string,int> var=vars.front();
									vars.pop_front();
									Data_Type varType;
									if((yyvsp[-2].integer_value)==263)
										varType=int_data_type;
									else
										varType=double_data_type;
									
									Symbol_Table_Entry *e= new Symbol_Table_Entry(var.first,varType,var.second);

									if(!symtab->variable_in_symbol_list_check(var.first))
										symtab->push_symbol(e);
									else
										yyerror("Variable is declared twice");
								}	
								(yyval.symbol_table) = symtab;							
							}
#line 1669 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 318 "parser.y" /* yacc.c:1646  */
    {
								(yyval.integer_value)=263;
							}
#line 1677 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 322 "parser.y" /* yacc.c:1646  */
    {
								(yyval.integer_value)=264;
							}
#line 1685 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 326 "parser.y" /* yacc.c:1646  */
    {
								(yyval.integer_value)=265;
							}
#line 1693 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 332 "parser.y" /* yacc.c:1646  */
    {
								vars.push_back(make_pair(*((yyvsp[0].string_value)),yylineno));
							}
#line 1701 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 336 "parser.y" /* yacc.c:1646  */
    {
								vars.push_back(make_pair(*((yyvsp[0].string_value)),yylineno));
							}
#line 1709 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 342 "parser.y" /* yacc.c:1646  */
    {
								(yyval.ast_list) = new list<Ast *>();
							}
#line 1717 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 346 "parser.y" /* yacc.c:1646  */
    {
			        			(yyvsp[-1].ast_list)->push_back((yyvsp[0].ast));
			        			(yyval.ast_list) = (yyvsp[-1].ast_list);
			        		}
#line 1726 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 353 "parser.y" /* yacc.c:1646  */
    {
								Ast* printAst = new Print_Ast((yyvsp[-1].ast),yylineno);
								(yyval.ast) =  printAst;
							}
#line 1735 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 358 "parser.y" /* yacc.c:1646  */
    {
								(yyval.ast)=(yyvsp[0].ast);
							}
#line 1743 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 362 "parser.y" /* yacc.c:1646  */
    {
								(yyval.ast)=(yyvsp[0].ast);
							}
#line 1751 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 366 "parser.y" /* yacc.c:1646  */
    {
								(yyval.ast)=(yyvsp[0].ast);
							}
#line 1759 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 370 "parser.y" /* yacc.c:1646  */
    {
								(yyval.ast)=(yyvsp[0].ast);
							}
#line 1767 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 374 "parser.y" /* yacc.c:1646  */
    {
								if((yyvsp[-1].ast_list)->empty()){
									yyerror("Empty block not allowed");
								}
								Ast * SeqAst = new Sequence_Ast(yylineno);
								list<Ast *>::iterator it;
								for(it=(yyvsp[-1].ast_list)->begin();it!=(yyvsp[-1].ast_list)->end();it++){
									((Sequence_Ast *)SeqAst)->ast_push_back(*it);
								}
								(yyval.ast) = SeqAst;
							}
#line 1783 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 386 "parser.y" /* yacc.c:1646  */
    {
								Ast * RetAst = new Return_Ast(NULL,curProc->get_proc_name(),yylineno);
								(yyval.ast) = RetAst;
							}
#line 1792 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 391 "parser.y" /* yacc.c:1646  */
    {
								Ast * RetAst = new Return_Ast((yyvsp[-1].ast),curProc->get_proc_name(),yylineno);
								(yyval.ast) = RetAst;
							}
#line 1801 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 396 "parser.y" /* yacc.c:1646  */
    {
								((Call_Ast*)(yyvsp[-1].ast))->set_register(new Register_Descriptor());
								(yyval.ast)=(yyvsp[-1].ast);
							}
#line 1810 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 403 "parser.y" /* yacc.c:1646  */
    {
								Ast* IfAst= new Selection_Statement_Ast((yyvsp[-3].ast),(yyvsp[-1].ast),(yyvsp[0].ast),yylineno);
								(yyval.ast) = IfAst;
							}
#line 1819 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 410 "parser.y" /* yacc.c:1646  */
    {
								// Ast * SeqAst = new Sequence_Ast(yylineno);
								// ((Sequence_Ast *)SeqAst)->ast_push_back($1);
								// $<ast>$=SeqAst;
								(yyval.ast)=(yyvsp[0].ast);
							}
#line 1830 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 419 "parser.y" /* yacc.c:1646  */
    {
								(yyval.ast)=NULL;
							}
#line 1838 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 423 "parser.y" /* yacc.c:1646  */
    {
								(yyval.ast)=(yyvsp[0].ast);
							}
#line 1846 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 429 "parser.y" /* yacc.c:1646  */
    {
								Ast* DoAst= new Iteration_Statement_Ast((yyvsp[-2].ast),(yyvsp[-5].ast),yylineno,1);
								(yyval.ast)= DoAst;
							}
#line 1855 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 436 "parser.y" /* yacc.c:1646  */
    {
								Ast* WhiAst= new Iteration_Statement_Ast((yyvsp[-2].ast),(yyvsp[0].ast),yylineno,0);
								(yyval.ast)= WhiAst;
							}
#line 1864 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 443 "parser.y" /* yacc.c:1646  */
    {
								// cout<<1<<endl;
								Ast * LogAst = new Logical_Expr_Ast(NULL,_logical_not,(yyvsp[0].ast),yylineno);
								// cout<<2<<endl;
								LogAst->check_ast();
								// cout<<3<<endl;
								(yyval.ast)=LogAst;
							}
#line 1877 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 452 "parser.y" /* yacc.c:1646  */
    {
								Ast * LogAst = new Logical_Expr_Ast((yyvsp[-2].ast),_logical_and,(yyvsp[0].ast),yylineno);
								LogAst->check_ast();
								(yyval.ast)=LogAst;
							}
#line 1887 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 458 "parser.y" /* yacc.c:1646  */
    {
								Ast * LogAst = new Logical_Expr_Ast((yyvsp[-2].ast),_logical_or,(yyvsp[0].ast),yylineno);
								LogAst->check_ast();
								(yyval.ast)=LogAst;
							}
#line 1897 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 464 "parser.y" /* yacc.c:1646  */
    {
								(yyval.ast)=(yyvsp[0].ast);
							}
#line 1905 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 468 "parser.y" /* yacc.c:1646  */
    {
								(yyval.ast)=(yyvsp[-1].ast);
							}
#line 1913 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 474 "parser.y" /* yacc.c:1646  */
    {
								if((yyvsp[-1].integer_value)==1)
								{	
									Ast* RelAst=new Relational_Expr_Ast((yyvsp[-2].ast),less_than,(yyvsp[0].ast),yylineno);
									RelAst->check_ast();
									(yyval.ast)=RelAst;
								}
								else if((yyvsp[-1].integer_value)==2)
								{	
									Ast* RelAst=new Relational_Expr_Ast((yyvsp[-2].ast),less_equalto,(yyvsp[0].ast),yylineno);
									RelAst->check_ast();
									(yyval.ast)=RelAst;
								}
								else if((yyvsp[-1].integer_value)==3)
								{	
									Ast* RelAst=new Relational_Expr_Ast((yyvsp[-2].ast),greater_than,(yyvsp[0].ast),yylineno);
									RelAst->check_ast();
									(yyval.ast)=RelAst;
								}
								else
								{	
									Ast* RelAst=new Relational_Expr_Ast((yyvsp[-2].ast),greater_equalto,(yyvsp[0].ast),yylineno);
									RelAst->check_ast();
									(yyval.ast)=RelAst;
								}

							}
#line 1945 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 502 "parser.y" /* yacc.c:1646  */
    {
								if((yyvsp[-1].integer_value)==1)
								{	
									Ast* RelAst=new Relational_Expr_Ast((yyvsp[-2].ast),equalto,(yyvsp[0].ast),yylineno);
									RelAst->check_ast();
									(yyval.ast)=RelAst;
								}
								else
								{	
									Ast* RelAst=new Relational_Expr_Ast((yyvsp[-2].ast),not_equalto,(yyvsp[0].ast),yylineno);
									RelAst->check_ast();
									(yyval.ast)=RelAst;
								}
							}
#line 1964 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 518 "parser.y" /* yacc.c:1646  */
    {
									(yyval.integer_value)=1;
								}
#line 1972 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 521 "parser.y" /* yacc.c:1646  */
    {
									(yyval.integer_value)=2;
								}
#line 1980 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 524 "parser.y" /* yacc.c:1646  */
    {
									(yyval.integer_value)=3;
								}
#line 1988 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 527 "parser.y" /* yacc.c:1646  */
    {
									(yyval.integer_value)=4;
								}
#line 1996 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 532 "parser.y" /* yacc.c:1646  */
    {
									(yyval.integer_value)=1;
								}
#line 2004 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 535 "parser.y" /* yacc.c:1646  */
    {
									(yyval.integer_value)=2;
								}
#line 2012 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 541 "parser.y" /* yacc.c:1646  */
    {
								if(!program_object.variable_proc_name_check(*(yyvsp[-3].string_value))){
									yyerror("call to unknown function");
								}
								else{
									Ast* callAst = new Call_Ast(*(yyvsp[-3].string_value),yylineno);
									((Call_Ast*)callAst)->set_actual_param_list(*(yyvsp[-1].ast_list));
									(yyval.ast)=callAst;
								}
							}
#line 2027 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 552 "parser.y" /* yacc.c:1646  */
    {
								if(!program_object.variable_proc_name_check(*(yyvsp[-2].string_value))){
									yyerror("call to unknown function");
								}
								else{
									Ast* callAst = new Call_Ast(*(yyvsp[-2].string_value),yylineno);
									list<Ast*> * exp = new list<Ast *>();
									((Call_Ast*)callAst)->set_actual_param_list(*exp);
									(yyval.ast)=callAst;
								}
							}
#line 2043 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 566 "parser.y" /* yacc.c:1646  */
    {
								(yyvsp[-2].ast_list)->push_back((yyvsp[0].ast));
								(yyval.ast_list)=(yyvsp[-2].ast_list);
							}
#line 2052 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 571 "parser.y" /* yacc.c:1646  */
    {
								list<Ast*> * exp = new list<Ast *>();
								exp->push_back((yyvsp[0].ast));
								(yyval.ast_list)=exp;
							}
#line 2062 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 579 "parser.y" /* yacc.c:1646  */
    {
								Ast* assAst = new Assignment_Ast((yyvsp[-3].ast),(yyvsp[-1].ast),yylineno);
								assAst->check_ast();
								(yyval.ast)= assAst;
							}
#line 2072 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 585 "parser.y" /* yacc.c:1646  */
    {
								Ast* assAst = new Assignment_Ast((yyvsp[-3].ast),(yyvsp[-1].ast),yylineno);
								assAst->check_ast();
								(yyval.ast)= assAst;
							}
#line 2082 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 593 "parser.y" /* yacc.c:1646  */
    {
								// cout<<"1"<<endl;
								//$2->print();
								// cout<<"2"<<endl;
								Ast *unaryAst = new UMinus_Ast((yyvsp[0].ast),NULL,yylineno);
								// unaryAst->check_ast();
								// cout<<"3"<<endl;
								(yyval.ast) = unaryAst;
							}
#line 2096 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 603 "parser.y" /* yacc.c:1646  */
    {
								Ast *plusAst = new Plus_Ast((yyvsp[-2].ast),(yyvsp[0].ast),yylineno);
								plusAst->check_ast();
								(yyval.ast) = plusAst;
							}
#line 2106 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 609 "parser.y" /* yacc.c:1646  */
    {
								Ast *minAst = new Minus_Ast((yyvsp[-2].ast),(yyvsp[0].ast),yylineno);
								minAst->check_ast();
								(yyval.ast) = minAst;
							}
#line 2116 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 615 "parser.y" /* yacc.c:1646  */
    {
								Ast *mulAst = new Mult_Ast((yyvsp[-2].ast),(yyvsp[0].ast),yylineno);
								mulAst->check_ast();
								(yyval.ast) = mulAst;
							}
#line 2126 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 621 "parser.y" /* yacc.c:1646  */
    {
								Ast *divAst = new Divide_Ast((yyvsp[-2].ast),(yyvsp[0].ast),yylineno);
								divAst->check_ast();
								(yyval.ast) = divAst;
							}
#line 2136 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 627 "parser.y" /* yacc.c:1646  */
    {
								Ast *CondAst= new Conditional_Expression_Ast((yyvsp[-4].ast),(yyvsp[-2].ast),(yyvsp[0].ast),yylineno);
								CondAst->check_ast();
								(yyval.ast) = CondAst;
							}
#line 2146 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 633 "parser.y" /* yacc.c:1646  */
    {
								(yyval.ast)=(yyvsp[-1].ast);
							}
#line 2154 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 637 "parser.y" /* yacc.c:1646  */
    {
								(yyval.ast) = (yyvsp[0].ast);
							}
#line 2162 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 641 "parser.y" /* yacc.c:1646  */
    {
								Ast* intAst = new Number_Ast<int>((yyvsp[0].integer_value),int_data_type,yylineno);
								(yyval.ast)= intAst;
							}
#line 2171 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 646 "parser.y" /* yacc.c:1646  */
    {
								Ast* doubAst = new Number_Ast<double>((yyvsp[0].double_value),double_data_type,yylineno);
								(yyval.ast) = doubAst;
							}
#line 2180 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 653 "parser.y" /* yacc.c:1646  */
    {
							Symbol_Table symtab ;
							if(curProc->get_local_list().variable_in_symbol_list_check(*(yyvsp[0].string_value))){
								symtab=curProc->get_local_list();
							}
							else if(curProc->get_formal_param_list().variable_in_symbol_list_check(*(yyvsp[0].string_value))){
								symtab=curProc->get_formal_param_list();
							}
							else if(gtab->variable_in_symbol_list_check(*(yyvsp[0].string_value))){
								symtab=*gtab;
							}
							else{
								yyerror("Variable has not been declared");
							}

							Ast* varAst = new Name_Ast(*(yyvsp[0].string_value),symtab.get_symbol_table_entry(*(yyvsp[0].string_value)),yylineno);
							varAst->set_data_type(symtab.get_symbol_table_entry(*(yyvsp[0].string_value)).get_data_type());
							(yyval.ast)= varAst;
						}
#line 2204 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2208 "parser.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
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
                      yytoken, &yylval);
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
  return yyresult;
}
#line 674 "parser.y" /* yacc.c:1906  */

void yyerror(char* s){
    printf("cs316: Error : Line : %d: %s\n",yylineno,s);
	exit(0);
}
// void yyparse()
