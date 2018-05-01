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

void TreeNode::printWhite(int aline,int level)
{
    if(aline)
    {
        std::cout<<std::endl;
        for(int i=0;i<level;i++)
            std::cout<<"    ";
    }
    else
    {
        std::cout<<" ";
    }
} 

void Id::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<name<<' ';
}

void Program::printAst(int aline,int level)
{
    std::cout<<"Program";
    for(int i=0;i<pvecClassDecl->size();i++)
        (*pvecClassDecl)[i]->printAst(1,1+level);
    std::cout<<std::endl;
}

void VarDecl::printAst(int aline,int level)
{
    Decl::printWhite(aline,level);
    std::cout<<"VarDecl ";
    pid->printAst(0,level);
    ptype->printAst(0,level);
}
void FunDecl::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"FnDecl ";
    pid->printAst(0,level);
    if(isStatic)
        std::cout<<"static ";
    ptype->printAst(0,level);
    if(pformals!=NULL)
    {
        printWhite(1,level+1);
        std::cout<<"formals";
        for(int i=0;i<pformals->size();i++)
            (*pformals)[i]->printAst(1,level+2);
    }
    pstmtblock->printAst(1,level+1);
}
void ClassDecl::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"ClassDecl ";
    pid->printAst(0,level);
    if(pParentId != NULL)
    {
        std::cout<<"Extends ";
        pParentId->printAst(0,level);
    }
    for(int i=0;i<pfields->size();i++)
    (*pfields)[i]->printAst(1,level+1);
}
void IntType::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"inttype ";
}
void BoolType::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"booltype ";
}
void StringType::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"stringtype ";
}
void VoidType::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"voidtype ";
}
void NamedType::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"classtype ";
    pid->printAst(0,level);
}
void ArrayType::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"arraytype ";
    nextArray->printAst(0,level);
}

void StmtBlock::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"StmtBlock";
    if(pstmts!=NULL)
    {
        for(int i=0;i<pstmts->size();i++)
            (*pstmts)[i]->printAst(1,level+1);
    }
}
void IfStmt::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"if";
    pexpr->printAst(1,level+1);
    if(pstmt1!=NULL)
        pstmt1->printAst(1,level+1);
    if(elsename=="else")
    {
        std::cout<<"else"<<std::endl;
        pstmt2->printAst(1,level+1);
    }
}

 void WhileStmt::printAst(int aline,int level)
 {
    printWhite(aline,level);
    std::cout<<"while";
    pexpr->printAst(1,level+1);
    pstmt->printAst(1,level+1);
}
void ForStmt::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"for";
    if(poptexpr1!=NULL)
        poptexpr1->printAst(1,level+1);
    if(pexpr!=NULL)
        pexpr->printAst(1,level+1);
    if(poptexpr2!=NULL)
        poptexpr2->printAst(1,level+1);
    pstmt->printAst(1,level+1);
}
void ReturnStmt::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"return";
    poptexpr->printAst(1,level+1);
}
void BreakStmt::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"break";
}
void PrintStmt::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"Print";
    for(int i=0;i<pexprs->size();i++)
        (*pexprs)[i]->printAst(1,level+1);
}
void AssignExpr::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"=";
    plvalue->printAst(1,level+1);
    pexpr->printAst(1,level+1);
}

void ArithmeticExpr::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<opname;
    pexpr1->printAst(1,level+1);
    pexpr2->printAst(1,level+1);
}
void RelationExpr::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<opname;
    pexpr1->printAst(1,level+1);
    pexpr2->printAst(1,level+1);
}
void LogicalExpr::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<opname;
    pexpr1->printAst(1,level+1);
    pexpr2->printAst(1,level+1);
}

void FieldAccess::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"FieldAccess ";
    if(pexpr!=NULL)
    {
        pexpr->printAst(0,level);
    }
    pid->printAst(0,level);
}
void ArrayAccess::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"ArrayAccess ";
    pexpr1->printAst(0,level);
    pexpr2->printAst(0,level);
}

void Call::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"call";
    if(pexpr!=NULL)
        pexpr->printAst(1,level+1);
    pid->printAst(1,level+1);
    for(int i=0;i<pactuals->size();i++)
        (*pactuals)[i]->printAst(1,level+1);
    }
void This::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"this ";
}

void ReadInteger::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"ReadInteger"<<std::endl;
}
void ReadLine::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"ReadLine"<<std::endl;
}

void Instanceof::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"instanceof"<<std::endl;
    pexpr->printAst(1,level+1);
    pid->printAst(1,level+1);
}

void NewExpr::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"New ";
    pid->printAst(0,level);
}

void NewArrayExpr::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"New ";
    ptype->printAst(0,level);
    std::cout<<"[] ";
    pexpr->printAst(0,level);
}
void IntCon::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"intcon "<<value;
}

void BoolCon::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"boolcon ";
    if(value)
        std::cout<<"true";
    else
        std::cout<<"false";
}
void StringCon::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"stringcon "<<value;
}
void NullCon::printAst(int aline,int level)
{
    printWhite(aline,level);
    std::cout<<"nullcon "<<"NULL";
}



