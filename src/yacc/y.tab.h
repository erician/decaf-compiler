/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
    NEWARRAY = 267,
    RETURN = 268,
    STRING = 269,
    THIS = 270,
    VOID = 271,
    WHILE = 272,
    STATIC = 273,
    PRINT = 274,
    READINTEGER = 275,
    READLINE = 276,
    INSTANCEOF = 277,
    NULLCONSTANT = 278,
    BOOLCONSTANT = 279,
    INTCONSTANT = 280,
    STRINGCONSTANT = 281,
    ID = 282,
    SEMI = 283,
    COMMA = 284,
    LC = 285,
    RC = 286,
    LOWER_THAN_ELSE = 287,
    ASSIGNOP = 288,
    OR = 289,
    AND = 290,
    GREATER = 291,
    LESS = 292,
    GREATEREQUAL = 293,
    LESSEQUAL = 294,
    EQUAL = 295,
    NOTEQUAL = 296,
    PLUS = 297,
    MINUS = 298,
    STAR = 299,
    DIV = 300,
    MOD = 301,
    NOT = 302,
    UMINUS = 303,
    LP = 304,
    RP = 305,
    LB = 306,
    RB = 307,
    DOT = 308
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
#define NEWARRAY 267
#define RETURN 268
#define STRING 269
#define THIS 270
#define VOID 271
#define WHILE 272
#define STATIC 273
#define PRINT 274
#define READINTEGER 275
#define READLINE 276
#define INSTANCEOF 277
#define NULLCONSTANT 278
#define BOOLCONSTANT 279
#define INTCONSTANT 280
#define STRINGCONSTANT 281
#define ID 282
#define SEMI 283
#define COMMA 284
#define LC 285
#define RC 286
#define LOWER_THAN_ELSE 287
#define ASSIGNOP 288
#define OR 289
#define AND 290
#define GREATER 291
#define LESS 292
#define GREATEREQUAL 293
#define LESSEQUAL 294
#define EQUAL 295
#define NOTEQUAL 296
#define PLUS 297
#define MINUS 298
#define STAR 299
#define DIV 300
#define MOD 301
#define NOT 302
#define UMINUS 303
#define LP 304
#define RP 305
#define LB 306
#define RB 307
#define DOT 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 21 "yacc/bison.y" /* yacc.c:1909  */

    int nullcon;
    int boolcon;
    int intcon;
    char stringcon[100+1];
    char identifier[100+1];
    Program *program;
    Id *id;
    Decl *decl;
    VarDecl *vardecl;
    FunDecl *fundecl;
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

    std::vector<Decl*> *decllist;
    std::vector<VarDecl*> *formals;
    std::vector<Decl*> *fields;

    std::vector<VarDecl*> *variables;

    std::vector<Stmt*> *stmts;

    std::vector<Expr*> *exprs;
    std::vector<Expr*> *actuals;

#line 224 "y.tab.h" /* yacc.c:1909  */
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
