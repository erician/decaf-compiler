#include "nt_symbol.h"

//GloScope
GloScope::GloScope()
{

}

bool GloScope::addEntry(const GloScopeEntry& entry)
{
    entries.push_back(entry);
    return true;
}

//GloScopeEntry
GloScopeEntry::GloScopeEntry()
{
    category = DC_CLASS;
}

bool GloScopeEntry::setCategory(int category)
{
    this->category = category;
}

int GloScopeEntry::getCategory() 
{
    return category;
}

bool GloScopeEntry::setClassName(std::string className)
{
    this->className = className;
}

std::string GloScopeEntry::getClassName() 
{
    return className;
}

bool GloScopeEntry::setClaDes(const ClaDes* claDes)
{   
    this->claDes = claDes;
}

const ClaDes* GloScopeEntry::getClaDes() 
{
    return claDes;
}

//ClaScopeEntry
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

//ClaDes
ClaDes()
{

}

bool setClassName(std::string className)
{
    this->className = className;
}

std::string ClaDes::getClassName()
{
    return className;
}

bool setParentName(std::string parentName)
{
    this->parentName = parentName;
}

std::string ClaDes::getParentName()
{
    return parentName;
}

bool ClaDes::setClaScope(const ClaScope* claScope)
{
    this->claScope = claScope;
}

const ClaScope* ClaDes::getClaScope()
{
    return claScope;
}

bool ClaDes::setParentClaDes(const ClaDes* parentClaDes)
{
    this->parentClaDes = parentClaDes;
}

const ClaDes* ClaDes::getParentClaDes()
{
    return parentClaDes;
}

//ClaScope
const ClaDes& getParentClaDes()
{
    return parentClaDes;
}
const ClaScope& getClaScope()
{
    return claScope;
}
