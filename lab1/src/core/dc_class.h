/*************************************************************************
	> File Name: not_terminal_class.h
	> Author: 
	> Mail: 
	> Created Time: Sun 27 Nov 2016 08:38:38 PM PST
 ************************************************************************/
 
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "../yacc/location.h"
#ifndef _NT_CLASS_H
#define _NT_CLASS_H
#endif
using namespace std;

//类的名字和非终结符的名字相同
class treenode;
class Id;
class Program;
class Decl;
class VarDecl;
class FnDecl;
class ClassDecl;

class Type;
class Inttype;
class Booltype;
class Stringtype;
class Voidtype;
class NamedType;
class ArrayType;

class StmtBlock;
class Stmt;
class IfStmt;
class WhileStmt;
class ForStmt;
class ReturnStmt;
class BreakStmt;
class PrintStmt;

class Expr;
class AssignExpr;
class ArithmeticExpr;
class RelationExpr;
class LogicalExpr;
class Lvalue;
class FieldAccess;
class Call;
class ArrayAccess;
class This;
class ReadInteger;
class ReadLine;
class Instanceof;
class NewExpr;
class NewArrayExpr;

class Constant;
class IntCon;
class BoolCon;
class StringCon;
class NullCon;

class treenode
{
public:
    YYLTYPE *plocation;
    treenode(YYLTYPE s1);
    treenode();
    YYLTYPE* getplocation(){return plocation;}
    virtual void printAst(int aline,int level)=0;
    void printWhite(int aline,int level);
};

class Program:public treenode
{
public:
    vector<Decl*> *pvecClassDecl;
	vector<GloScope*> *pvecGloScope;
    stack< vector<Scope*>* > *pstack;
    Program(vector<Decl*> *s1);
    void Program::buildSym()
    void printAst(int aline,int level);
};

class Id:public treenode
{
public:
    string name;
    Id(char* str,YYLTYPE loc);          //id 是字符串
    void printAst(int aline,int level);
    string getidname();
};

/**************decl************/
class Decl:public treenode
{
public:
    Id *pId;
    Decl(Id* s);
};
class VarDecl:public Decl
{
public:
    Type* ptype;
    VarDecl(Type* s1,Id* s2);
    void printAst(int aline,int level);
};

class FnDecl:public Decl
{
public:
    Type* ptype;
    vector<VarDecl*>* pformals;
    StmtBlock* pstmtblock;
    int isstatic;   //表示是否为static，0不是，1是
    FnDecl(int s,Type* s1,Id* s2,vector<VarDecl*>* s4,StmtBlock* s6);
    void printAst(int aline,int level); 
};

class ClassDecl:public Decl
{
public:
    Id* pParentId;
    vector<Decl*> *pfields;
    //使用NULL表示是否继承，是否有Fields
    ClassDecl(Id* s2,Id* s4,vector<Decl*> *s6);
    void buildSym(stack<vector<Scope*>*> *pstack, GloScope* _pgloscope);
    void printAst(int aline,int level);
};
/**********type******************/
class Type:public treenode
{
public:
    string _typename;//typename重名，前加_
    Type(const char* s);
    string gettypename();
};

