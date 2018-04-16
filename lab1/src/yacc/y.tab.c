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
#line 1 "yacc/bison.y" /* yacc.c:339  */

#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#ifndef _BISON_H
#include "location.h"
#include "../core/dc_error.h"
#include "bison.h"
#endif


#line 79 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOL = 258,
    BREAK = 259,
    CLASS = 260,
    ELSE = 261,
    EXTENDS = 262,
    FOR = 263,
    IF = 264,
    INT = 265,
    NEW = 266,
    RETURN = 267,
    STRING = 268,
    THIS = 269,
    VOID = 270,
    WHILE = 271,
    STATIC = 272,
    PRINT = 273,
    READINTEGER = 274,
    READLINE = 275,
    INSTANCEOF = 276,
    NULLCONSTANT = 277,
    BOOLCONSTANT = 278,
    INTCONSTANT = 279,
    STRINGCONSTANT = 280,
    ID = 281,
    SEMI = 282,
    COMMA = 283,
    LC = 284,
    RC = 285,
    LOWER_THAN_ELSE = 286,
    ASSIGNOP = 287,
    OR = 288,
    AND = 289,
    GREATER = 290,
    LESS = 291,
    GREATEREQUAL = 292,
    LESSEQUAL = 293,
    EQUAL = 294,
    NOTEQUAL = 295,
    PLUS = 296,
    MINUS = 297,
    STAR = 298,
    DIV = 299,
    MOD = 300,
    NOT = 301,
    UMINUS = 302,
    LP = 303,
    RP = 304,
    LB = 305,
    RB = 306,
    DOT = 307
  };
#endif
/* Tokens.  */
#define BOOL 258
#define BREAK 259
#define CLASS 260
#define ELSE 261
#define EXTENDS 262
#define FOR 263
#define IF 264
#define INT 265
#define NEW 266
#define RETURN 267
#define STRING 268
#define THIS 269
#define VOID 270
#define WHILE 271
#define STATIC 272
#define PRINT 273
#define READINTEGER 274
#define READLINE 275
#define INSTANCEOF 276
#define NULLCONSTANT 277
#define BOOLCONSTANT 278
#define INTCONSTANT 279
#define STRINGCONSTANT 280
#define ID 281
#define SEMI 282
#define COMMA 283
#define LC 284
#define RC 285
#define LOWER_THAN_ELSE 286
#define ASSIGNOP 287
#define OR 288
#define AND 289
#define GREATER 290
#define LESS 291
#define GREATEREQUAL 292
#define LESSEQUAL 293
#define EQUAL 294
#define NOTEQUAL 295
#define PLUS 296
#define MINUS 297
#define STAR 298
#define DIV 299
#define MOD 300
#define NOT 301
#define UMINUS 302
#define LP 303
#define RP 304
#define LB 305
#define RB 306
#define DOT 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 15 "yacc/bison.y" /* yacc.c:355  */

    int nullcon;
    int boolcon;
    int intcon;
    char stringcon[100+1];
    char identifier[100+1];
    Program *program;
    Id *id;
    Decl *decl;
    VarDecl *vardecl;
    FnDecl *fndecl;
    ClassDecl *classdecl;

    Type *type;
    IntType *inttype;
    BoolType *booltype;
    StringType *stringtype;
    VoidType *voidtype;
    NamedType *nametype;
    ArrayType *arraytype;

    StmtBlock *stmtblock;
    Stmt *stmt;
    IfStmt *ifstmt;
    WhileStmt *whilestmt;
    ForStmt *forstmt;
    ReturnStmt *returnstmt;
    BreakStmt *breakstmt;
    PrintStmt *printstmt;

    Expr *expr;
    AssignExpr *assignexpr;
    ArithmeticExpr *arithmeticexpr;
    RelationExpr *relationexpr;
    LogicalExpr *logicalexpr;
    Lvalue *lvalue;
    FieldAccess *fieldaccess;
    ArrayAccess *arrayaccess;
    Call *call;
    This *_this;
    ReadInteger *readinteger;
    ReadLine *readline;
    Instanceof *instanceof;
    NewExpr *newexpr;
    NewArrayExpr *newarrayexpr;

    Constant *constant;
    IntCon *intconstant;
    BoolCon *boolconstant;
    StringCon *stringconstant;
    NullCon *nullconstant;

    vector<Decl*> *decllist;
    vector<VarDecl*> *formals;
    vector<Decl*> *fields;

    vector<VarDecl*> *variables;
    vector<VarDecl*> *vardecls;

    vector<Stmt*> *stmts;

    vector<Expr*> *exprs;
    vector<Expr*> *actuals;

