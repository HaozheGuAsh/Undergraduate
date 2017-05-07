/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */

#line 67 "HW6-sql.tab.cpp" /* yacc.c:339  */

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
    IDENT = 258,
    NUMBER = 259,
    STRING = 260,
    NUL = 261,
    SELECT = 262,
    AS = 263,
    FROM = 264,
    WHERE = 265,
    GROUP = 266,
    BY = 267,
    HAVING = 268,
    ORDER = 269,
    ASC = 270,
    DESC = 271,
    INSERT = 272,
    INTO = 273,
    VALUES = 274,
    UPDATE = 275,
    SET = 276,
    DELETE = 277,
    CREATE = 278,
    TABLE = 279,
    DESCRIBE = 280,
    SHOW = 281,
    TABLES = 282,
    DROP = 283,
    UNIQUE = 284,
    DISTINCT = 285,
    PRIMARY = 286,
    KEY = 287,
    IN = 288,
    NOTEQ = 289,
    GEQ = 290,
    LEQ = 291,
    AND = 292,
    OR = 293,
    NOT = 294,
    QUIT = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 156 "HW6-sql.tab.cpp" /* yacc.c:358  */

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   243

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  151

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

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
      42,    43,    50,    48,    45,    49,     2,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
      47,    44,    46,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    44,    44,    45,    46,    49,    52,    55,    58,    64,
      67,    70,    74,    78,    81,    85,    91,    97,    98,   100,
     102,   104,   106,   108,   110,   114,   116,   120,   122,   127,
     129,   131,   135,   145,   146,   149,   150,   153,   154,   158,
     160,   164,   167,   168,   172,   174,   178,   180,   182,   184,
     186,   188,   192,   194,   198,   200,   204,   206,   210,   212,
     214,   216,   218,   220,   225,   227,   231,   233,   235,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "NUMBER", "STRING", "NUL",
  "SELECT", "AS", "FROM", "WHERE", "GROUP", "BY", "HAVING", "ORDER", "ASC",
  "DESC", "INSERT", "INTO", "VALUES", "UPDATE", "SET", "DELETE", "CREATE",
  "TABLE", "DESCRIBE", "SHOW", "TABLES", "DROP", "UNIQUE", "DISTINCT",
  "PRIMARY", "KEY", "IN", "NOTEQ", "GEQ", "LEQ", "AND", "OR", "NOT",
  "QUIT", "';'", "'('", "')'", "'='", "','", "'>'", "'<'", "'+'", "'-'",
  "'*'", "'/'", "$accept", "program", "sql_command", "tablename",
  "colname", "expr", "fcall", "fncargs", "value", "select_expr",
  "whereclause", "havingclause", "groupclause", "grouplist", "groupspec",
  "orderclause", "orderlist", "orderspec", "projection", "outcol", "join",
  "data_list", "column_decls", "column_decl", "bin_op", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,    59,    40,    41,    61,    44,    62,    60,    43,    45,
      42,    47
};
# endif

#define YYPACT_NINF -41

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-41)))

