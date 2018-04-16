/*************************************************************************
	> File Name: not_terminal_class.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 28 Nov 2016 12:07:01 AM PST
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#ifndef _NT_CLASS_H
#include "nt_class.h"
#endif

using namespace std;
//类的构造函数
treenode::treenode()
{
    plocation=NULL;
    pparent=NULL;
}
treenode::treenode(YYLTYPE s1)
{
    plocation=new YYLTYPE(s1);
    pparent=NULL;
}
Id::Id(char* str,YYLTYPE loc):treenode(loc)
{
    pscope=NULL;
    name = str;
}

Program::Program(vector<Decl*> *s1)
{
    pdecllist = s1;

    if(pdecllist)
    for(int i=0;i<pdecllist->size();i++)
        (*pdecllist)[i]->setparent(this);
}
/*************decl************/
Decl::Decl(Id *s)
{
    pid=s;

}
//加这个构造函数，防止不在：后构造而出错
VarDecl::VarDecl(Type* s1,Id* s2):Decl(s2)
{
    ptype = s1;
    
    pid->setparent(this);
    ptype->setparent(this);
}
FnDecl::FnDecl(int s,Type* s1,Id* s2,vector<VarDecl*>* s4,StmtBlock* s6):Decl(s2)
{
    isstatic = s;
    ptype = s1;
    pformals = s4;
    pstmtblock = s6;
    
    pid->setparent(this);
    ptype->setparent(this);
    for(int i=0;i<pformals->size();i++)
        (*pformals)[i]->setparent(this);
    pstmtblock->setparent(this);
}
ClassDecl::ClassDecl(Id* s2,Id* s4,vector<Decl*>* s6):Decl(s2)
{
    base = s4;
    pfields = s6;
    
    pid->setparent(this);
    if(base!=NULL)
        base->setparent(this);
    if(pfields)
        for(int i=0;i<pfields->size();i++)
            (*pfields)[i]->setparent(this);

}
/**********type****************/
Type::Type(const char* s)
{
    _typename = s;
}

IntType::IntType(const char* s):Type(s)
{
}
BoolType::BoolType(const char* s):Type(s)
{
}
StringType::StringType(const char* s):Type(s)
{
}
VoidType::VoidType(const char* s):Type(s)
{
}

