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

void treenode::PrintWhite(int aline,int level)
{
    if(aline)
    {
        cout<<endl;
        for(int i=0;i<level;i++)
            cout<<"    ";
    }
    else
    {
        cout<<" ";
    }
} 

void Id::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<name<<' ';
}

void Program::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"Program";
    for(int i=0;i<pdecllist->size();i++)
        (*pdecllist)[i]->Print(1,1+level);
}

void VarDecl::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"VarDecl ";
    pid->Print(0,level);
    ptype->Print(0,level);
}
void FnDecl::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"FnDecl ";
    pid->Print(0,level);
    if(isstatic)
        cout<<"static ";
    ptype->Print(0,level);
    if(pformals!=NULL)
    {
        PrintWhite(1,level+1);
        cout<<"formals";
        for(int i=0;i<pformals->size();i++)
            (*pformals)[i]->Print(1,level+2);
    }
    pstmtblock->Print(1,level+1);
}
void ClassDecl::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"ClassDecl ";
    pid->Print(0,level);
    if(base!=NULL)
    {
        cout<<"Extends ";
        base->Print(0,level);
    }
    for(int i=0;i<pfields->size();i++)
    (*pfields)[i]->Print(1,level+1);
}
void IntType::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"inttype ";
}
void BoolType::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"booltype ";
}
void StringType::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"stringtype ";
}
void VoidType::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"voidtype ";
}
void NamedType::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"classtype ";
    pid->Print(0,level);
}
void ArrayType::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"arraytype ";
    ptype->Print(0,level);
}

void StmtBlock::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"StmtBlock";
    if(pvardecls!=NULL)
    {
        for(int i=0;i<pvardecls->size();i++)
            (*pvardecls)[i]->Print(1,level+1);
    }
    if(pstmts!=NULL)
    {
        for(int i=0;i<pstmts->size();i++)
            (*pstmts)[i]->Print(1,level+1);
    }
}
void IfStmt::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"if";
    pexpr->Print(1,level+1);
    if(pstmt1!=NULL)
        pstmt1->Print(1,level+1);
    if(elsename=="else")
    {
        cout<<"else"<<endl;
        pstmt2->Print(1,level+1);
    }
}

 void WhileStmt::Print(int aline,int level)
 {
    PrintWhite(aline,level);
    cout<<"while";
    pexpr->Print(1,level+1);
    pstmt->Print(1,level+1);
}
void ForStmt::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"for";
    if(poptexpr1!=NULL)
        poptexpr1->Print(1,level+1);
    if(pexpr!=NULL)
        pexpr->Print(1,level+1);
    if(poptexpr2!=NULL)
        poptexpr2->Print(1,level+1);
    pstmt->Print(1,level+1);
}
void ReturnStmt::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"return";
    poptexpr->Print(1,level+1);
}
void BreakStmt::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"break";
}
void PrintStmt::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"Print";
    for(int i=0;i<pexprs->size();i++)
        (*pexprs)[i]->Print(1,level+1);
}
void AssignExpr::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"=";
    plvalue->Print(1,level+1);
    pexpr->Print(1,level+1);
}

void ArithmeticExpr::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<opname;
    pexpr1->Print(1,level+1);
    pexpr2->Print(1,level+1);
}
void RelationExpr::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<opname;
    pexpr1->Print(1,level+1);
    pexpr2->Print(1,level+1);
}
void LogicalExpr::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<opname;
    pexpr1->Print(1,level+1);
    pexpr2->Print(1,level+1);
}

void FieldAccess::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"FieldAccess ";
    if(pexpr!=NULL)
    {
        pexpr->Print(0,level);
    }
    pid->Print(0,level);
}
void ArrayAccess::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"ArrayAccess ";
    pexpr1->Print(0,level);
    pexpr2->Print(0,level);
}

void Call::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"call"<<endl;
    if(pexpr!=NULL)
        pexpr->Print(1,level+1);
    pid->Print(1,level+1);
    for(int i=0;i<pactuals->size();i++)
        (*pactuals)[i]->Print(1,level+1);
    }
void This::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"this ";
}

void ReadInteger::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"ReadInteger"<<endl;
}
void ReadLine::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"ReadLine"<<endl;
}

void Instanceof::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"instanceof"<<endl;
    pexpr->Print(1,level+1);
    pid->Print(1,level+1);
}

void NewExpr::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"New ";
    pid->Print(0,level);
}

void NewArrayExpr::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"New ";
    ptype->Print(0,level);
    cout<<"[] ";
    pexpr->Print(0,level);
}
void IntCon::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"intcon "<<value;
}

void BoolCon::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"boolcon ";
    if(value)
        cout<<"true";
    else
        cout<<"false";
}
void StringCon::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"stringcon "<<value;
}
void NullCon::Print(int aline,int level)
{
    PrintWhite(aline,level);
    cout<<"nullcon "<<"NULL";
}






