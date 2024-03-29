/*************************************************************************
	> File Name: not_terminal_class.h
	> Author: 
	> Mail: 
	> Created Time: Sun 27 Nov 2016 08:38:38 PM PST
 ************************************************************************/
#ifndef DC_CORE_DC_CLASS_H_
#define DC_CORE_DC_CLASS_H_

#include <iostream>
#include <stack>
#include <vector>

#ifndef DC_YACC_LOCATION_H_ 
#include "yacc/location.h"
#endif

#ifndef DC_CORE_DC_SYMBOL_H_
#include "core/dc_symbol.h"
#endif

#ifndef DC_CORE_DC_ENUM_H_
#include "core/dc_enum.h"
#endif


//类的名字和非终结符的名字相同
class TreeNode;
class Id;
class Program;
class Decl;
class VarDecl;
class FunDecl;
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

class TreeNode
{
public:
    YYLTYPE *plocation;
    TreeNode(YYLTYPE s1);
    TreeNode();
    YYLTYPE* getplocation(){return plocation;}
    virtual void printAst(int aline,int level)=0;
    //check
    virtual bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    virtual bool checkBreak(bool isWhileOrForBlock);
    virtual bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    bool checkExprType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope, Expr* pexpr, TypeInfo* properTypeInfo);
    bool cmpTypeInfo(TypeInfo* typeInfo1, TypeInfo* typeInfo2);
    //get type
    virtual TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    virtual YYLTYPE* getLocation();
};

class Program:public TreeNode
{
private:
    std::vector<Decl*> *pvecClassDecl;
    GloScope *gloScope;
public:
    Program(std::vector<Decl*> *s1);
    void printAst(int aline,int level);
    void buildSym();
    void printSym(int aline, int level);
    
    bool checkStaticSemantic();
    bool checkScope();
    bool checkStmt();
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    bool checkBreak(bool isWhileOrForBlock);
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
};

class Id:public TreeNode
{
public:
    std::string name;
    Id(char* str,YYLTYPE loc);          //id 是字符串
    void printAst(int aline,int level);
    std::string getidname();
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};

/**************decl************/
class Decl:public TreeNode
{
public:
    Id *pid;
    Decl(Id* s);
    TypeInfo* getTypeInfoFromType(Type* type);
    virtual Entry *buildClassSym(std::string name); 
    virtual Entry *buildGlobalSym(); 
};

/**************stmt************/
class Stmt:public TreeNode
{
public:
    Stmt();
    virtual Entry *buildLocalSym(Scope* parentScope);   
};

class VarDecl:public Decl, public Stmt
{
public:
    Type* ptype;
    VarDecl(Type* s1,Id* s2);
    void printAst(int aline,int level);
    Entry* buildClassSym(std::string name);
    Entry* buildFormalSym();
    Entry* buildLocalSym(Scope* parentScope);
};

class FunDecl:public Decl
{
public:
    Type* ptype;
    std::vector<VarDecl*>* pformals;
    StmtBlock* pstmtblock;
    bool isStatic;
    FunDecl(int s,Type* s1,Id* s2,std::vector<VarDecl*>* s4,StmtBlock* s6);
    void printAst(int aline,int level);
    Entry *buildClassSym(std::string name);   
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    bool checkBreak(bool isWhileOrForBlock);
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
};

class ClassDecl:public Decl
{
public:
    Id* pParentId;
    std::vector<Decl*> *pfields;
    //使用NULL表示是否继承，是否有Fields
    ClassDecl(Id* s2,Id* s4,std::vector<Decl*> *s6);
    void printAst(int aline,int level);
    Entry* buildGlobalSym();
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    bool checkBreak(bool isWhileOrForBlock);
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
};
/**********type******************/
class Type:public TreeNode
{
protected:
    int type; 
public:   
    Type();
    int getType();
};