#line 288 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 319 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   592

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  210

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   148,   148,   151,   152,   155,   156,   157,   160,   161,
     164,   165,   166,   167,   168,   171,   174,   177,   179,   181,
     183,   187,   188,   191,   193,   196,   198,   200,   202,   206,
     207,   210,   211,   225,   227,   229,   231,   234,   235,   238,
     239,   242,   243,   244,   245,   246,   247,   248,   249,   253,
     255,   260,   264,   268,   274,   280,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   295,   297,   299,   301,
     308,   311,   315,   319,   321,   323,   325,   327,   329,   333,
     335,   337,   339,   341,   343,   347,   349,   351,   356,   358,
     362,   363,   366,   367,   370,   371,   374,   376,   380,   383,
     384,   387,   388,   389,   390
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "BREAK", "CLASS", "ELSE",
  "EXTENDS", "FOR", "IF", "INT", "NEW", "RETURN", "STRING", "THIS", "VOID",
  "WHILE", "STATIC", "PRINT", "READINTEGER", "READLINE", "INSTANCEOF",
  "NULLCONSTANT", "BOOLCONSTANT", "INTCONSTANT", "STRINGCONSTANT", "ID",
  "SEMI", "COMMA", "LC", "RC", "LOWER_THAN_ELSE", "ASSIGNOP", "OR", "AND",
  "GREATER", "LESS", "GREATEREQUAL", "LESSEQUAL", "EQUAL", "NOTEQUAL",
  "PLUS", "MINUS", "STAR", "DIV", "MOD", "NOT", "UMINUS", "LP", "RP", "LB",
  "RB", "DOT", "$accept", "Program", "DeclList", "Decl", "VarDecl", "Type",
  "NamedType", "ArrayType", "FnDecl", "Formals", "Variables", "ClassDecl",
  "Fields", "Field", "StmtBlock", "VarDecls", "Stmts", "Stmt", "IfStmt",
  "WhileStmt", "ForStmt", "ReturnStmt", "BreakStmt", "PrintStmt", "Expr",
  "NewExpr", "NewArrayExpr", "AssignExpr", "ArithmeticExpr",
  "RelationalExpr", "LogicalExpr", "Exprs", "OptExpr", "LValue",
  "FieldAccess", "Call", "ArrayAccess", "Actuals", "Constant", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307
};
# endif

