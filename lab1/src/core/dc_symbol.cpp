
#ifndef DC_CORE_DC_SYMBOL_H_
#include "core/dc_symbol.h"
#endif

//GloScope
GloScope::GloScope()
{

}

bool GloScope::addEntry(Entry* entry)
{
    entries.push_back(entry);
    return true;
}

//GloScopeEntry
GloScopeEntry::GloScopeEntry()
{
    category = DC::CATEGORY::DC_CLASS;
}

GloScopeEntry::GloScopeEntry(std::string className, ClaDes* claDes)
{
    category = DC::CATEGORY::DC_CLASS;
    this->className = className;
    this->claDes = claDes;
}

bool GloScopeEntry::setCategory(int category)
{
    this->category = category;
    return true;
}

int GloScopeEntry::getCategory() 
{
    return category;
}

bool GloScopeEntry::setClassName(std::string className)
{
    this->className = className;
    return true;
}

std::string GloScopeEntry::getClassName() 
{
    return className;
}

bool GloScopeEntry::setClaDes(ClaDes* claDes)
{   
    this->claDes = claDes;
    return true;
}

const ClaDes* GloScopeEntry::getClaDes() 
{
    return claDes;
}

//ClaDes
ClaDes::ClaDes()
{
    parentClaDes = NULL;
    this->claScope = NULL;
}

bool ClaDes::setParentName(std::string parentName)
{
    this->parentName = parentName;
    return true;
}

std::string ClaDes::getParentName()
{
    return parentName;
}

bool ClaDes::setClaScope(ClaScope* claScope)
{
    this->claScope = claScope;
    return true;
}

const ClaScope* ClaDes::getClaScope()
{
    return claScope;
}

bool ClaDes::setParentClaDes(ClaDes* parentClaDes)
{
    this->parentClaDes = parentClaDes;
    return true;
}

const ClaDes* ClaDes::getParentClaDes()
{
    return parentClaDes;
}

//ClaScope
ClaScope::ClaScope()
{

}
bool ClaScope::addEntry(Entry* entry)
{
    this->entries.push_back(entry);
    return true;
}

TypeInfo::TypeInfo()
{
    className = "";
    arrayLevel = 0;
}

bool TypeInfo::setType(int type)
{
    this->type = type;
    return true;
}

int TypeInfo::getType()
{
    return type;
}

bool TypeInfo::setArrayLevel(int level)
{
    this->arrayLevel = level;
    return true;
}

int TypeInfo::getArrayLevel()
{
    return arrayLevel;
}

bool TypeInfo::setClassName(std::string className)
{
    this->className = className;
    return true;
}



//ClaScopeEntry
ClaScopeEntry::ClaScopeEntry()
{
    this->funDes = NULL;
}

bool ClaScopeEntry::setName(std::string name)
{
    this->name = name;
    return true;
}

std::string ClaScopeEntry::getName()
{
    return name;
}

bool ClaScopeEntry::setCategory(int category)
{
    this->category = category;
    return true;
}

int  ClaScopeEntry::getCategory()
{
    return category;
}
    
bool ClaScopeEntry::setTypeInfo(TypeInfo* typeInfo)
{
    this->typeInfo = typeInfo;
    return true;
}

const TypeInfo* ClaScopeEntry::getTypeInfo()
{
    return typeInfo;
}
 
bool ClaScopeEntry::setFunDes(FunDes *funDes)
{
    this->funDes = funDes;
    return true;
}

const FunDes* ClaScopeEntry::getFunDes()
{
    return funDes;
}
//function descriptor
FunDes::FunDes()
{
    this->isStatic = false;
    this->isMain = false;
}

bool FunDes::setIsStatic(bool isStatic)
{
    this->isStatic = isStatic;
    return true;
}

bool FunDes::getIsStatic()
{
    return isStatic;
}

bool FunDes::setIsMain(bool isMain)
{
    this->isMain = isMain;
    return true;
}

bool FunDes::getIsMain()
{
    return isMain;
}

bool FunDes::setForScope(ForScope *forScope)
{
    this->forScope = forScope;
    return true;
}

const ForScope* FunDes::getForScope()
{
    return this->forScope;
}
//formal scope
ForScope::ForScope()
{

}
bool ForScope::addEntry(Entry *entry)
{
    this->entries.push_back(entry);
    return true;
}
bool ForScope::setLocScopeEntry(Entry *locScopeEntry)
{
    this->locScopeEntry = (LocScopeEntry*)locScopeEntry;
    return true;
}
const LocScopeEntry* ForScope::getLocScopeEntry()
{
    return this->locScopeEntry;
}
//formal scope entry
ForScopeEntry::ForScopeEntry()
{

}
bool ForScopeEntry::setName(std::string name)
{
    this->name = name;
    return true;
}
std::string ForScopeEntry::getName()
{
    return this->name;
}
bool ForScopeEntry::setTypeInfo(TypeInfo *typeInfo)
{
    this->typeInfo = typeInfo;
    return true;
}
const TypeInfo* ForScopeEntry::getTypeInfo()
{
    return this->typeInfo;
}
//local scope
LocScope::LocScope()
{

}
bool LocScope::addEntry(Entry* entry)
{
    this->entries.push_back(entry);
    return true;
}
//local scope entry
LocScopeEntry::LocScopeEntry()
{

}
bool LocScopeEntry::setName(std::string name)
{
    this->name = name;
    return true;
}
std::string LocScopeEntry::getName()
{
    return name;
}
bool LocScopeEntry::setCategory(int category)
{
    this->category = category;
    return true;
}
int LocScopeEntry::getCategory()
{
    return category;
}

bool LocScopeEntry::setTypeInfo(TypeInfo *typeInfo)
{
    this->typeInfo = typeInfo;
    return true;
}

const TypeInfo* LocScopeEntry::getTypeInfo()
{
    return this->typeInfo;
}

bool LocScopeEntry::setSubLocScope(LocScope* subLocScopeEntry)
{
    this->subLocScope = subLocScope;
    return true;
}
const LocScope* LocScopeEntry::getSubLocScope()
{
    return subLocScope;
}





