#ifndef DC_CORE_DC_CLASS_H_
#include "core/dc_class.h"
#endif

#ifndef DC_CORE_DC_SYMBOL_H_
#include "core/dc_symbol.h"
#endif

#ifndef DC_LEX_FLEX_H_
#include "core/dc_error.h"
#endif

bool Program::checkStaticSemantic()
{
    return gloScope->check();
}

bool GloScope::check()
{
    if(this->checkUndefinedClass() == false)
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
    bool doesHaveError = false;
    for(auto gloScopeEntry : entries)
    {
        ClaDes* claDes = ((GloScopeEntry*)gloScopeEntry)->getClaDes();
        if (claDes->getParentName() != "")
        {
            GloScopeEntry* parentGloScopeEntry = findClass(claDes->getParentName());
            if(parentGloScopeEntry == NULL)
            {
                doesHaveError = true;
                IssueError::UnDefinedClass(((GloScopeEntry*)gloScopeEntry)->getParentClassLocation(), claDes->getParentName());
            }
            else
            {
                claDes->setParentClaDes(parentGloScopeEntry->getClaDes());
            }
        }
    }
    return doesHaveError;
}