#define YYPACT_NINF -90

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-90)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     160,   -90,    -5,   -90,   -90,    -4,   206,    47,   160,   -90,
     -90,   -23,   -90,   -90,   -90,   -90,    -1,     7,    24,    30,
     -21,   -90,   -90,     3,     6,    33,    75,    96,   -90,    29,
      34,    57,   -90,    96,   -90,    64,   -90,   -90,   -90,   355,
     -90,   -11,    51,    68,    96,    96,   -90,    53,   361,   -90,
     -90,   -90,    74,    96,    55,    59,    74,   -90,   383,   132,
     -90,    -9,    74,    74,   -90,   -90,    85,    67,    69,    84,
      12,   -90,    72,    78,    79,    82,    83,   -90,   -90,   -90,
     -90,    86,   -90,    12,    12,    12,   -90,    -8,   -90,   178,
     219,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   521,   -90,
     -90,   -90,   -90,   -90,   -90,   111,    91,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,    12,    12,    99,   109,   133,
      12,    12,   115,   117,    12,    12,   -43,   -43,   421,    13,
     -90,   -90,   260,   -90,   -90,    12,    12,    12,    12,    12,
      12,    12,    12,    12,    12,    12,    12,    12,    12,   141,
     -90,    12,   144,   441,   119,   331,   -90,   461,   521,    -3,
     -90,   -90,   401,   148,   123,   -90,   -90,   540,   296,   210,
     210,   210,   210,   210,   210,   248,   248,   -43,   -43,   -43,
     481,   131,   521,    12,   301,   -90,   501,   301,    12,   157,
     159,   -90,   -90,    12,   381,   187,   -90,   -90,   521,   -90,
     146,   156,    12,   301,   -90,   -90,   161,   -90,   301,   -90
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    11,     0,    10,    12,     0,     0,     0,     2,     4,
       5,     0,    13,    14,     6,     7,    15,     0,     0,     0,
       0,     1,     3,     0,     0,     0,     0,    21,    15,     0,
       0,     0,     8,    21,    16,     0,    28,    31,    32,     0,
      30,     0,     0,    22,    21,    21,     9,     0,     0,    27,
      29,    24,     0,     0,     0,     0,     0,    26,     0,    91,
      18,     0,     0,     0,    17,    25,     0,     0,     0,     0,
      91,    59,     0,     0,     0,     0,     0,   104,   102,   101,
     103,    94,    36,     0,     0,     0,    38,     0,    48,    91,
      91,    40,    42,    43,    44,    46,    45,    47,    90,    68,
      69,    56,    62,    63,    64,     0,    58,    92,    60,    93,
      57,    23,    20,    19,    54,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   100,    78,    87,     0,     0,
      34,    37,    91,    35,    39,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      41,     0,     0,     0,     0,     0,    53,     0,    89,     0,
      65,    66,     0,    99,     0,    61,    33,    86,    85,    79,
      80,    81,    82,    83,    84,    73,    74,    75,    76,    77,
       0,    95,    72,     0,    91,    70,     0,    91,     0,     0,
       0,    96,    98,   100,     0,    49,    71,    51,    88,    55,
       0,     0,    91,    91,    67,    97,     0,    50,    91,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -90,   -90,   -90,   198,     2,    80,   -90,   -90,    16,   -25,
     -90,   -90,   164,    23,    66,   -90,   124,   -89,   -90,   -90,
     -90,   -90,   -90,   -90,   -72,   -90,   -90,   -90,   -90,   -90,
     -90,    93,   -70,   -90,   -90,   -90,   -90,    22,   -90
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    37,    11,    12,    13,    38,    42,
      43,    15,    39,    40,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   163,   105,   106,   107,   108,   109,   164,   110
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     119,   134,    10,    23,    31,    30,    25,   148,    47,   149,
      10,   126,   127,   128,    31,    51,    14,   111,   129,    54,
      55,    16,    17,    69,    14,   188,    71,    24,    26,    24,
      32,    74,    75,    76,    77,    78,    79,    80,    81,    24,
      32,    24,    24,   134,   153,   152,   189,    21,   157,   158,
      28,    33,   162,   158,    83,    27,    29,    34,    84,    35,
      85,    86,    50,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,    44,     1,   182,
      18,    50,    45,   186,    46,     3,    20,     1,     4,    18,
       5,   131,     6,    48,     3,   195,    53,     4,   197,     1,
      52,    18,    56,    59,    62,    36,     3,    41,    63,     4,
     117,   194,   114,    41,   207,   115,   198,   116,    60,   209,
     120,   158,    64,   151,    41,    41,   121,   122,   112,   113,
     123,   124,   206,    61,   125,     1,    66,    18,   150,    87,
      67,    68,     3,    69,    70,     4,    71,   154,    72,   118,
      73,    74,    75,    76,    77,    78,    79,    80,    81,   155,
     156,    59,    82,     1,   160,     2,   161,   181,   185,    87,
       3,   183,   191,     4,    83,     5,   188,     6,    84,   193,
      85,     1,    66,    18,   199,   200,    67,    68,     3,    69,
      70,     4,    71,   203,    72,   204,    73,    74,    75,    76,
      77,    78,    79,    80,    81,   205,    22,    59,   130,     1,
     208,    18,    58,   132,   159,   201,     3,     0,     0,     4,
      83,    19,     0,    66,    84,     0,    85,    67,    68,     0,
      69,    70,     0,    71,     0,    72,     0,    73,    74,    75,
      76,    77,    78,    79,    80,    81,     0,     0,    59,   133,
       0,   143,   144,   145,   146,   147,     0,     0,     0,     0,
     148,    83,   149,     0,    66,    84,     0,    85,    67,    68,
       0,    69,    70,     0,    71,     0,    72,     0,    73,    74,
      75,    76,    77,    78,    79,    80,    81,     0,     0,    59,
     166,   145,   146,   147,     0,     0,     0,     0,   148,     0,
     149,     0,    83,     0,     0,    66,    84,     0,    85,    67,
      68,     0,    69,    70,     0,    71,     0,    72,     0,    73,
      74,    75,    76,    77,    78,    79,    80,    81,     0,     0,
      59,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,    69,    83,     0,    71,   148,    84,   149,    85,
      74,    75,    76,    77,    78,    79,    80,    81,     1,     0,
      18,     0,     0,     0,     1,     3,    18,     0,     4,     0,
       5,     3,     6,    83,     4,     0,     5,    84,     6,    85,
       0,     0,    34,     0,     0,    49,     1,     0,    18,     0,
       0,    57,     0,     3,     0,     0,     4,     0,     5,     0,
       6,     0,     0,     0,     0,     0,     0,     0,   202,     0,
       0,     0,     0,    65,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,     0,     0,   190,
       0,   148,     0,   149,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,     0,     0,     0,
       0,   148,     0,   149,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,     0,     0,     0,
     165,   148,     0,   149,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,     0,     0,     0,
     184,   148,     0,   149,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,     0,     0,     0,
     187,   148,     0,   149,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,     0,     0,     0,
       0,   148,   192,   149,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,     0,     0,     0,
       0,   148,   196,   149,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,     0,     0,     0,
       0,   148,     0,   149,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,     0,     0,     0,     0,
     148,     0,   149
};

