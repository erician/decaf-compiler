
#ifndef DC_CORE_DC_CLASS_H_
#include "core/dc_class.h"
#endif

#ifndef DC_CORE_DC_SYMBOL_H_
#include "core/dc_symbol.h"
#endif

#ifndef DC_UTILS_PRINT_DC_PRINT_H_
#include "utils/print/dc_print.h"
#endif

void Program::printSym(int aline, int level)
{
    gloScope->printSym(aline, level);
}

void GloScope::printSym(int aline, int level)
{
    //global scope
    std::cout<<"GLOBAL SCOPE:";
    for(auto gloScopeEntry : entries)
    {
        gloScopeEntry->printSym(1, level+1);
    }
    std::cout<<std::endl;
}

void GloScopeEntry::printSym(int aline, int level)
{
    DC::UTILS::PRINT::printWhite(aline, level);
    std::cout<<"class ";
    std::cout<<className;
    claDes->printSym(0, level);
}

void ClaDes::printSym(int aline, int level)
{
    DC::UTILS::PRINT::printWhite(aline, level);
    if(parentName != "")
    {
        std::cout<<": "<<parentName;
    }
    claScope->printSym(1, level + 1);
}

void ClaScope::printSym(int aline, int level)
{
    DC::UTILS::PRINT::printWhite(aline, level);
    std::cout<<"CLASS SCOPE OF "<<className;
    for(auto claScopeEntry : entries)
    {
        claScopeEntry->printSym(1, level+1);
    }
}

void ClaScopeEntry::printSym(int aline, int level)
{
    DC::UTILS::PRINT::printWhite(aline, level);
    if(category == DC::CATEGORY::DC_VAR)
    {
        std::cout<<"variable "<<name;
        typeInfo->printSym(0, level);
    }
    else if(category == DC::CATEGORY::DC_FUN)
    {
        std::cout<<"function "<<name;
        typeInfo->printSym(0, level);
        funDes->printSym(0, level);
    }
}

void TypeInfo::printSym(int aline, int level)
{
    DC::UTILS::PRINT::printWhite(aline, level);
    switch(type)
    {
        case(DC::TYPE::DC_NAMED):
            std::cout<<DC::TYPE::DC_TYPENAME[type]<<" "<<className;
            break;
        case(DC::TYPE::DC_ARRAY):
            std::cout<<DC::TYPE::DC_TYPENAME[arrayType];
            if(arrayType == DC::TYPE::DC_NAMED)
            {
                std::cout<<" "<<className;
            }
            for(int i=0; i<arrayLevel; i++)
            {
                std::cout<<"[]";
            }
            break;
        default:
            std::cout<<DC::TYPE::DC_TYPENAME[type];
            break;
    }
}

void FunDes::printSym(int aline, int level)
{
    DC::UTILS::PRINT::printWhite(aline, level);
    if(isStatic)
    {
        std::cout<<"static";
    }
    if(isMain)
    {
        std::cout<<" main";
    }
    forScope->printSym(1, level);
}

void ForScope::printSym(int aline, int level)
{
    DC::UTILS::PRINT::printWhite(aline, level);
    std::cout<<"FORMAL SCOPE OF "<<funName;
    for(auto forScopeEntry : entries)
    {
        forScopeEntry->printSym(1, level + 1);
    }
    DC::UTILS::PRINT::printWhite(1, level + 1);
    std::cout<<"LOCAL SCOPE:";
    locScopeEntry->printSym(1, level + 2);
}

void ForScopeEntry::printSym(int aline, int level)
{
    DC::UTILS::PRINT::printWhite(aline, level);
    std::cout<<"variable "<<name;
    typeInfo->printSym(0, level);
}

void LocScope::printSym(int aline, int level)
{
    for(auto locScopeEntry : entries)
    {
        locScopeEntry->printSym(1, level);
    }
}

void LocScopeEntry::printSym(int aline, int level)
{
    if (name == "")
    {
        if(subLocScope != NULL)
        {
            subLocScope->printSym(1, level);
        }
    }
    else
    {
        DC::UTILS::PRINT::printWhite(aline, level);
        std::cout<<"variable "<<name;
        typeInfo->printSym(0, level);
        if(subLocScope != NULL)
        {
            subLocScope->printSym(1, level+1);
        }
    }
}