#define YYTABLE_NINF -17

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -41,     7,   -41,   -31,    33,    -1,    18,    16,    10,    18,
       4,    17,    43,   -41,    49,   -41,    37,   -41,   -41,     8,
     -41,    77,   -41,   -41,     0,   -41,    18,   -41,    28,    18,
      18,    55,    59,    18,   -41,   -41,     1,    61,   116,    31,
      56,    62,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,    57,    18,    33,    21,    56,    91,
      74,   -41,   -41,    67,   -41,   192,     9,   -41,   -41,   -41,
     -41,   110,   -41,     8,   -41,   -41,     6,   -41,    76,    78,
      85,    63,    56,   -41,   -41,    63,    93,   135,    94,    63,
      18,   109,    66,   -41,    63,   154,    32,    13,   -41,   192,
     -41,   -41,   -41,   192,   -41,   126,   127,   -41,   -41,   -41,
      46,    97,   -41,    90,   -41,    98,    56,    56,    63,   128,
     114,    82,    63,   -41,   -41,   -41,   -41,   111,   -41,   192,
     145,   -41,   -41,   -41,   -41,   -41,   173,    56,    89,   -41,
     -41,    65,    79,   113,   -41,   -41,   -41,   -41,   -41,    89,
     -41
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     0,    14,    29,    30,    31,     0,
      55,     0,    24,    17,     0,    52,     0,    15,     0,     0,
       0,     0,     0,     0,     4,     7,     0,    29,     0,     0,
       0,     0,    70,    73,    74,    79,    80,    69,    71,    72,
      75,    76,    77,    78,     0,     0,     0,     0,     0,     0,
       0,    11,    12,     0,    26,    27,     0,    23,    22,    16,
      54,     0,    29,     0,    18,    56,    33,    53,     0,     0,
       0,     0,     0,    13,    25,     0,     0,     0,     0,     0,
       0,    37,     0,     6,     0,     0,    66,     0,    64,    28,
      21,    19,    20,    34,    57,     0,    35,    58,    59,    60,
       0,     0,     9,     0,    67,     0,     0,     0,     0,    42,
       0,     0,     0,    68,    10,    65,    41,    38,    39,    36,
       0,    32,     5,    61,    62,    63,     0,     0,     0,     8,
      40,    46,    49,    43,    44,    47,    48,    50,    51,     0,
      45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -41,   -41,   -41,    -7,   -40,   -16,   -41,   -41,   107,   -18,
     -41,   -41,   -41,   -41,    38,   -41,   -41,    25,   -41,   120,
     -41,   -41,   -41,    64,   -41
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    13,    28,    20,    21,    22,    66,    23,    14,
      91,   119,   106,   127,   128,   131,   143,   144,    24,    25,
      76,   110,    97,    98,    54
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,    39,    31,    38,    37,    17,    18,     2,     3,    55,
      15,    37,    17,    18,     4,     4,    89,    26,    80,    57,
      65,    27,    59,    60,     5,    29,    63,     6,     4,     7,
       8,    32,     9,    10,    30,    11,    16,    17,    18,    79,
      78,    33,    96,    19,    64,    56,   -16,    12,    75,    58,
      19,    90,    84,    86,    85,    88,   115,    87,   116,    69,
      72,    17,    18,   113,   114,    95,    37,    17,    18,    99,
     107,   108,   109,   103,    68,    19,    96,   126,   111,    36,
     145,   146,   -16,   104,    34,    40,   133,   134,   135,   120,
      35,   121,    69,   141,   147,   148,    61,   126,   142,    73,
      62,    81,   129,    36,    71,    19,   136,   122,    83,   142,
      41,    42,    43,    44,    45,    46,    82,     4,    92,    93,
     105,    47,   123,    48,    49,    50,    51,    52,    53,    94,
      41,    42,    43,    44,    45,    46,   100,   102,   117,   124,
     118,    47,   130,    48,    49,    50,    51,    52,    53,    41,
      42,    43,    44,    45,    46,   132,   137,   138,   149,    67,
      47,    74,    48,    49,    50,    51,    52,    53,    41,    42,
      43,    44,    45,    46,   150,   140,    77,     0,   101,    47,
     125,    48,    49,    50,    51,    52,    53,    41,    42,    43,
      44,    45,    46,     0,     0,   112,     0,     0,    47,     0,
      48,    49,    50,    51,    52,    53,    41,    42,    43,    44,
      45,    46,     0,     0,   139,     0,     0,    47,     0,    48,
      49,    50,    51,    52,    53,    41,    42,    43,    44,    45,
      46,     0,     0,     0,     0,     0,    47,     0,    48,    49,
      50,    51,    52,    53
};

