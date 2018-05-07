/*************************************************************************
	> File Name: nt_buildsym.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 29 Nov 2016 07:23:43 PM PST
 ************************************************************************/
#ifndef DC_CORE_DC_CLASS_H_
#include "core/dc_class.h"
#endif

#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>

#ifndef DC_CORE_DC_ERROR_H_
#include "core/dc_error.h"
#endif

#ifndef DC_CORE_DC_CONST_H_
#include "core/dc_const.h"
#endif

#include "yacc/y.tab.h"

//Id
std::string Id::getidname()
{
    return name;
}

int Type::getType()
{
    return type;
}
//
std::string NamedType::getClassName()
{
    return pid->getidname();
}

//ArrayType
Type* ArrayType::getNextArray()
{
    return nextArray;
}
int ArrayType::getArrayLevel()
{
    int level = 1;
    Type *mytype = nextArray;
    while((mytype->getType()) == DC::TYPE::DC_ARRAY)
    {
        level++;
        mytype = ((ArrayType*)mytype)->getNextArray();
    }
    return level;
}
Type* ArrayType::getArrayType()
{
    Type *arrayType = nextArray;
    do{
        if (arrayType->getType() == DC::TYPE::DC_ARRAY)
        {
            arrayType = ((ArrayType*)arrayType)->getNextArray();
        }
        else
        {
            break;
        }
        
    }while(true);
    return arrayType;
}
//type info
TypeInfo* Decl::getTypeInfoFromType(Type* type)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo->setType(type->getType());
    switch(type->getType())
    {
        case(DC::TYPE::DC_NAMED):
            typeInfo->setClassName(((NamedType*)type)->getClassName());
            break;
        case(DC::TYPE::DC_ARRAY):
            Type* arrayType = ((ArrayType*)type)->getArrayType();
            if (arrayType->getType() == DC::TYPE::DC_NAMED)
            {
                typeInfo->setClassName(((NamedType*)arrayType)->getClassName());
            }
            typeInfo->setArrayType(arrayType->getType());
            typeInfo->setArrayLevel(((ArrayType*)type)->getArrayLevel());
            break;
        
    }
    return typeInfo;
}

//program
void Program::buildSym()
{    
    gloScope = new GloScope();
    for(int i=0; i<pvecClassDecl->size(); i++)
    {
        gloScope->addEntry(((*pvecClassDecl)[i])->buildGlobalSym()); 
    }
}

Entry* Decl::buildClassSym(std::string name)
{
    return NULL;
}

Entry* Decl::buildGlobalSym()
{
    return NULL;
}

Entry* ClassDecl::buildGlobalSym()
{
    ClaDes *claDes = new ClaDes();
    if(pParentId==NULL)
    {
        //"" means it doesnot have parent
        claDes->setParentName("");
    }
    else
    {
        claDes->setParentName(pParentId->getidname());
    }
    if (pfields->size() != 0)
    {
        ClaScope *claScope = new ClaScope();
        for(int i=0; i<pfields->size(); i++)
        {
            claScope->addEntry(((*pfields)[i])->buildClassSym(pid->getidname()));
        }
        claScope->setClassName(pid->getidname());
        claDes->setClaScope(claScope);
    }
    GloScopeEntry *gloScopeEntry = new GloScopeEntry();
    gloScopeEntry->setClassName(pid->getidname());
    gloScopeEntry->setClaDes(claDes);
    gloScopeEntry->setLocation(pid->getplocation());
    if(claDes->getParentName() != "")
        gloScopeEntry->setParentClassLocation(pParentId->getplocation());
    return gloScopeEntry;
}

Entry* VarDecl::buildClassSym(std::string name)
{
    ClaScopeEntry *claScopeEntry = new ClaScopeEntry();
    claScopeEntry->setName(pid->getidname());
    claScopeEntry->setCategory(DC::CATEGORY::DC_VAR);
    claScopeEntry->setTypeInfo(getTypeInfoFromType(ptype));
    claScopeEntry->setFunDes(NULL);
    claScopeEntry->setLocation(pid->getplocation());
    return claScopeEntry;
}

