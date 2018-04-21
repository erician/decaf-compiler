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
typedef union YYSTYPE YYSTYPE;
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

    vector<const Expr&> *exprs;
    vector<Expr*> *actuals;

#line 288 "y.tab.c" /* yacc.c:355  */
};
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

#line 317 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   579

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  207

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
       0,   147,   147,   150,   151,   155,   156,   159,   160,   161,
     162,   163,   166,   169,   172,   174,   176,   178,   182,   183,
     186,   188,   191,   193,   195,   197,   201,   202,   205,   206,
     220,   222,   224,   226,   229,   230,   233,   234,   237,   238,
     239,   240,   241,   242,   243,   244,   248,   250,   255,   259,
     263,   269,   275,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   290,   292,   294,   296,   303,   306,   310,
     314,   316,   318,   320,   322,   324,   328,   330,   332,   334,
     336,   338,   342,   344,   346,   351,   353,   357,   358,   361,
     362,   365,   366,   369,   371,   375,   378,   379,   382,   383,
     384,   385
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
  "RB", "DOT", "$accept", "Program", "DeclList", "VarDecl", "Type",
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

#define YYPACT_NINF -87

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-87)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      18,     0,    54,    18,   -87,    -2,   -87,   -87,    29,     4,
      27,   -87,    33,   -87,   -87,    35,    97,   -87,   -87,   -22,
     -87,   -87,   -87,   348,   -87,   354,   -87,    14,    51,   -11,
       2,    31,   -87,   -87,   -87,   370,   159,    36,    37,    70,
     -87,   159,   -87,   -87,   -10,    50,    75,   159,   159,   -87,
      56,   -87,    77,   159,    59,    71,    77,   125,   -87,    -4,
      77,    77,   -87,    95,    76,    78,    91,   324,   -87,    79,
      83,    92,    94,   104,   -87,   -87,   -87,   -87,   105,   -87,
     324,   324,   324,   -87,     7,   -87,   171,   212,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   508,   -87,   -87,   -87,   -87,
     -87,   -87,    96,    93,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   324,   324,   108,   113,   138,   324,   324,   121,
     128,   324,   324,   -14,   -14,   408,     5,   -87,   -87,   253,
     -87,   -87,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   152,   -87,   324,   161,
     428,   137,    67,   -87,   448,   508,     9,   -87,   -87,   388,
     180,   150,   -87,   -87,   527,   289,   116,   116,   116,   116,
     116,   116,   160,   160,   -14,   -14,   -14,   468,   163,   508,
     324,   294,   -87,   488,   294,   324,   182,   188,   -87,   -87,
     324,   368,   209,   -87,   -87,   508,   -87,   169,   173,   324,
     294,   -87,   -87,   176,   -87,   294,   -87
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     4,     0,     1,     3,     0,     0,
       0,     8,     0,     7,     9,     0,     0,    25,    28,     0,
      10,    11,    29,     0,    27,     0,    12,     0,     0,     0,
       0,     0,    24,    26,    23,     0,    18,     0,     0,     0,
       5,    18,    13,    22,     0,     0,    19,    18,    18,     6,
       0,    21,     0,     0,     0,     0,     0,    88,    15,     0,
       0,     0,    14,     0,     0,     0,     0,    88,    56,     0,
       0,     0,     0,     0,   101,    99,    98,   100,    91,    33,
       0,     0,     0,    35,     0,    45,    88,    88,    37,    39,
      40,    41,    43,    42,    44,    87,    65,    66,    53,    59,
      60,    61,     0,    55,    89,    57,    90,    54,    20,    17,
      16,    51,    88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    97,    75,    84,     0,     0,    31,    34,    88,
      32,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,     0,     0,    50,     0,    86,     0,    62,    63,     0,
      96,     0,    58,    30,    83,    82,    76,    77,    78,    79,
      80,    81,    70,    71,    72,    73,    74,     0,    92,    69,
       0,    88,    67,     0,    88,     0,     0,     0,    93,    95,
      97,     0,    46,    68,    48,    85,    52,     0,     0,    88,
      88,    64,    94,     0,    47,    88,    49
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -87,   -87,   -87,   -55,    -6,   -87,   -87,   -87,   -23,   -87,
     224,   204,   -15,   146,   -87,   153,   -86,   -87,   -87,   -87,
     -87,   -87,   -87,   -69,   -87,   -87,   -87,   -87,   -87,   -87,
     122,   -67,   -87,   -87,   -87,   -87,    53,   -87
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    18,    19,    20,    21,    22,    45,    46,
       4,    23,    24,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     160,   102,   103,   104,   105,   106,   161,   107
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     116,   131,    83,    39,    30,     8,    39,    11,    33,    12,
      29,   123,   124,   125,    13,    38,    51,    14,    50,    15,
      33,    16,   108,     1,    54,    55,     5,     9,    31,    40,
      44,   128,    40,   126,    17,    44,   145,   185,   146,    31,
      31,    44,    44,   131,   150,   149,    31,    59,   154,   155,
      41,    84,   159,   155,     6,    10,    25,    31,   186,    26,
     115,    27,    36,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,    37,    66,   179,
      84,    68,    42,   183,    47,    48,    71,    72,    73,    74,
      75,    76,    77,    78,    11,   192,    12,    49,   194,    52,
      11,    13,    12,    53,    14,    56,    57,    13,    60,    80,
      14,   191,    28,    81,   204,    82,   195,   114,    42,   206,
      61,   155,   111,   147,   112,   148,   113,   117,    11,    63,
      12,   118,   203,    64,    65,    13,    66,    67,    14,    68,
     119,    69,   120,    70,    71,    72,    73,    74,    75,    76,
      77,    78,   121,   122,    57,    79,   151,   140,   141,   142,
     143,   144,    11,   152,    12,   153,   145,    80,   146,    13,
     157,    81,    14,    82,    11,    63,    12,   158,   178,    64,
      65,    13,    66,    67,    14,    68,   182,    69,   180,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    58,   188,
      57,   127,    62,   142,   143,   144,   109,   110,   185,   196,
     145,   190,   146,    80,   197,   200,    63,    81,   201,    82,
      64,    65,   202,    66,    67,   205,    68,     7,    69,    35,
      70,    71,    72,    73,    74,    75,    76,    77,    78,   129,
     156,    57,   130,   198,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    80,     0,     0,    63,    81,     0,
      82,    64,    65,     0,    66,    67,     0,    68,     0,    69,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
       0,     0,    57,   163,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    80,     0,     0,    63,    81,
       0,    82,    64,    65,     0,    66,    67,     0,    68,     0,
      69,     0,    70,    71,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    57,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,    66,    80,     0,    68,   145,
      81,   146,    82,    71,    72,    73,    74,    75,    76,    77,
      78,    11,     0,    12,     0,     0,     0,    11,    13,    12,
       0,    14,     0,    15,    13,    16,    80,    14,     0,    15,
      81,    16,    82,    11,     0,    12,     0,     0,    32,     0,
      13,     0,     0,    14,    34,    15,     0,    16,     0,     0,
       0,     0,     0,     0,     0,   199,     0,     0,     0,     0,
      43,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,   187,     0,   145,     0,
     146,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,     0,     0,   145,     0,
     146,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,     0,   162,   145,     0,
     146,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,     0,   181,   145,     0,
     146,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,     0,   184,   145,     0,
     146,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,     0,     0,   145,   189,
     146,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,     0,     0,   145,   193,
     146,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,     0,     0,   145,     0,
     146,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,     0,     0,     0,     0,   145,     0,   146
};