NamedType::NamedType(const char* s,Id* s2):Type(s)
{
    pid = s2;
    pid->setparent(this);
}
ArrayType::ArrayType(const char* s,Type* s1):Type(s)
{
    ptype = s1;
    ptype->setparent(this);
}
/***********StmtBlock*************/
StmtBlock::StmtBlock(vector<VarDecl*>* s2,vector<Stmt*> *s3)
{
    pvardecls=s2;
    pstmts=s3;
    
    if(pvardecls)
        for(int i=0;i<pvardecls->size();i++)
            (*pvardecls)[i]->setparent(this);
    if(pstmts)
        for(int i=0;i<pstmts->size();i++)
            (*pstmts)[i]->setparent(this);
}
Stmt::Stmt()
{

}
IfStmt::IfStmt(Expr* s3,Stmt* s5,const char* s6,Stmt* s7)
{
    pexpr=s3;
    pstmt1=s5;
    elsename=s6;
    pstmt2=s7;
    
    pexpr->setparent(this);
    if(pstmt1!=NULL)
        pstmt1->setparent(this);
    if(pstmt2)
        pstmt2->setparent(this);
}
WhileStmt::WhileStmt(Expr* s3,Stmt* s5)
{
    pexpr=s3;
    pstmt=s5;

    pexpr->setparent(this);
    pstmt->setparent(this);
}
ForStmt::ForStmt(Expr* s3,Expr* s5,Expr* s7,Stmt* s9)
{
    poptexpr1=s3;
    pexpr=s5;
    poptexpr2=s7;
    pstmt=s9;
    if(poptexpr1)
    	poptexpr1->setparent(this);
    pexpr->setparent(this);
    if(poptexpr2)
    	poptexpr2->setparent(this);
    pstmt->setparent(this);
}
ReturnStmt::ReturnStmt(Expr* s2,YYLTYPE loc)
{
		//自己设置location
		plocation=new YYLTYPE(loc);
		
    poptexpr=s2;

    if(poptexpr)
    	poptexpr->setparent(this);
}
BreakStmt::BreakStmt(YYLTYPE loc)
{
		//自己设置location
		plocation=new YYLTYPE(loc);

}
PrintStmt::PrintStmt(vector<Expr*> *s3)
{
    pexprs=s3;

    for(int i=0;i<pexprs->size();i++)
        (*pexprs)[i]->setparent(this);
}
/**************Expr***********/
Expr::Expr()
{

}
AssignExpr::AssignExpr(Lvalue* s1,Expr* s3)
{
    plvalue=s1;
    pexpr=s3;

    plvalue->setparent(this);
    pexpr->setparent(this);
}
ArithmeticExpr::ArithmeticExpr(Expr* s1,const char* s,Expr* s3)
{
    pexpr1=s1;
    pexpr2=s3;
    opname=s;

    pexpr1->setparent(this);
    if(pexpr2)
        pexpr2->setparent(this);
}
RelationExpr::RelationExpr(Expr* s1,const char* s,Expr* s3)
{
    pexpr1=s1;
    pexpr2=s3;
    opname=s;

    pexpr1->setparent(this);
    pexpr2->setparent(this);
}
LogicalExpr::LogicalExpr(Expr* s1,const char* s,Expr* s3)
{
    pexpr1=s1;
    pexpr2=s3;
    opname=s;

    pexpr1->setparent(this);
    if(pexpr2)
        pexpr2->setparent(this);
}
Lvalue::Lvalue()
{
    
}
FieldAccess::FieldAccess(Expr* s1,Id* s3)
{
    pexpr=s1;
    pid=s3;

    if(pexpr)
        pexpr->setparent(this);
    pid->setparent(this);
}
ArrayAccess::ArrayAccess(Expr* s1,Expr* s3)
{
    pexpr1=s1;
    pexpr2=s3;

    pexpr1->setparent(this);
    pexpr2->setparent(this);
}
Call::Call(Expr* s1,Id* s3,vector<Expr*> *s5)
{
    pid=s3;
    pexpr=s1;
    pactuals=s5;

    pid->setparent(this);
    if(pactuals)
        for(int i=0;i<pactuals->size();i++)
            (*pactuals)[i]->setparent(this);
    if(pexpr)
        pexpr->setparent(this);
}
This::This()
{
    
}
ReadInteger::ReadInteger()
{

}
ReadLine::ReadLine()
{
    
}
Instanceof::Instanceof(Expr* s3,Id* s5)
{
    pexpr=s3;
    pid=s5;

    pexpr->setparent(this);
    pid->setparent(this);
}
NewExpr::NewExpr(Id* s2)
{
    pid=s2;

    pid->setparent(this);
}
NewArrayExpr::NewArrayExpr(Type* s2,Expr* s4)
{
    ptype=s2;
    pexpr=s4;

    ptype->setparent(this);
    pexpr->setparent(this);
}
/**************constant*************/
Constant::Constant()
{
    
}
IntCon::IntCon(int s1,YYLTYPE loc)
{
		//自己设置location
		plocation=new YYLTYPE(loc);
    value=s1;
}
BoolCon::BoolCon(int s1,YYLTYPE loc)
{
		//自己设置location
		plocation=new YYLTYPE(loc);
    value=s1;
}
StringCon::StringCon(const char* s1,YYLTYPE loc)
{
		//自己设置location
		plocation=new YYLTYPE(loc);
    value=s1;
}
NullCon::NullCon(int s1,YYLTYPE loc)
{
    //自己设置location
		plocation=new YYLTYPE(loc);
    value=s1;
}