static const yytype_int16 yycheck[] =
{
      40,    19,     9,    19,     3,     4,     5,     0,     1,     9,
      41,     3,     4,     5,     7,     7,    10,    18,    58,    26,
      36,     3,    29,    30,    17,     9,    33,    20,     7,    22,
      23,    27,    25,    26,    24,    28,     3,     4,     5,    57,
      19,    24,    82,    42,    43,    45,     9,    40,    55,    21,
      42,    45,    43,    71,    45,    73,    43,    73,    45,     3,
       3,     4,     5,    31,    32,    81,     3,     4,     5,    85,
       4,     5,     6,    89,    43,    42,   116,   117,    94,    42,
      15,    16,    45,    90,    41,     8,     4,     5,     6,    43,
      41,    45,     3,     4,    15,    16,    41,   137,   138,    42,
      41,    10,   118,    42,    42,    42,   122,    10,    41,   149,
      33,    34,    35,    36,    37,    38,    42,     7,    42,    41,
      11,    44,    32,    46,    47,    48,    49,    50,    51,    44,
      33,    34,    35,    36,    37,    38,    43,    43,    12,    41,
      13,    44,    14,    46,    47,    48,    49,    50,    51,    33,
      34,    35,    36,    37,    38,    41,    45,    12,    45,    43,
      44,    54,    46,    47,    48,    49,    50,    51,    33,    34,
      35,    36,    37,    38,   149,   137,    56,    -1,    43,    44,
     116,    46,    47,    48,    49,    50,    51,    33,    34,    35,
      36,    37,    38,    -1,    -1,    41,    -1,    -1,    44,    -1,
      46,    47,    48,    49,    50,    51,    33,    34,    35,    36,
      37,    38,    -1,    -1,    41,    -1,    -1,    44,    -1,    46,
      47,    48,    49,    50,    51,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    44,    -1,    46,    47,
      48,    49,    50,    51
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    53,     0,     1,     7,    17,    20,    22,    23,    25,
      26,    28,    40,    54,    61,    41,     3,     4,     5,    42,
      56,    57,    58,    60,    70,    71,    18,     3,    55,     9,
      24,    55,    27,    24,    41,    41,    42,     3,    57,    61,
       8,    33,    34,    35,    36,    37,    38,    44,    46,    47,
      48,    49,    50,    51,    76,     9,    45,    55,    21,    55,
      55,    41,    41,    55,    43,    57,    59,    43,    43,     3,
      56,    42,     3,    42,    60,    55,    72,    71,    19,    61,
      56,    10,    42,    41,    43,    45,    61,    57,    61,    10,
      45,    62,    42,    41,    44,    57,    56,    74,    75,    57,
      43,    43,    43,    57,    55,    11,    64,     4,     5,     6,
      73,    57,    41,    31,    32,    43,    45,    12,    13,    63,
      43,    45,    10,    32,    41,    75,    56,    65,    66,    57,
      14,    67,    41,     4,     5,     6,    57,    45,    12,    41,
      66,     4,    56,    68,    69,    15,    16,    15,    16,    45,
      69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    55,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    58,    58,    59,    59,    60,
      60,    60,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    67,    67,    68,    68,    69,    69,    69,    69,
      69,    69,    70,    70,    71,    71,    72,    72,    73,    73,
      73,    73,    73,    73,    74,    74,    75,    75,    75,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     3,     8,     5,     2,     9,     6,
       7,     3,     3,     4,     2,     1,     1,     1,     3,     5,
       5,     5,     3,     3,     1,     4,     3,     1,     3,     1,
       1,     1,     8,     0,     2,     0,     2,     0,     3,     1,
       3,     1,     0,     3,     1,     3,     1,     2,     2,     1,
       2,     2,     1,     3,     3,     1,     1,     3,     1,     1,
       1,     3,     3,     3,     1,     3,     1,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
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
        case 3:
#line 45 "HW6-sql.ypp" /* yacc.c:1646  */
    { freen = initfreen; /* Recover unused nodes */ }
#line 1360 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 46 "HW6-sql.ypp" /* yacc.c:1646  */
    { return 0; }
#line 1366 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 50 "HW6-sql.ypp" /* yacc.c:1646  */
    { print_relation(evalexpr(optimize(compile(makeexpr(OP_INSERTROW, 2, (yyvsp[-5]), (yyvsp[-2])))),0)); (yyval)=0; }
#line 1372 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 53 "HW6-sql.ypp" /* yacc.c:1646  */
    { print_relation(evalexpr(optimize(compile(makeexpr(OP_INSERT, 2, (yyvsp[-2]), (yyvsp[-1])))),0)); (yyval)=0; }
#line 1378 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 56 "HW6-sql.ypp" /* yacc.c:1646  */
    { print_relation(evalexpr(optimize(compile((yyvsp[-1]))),0)); }
#line 1384 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 59 "HW6-sql.ypp" /* yacc.c:1646  */
    { print_relation(evalexpr(optimize(compile(
			makeexpr(OP_UPDATE, 2, (yyvsp[-7]), makeexpr(OP_PROJECTION,2,makeexpr(OP_SELECTION, 2, (yyvsp[-7]), (yyvsp[-1])), 
									    makeexpr(OP_RLIST,2,makeexpr(OP_AS,2,(yyvsp[-5]),(yyvsp[-3])),0)))
			)),0)); (yyval)=0; }
#line 1393 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 65 "HW6-sql.ypp" /* yacc.c:1646  */
    { print_relation(evalexpr(optimize(compile(makeexpr(OP_DELETE, 2, (yyvsp[-3]), (yyvsp[-1])))),0)); (yyval)=0; }
#line 1399 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 68 "HW6-sql.ypp" /* yacc.c:1646  */
    { print_relation(evalexpr(optimize(compile(makeexpr(OP_CREATETABLE, 2, (yyvsp[-4]), (yyvsp[-2])))),0)); (yyval)=0; }
#line 1405 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 71 "HW6-sql.ypp" /* yacc.c:1646  */
    { print_relation(evalexpr(optimize(compile(makeexpr(OP_DESCRIBE, 1, (yyvsp[-1]), 0))),0)); (yyval)=0; }
#line 1411 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 75 "HW6-sql.ypp" /* yacc.c:1646  */
    { print_relation(evalexpr(optimize(compile(makeexpr(OP_SHOWTABLES, 0, 0, 0))),0)); (yyval)=0; }
#line 1417 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 79 "HW6-sql.ypp" /* yacc.c:1646  */
    { print_relation(evalexpr(optimize(compile(makeexpr(OP_DROPTABLE, 2, (yyvsp[-1]), 0))),0)); (yyval)=0; }
#line 1423 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 86 "HW6-sql.ypp" /* yacc.c:1646  */
    {
		  (yyval) = makeexpr(OP_TABLENAME, 1, (yyvsp[0]), 0);
		}
#line 1431 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 92 "HW6-sql.ypp" /* yacc.c:1646  */
    {
		  (yyval) = makeexpr(OP_COLNAME, 1, (yyvsp[0]), 0);
		}
#line 1439 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 99 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr((intptr_t )(yyvsp[-1]), 2, (yyvsp[-2]), (yyvsp[0])); }
#line 1445 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 101 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr((intptr_t )(yyvsp[-3]), 2, (yyvsp[-4]), (yyvsp[-1])); }
#line 1451 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 103 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr((intptr_t )(yyvsp[-3]), 2, (yyvsp[-4]), (yyvsp[-1])); }
#line 1457 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 105 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_IN, 2, (yyvsp[-4]), (yyvsp[-1])); }
#line 1463 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 107 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1469 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 109 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1475 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 111 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1481 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 115 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_FCALL, 2, makeexpr(OP_FNAME, 1, (yyvsp[-3]), 0), (yyvsp[-1])); }
#line 1487 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 117 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_FCALL, 2, makeexpr(OP_FNAME, 1, (yyvsp[-2]), 0), 0); }
#line 1493 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 121 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, (yyvsp[0]), 0); }
#line 1499 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 123 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, (yyvsp[0]), (yyvsp[-2])); }
#line 1505 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 128 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_COLNAME, 1, (yyvsp[0]), 0); }
#line 1511 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 130 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_NUMBER, 1, (yyvsp[0]), 0); }
#line 1517 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 132 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_STRING, 1, (yyvsp[0]), 0); }
#line 1523 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 136 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-4]);
		  if((yyvsp[-3])) (yyval) = makeexpr(OP_SELECTION, 2, (yyval), (yyvsp[-3]));
		  if((yyvsp[-2])) (yyval) = makeexpr(OP_GROUP, 2, (yyval), (yyvsp[-2]));
		  (yyval) = makeexpr(OP_PROJECTION, 2, (yyval), (yyvsp[-6]));
		  if((yyvsp[-1])) (yyval) = makeexpr(OP_SELECTION, 2, (yyval), (yyvsp[-1]));
		  if((yyvsp[0])) (yyval) = makeexpr(OP_SORT, 2, (yyval), (yyvsp[0]));
		}
