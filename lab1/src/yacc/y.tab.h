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
#line 15 "yacc/bison.y" /* yacc.c:1909  */

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

#line 223 "y.tab.h" /* yacc.c:1909  */
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