static const yytype_int16 yycheck[] =
{
      70,    90,     0,    26,     1,    26,     7,    50,    33,    52,
       8,    83,    84,    85,     1,    26,     0,    26,    26,    44,
      45,    26,    26,    11,     8,    28,    14,    50,    29,    50,
      27,    19,    20,    21,    22,    23,    24,    25,    26,    50,
      27,    50,    50,   132,   116,   115,    49,     0,   120,   121,
      26,    48,   124,   125,    42,    48,    26,    51,    46,    26,
      48,    59,    39,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,    48,     3,   151,
       5,    58,    48,   155,    27,    10,     6,     3,    13,     5,
      15,    89,    17,    29,    10,   184,    28,    13,   187,     3,
      49,     5,    49,    29,    49,    30,    10,    27,    49,    13,
      26,   183,    27,    33,   203,    48,   188,    48,    52,   208,
      48,   193,    56,    32,    44,    45,    48,    48,    62,    63,
      48,    48,   202,    53,    48,     3,     4,     5,    27,    59,
       8,     9,    10,    11,    12,    13,    14,    48,    16,    69,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    50,
      27,    29,    30,     3,    49,     5,    49,    26,    49,    89,
      10,    27,    49,    13,    42,    15,    28,    17,    46,    48,
      48,     3,     4,     5,    27,    26,     8,     9,    10,    11,
      12,    13,    14,     6,    16,    49,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    49,     8,    29,    30,     3,
      49,     5,    48,    89,   121,   193,    10,    -1,    -1,    13,
      42,    15,    -1,     4,    46,    -1,    48,     8,     9,    -1,
      11,    12,    -1,    14,    -1,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    29,    30,
      -1,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      50,    42,    52,    -1,     4,    46,    -1,    48,     8,     9,
      -1,    11,    12,    -1,    14,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    29,
      30,    43,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,
      52,    -1,    42,    -1,    -1,     4,    46,    -1,    48,     8,
       9,    -1,    11,    12,    -1,    14,    -1,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      29,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    11,    42,    -1,    14,    50,    46,    52,    48,
      19,    20,    21,    22,    23,    24,    25,    26,     3,    -1,
       5,    -1,    -1,    -1,     3,    10,     5,    -1,    13,    -1,
      15,    10,    17,    42,    13,    -1,    15,    46,    17,    48,
      -1,    -1,    51,    -1,    -1,    30,     3,    -1,     5,    -1,
      -1,    30,    -1,    10,    -1,    -1,    13,    -1,    15,    -1,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    30,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    28,
      -1,    50,    -1,    52,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    50,    -1,    52,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      49,    50,    -1,    52,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      49,    50,    -1,    52,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      49,    50,    -1,    52,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    50,    51,    52,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    50,    51,    52,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    50,    -1,    52,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      50,    -1,    52
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,    10,    13,    15,    17,    54,    55,    56,
      57,    58,    59,    60,    61,    64,    26,    26,     5,    15,
      58,     0,    56,    26,    50,     7,    29,    48,    26,    26,
      26,     1,    27,    48,    51,    26,    30,    57,    61,    65,
      66,    58,    62,    63,    48,    48,    27,    62,    29,    30,
      66,    26,    49,    28,    62,    62,    49,    30,    65,    29,
      67,    58,    49,    49,    67,    30,     4,     8,     9,    11,
      12,    14,    16,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    30,    42,    46,    48,    57,    58,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    85,    86,    87,    88,    89,
      91,    26,    67,    67,    27,    48,    48,    26,    58,    85,
      48,    48,    48,    48,    48,    48,    77,    77,    77,    26,
      30,    57,    69,    30,    70,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    50,    52,
      27,    32,    85,    77,    48,    50,    27,    77,    77,    84,
      49,    49,    77,    84,    90,    49,    30,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    26,    77,    27,    49,    49,    77,    49,    28,    49,
      28,    49,    51,    48,    77,    70,    51,    70,    77,    27,
      26,    90,    27,     6,    49,    49,    85,    70,    49,    70
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    56,    57,    57,
      58,    58,    58,    58,    58,    59,    60,    61,    61,    61,
      61,    62,    62,    63,    63,    64,    64,    64,    64,    65,
      65,    66,    66,    67,    67,    67,    67,    68,    68,    69,
      69,    70,    70,    70,    70,    70,    70,    70,    70,    71,
      71,    72,    73,    74,    75,    76,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      78,    79,    80,    81,    81,    81,    81,    81,    81,    82,
      82,    82,    82,    82,    82,    83,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    87,    88,    88,    89,    90,
      90,    91,    91,    91,    91
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     4,
       1,     1,     1,     1,     1,     2,     3,     6,     6,     7,
       7,     0,     1,     4,     2,     7,     6,     5,     4,     2,
       1,     1,     1,     4,     3,     3,     2,     2,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     5,
       7,     5,     9,     3,     2,     5,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     3,     6,     1,     1,
       4,     5,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     1,
       1,     0,     1,     1,     1,     3,     4,     6,     4,     1,
       0,     1,     1,     1,     1
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
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
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
     '$$ = $1'.

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
        case 2:
#line 148 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.program)=new Program((yyvsp[0].decllist)); ast_root = (yyval.program);}
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 151 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.decllist)=(yyvsp[-1].decllist))->push_back((yyvsp[0].decl));}
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 152 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.decllist)=new vector<Decl*>)->push_back((yyvsp[0].decl));}
#line 1727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 155 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.decl)=(yyvsp[0].vardecl);}
#line 1733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 156 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.decl)=(yyvsp[0].fndecl);}
#line 1739 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 157 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.decl)=(yyvsp[0].classdecl);}
#line 1745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 160 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.vardecl)=new VarDecl((yyvsp[-2].type),(new Id((yyvsp[-1].identifier),(yylsp[-1]))));}
#line 1751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 161 "yacc/bison.y" /* yacc.c:1646  */
    {}
