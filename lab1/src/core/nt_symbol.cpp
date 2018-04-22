#include "nt_symbol.h"

GloScopeEntry::GloScopeEntry(std::string className, std::string catagory, ClaDes *pClades)
{
    this->className = className;
    this->catagory = catagory;
    this->pClades = pClades;
}

GloScopeEntry::GloScopeEntry(std::string className, ClaDes *pClades)
{
    this->className = className;
    this->catagory = "class";
    this->pClades = pClades;
}

std::string GloScopeEntry::getClassName() 
{
    return className;
}

std::string GloScopeEntry::getCategory() 
{
    return category;
}

const ClaDes* GloScopeEntry::getPClaDes() 
{
    return (const ClaDes*)pClaDes;
}

ClaScopeEntry::ClaScopeEntry(std::string name, std::string category, Type *pType, FunDes *pFunDes)
{
    this->name = name;
    this->category = category;
    this->pType = pType;
    this->pFunDes = pFunDes;
}

std::string ClaScopeEntry::getName()
{
    return name;
}

std::string ClaScopeEntry::getCategory()
{
    return category;
}

const Type* ClaScopeEntry::getPType()
{
    return (const Type*)pType;
}

const FunDes* ClaScopeEntry::getPFunDes()
{
    return (const FunDes*)pFunDes;
}




ClaDes::ClaDes(string className, string parentName, ClaDes *pParentClaDes, vector<ClaScope*> *pvecClaScope)
{
    this->className = className;
    this->parentName = parentName;
    this->pParentClaDes = pParentClaDes;
    this->pvecClaScope = pvecClaScope;
}