static const yytype_int16 yycheck[] =
{
      67,    87,    57,     1,    26,     7,     1,     3,    23,     5,
      16,    80,    81,    82,    10,    26,    26,    13,    41,    15,
      35,    17,    26,     5,    47,    48,    26,    29,    50,    27,
      36,    86,    27,    26,    30,    41,    50,    28,    52,    50,
      50,    47,    48,   129,   113,   112,    50,    53,   117,   118,
      48,    57,   121,   122,     0,    26,    29,    50,    49,    26,
      66,    26,    48,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,    26,    11,   148,
      86,    14,    51,   152,    48,    48,    19,    20,    21,    22,
      23,    24,    25,    26,     3,   181,     5,    27,   184,    49,
       3,    10,     5,    28,    13,    49,    29,    10,    49,    42,
      13,   180,    15,    46,   200,    48,   185,    26,    51,   205,
      49,   190,    27,    27,    48,    32,    48,    48,     3,     4,
       5,    48,   199,     8,     9,    10,    11,    12,    13,    14,
      48,    16,    48,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    48,    48,    29,    30,    48,    41,    42,    43,
      44,    45,     3,    50,     5,    27,    50,    42,    52,    10,
      49,    46,    13,    48,     3,     4,     5,    49,    26,     8,
       9,    10,    11,    12,    13,    14,    49,    16,    27,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    52,    49,
      29,    30,    56,    43,    44,    45,    60,    61,    28,    27,
      50,    48,    52,    42,    26,     6,     4,    46,    49,    48,
       8,     9,    49,    11,    12,    49,    14,     3,    16,    25,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    86,
     118,    29,    30,   190,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    -1,    -1,     4,    46,    -1,
      48,     8,     9,    -1,    11,    12,    -1,    14,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,     4,    46,
      -1,    48,     8,     9,    -1,    11,    12,    -1,    14,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    29,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    11,    42,    -1,    14,    50,
      46,    52,    48,    19,    20,    21,    22,    23,    24,    25,
      26,     3,    -1,     5,    -1,    -1,    -1,     3,    10,     5,
      -1,    13,    -1,    15,    10,    17,    42,    13,    -1,    15,
      46,    17,    48,     3,    -1,     5,    -1,    -1,    30,    -1,
      10,    -1,    -1,    13,    30,    15,    -1,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      30,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    28,    -1,    50,    -1,
      52,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,
      52,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    49,    50,    -1,
      52,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    49,    50,    -1,
      52,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    49,    50,    -1,
      52,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    50,    51,
      52,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    50,    51,
      52,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,
      52,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,    52
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    54,    55,    63,    26,     0,    63,     7,    29,
      26,     3,     5,    10,    13,    15,    17,    30,    56,    57,
      58,    59,    60,    64,    65,    29,    26,    26,    15,    57,
      26,    50,    30,    65,    30,    64,    48,    26,    26,     1,
      27,    48,    51,    30,    57,    61,    62,    48,    48,    27,
      61,    26,    49,    28,    61,    61,    49,    29,    66,    57,
      49,    49,    66,     4,     8,     9,    11,    12,    14,    16,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    30,
      42,    46,    48,    56,    57,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    84,    85,    86,    87,    88,    90,    26,    66,
      66,    27,    48,    48,    26,    57,    84,    48,    48,    48,
      48,    48,    48,    76,    76,    76,    26,    30,    56,    68,
      30,    69,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    50,    52,    27,    32,    84,
      76,    48,    50,    27,    76,    76,    83,    49,    49,    76,
      83,    89,    49,    30,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    26,    76,
      27,    49,    49,    76,    49,    28,    49,    28,    49,    51,
      48,    76,    69,    51,    69,    76,    27,    26,    89,    27,
       6,    49,    49,    84,    69,    49,    69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    57,    57,    57,
      57,    57,    58,    59,    60,    60,    60,    60,    61,    61,
      62,    62,    63,    63,    63,    63,    64,    64,    65,    65,
      66,    66,    66,    66,    67,    67,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    71,    72,
      73,    74,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    77,    78,    79,
      80,    80,    80,    80,    80,    80,    81,    81,    81,    81,
      81,    81,    82,    82,    82,    83,    83,    84,    84,    85,
      85,    86,    86,    87,    87,    88,    89,    89,    90,    90,
      90,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     3,     4,     1,     1,     1,
       1,     1,     2,     3,     6,     6,     7,     7,     0,     1,
       4,     2,     7,     6,     5,     4,     2,     1,     1,     1,
       4,     3,     3,     2,     2,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     5,     7,     5,     9,
       3,     2,     5,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     3,     6,     1,     1,     4,     5,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     1,     1,     0,     1,
       1,     1,     3,     4,     6,     4,     1,     0,     1,     1,
       1,     1
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
#line 147 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.program)=new Program(*(yyvsp[0].decllist)); program = (yyval.program);}
#line 1709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 150 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.decllist)=(yyvsp[-1].decllist))->push_back((yyvsp[0].classdecl));}
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 151 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.decllist)=new vector<Decl*>)->push_back((yyvsp[0].classdecl));}
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 155 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.vardecl)=new VarDecl((yyvsp[-2].type),(new Id((yyvsp[-1].identifier),(yylsp[-1]))));}
#line 1727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 156 "yacc/bison.y" /* yacc.c:1646  */
    {}