#line 1757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 164 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.type)=new IntType("int");}
#line 1763 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 165 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.type)=new BoolType("bool");}
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 166 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.type)=new StringType("string");}
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 167 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.type)=(yyvsp[0].nametype);}
#line 1781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 168 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.type)=(yyvsp[0].arraytype);}
#line 1787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 171 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.nametype)=new NamedType("class",new Id((yyvsp[0].identifier),(yylsp[0])));}
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 174 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arraytype)=new ArrayType("[]",(yyvsp[-2].type));}
#line 1799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 178 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.fndecl)=new FnDecl(0,(yyvsp[-5].type),new Id((yyvsp[-4].identifier),(yylsp[-4])),(yyvsp[-2].formals),(yyvsp[0].stmtblock));}
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 180 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.fndecl)=new FnDecl(0,(new VoidType("void")),new Id((yyvsp[-4].identifier),(yylsp[-4])),(yyvsp[-2].formals),(yyvsp[0].stmtblock));}
#line 1811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 182 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.fndecl)=new FnDecl(1,(yyvsp[-5].type),new Id((yyvsp[-4].identifier),(yylsp[-4])),(yyvsp[-2].formals),(yyvsp[0].stmtblock));}
#line 1817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 184 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.fndecl)=new FnDecl(1,(new VoidType("void")),new Id((yyvsp[-4].identifier),(yylsp[-4])),(yyvsp[-2].formals),(yyvsp[0].stmtblock));}
#line 1823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 187 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.formals)=new vector<VarDecl*>;}
#line 1829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 188 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.formals)=(yyvsp[0].variables);}
#line 1835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 192 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.variables)=(yyvsp[-3].variables))->push_back(new VarDecl((yyvsp[-1].type),new Id((yyvsp[0].identifier),(yylsp[0]))));}
#line 1841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 193 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.variables)=new vector<VarDecl*>)->push_back(new VarDecl((yyvsp[-1].type),new Id((yyvsp[0].identifier),(yylsp[0]))));}
#line 1847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 197 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.classdecl)=new ClassDecl(new Id((yyvsp[-5].identifier),(yylsp[-5])),new Id((yyvsp[-3].identifier),(yylsp[-3])),(yyvsp[-1].fields));}
#line 1853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 199 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.classdecl)=new ClassDecl(new Id((yyvsp[-4].identifier),(yylsp[-4])),new Id((yyvsp[-2].identifier),(yylsp[-2])),NULL);}
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 201 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.classdecl)=new ClassDecl(new Id((yyvsp[-3].identifier),(yylsp[-3])),NULL,(yyvsp[-1].fields));}
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 203 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.classdecl)=new ClassDecl(new Id((yyvsp[-2].identifier),(yylsp[-2])),NULL,NULL);}
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 206 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.fields)=(yyvsp[-1].fields))->push_back((yyvsp[0].decl));}
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 207 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.fields)=new vector<Decl*>)->push_back((yyvsp[0].decl));}
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 210 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.decl)=(yyvsp[0].vardecl);}
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 211 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.decl)=(yyvsp[0].fndecl);}
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 226 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmtblock)=new StmtBlock((yyvsp[-2].vardecls),(yyvsp[-1].stmts));}
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 228 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmtblock)=new StmtBlock((yyvsp[-1].vardecls),NULL);}
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 230 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmtblock)=new StmtBlock(NULL,(yyvsp[-1].stmts));}
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 231 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmtblock)=new StmtBlock(NULL,NULL);}
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 234 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.vardecls)=(yyvsp[-1].vardecls))->push_back((yyvsp[0].vardecl));}
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 235 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.vardecls)=new vector<VarDecl*>)->push_back((yyvsp[0].vardecl));}
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 238 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.stmts)=(yyvsp[-1].stmts))->push_back((yyvsp[0].stmt));}
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 239 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.stmts)=new vector<Stmt*>)->push_back((yyvsp[0].stmt));}
#line 1943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 242 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[-1].expr);}
#line 1949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 243 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].ifstmt);}
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 244 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].whilestmt);}
#line 1961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 245 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].forstmt);}
#line 1967 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 246 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].breakstmt);}
#line 1973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 247 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].returnstmt);}
#line 1979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 248 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].printstmt);}
#line 1985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 249 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].stmtblock);}
#line 1991 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 254 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.ifstmt)=new IfStmt((yyvsp[-2].expr),(yyvsp[0].stmt),"",NULL);}
#line 1997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 256 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.ifstmt)=new IfStmt((yyvsp[-4].expr),(yyvsp[-2].stmt),"else",(yyvsp[0].stmt));}
#line 2003 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 261 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.whilestmt)=new WhileStmt((yyvsp[-2].expr),(yyvsp[0].stmt));}
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 265 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.forstmt)=new ForStmt((yyvsp[-6].expr),(yyvsp[-4].expr),(yyvsp[-2].expr),(yyvsp[0].stmt));}
#line 2015 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 269 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.returnstmt)=new ReturnStmt((yyvsp[-1].expr),(yylsp[-2]));
																//为了获得return位置，当optexpr为NULL时，确定return的位置
																}