class IntType:public Type
{
public:
    IntType(const char* s);
    void printAst(int aline,int level);
    
};
class BoolType:public Type
{
public:
    BoolType(const char* s);
    void printAst(int aline,int level);
    
};
class StringType:public Type
{
public:
    StringType(const char* s);
    void printAst(int aline,int level);
    
};
class VoidType:public Type
{
public:
    VoidType(const char* s);
    void printAst(int aline,int level);
    
};
//NamedType 只有class ID；
class NamedType:public Type
{
public:
    Id* pid;
    NamedType(const char* s,Id* s2);
    void printAst(int aline,int level);
    Id *getpid();
    string get_named_id_name();
};
class ArrayType:public Type
{
public:
    Type* ptype;
    ArrayType(const char* s,Type* s1);
    void printAst(int aline,int level);
    Type* get_type_pointer();
    
};
/***********StmtBlock***********/
class Stmt:public treenode
{
public:
    Stmt();
};
class StmtBlock:public Stmt
{
public:
    vector<VarDecl*> *pvardecls;
    vector<Stmt*> *pstmts;
    StmtBlock(vector<VarDecl*> *s2,vector<Stmt*> *s3);
    void printAst(int aline,int level);
};
class IfStmt:public Stmt
{
public:
    Expr *pexpr;
    Stmt *pstmt1;
    string elsename;
    Stmt *pstmt2;
    IfStmt(Expr *s3,Stmt *s5,const char *s6,Stmt *s7);
    void printAst(int aline,int level);
};
class WhileStmt:public Stmt
{
public:
    Expr *pexpr;
    Stmt *pstmt;
    WhileStmt(Expr *s3,Stmt *s5);
    void printAst(int aline,int level);
};
class ForStmt:public Stmt
{
public:
    Expr* poptexpr1;
    Expr *pexpr;
    Expr* poptexpr2;
    Stmt* pstmt;
    ForStmt(Expr* s3,Expr* s5,Expr* s7,Stmt* s9);
    void printAst(int aline,int level);
};
class ReturnStmt:public Stmt
{
public:
    Expr* poptexpr;
    ReturnStmt(Expr* s2,YYLTYPE loc);
    void printAst(int aline,int level);
};
class BreakStmt:public Stmt
{
public:
    BreakStmt(YYLTYPE loc);
    void printAst(int aline,int level);
};
class PrintStmt:public Stmt
{
public:
    vector<Expr*> *pexprs;
    PrintStmt(vector<Expr*> *s3);
    void printAst(int aline,int level);
};
/************expr*************/
class Expr:public Stmt
{
public:
    Expr();
};
class AssignExpr:public Expr
{
public:
    Lvalue* plvalue;
    Expr* pexpr;
    AssignExpr(Lvalue* s1,Expr* s3);
    void printAst(int aline,int level);
};
class ArithmeticExpr:public Expr
{
public:
    Expr* pexpr1;
    Expr* pexpr2;
    string opname;
    ArithmeticExpr(Expr* s1,const char *s,Expr* s3);
    void printAst(int aline,int level);
};
class RelationExpr:public Expr
{
public:
    Expr* pexpr1;
    Expr* pexpr2;
    string opname;
    RelationExpr(Expr* s1,const char* s,Expr* s3);
    void printAst(int aline,int level);
};
class LogicalExpr:public Expr
{
public:
    Expr* pexpr1;
    Expr* pexpr2;
    string opname;
    LogicalExpr(Expr* s1,const char* s,Expr* s3);
    void printAst(int aline,int level);
};
class Lvalue:public Expr
{
public:
    Lvalue();
};
class FieldAccess:public Lvalue
{
public:
    //因为decaf的变量成员都是私有的，所以不会有类名.
    //唯一有的是this.
    Expr* pexpr;
    Id* pid;
    FieldAccess(Expr* s1,Id* s3);
    void printAst(int aline,int level);
};
class ArrayAccess:public Lvalue
{
public:
    Expr* pexpr1;
    Expr* pexpr2;
    ArrayAccess(Expr* s1,Expr* s3);
    void printAst(int aline,int level);
};
class Call:public Expr
{
public:
    Id* pid;
    vector<Expr*> *pactuals;
    Expr* pexpr;
    Call(Expr* s1,Id* s3,vector<Expr*> *s5);
    void printAst(int aline,int level);
};
class This:public Expr
{
    //这个class好像没什么用处
public:
    This();
    void printAst(int aline,int level);
};
class ReadInteger:public Expr
{
public:
    ReadInteger();
    void printAst(int aline,int level);
};
class ReadLine:public Expr
{
public:
    ReadLine();
    void printAst(int aline,int level);
};
class Instanceof:public Expr
{
public:
    Expr* pexpr;
    Id* pid;
    Instanceof(Expr* s3,Id* s5);
    void printAst(int aline,int level);
};
class NewExpr:public Expr
{
public:
    Id* pid;
    NewExpr(Id* s2);
    void printAst(int aline,int level);
};
class NewArrayExpr:public Expr
{
public:
    Type* ptype;
    Expr* pexpr;
    NewArrayExpr(Type* s2,Expr* s4);
    void printAst(int aline,int level);
};
/*********constant**********/
class Constant:public Expr
{
public:
    Constant();
};
class IntCon:public Constant
{
public:
    int value;
    IntCon(int s1,YYLTYPE loc);
    void printAst(int aline,int level);
};
class BoolCon:public Constant
{
public:
    int value;
    BoolCon(int s1,YYLTYPE loc);
    void printAst(int aline,int level);
};
class StringCon:public Constant
{
public:
    string value;
    StringCon(const char *s1,YYLTYPE loc);
    void printAst(int aline,int level);
};
class NullCon:public Constant
{
public:
    int value;
    NullCon(int s1,YYLTYPE loc);
    void printAst(int aline,int level);
};