#line 1733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 159 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.type)=new IntType("int");}
#line 1739 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 160 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.type)=new BoolType("bool");}
#line 1745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 161 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.type)=new StringType("string");}
#line 1751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 162 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.type)=(yyvsp[0].nametype);}
#line 1757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 163 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.type)=(yyvsp[0].arraytype);}
#line 1763 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 166 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.nametype)=new NamedType("class",new Id((yyvsp[0].identifier),(yylsp[0])));}
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 169 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arraytype)=new ArrayType("[]",(yyvsp[-2].type));}
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 173 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.fndecl)=new FnDecl(0,(yyvsp[-5].type),new Id((yyvsp[-4].identifier),(yylsp[-4])),(yyvsp[-2].formals),(yyvsp[0].stmtblock));}
#line 1781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 175 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.fndecl)=new FnDecl(0,(new VoidType("void")),new Id((yyvsp[-4].identifier),(yylsp[-4])),(yyvsp[-2].formals),(yyvsp[0].stmtblock));}
#line 1787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 177 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.fndecl)=new FnDecl(1,(yyvsp[-5].type),new Id((yyvsp[-4].identifier),(yylsp[-4])),(yyvsp[-2].formals),(yyvsp[0].stmtblock));}
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 179 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.fndecl)=new FnDecl(1,(new VoidType("void")),new Id((yyvsp[-4].identifier),(yylsp[-4])),(yyvsp[-2].formals),(yyvsp[0].stmtblock));}
#line 1799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 182 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.formals)=new vector<VarDecl*>;}
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 183 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.formals)=(yyvsp[0].variables);}
#line 1811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 187 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.variables)=(yyvsp[-3].variables))->push_back(new VarDecl((yyvsp[-1].type),new Id((yyvsp[0].identifier),(yylsp[0]))));}
#line 1817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 188 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.variables)=new vector<VarDecl*>)->push_back(new VarDecl((yyvsp[-1].type),new Id((yyvsp[0].identifier),(yylsp[0]))));}
#line 1823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 192 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.classdecl)=new ClassDecl(new Id((yyvsp[-5].identifier),(yylsp[-5])),new Id((yyvsp[-3].identifier),(yylsp[-3])),(yyvsp[-1].fields));}
#line 1829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 194 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.classdecl)=new ClassDecl(new Id((yyvsp[-4].identifier),(yylsp[-4])),new Id((yyvsp[-2].identifier),(yylsp[-2])),NULL);}
#line 1835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 196 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.classdecl)=new ClassDecl(new Id((yyvsp[-3].identifier),(yylsp[-3])),NULL,(yyvsp[-1].fields));}
#line 1841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 198 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.classdecl)=new ClassDecl(new Id((yyvsp[-2].identifier),(yylsp[-2])),NULL,NULL);}
#line 1847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 201 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.fields)=(yyvsp[-1].fields))->push_back((yyvsp[0].decl));}
#line 1853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 202 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.fields)=new vector<Decl*>)->push_back((yyvsp[0].decl));}
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 205 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.decl)=(yyvsp[0].vardecl);}
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 206 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.decl)=(yyvsp[0].fndecl);}
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 221 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmtblock)=new StmtBlock((yyvsp[-2].vardecls),(yyvsp[-1].stmts));}
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 223 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmtblock)=new StmtBlock((yyvsp[-1].vardecls),NULL);}
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 225 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmtblock)=new StmtBlock(NULL,(yyvsp[-1].stmts));}
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 226 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmtblock)=new StmtBlock(NULL,NULL);}
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 229 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.vardecls)=(yyvsp[-1].vardecls))->push_back((yyvsp[0].vardecl));}
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 230 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.vardecls)=new vector<VarDecl*>)->push_back((yyvsp[0].vardecl));}
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 233 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.stmts)=(yyvsp[-1].stmts))->push_back((yyvsp[0].stmt));}
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 234 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.stmts)=new vector<Stmt*>)->push_back((yyvsp[0].stmt));}
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 237 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[-1].expr);}
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 238 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].ifstmt);}
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 239 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].whilestmt);}
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 240 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].forstmt);}
#line 1943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 241 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].breakstmt);}
#line 1949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 242 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].returnstmt);}
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 243 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].printstmt);}
#line 1961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 244 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.stmt)=(yyvsp[0].stmtblock);}
#line 1967 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 249 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.ifstmt)=new IfStmt((yyvsp[-2].expr),(yyvsp[0].stmt),"",NULL);}
#line 1973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 251 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.ifstmt)=new IfStmt((yyvsp[-4].expr),(yyvsp[-2].stmt),"else",(yyvsp[0].stmt));}
#line 1979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 256 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.whilestmt)=new WhileStmt((yyvsp[-2].expr),(yyvsp[0].stmt));}
#line 1985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 260 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.forstmt)=new ForStmt((yyvsp[-6].expr),(yyvsp[-4].expr),(yyvsp[-2].expr),(yyvsp[0].stmt));}
#line 1991 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 264 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.returnstmt)=new ReturnStmt((yyvsp[-1].expr),(yylsp[-2]));
																//为了获得return位置，当optexpr为NULL时，确定return的位置
																}
