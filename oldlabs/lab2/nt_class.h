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
#include "nt_buildsym.h"    //自己定义YYLTYPE，方便使用
#include "nt_gentac.h"
#include "location.h"
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
class inttype;
class booltype;
class stringtype;
class voidtype;
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
    treenode *pparent;

    treenode(YYLTYPE s1);
    //nt_genast.cpp
    treenode();
    void setparent(treenode *p){pparent=p;}
    YYLTYPE* getplocation(){return plocation;}
    //nt_printast.cpp
    virtual void Print(int aline,int level);
    void PrintWhite(int aline,int level);
};
class Id:public treenode
{
public:
    string name;
    Scope *pscope;
    Id(char* str,YYLTYPE loc);          //id 是字符串
    void Print(int aline,int level);
    string getidname();
    void checkdecl_class(Scope *pscope);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    void checkdecl_fun(vector<Scope*> *pvec_scope);
	void setpscope(Scope* p) { pscope=p;}
    Scope* getpscope(); 	
};
class Program:public treenode
{
public:
    vector<Decl*> *pdecllist;
    vector<GloScope*> *pvec_gloscope;
    stack< vector<Scope*>* > *pstack;
    vector<Functy> vec_functy;
    vector<ClassInfo> vec_classinfo;

	vector<string> vec_data; 	//最后打印的数据区
    Program(vector<Decl*> *s1);
    void Print(int aline,int level);
    //nt_buildsym.cpp
    void buildsym();
    void printsym();
    void gentac();
    void printtac();
	void genmips();
    
};
/**************decl************/
class Decl:public treenode
{
public:
    Id *pid;
    Decl(Id* s);

    virtual void buildsym(stack<vector<Scope*>*> *pst,GloScope* pgloscope);
    //要使用引用，不然修改不了vector内的值
    virtual void gentac(vector<Functy> &vec_functy,vector<ClassInfo> &vec_classinfo);
    
    virtual void gentac_var_functy(ClassInfo &classinfo,vector<Functy> &vec_functy);
};
class VarDecl:public Decl
{
public:
    Type* ptype;
    VarDecl(Type* s1,Id* s2);
    void Print(int aline,int level);
    void buildsym(stack<vector<Scope*>*> *pst,GloScope *pgloscope);
    void buildformals(stack<vector<Scope*>*> *pst,vector<LocScope*>*  pvec_locscope,vector<ClaScope*>* pvec_clascope);
    void buildlocal(vector<LocScope*> *pvec_locscope,vector<vector<LocScope*>*> *pvecvec_locscope,vector<Scope*> *pvec_for_loc_scope);
    void gentac_var_functy(ClassInfo &classinfo,vector<Functy> &vec_functy);
    void gentac_formal(int offset,vector<SaveFormal*> &formal);//返回参数的空间
    
};

class FnDecl:public Decl
{
public:
    Type* ptype;
    vector<VarDecl*>* pformals;
    StmtBlock* pstmtblock;
    int isstatic;   //表示是否为static，0不是，1是
    FnDecl(int s,Type* s1,Id* s2,vector<VarDecl*>* s4,StmtBlock* s6);
    void Print(int aline,int level);
    void buildsym(stack<vector<Scope*>*> *pst,GloScope *pgloscope);
    void gentac_var_functy(ClassInfo &classinfo,vector<Functy> &vec_functy);
    
};
class ClassDecl:public Decl
{
public:
    Id* base;
    vector<Decl*> *pfields;
    //使用NULL表示是否继承，是否有Fields
    ClassDecl(Id* s2,Id* s4,vector<Decl*> *s6);
    void Print(int aline,int level);
    void buildsym(stack<vector<Scope*>*> *pst,GloScope *pgloscope);
    void gentac(vector<Functy> &vec_functy,vector<ClassInfo> &vec_classinfo);

};
/**********type******************/
class Type:public treenode
{
public:
    string _typename;//typename重名，前加_
    Type(const char* s);
    virtual string get_named_id_name();
    virtual Type* get_type_pointer();
    virtual Id *getpid();
    string gettypename();
};

