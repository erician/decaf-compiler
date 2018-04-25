#include "nt_symbol.h"

//GloScope
GloScope::GloScope()
{

}

bool GloScope::addEntry(GloScopeEntry* entry)
{
    entries.push_back(entry);
    return true;
}

//GloScopeEntry
GloScopeEntry::GloScopeEntry()
{
    category = DC_CLASS;
}

GloScopeEntry::GloScopeEntry(std::string className, ClaDes* claDes)
{
    category = DC_CLASS;
    this->className = className;
    this->claDes = claDes;
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

//ClaDes
ClaDes()
{
    parentClaDes = NULL;
    this->claScope = NULL;
}

bool ClaDes::setParentName(std::string parentName)
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
ClaScope::ClaScope()
{

}
bool ClaScope::addEntry(ClaScopeEntry* entry)
{
    this->entries.push_back(entry);
}

TypeInfo::TypeInfo()
{
    className = "";
    arrayLevel = 0;
}

bool TypeInfo::setType(int type)
{
    this->type = type;
}

int getType()
{
    return type;
}

bool setArrayLevle(int level)
{
    this->arrayLevel = level;
}

int getArrayLevel()
{
    return arrayLevel;
}

bool setClassName(std::string className)
{
    this->className = className;
}

std::string getClassName()
{
    return className;
}

//ClaScopeEntry
ClaScopeEntry::ClaScopeEntry()
{
    this->funDes = NULL;
}

bool ClaScopeEntry::setName(std::string name)
{
    this->name = name;
}

std::string ClaScopeEntry::getName()
{
    return name;
}

bool ClaScopeEntry::setCategory(int category)
{
    this->category = categort;
}

int  ClaScopeEntry::getCategory()
{
    return category;
}
    
bool ClaScopeEntry::setTypeInfo(TypeInfo* typeInfo)
{
    this->typeInfo = typeInfo;
}

int ClaScopeEntry::getTypeInfo()
{
    return typeInfo;
}
 
bool ClaScopeEntry::setFunDes(FunDes *funDes)
{
    this->funDes = funDes;
}

const FunDes* ClaScopeEntry::getFunDes()
{
    return funDes;
}