class IntType:public Type
{
public:
    IntType();
    void printAst(int aline,int level);
    
};
class BoolType:public Type
{
public:
    BoolType();
    void printAst(int aline,int level);
    
};
class StringType:public Type
{
public:
    StringType();
    void printAst(int aline,int level);
    
};
class VoidType:public Type
{
public:
    VoidType();
    void printAst(int aline,int level);
    
};
//NamedType 只有class ID；
class NamedType:public Type
{
public:
    Id* pid;
    NamedType(Id* s2);
    void printAst(int aline,int level);
    Id *getpid();
    std::string getClassName();
};
class ArrayType:public Type
{
public:
    Type* nextArray;
    ArrayType(Type* s1);
    void printAst(int aline,int level);
    Type* getNextArray();
    int getArrayLevel();
    Type* getArrayType();
};
/***********stmt***********/
class StmtBlock:public Stmt
{
public:
    std::vector<Stmt*> *pstmts;
    StmtBlock(std::vector<Stmt*> *s2);
    void printAst(int aline,int level);
    //return LocScopeEntry with name="" and subLocScope not NULL;
    Entry* buildLocalSym(Scope* parentScope);    
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkBreak(bool isWhileOrForBlock);
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
};
class IfStmt:public Stmt
{
public:
    Expr *pexpr;
    Stmt *pstmt1;
    std::string elsename;
    Stmt *pstmt2;
    IfStmt(Expr *s3,Stmt *s5,const char *s6,Stmt *s7);
    void printAst(int aline,int level);
    Entry *buildLocalSym(Scope* parentScope); 
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkBreak(bool isWhileOrForBlock);
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
};
class WhileStmt:public Stmt
{
public:
    Expr *pexpr;
    Stmt *pstmt;
    WhileStmt(Expr *s3,Stmt *s5);
    void printAst(int aline,int level);
    Entry* buildLocalSym(Scope* parentScope); 
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkBreak(bool isWhileOrForBlock);
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
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
    Entry* buildLocalSym(Scope* parentScope); 
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkBreak(bool isWhileOrForBlock);
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
};
class ReturnStmt:public Stmt
{
public:
    Expr* poptexpr;
    ReturnStmt(Expr* s2,YYLTYPE loc);
    void printAst(int aline,int level);
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    YYLTYPE* getLocation();
};
class BreakStmt:public Stmt
{
public:
    BreakStmt(YYLTYPE loc);
    void printAst(int aline,int level);
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    bool checkBreak(bool isWhileOrForBlock);
    YYLTYPE* getLocation();
};
class PrintStmt:public Stmt
{
public:
    std::vector<Expr*> *pexprs;
    PrintStmt(std::vector<Expr*> *s3);
    void printAst(int aline,int level);
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
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
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class ArithmeticExpr:public Expr
{
public:
    Expr* pexpr1;
    Expr* pexpr2;
    std::string opname;
    ArithmeticExpr(Expr* s1,const char *s,Expr* s3);
    void printAst(int aline,int level);
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class RelationExpr:public Expr
{
public:
    Expr* pexpr1;
    Expr* pexpr2;
    std::string opname;
    RelationExpr(Expr* s1,const char* s,Expr* s3);
    void printAst(int aline,int level);
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class LogicalExpr:public Expr
{
public:
    Expr* pexpr1;
    Expr* pexpr2;
    std::string opname;
    LogicalExpr(Expr* s1,const char* s,Expr* s3);
    void printAst(int aline,int level);
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
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
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class ArrayAccess:public Lvalue
{
public:
    Expr* pexpr1;
    Expr* pexpr2;
    ArrayAccess(Expr* s1,Expr* s3);
    void printAst(int aline,int level);
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class Call:public Expr
{
public:
    Id* pid;
    std::vector<Expr*> *pactuals;
    Expr* pexpr;
    Call(Expr* s1,Id* s3,std::vector<Expr*> *s5);
    void printAst(int aline,int level);
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkActualsAndFormalsMatch(GloScope* gloScope, ClaDes* claDes, Scope* currentScope, std::vector<Entry*> formals);
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class This:public Expr
{
public:
    This(YYLTYPE loc);
    void printAst(int aline,int level);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class ReadInteger:public Expr
{
public:
    ReadInteger(YYLTYPE loc);
    void printAst(int aline,int level);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class ReadLine:public Expr
{
public:
    ReadLine(YYLTYPE loc);
    void printAst(int aline,int level);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class Instanceof:public Expr
{
public:
    Expr* pexpr;
    Id* pid;
    Instanceof(Expr* s3,Id* s5);
    void printAst(int aline,int level);
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class NewExpr:public Expr
{
public:
    Id* pid;
    NewExpr(Id* s2);
    void printAst(int aline,int level);
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class NewArrayExpr:public Expr
{
public:
    Type* ptype;
    Expr* pexpr;
    NewArrayExpr(Type* s2, YYLTYPE loc, Expr* s4);
    void printAst(int aline,int level);
    //check
    bool checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope); 
    bool checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
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
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class BoolCon:public Constant
{
public:
    int value;
    BoolCon(int s1,YYLTYPE loc);
    void printAst(int aline,int level);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class StringCon:public Constant
{
public:
    std::string value;
    StringCon(const char *s1,YYLTYPE loc);
    void printAst(int aline,int level);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};
class NullCon:public Constant
{
public:
    int value;
    NullCon(int s1,YYLTYPE loc);
    void printAst(int aline,int level);
    //get type
    TypeInfo* getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope);
    //get location
    YYLTYPE* getLocation();
};

#endif