class IntType:public Type
{
public:
    IntType(const char* s);
    void Print(int aline,int level);
    
};
class BoolType:public Type
{
public:
    BoolType(const char* s);
    void Print(int aline,int level);
    
};
class StringType:public Type
{
public:
    StringType(const char* s);
    void Print(int aline,int level);
    
};
class VoidType:public Type
{
public:
    VoidType(const char* s);
    void Print(int aline,int level);
    
};
//NamedType 只有class ID；
class NamedType:public Type
{
public:
    Id* pid;
    NamedType(const char* s,Id* s2);
    void Print(int aline,int level);
    Id *getpid();
    string get_named_id_name();
};
class ArrayType:public Type
{
public:
    Type* ptype;
    ArrayType(const char* s,Type* s1);
    void Print(int aline,int level);
    Type* get_type_pointer();
    
};
/***********StmtBlock***********/
class Stmt:public treenode
{
public:
    Stmt();
    virtual void buildlocal(vector<LocScope*> *pvec_locscope,vector<Scope*> *pvec_for_loc_scope);
    virtual void checkdecl_var(vector<Scope*> *pvec_scope);
    virtual TYPE* checktype();
    virtual void stmt_checkbreak(int i=0);
    virtual Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class StmtBlock:public Stmt
{
public:
    vector<VarDecl*> *pvardecls;
    vector<Stmt*> *pstmts;
    StmtBlock(vector<VarDecl*> *s2,vector<Stmt*> *s3);
    void Print(int aline,int level);
    void buildlocal(vector<LocScope*> *pvec_locscope,vector<Scope*> *pvec_for_loc_scope);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    void stmt_checkbreak(int i=0);
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class IfStmt:public Stmt
{
public:
    Expr *pexpr;
    Stmt *pstmt1;
    string elsename;
    Stmt *pstmt2;
    IfStmt(Expr *s3,Stmt *s5,const char *s6,Stmt *s7);
    void Print(int aline,int level);
    void buildlocal(vector<LocScope*> *pvec_locscope,vector<Scope*> *pvec_for_loc_scope);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    void stmt_checkbreak(int i=0);
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class WhileStmt:public Stmt
{
public:
    Expr *pexpr;
    Stmt *pstmt;
    WhileStmt(Expr *s3,Stmt *s5);
    void Print(int aline,int level);
    void buildlocal(vector<LocScope*> *pvec_locscope,vector<Scope*> *pvec_for_loc_scope);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    void stmt_checkbreak(int i=0);
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class ForStmt:public Stmt
{
public:
    Expr* poptexpr1;
    Expr *pexpr;
    Expr* poptexpr2;
    Stmt* pstmt;
    ForStmt(Expr* s3,Expr* s5,Expr* s7,Stmt* s9);
    void Print(int aline,int level);
    void buildlocal(vector<LocScope*> *pvec_locscope,vector<Scope*> *pvec_for_loc_scope);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    void stmt_checkbreak(int i=0);
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class ReturnStmt:public Stmt
{
public:
    Expr* poptexpr;
    ReturnStmt(Expr* s2,YYLTYPE loc);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class BreakStmt:public Stmt
{
public:
    BreakStmt(YYLTYPE loc);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    void stmt_checkbreak(int i=0);
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class PrintStmt:public Stmt
{
public:
    vector<Expr*> *pexprs;
    PrintStmt(vector<Expr*> *s3);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
/************expr*************/
class Expr:public Stmt
{
public:
    Expr();
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
};
class AssignExpr:public Expr
{
public:
    Lvalue* plvalue;
    Expr* pexpr;
    AssignExpr(Lvalue* s1,Expr* s3);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class ArithmeticExpr:public Expr
{
public:
    Expr* pexpr1;
    Expr* pexpr2;
    string opname;
    ArithmeticExpr(Expr* s1,const char *s,Expr* s3);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class RelationExpr:public Expr
{
public:
    Expr* pexpr1;
    Expr* pexpr2;
    string opname;
    RelationExpr(Expr* s1,const char* s,Expr* s3);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class LogicalExpr:public Expr
{
public:
    Expr* pexpr1;
    Expr* pexpr2;
    string opname;
    LogicalExpr(Expr* s1,const char* s,Expr* s3);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class Lvalue:public Expr
{
public:
    Lvalue();
    void checkdecl_var(vector<Scope*> *pvec_scope);
    virtual int IsVarMem();
    virtual Location* IsArray(vector<Instruction*> &functy_code);
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class FieldAccess:public Lvalue
{
public:
    //因为decaf的变量成员都是私有的，所以不会有类名.
    //唯一有的是this.
    Expr* pexpr;
    Id* pid;
    FieldAccess(Expr* s1,Id* s3);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    int IsVarMem();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class ArrayAccess:public Lvalue
{
public:
    Expr* pexpr1;
    Expr* pexpr2;
    ArrayAccess(Expr* s1,Expr* s3);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    Location* IsArray(vector<Instruction*> &functy_code);
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class Call:public Expr
{
public:
    Id* pid;
    vector<Expr*> *pactuals;
    Expr* pexpr;
    Call(Expr* s1,Id* s3,vector<Expr*> *s5);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class This:public Expr
{
    //这个class好像没什么用处
public:
    This();
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    //TYPE* checktype();
    //Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class ReadInteger:public Expr
{
public:
    ReadInteger();
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    //TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class ReadLine:public Expr
{
public:
    ReadLine();
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    //TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class Instanceof:public Expr
{
public:
    Expr* pexpr;
    Id* pid;
    Instanceof(Expr* s3,Id* s5);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    //TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class NewExpr:public Expr
{
public:
    Id* pid;
    NewExpr(Id* s2);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    //TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class NewArrayExpr:public Expr
{
public:
    Type* ptype;
    Expr* pexpr;
    NewArrayExpr(Type* s2,Expr* s4);
    void Print(int aline,int level);
    void checkdecl_var(vector<Scope*> *pvec_scope);
    //TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
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
    void Print(int aline,int level);
    TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class BoolCon:public Constant
{
public:
    int value;
    BoolCon(int s1,YYLTYPE loc);
    void Print(int aline,int level);
    TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class StringCon:public Constant
{
public:
    string value;
    StringCon(const char *s1,YYLTYPE loc);
    void Print(int aline,int level);
    TYPE* checktype();
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
class NullCon:public Constant
{
public:
    int value;
    NullCon(int s1,YYLTYPE loc);
    void Print(int aline,int level);
    TYPE* checktype();  
    Location* gentac_stmt(vector<Instruction*> &functy_code);
};