#line 1999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 269 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.breakstmt)=new BreakStmt((yylsp[-1]));
																	//获得break位置
																}
#line 2007 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 276 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.printstmt)=new PrintStmt(*(yyvsp[-2].exprs));}
#line 2013 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 279 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].assignexpr);}
#line 2019 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 280 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].constant);}
#line 2025 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 281 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].lvalue);}
#line 2031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 282 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=new This();}
#line 2037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 283 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].call);}
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 284 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[-1].expr);}
#line 2049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 285 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].arithmeticexpr);}
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 286 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].relationexpr);}
#line 2061 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 287 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].logicalexpr);}
#line 2067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 289 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=new ReadInteger();}
#line 2073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 291 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=new ReadLine();}
#line 2079 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 293 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=new Instanceof((yyvsp[-3].expr),new Id((yyvsp[-1].identifier),(yylsp[-1])));}
#line 2085 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 295 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].newexpr);}
#line 2091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 297 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].newarrayexpr);}
#line 2097 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 304 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.newexpr)=new NewExpr(new Id((yyvsp[-2].identifier),(yylsp[-2])));}
#line 2103 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 307 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.newarrayexpr)=new NewArrayExpr((yyvsp[-3].type),(yyvsp[-1].expr));}
#line 2109 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 311 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.assignexpr)=new AssignExpr((yyvsp[-2].lvalue),(yyvsp[0].expr));}
#line 2115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 315 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arithmeticexpr)=new ArithmeticExpr((yyvsp[-2].expr),"+",(yyvsp[0].expr));}
#line 2121 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 317 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arithmeticexpr)=new ArithmeticExpr((yyvsp[-2].expr),"-",(yyvsp[0].expr));}
#line 2127 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 319 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arithmeticexpr)=new ArithmeticExpr((yyvsp[-2].expr),"*",(yyvsp[0].expr));}
#line 2133 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 321 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arithmeticexpr)=new ArithmeticExpr((yyvsp[-2].expr),"/",(yyvsp[0].expr));}
#line 2139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 323 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arithmeticexpr)=new ArithmeticExpr((yyvsp[-2].expr),"%",(yyvsp[0].expr));}
#line 2145 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 325 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arithmeticexpr)=new ArithmeticExpr(NULL,"-",(yyvsp[0].expr));}
#line 2151 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 329 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.relationexpr)=new RelationExpr((yyvsp[-2].expr),">",(yyvsp[0].expr));}
#line 2157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 331 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.relationexpr)=new RelationExpr((yyvsp[-2].expr),"<",(yyvsp[0].expr));}
#line 2163 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 333 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.relationexpr)=new RelationExpr((yyvsp[-2].expr),">=",(yyvsp[0].expr));}
#line 2169 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 335 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.relationexpr)=new RelationExpr((yyvsp[-2].expr),"<=",(yyvsp[0].expr));}
#line 2175 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 337 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.relationexpr)=new RelationExpr((yyvsp[-2].expr),"==",(yyvsp[0].expr));}
#line 2181 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 339 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.relationexpr)=new RelationExpr((yyvsp[-2].expr),"!=",(yyvsp[0].expr));}
#line 2187 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 343 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.logicalexpr)=new LogicalExpr((yyvsp[-2].expr),"&&",(yyvsp[0].expr));}
#line 2193 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 345 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.logicalexpr)=new LogicalExpr((yyvsp[-2].expr),"||",(yyvsp[0].expr));}
#line 2199 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 347 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.logicalexpr)=new LogicalExpr(NULL,"!",(yyvsp[0].expr));}
#line 2205 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 352 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.exprs)=(yyvsp[-2].exprs))->push_back(*(yyvsp[0].expr));}
#line 2211 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 354 "yacc/bison.y" /* yacc.c:1646  */
    {((yyval.exprs)=new vector<const Expr&>)->push_back(*(yyvsp[0].expr));}
