#ifndef DC_CORE_DC_CLASS_H_
#include "core/dc_class.h"
#endif

#ifndef DC_CORE_DC_SYMBOL_H_
#include "core/dc_symbol.h"
#endif

#ifndef DC_LEX_FLEX_H_
#include "core/dc_error.h"
#endif

#include <map>

bool Program::checkStaticSemantic()
{
    return gloScope->check();
}

bool GloScope::check()
{
    if(checkUndefinedClass() == false)
        return false;
    if(checkRedefinedClass() == false)
        return false;
    
    return true;
}

GloScopeEntry* GloScope::findClass(std::string className)
{
    for(auto gloScopeEntry : entries)
    {
        if(((GloScopeEntry*)gloScopeEntry) -> getClassName() == className)
        {
            return (GloScopeEntry*)gloScopeEntry;
        }
    }
    return NULL;
}

bool GloScope::checkUndefinedClass()
{
    bool noErrors = true;
    for(auto gloScopeEntry : entries)
    {
        ClaDes* claDes = ((GloScopeEntry*)gloScopeEntry)->getClaDes();
        if (claDes->getParentName() != "")
        {
            GloScopeEntry* parentGloScopeEntry = findClass(claDes->getParentName());
            if(parentGloScopeEntry == NULL)
            {
                noErrors = false;
                IssueError::UndefinedClass(((GloScopeEntry*)gloScopeEntry)->getParentClassLocation(), claDes->getParentName());
            }
            else
            {
                claDes->setParentClaDes(parentGloScopeEntry->getClaDes());
            }
        }
    }
    return noErrors;
}

bool GloScope::checkRedefinedClass()
{
    bool noErrors = true;
    std::map<std::string, bool> doesClassExistMap;
    for(auto gloScopeEntry : entries)
    {
        std::string className = ((GloScopeEntry*)gloScopeEntry) -> getClassName();
        if(doesClassExistMap.find(className) == doesClassExistMap.end())
        {
            doesClassExistMap[className] = true;
        }
        else
        {
            noErrors = false;
            IssueError::RedefinedClass(((GloScopeEntry*)gloScopeEntry) -> getLocation(), ((GloScopeEntry*)gloScopeEntry) -> getClassName());
        }
    }
    return noErrors;
}