#line 1535 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 145 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = 0; }
#line 1541 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 146 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1547 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 149 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = 0; }
#line 1553 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 150 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1559 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 153 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = 0; }
#line 1565 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 155 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1571 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 159 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, (yyvsp[0]), 0); }
#line 1577 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 161 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, (yyvsp[0]), (yyvsp[-2])); }
#line 1583 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 167 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = 0; }
#line 1589 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 169 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1595 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 173 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, (yyvsp[0]), 0); }
#line 1601 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 175 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, (yyvsp[0]), (yyvsp[-2])); }
#line 1607 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 179 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, (yyvsp[0]), 0), 0); }
#line 1613 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 181 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, (yyvsp[-1]), 0), 0); }
#line 1619 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 183 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_SORTSPEC, 2, makeexpr(OP_NUMBER, 1, (yyvsp[-1]), 0), makeexpr(OP_NULL, 0, 0, 0)); }
#line 1625 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 185 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_SORTSPEC, 2, (yyvsp[0]), 0); }
#line 1631 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 187 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_SORTSPEC, 2, (yyvsp[-1]), 0); }
#line 1637 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 189 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_SORTSPEC, 2, (yyvsp[-1]), makeexpr(OP_NULL, 0, 0, 0)); }
#line 1643 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 193 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, (yyvsp[0]), 0); }
#line 1649 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 195 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, (yyvsp[0]), (yyvsp[-2])); }
#line 1655 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 199 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_OUTCOLNAME, 2, (yyvsp[-2]), (yyvsp[0])); }
#line 1661 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 201 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_OUTCOLNAME, 2, (yyvsp[0]), (yyvsp[0])); }
#line 1667 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 205 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1673 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 207 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_PRODUCT, 2, (yyvsp[-2]), (yyvsp[0])); }
#line 1679 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 211 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, makeexpr(OP_NUMBER, 1, (yyvsp[0]), 0), 0); }
#line 1685 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 213 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, makeexpr(OP_STRING, 1, (yyvsp[0]), 0), 0); }
#line 1691 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 215 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, makeexpr(OP_NULL,0,0, 0), 0); }
#line 1697 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 217 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, makeexpr(OP_NUMBER, 1, (yyvsp[0]), 0), (yyvsp[-2])); }
#line 1703 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 219 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, makeexpr(OP_STRING, 1, (yyvsp[0]), 0), (yyvsp[-2])); }
#line 1709 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 221 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, makeexpr(OP_NULL, 0, 0, 0), (yyvsp[-2])); }
#line 1715 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 226 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, (yyvsp[0]), 0); }
#line 1721 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 228 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_RLIST, 2, (yyvsp[0]), (yyvsp[-2])); }
#line 1727 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 232 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_COLUMNDEF, 2, (yyvsp[0]), 0); }
#line 1733 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 234 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_COLUMNDEF, 2, (yyvsp[-1]), makestrexpr("KEY")); }
#line 1739 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 236 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = makeexpr(OP_COLUMNDEF, 2, (yyvsp[-2]), makestrexpr("PRIMARY")); }
#line 1745 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 239 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (expr)OP_EQUAL; }
#line 1751 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 240 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (expr)OP_NOTEQ; }
#line 1757 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 241 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (expr)OP_GT; }
#line 1763 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 242 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (expr)OP_LT; }
#line 1769 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 243 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (expr)OP_GEQ; }
#line 1775 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 244 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (expr)OP_LEQ; }
#line 1781 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 245 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (expr)OP_PLUS; }
#line 1787 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 246 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (expr)OP_BMINUS; }
#line 1793 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 247 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (expr)OP_TIMES; }
#line 1799 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 248 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (expr)OP_DIVIDE; }
#line 1805 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 249 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (expr)OP_AND; }
#line 1811 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 250 "HW6-sql.ypp" /* yacc.c:1646  */
    { (yyval) = (expr)OP_OR; }
#line 1817 "HW6-sql.tab.cpp" /* yacc.c:1646  */
    break;


#line 1821 "HW6-sql.tab.cpp" /* yacc.c:1646  */
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
#line 253 "HW6-sql.ypp" /* yacc.c:1906  */

int
yyerror(char *str)
{
	printf("Line %d: %s\n", linenum, str);
	return 1;
}

