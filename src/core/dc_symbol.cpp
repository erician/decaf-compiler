
#ifndef DC_CORE_DC_SYMBOL_H_
#include "core/dc_symbol.h"
#endif

//Entry
bool Entry::setLocation(YYLTYPE* location)
{
    this->location = location;
    return true;
}

YYLTYPE* Entry::getLocation()
{
    return this->location;
}

//Scope

Scope* Scope::getParentScope()
{
    return NULL;
}

//GloScope
GloScope::GloScope()
{

}

bool GloScope::addEntry(Entry* entry)
{
    if(entry == NULL)
    {
        return false;
    }
    entries.push_back(entry);
    return true;
}

std::vector<Entry*> GloScope::getEntries()
{
    return entries;
}

//GloScopeEntry
GloScopeEntry::GloScopeEntry()
{
    category = DC::CATEGORY::DC_CLASS;
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

ClaDes* GloScopeEntry::getClaDes() 
{
    return claDes;
}

bool GloScopeEntry::setParentClassLocation(YYLTYPE *location)
{
    this->parentClassLocation = location;
    return true;
}

YYLTYPE* GloScopeEntry::getParentClassLocation()
{
    return parentClassLocation;
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

ClaScope* ClaDes::getClaScope()
{
    return claScope;
}

bool ClaDes::setParentClaDes(ClaDes* parentClaDes)
{
    this->parentClaDes = parentClaDes;
    return true;
}

ClaDes* ClaDes::getParentClaDes()
{
    return parentClaDes;
}

//ClaScope
ClaScope::ClaScope()
{

}
bool ClaScope::addEntry(Entry* entry)
{
    if(entry == NULL)
    {
        return false;
    }
    this->entries.push_back(entry);
    return true;
}

std::vector<Entry*> ClaScope::getEntries()
{
    return entries;
}

bool ClaScope::setClassName(std::string className)
{
    this->className = className;
    return true;
}

std::string ClaScope::getClassName()
{
    return className;
}

//type info
TypeInfo::TypeInfo()
{
    type = -1;
    className = "";
    arrayLevel = 0;
    arrayType = -1;
    name = "";
    location = NULL;
}

TypeInfo::TypeInfo(TypeInfo* typeInfo)
{
    this->setType(typeInfo->getType());
    this->setClassName(typeInfo->getClassName());
    this->setArrayLevel(typeInfo->getArrayLevel());
    this->setArrayType(typeInfo->getArrayType());
    this->setName(typeInfo->getName());
    this->setLocation(typeInfo->getLocation());
}

bool TypeInfo::setType(int type)
{
    this->type = type;
    return true;
}

TypeInfo* TypeInfo::withType(int type)
{
    this -> type = type;
    return this;
}

int TypeInfo::getType()
{
    return type;
}

std::string TypeInfo::typeIntToString(int type)
{
    switch(type)
    {
        case DC::TYPE::TYPE::DC_BOOL:
            return "bool";
        case DC::TYPE::TYPE::DC_INT:
            return "int";
        case DC::TYPE::TYPE::DC_VOID:
            return "void";
        case DC::TYPE::TYPE::DC_STRING:
            return "string";
        case DC::TYPE::TYPE::DC_NAMED:
            return std::string("class ") + className;
        case DC::TYPE::TYPE::DC_ARRAY:
        {
            std::string returnVal = typeIntToString(arrayType);
            for(int i=0; i < arrayLevel; i++)
                returnVal += "[]";
            return returnVal;
        }
        default:
            ; 
    }
    return "";
}

std::string TypeInfo::getTypeName()
{
    return typeIntToString(type);
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

bool TypeInfo::setArrayType(int type)
{
    this->arrayType = type;
    return true;
}

int TypeInfo::getArrayType()
{
    return arrayType;
}

bool TypeInfo::setClassName(std::string className)
{
    this->className = className;
    return true;
}

std::string TypeInfo::getClassName()
{
    return this -> className;
}

bool TypeInfo::setName(std::string name)
{
    this -> name = name;
    return true;
}
std::string TypeInfo::getName()
{
    return this -> name;
}

bool TypeInfo::setLocation(YYLTYPE* location)
{
    this -> location = location;
    return true;
}
YYLTYPE* TypeInfo::getLocation()
{
    return this -> location;
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

TypeInfo* ClaScopeEntry::getTypeInfo()
{
    return typeInfo;
}
 
bool ClaScopeEntry::setFunDes(FunDes *funDes)
{
    this->funDes = funDes;
    return true;
}

FunDes* ClaScopeEntry::getFunDes()
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

ForScope* FunDes::getForScope()
{
    return this->forScope;
}
//formal scope
ForScope::ForScope()
{
    this -> className = "";
}
bool ForScope::addEntry(Entry *entry)
{
    if(entry == NULL)
    {
        return false;
    }
    this->entries.push_back(entry);
    return true;
}

std::vector<Entry*> ForScope::getEntries()
{
    return entries;
}

bool ForScope::setLocScopeEntry(Entry *locScopeEntry)
{
    this->locScopeEntry = (LocScopeEntry*)locScopeEntry;
    return true;
}
LocScopeEntry* ForScope::getLocScopeEntry()
{
    return this->locScopeEntry;
}

bool ForScope::setFunName(std::string funName)
{
    this->funName = funName;
    return true;
}

std::string ForScope::getFunName()
{
    return funName;
}

bool ForScope::setClassName(std::string className)
{
    this->className = className;
    return true;
}

std::string ForScope::getClassName()
{
    return this -> className;
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
TypeInfo* ForScopeEntry::getTypeInfo()
{
    return this->typeInfo;
}
//local scope
LocScope::LocScope()
{
    parentScope = NULL;
    start = 0;
}
bool LocScope::addEntry(Entry* entry)
{
    if(entry == NULL)
    {
        return false;
    }
    this->entries.push_back(entry);
    return true;
}

std::vector<Entry*> LocScope::getEntries()
{
    return entries;
}

bool LocScope::setParentScope(Scope* parentScope)
{
    this->parentScope = parentScope;
    return true;
}
Scope* LocScope::getParentScope()
{
    return this->parentScope;
}

void LocScope::setStart(int start)
{
    this->start = start;
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

TypeInfo* LocScopeEntry::getTypeInfo()
{
    return this->typeInfo;
}

bool LocScopeEntry::setSubLocScope(LocScope* subLocScope)
{
    this->subLocScope = subLocScope;
    return true;
}

LocScope* LocScopeEntry::getSubLocScope()
{
    return subLocScope;
}