Entry* FunDecl::buildClassSym(std::string className)
{
    ClaScopeEntry *claScopeEntry = new ClaScopeEntry();
    claScopeEntry->setCategory(DC::CATEGORY::DC_FUN);
    claScopeEntry->setName(pid->getidname());
    claScopeEntry->setTypeInfo(getTypeInfoFromType(ptype));
    //function descriptor
    FunDes *funDes = new FunDes();
    funDes->setIsStatic(isStatic);
    if (pid->getidname() == DC::MAIN)
    {
        funDes->setIsMain(true);
    }
    else
    {
        funDes->setIsMain(false);
    }
    //formal scope
    ForScope *forScope = new ForScope();
    if (isStatic == false)
    {//add this first
        ForScopeEntry *forScopeEntry = new ForScopeEntry();
        forScopeEntry->setName("this");
        TypeInfo *typeInfo = new TypeInfo();
        typeInfo->setType(DC::TYPE::DC_NAMED);
        typeInfo->setClassName(className);
        forScopeEntry->setTypeInfo(typeInfo);
        forScope->addEntry(forScopeEntry);
    }
    for(int i=0; pformals!=NULL && i<pformals->size(); i++)
    {
        forScope->addEntry((*pformals)[i]->buildFormalSym());
    }
    //set local scope
    forScope->setLocScopeEntry(pstmtblock->buildLocalSym());
    forScope->setFunName(pid->getidname());
    funDes->setForScope(forScope);
    claScopeEntry->setFunDes(funDes);
    claScopeEntry->setLocation(pid->getplocation());
    return claScopeEntry;
}

Entry* VarDecl::buildFormalSym()
{
    ForScopeEntry *forScopeEntry = new ForScopeEntry();
    forScopeEntry->setName(pid->getidname());
    forScopeEntry->setTypeInfo(getTypeInfoFromType(ptype));
    forScopeEntry->setLocation(pid->getplocation());
    return forScopeEntry;
}

Entry* VarDecl::buildLocalSym()
{
    LocScopeEntry *locScopeEntry = new LocScopeEntry();
    locScopeEntry->setName(pid->getidname());
    locScopeEntry->setCategory(DC::CATEGORY::DC_VAR);
    locScopeEntry->setTypeInfo(getTypeInfoFromType(ptype));
    locScopeEntry->setSubLocScope(NULL);
    locScopeEntry->setLocation(pid->getplocation());
    return locScopeEntry;
}

Entry* Stmt::buildLocalSym()
{
    return NULL;
}

Entry* StmtBlock::buildLocalSym()
{
    LocScope *locScope = new LocScope();
    for (auto pstmt : *(pstmts))
    {
        locScope->addEntry(pstmt->buildLocalSym());
    }
    LocScopeEntry *locScopeEntry = new LocScopeEntry();
    locScopeEntry->setName("");
    locScopeEntry->setSubLocScope(locScope);
    return locScopeEntry;
}

Entry* IfStmt::buildLocalSym()
{
    LocScope *locScope = new LocScope();
    if(pstmt1 != NULL)
    {
        locScope->addEntry(pstmt1->buildLocalSym());
    }
    if(pstmt2 != NULL)
    {
        locScope->addEntry(pstmt2->buildLocalSym());
    }
    LocScopeEntry *locScopeEntry = new LocScopeEntry();
    locScopeEntry->setName("");
    locScopeEntry->setSubLocScope(locScope);
    return locScopeEntry;
}

Entry* WhileStmt::buildLocalSym()
{
    if (pstmt != NULL)
    {
        return pstmt->buildLocalSym();
    }
    else
    {
        return NULL;
    }
}

Entry* ForStmt::buildLocalSym()
{
    if (pstmt != NULL)
    {
        return pstmt->buildLocalSym();
    }
    else
    {
        return NULL;
    }
}