#line 2023 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 274 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.breakstmt)=new BreakStmt((yylsp[-1]));
																	//获得break位置
																}
#line 2031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 281 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.printstmt)=new PrintStmt((yyvsp[-2].exprs));}
#line 2037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 284 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].assignexpr);}
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 285 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].constant);}
#line 2049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 286 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].lvalue);}
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 287 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=new This();}
#line 2061 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 288 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].call);}
#line 2067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 289 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[-1].expr);}
#line 2073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 290 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].arithmeticexpr);}
#line 2079 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 291 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].relationexpr);}
#line 2085 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 292 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].logicalexpr);}
#line 2091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 294 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=new ReadInteger();}
#line 2097 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 296 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=new ReadLine();}
#line 2103 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 298 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=new Instanceof((yyvsp[-3].expr),new Id((yyvsp[-1].identifier),(yylsp[-1])));}
#line 2109 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 300 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].newexpr);}
#line 2115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 302 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].newarrayexpr);}
#line 2121 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 309 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.newexpr)=new NewExpr(new Id((yyvsp[-2].identifier),(yylsp[-2])));}
#line 2127 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 312 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.newarrayexpr)=new NewArrayExpr((yyvsp[-3].type),(yyvsp[-1].expr));}
#line 2133 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 316 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.assignexpr)=new AssignExpr((yyvsp[-2].lvalue),(yyvsp[0].expr));}
#line 2139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 320 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arithmeticexpr)=new ArithmeticExpr((yyvsp[-2].expr),"+",(yyvsp[0].expr));}
#line 2145 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 322 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arithmeticexpr)=new ArithmeticExpr((yyvsp[-2].expr),"-",(yyvsp[0].expr));}
#line 2151 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 324 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arithmeticexpr)=new ArithmeticExpr((yyvsp[-2].expr),"*",(yyvsp[0].expr));}
#line 2157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 326 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arithmeticexpr)=new ArithmeticExpr((yyvsp[-2].expr),"/",(yyvsp[0].expr));}
#line 2163 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 328 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arithmeticexpr)=new ArithmeticExpr((yyvsp[-2].expr),"%",(yyvsp[0].expr));}
#line 2169 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 330 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arithmeticexpr)=new ArithmeticExpr(NULL,"-",(yyvsp[0].expr));}
#line 2175 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 334 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.relationexpr)=new RelationExpr((yyvsp[-2].expr),">",(yyvsp[0].expr));}
#line 2181 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 336 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.relationexpr)=new RelationExpr((yyvsp[-2].expr),"<",(yyvsp[0].expr));}
#line 2187 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 338 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.relationexpr)=new RelationExpr((yyvsp[-2].expr),">=",(yyvsp[0].expr));}
#line 2193 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 340 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.relationexpr)=new RelationExpr((yyvsp[-2].expr),"<=",(yyvsp[0].expr));}
#line 2199 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 342 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.relationexpr)=new RelationExpr((yyvsp[-2].expr),"==",(yyvsp[0].expr));}
#line 2205 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 344 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.relationexpr)=new RelationExpr((yyvsp[-2].expr),"!=",(yyvsp[0].expr));}
#line 2211 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 348 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.logicalexpr)=new LogicalExpr((yyvsp[-2].expr),"&&",(yyvsp[0].expr));}
#line 2217 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 350 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.logicalexpr)=new LogicalExpr((yyvsp[-2].expr),"||",(yyvsp[0].expr));}
#line 2223 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 352 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.logicalexpr)=new LogicalExpr(NULL,"!",(yyvsp[0].expr));}
#line 2229 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 357 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.exprs)=(yyvsp[-2].exprs))->push_back((yyvsp[0].expr));}
#line 2235 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 359 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.exprs)=new vector<Expr*>)->push_back((yyvsp[0].expr));}
#line 2241 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 362 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 2247 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 363 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=NULL;}
#line 2253 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 366 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.lvalue)=(yyvsp[0].fieldaccess);}
#line 2259 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 367 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.lvalue)=(yyvsp[0].arrayaccess);}
#line 2265 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 370 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.fieldaccess)=new FieldAccess(NULL,new Id((yyvsp[0].identifier),(yylsp[0])));}
#line 2271 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 371 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.fieldaccess)=new FieldAccess((yyvsp[-2].expr),new Id((yyvsp[0].identifier),(yylsp[0])));}
#line 2277 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 375 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.call)=new Call(NULL,new Id((yyvsp[-3].identifier),(yylsp[-3])),(yyvsp[-1].actuals));}
#line 2283 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 377 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.call)=new Call((yyvsp[-5].expr),new Id((yyvsp[-3].identifier),(yylsp[-3])),(yyvsp[-1].actuals));}
#line 2289 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 380 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arrayaccess)=new ArrayAccess((yyvsp[-3].expr),(yyvsp[-1].expr));}
#line 2295 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 383 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.actuals)=(yyvsp[0].exprs);}
#line 2301 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 384 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.actuals)=NULL;}
#line 2307 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 387 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.constant)=new IntCon((yyvsp[0].intcon),(yylsp[0]));}
#line 2313 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 388 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.constant)=new BoolCon((yyvsp[0].boolcon),(yylsp[0]));}
#line 2319 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 389 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.constant)=new StringCon((yyvsp[0].stringcon),(yylsp[0]));}
#line 2325 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 390 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.constant)=new NullCon((yyvsp[0].nullcon),(yylsp[0]));}
#line 2331 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2335 "y.tab.c" /* yacc.c:1646  */
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 392 "yacc/bison.y" /* yacc.c:1906  */


void yyerror(const char* msg) 
{
    errornum++;   
    IssueError::Printyyerror(&yylloc,yytext);
}
