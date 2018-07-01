/*************************************************************************
	> File Name: not_terminal_class.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 28 Nov 2016 12:07:01 AM PST
 ************************************************************************/
#ifndef DC_CORE_DC_CLASS_H_
#include "core/dc_class.h"
#endif

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifndef DC_YACC_LOCATION_H_
#include "yacc/location.h"
#endif

//类的构造函数
TreeNode::TreeNode()
{
    plocation=NULL;
}
TreeNode::TreeNode(YYLTYPE s1)
{
    plocation=new YYLTYPE(s1);
}
Id::Id(char* str,YYLTYPE loc):TreeNode(loc)
{
    name = str;
}

Program::Program(std::vector<Decl*> *s1)
{
    pvecClassDecl = s1;
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
}
FunDecl::FunDecl(int s,Type* s1,Id* s2,std::vector<VarDecl*>* s4,StmtBlock* s6):Decl(s2)
{
    if (s == 0)
    {
        this->isStatic = false;
    }
    else
    {
        this->isStatic = true;
    }
    ptype = s1;
    pformals = s4;
    pstmtblock = s6;
}
ClassDecl::ClassDecl(Id* s2,Id* s4,std::vector<Decl*>* s6):Decl(s2)
{
    pParentId = s4;
    pfields = s6;
}
/**********type****************/
Type::Type()
{
}

IntType::IntType()
{
    type = DC::TYPE::DC_INT;
}
BoolType::BoolType()
{
    type = DC::TYPE::DC_BOOL;
}
StringType::StringType()
{
    type = DC::TYPE::DC_STRING;
}
VoidType::VoidType()
{
    type = DC::TYPE::DC_VOID;
}

NamedType::NamedType(Id* s2)
{
    type = DC::TYPE::DC_NAMED;
    pid = s2;
}
ArrayType::ArrayType(Type* s1)
{
    type = DC::TYPE::DC_ARRAY;
    nextArray = s1;
}

/***********StmtBlock*************/
StmtBlock::StmtBlock(std::vector<Stmt*> *s2)
{
    pstmts=s2;
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
}
WhileStmt::WhileStmt(Expr* s3,Stmt* s5)
{
    pexpr=s3;
    pstmt=s5;
}
ForStmt::ForStmt(Expr* s3,Expr* s5,Expr* s7,Stmt* s9)
{
    poptexpr1=s3;
    pexpr=s5;
    poptexpr2=s7;
    pstmt=s9;
}
ReturnStmt::ReturnStmt(Expr* s2,YYLTYPE loc)
{
	//自己设置location
	plocation=new YYLTYPE(loc);
    poptexpr=s2;
}
BreakStmt::BreakStmt(YYLTYPE loc)
{
	//自己设置location
	plocation=new YYLTYPE(loc);
}
PrintStmt::PrintStmt(std::vector<Expr*> *s3)
{
    pexprs=s3;
}
/**************Expr***********/
Expr::Expr()
{

}
AssignExpr::AssignExpr(Lvalue* s1,Expr* s3)
{
    plvalue=s1;
    pexpr=s3;
}
ArithmeticExpr::ArithmeticExpr(Expr* s1,const char* s,Expr* s3)
{
    pexpr1=s1;
    pexpr2=s3;
    opname=s;
}
RelationExpr::RelationExpr(Expr* s1,const char* s,Expr* s3)
{
    pexpr1=s1;
    pexpr2=s3;
    opname=s;
}
LogicalExpr::LogicalExpr(Expr* s1,const char* s,Expr* s3)
{
    pexpr1=s1;
    pexpr2=s3;
    opname=s;
}
Lvalue::Lvalue()
{
    
}
FieldAccess::FieldAccess(Expr* s1,Id* s3)
{
    pexpr=s1;
    pid=s3;
}
ArrayAccess::ArrayAccess(Expr* s1,Expr* s3)
{
    pexpr1=s1;
    pexpr2=s3;
}
Call::Call(Expr* s1,Id* s3,std::vector<Expr*> *s5)
{
    pid=s3;
    pexpr=s1;
    pactuals=s5;
}
This::This(YYLTYPE loc)
{
    plocation=new YYLTYPE(loc);
}
ReadInteger::ReadInteger(YYLTYPE loc)
{
    plocation=new YYLTYPE(loc);
}
ReadLine::ReadLine(YYLTYPE loc)
{
    plocation=new YYLTYPE(loc);
}
Instanceof::Instanceof(Expr* s3,Id* s5)
{
    pexpr=s3;
    pid=s5;
}
NewExpr::NewExpr(Id* s2)
{
    pid=s2;
}
NewArrayExpr::NewArrayExpr(Type* s2, YYLTYPE loc, Expr* s4)
{
    ptype=s2;
    plocation=new YYLTYPE(loc);
    pexpr=s4;
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