#line 2217 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 357 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=(yyvsp[0].expr);}
#line 2223 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 358 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.expr)=NULL;}
#line 2229 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 361 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.lvalue)=(yyvsp[0].fieldaccess);}
#line 2235 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 362 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.lvalue)=(yyvsp[0].arrayaccess);}
#line 2241 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 365 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.fieldaccess)=new FieldAccess(NULL,*(new Id((yyvsp[0].identifier),(yylsp[0]))));}
#line 2247 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 366 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.fieldaccess)=new FieldAccess(*(yyvsp[-2].expr),*(new Id((yyvsp[0].identifier),(yylsp[0]))));}
#line 2253 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 370 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.call)=new Call(NULL,*(new Id((yyvsp[-3].identifier),(yylsp[-3]))),(yyvsp[-1].actuals));}
#line 2259 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 372 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.call)=new Call(*(yyvsp[-5].expr),*(new Id((yyvsp[-3].identifier),(yylsp[-3]))),(yyvsp[-1].actuals));}
#line 2265 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 375 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.arrayaccess)=new ArrayAccess(*(yyvsp[-3].expr),*(yyvsp[-1].expr));}
#line 2271 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 378 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.actuals)=(yyvsp[0].exprs);}
#line 2277 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 379 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.actuals)=NULL;}
#line 2283 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 382 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.constant)=new IntCon((yyvsp[0].intcon),(yylsp[0]));}
#line 2289 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 383 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.constant)=new BoolCon((yyvsp[0].boolcon),(yylsp[0]));}
#line 2295 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 384 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.constant)=new StringCon((yyvsp[0].stringcon),(yylsp[0]));}
#line 2301 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 385 "yacc/bison.y" /* yacc.c:1646  */
    {(yyval.constant)=new NullCon((yyvsp[0].nullcon),(yylsp[0]));}
#line 2307 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2311 "y.tab.c" /* yacc.c:1646  */
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
#line 387 "yacc/bison.y" /* yacc.c:1906  */


void yyerror(const char* msg) 
{
    errornum++;   
    IssueError::Printyyerror(&yylloc,yytext);
}
