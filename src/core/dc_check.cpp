#ifndef DC_CORE_DC_CLASS_H_
#include "core/dc_class.h"
#endif

#ifndef DC_CORE_DC_SYMBOL_H_
#include "core/dc_symbol.h"
#endif

#ifndef DC_LEX_FLEX_H_
#include "core/dc_error.h"
#endif

#ifndef DC_CORE_DC_ENUM_H_
#include "core/dc_enum.h"
#endif

#ifndef DC_CORE_DC_CONST_H_
#include "core/dc_const.h"
#endif

#ifndef DC_YACC_LOCATION_H_
#include "yacc/location.h"
#endif

#include <map>
#include <typeinfo>

//returnval: true means no error, or false
bool Program::checkStaticSemantic()
{
    return checkScope() == false ? false : checkStmt(); 
}

//mainly check things about undefine and redefine 
bool Program::checkScope()
{
    return gloScope->check();
}

//mainly check whether statement is legal 
bool Program::checkStmt()
{
    return checkUndefinedVariables(gloScope, gloScope);
}

/*
 * check scope 
*/
bool GloScope::check()
{
    //we will set the order of checking later and when to return false.
    if(checkClass() == false)
        return false;
    if(checkMain() == false)
        return false;
    if(checkAttributesAndMethods() == false)
        return false;
    return checkRedefinedLocalVariables();
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

LocScope* LocScope::nextSubLocScope()
{
    if(start >= entries.size())
        return NULL;
    for(int i = start; i < entries.size(); i++)
    {
        if(entries[i]->getSubLocScope() != NULL)
        {
            start = i + 1;
            return entries[i]->getSubLocScope();
        }
    }
    start = entries.size();
    return NULL;
}

bool LocScope::findId(std::string idName, YYLTYPE *plocation)
{
    
}

//class
bool GloScope::checkClass()
{
    return checkUndefinedClass() \
            && checkRedefinedClass();
}

bool GloScope::checkUndefinedClass()
{
    bool noErrors = true;
    for(auto gloScopeEntry : entries)
    {
        noErrors = ((GloScopeEntry*)gloScopeEntry) -> checkUndefinedClass(this) ? noErrors : false;
    }
    return noErrors;
}

bool GloScopeEntry::checkUndefinedClass(GloScope* gloScope)
{
    bool noErrors = true;
    if (claDes->getParentName() != "")
    {
        GloScopeEntry* parentGloScopeEntry = gloScope->findClass(claDes->getParentName());
        if(parentGloScopeEntry == NULL)
        {
            noErrors = false;
            IssueError::UndefinedClass(parentClassLocation, claDes->getParentName());
        }
        else
        {
            claDes->setParentClaDes(parentGloScopeEntry->getClaDes());
        }
    }
    noErrors = claDes->getClaScope()->checkUndefinedClass(gloScope) ? noErrors : false;
    return noErrors;
}

bool ClaScope::checkUndefinedClass(GloScope* gloScope)
{
    bool noErrors = true;
    for(auto claScopeEntry : entries)
    {
        noErrors = ((ClaScopeEntry*)claScopeEntry)->checkUndefinedClass(gloScope) ? noErrors : false;
    }
    return noErrors;
}

bool ClaScopeEntry::checkUndefinedClass(GloScope* gloScope)
{
    bool noErrors = true;
    std::string className = typeInfo->getClassName();
    if(className != "" && gloScope -> findClass(className) == NULL)
    {
        noErrors = false;
        IssueError::UndefinedClass(typeInfo->getLocation(), className);
    }
    if(category == DC::CATEGORY::DC_FUN)
    {
        noErrors = funDes->getForScope()->checkUndefinedClass(gloScope) ? noErrors : false;
    }
    return noErrors;    
}

bool ForScope::checkUndefinedClass(GloScope* gloScope)
{
    bool noErrors = true;
    for(auto forScopeEntry : entries)
        noErrors = ((ForScopeEntry*)forScopeEntry)->checkUndefinedClass(gloScope) ? noErrors : false;
    if(locScopeEntry != NULL)
        noErrors = locScopeEntry->checkUndefinedClass(gloScope) ? noErrors : false;  
    return noErrors;
}

bool ForScopeEntry::checkUndefinedClass(GloScope* gloScope)
{
    std::string className = typeInfo->getClassName();
    if(className != "" && gloScope -> findClass(className) == NULL)
    {
        IssueError::UndefinedClass(typeInfo->getLocation(), className);
        return false;
    }
    else
    {
        return true;
    }
}

bool LocScope::checkUndefinedClass(GloScope* gloScope)
{
    bool noErrors = true;
    for(auto locScopeEntry : entries)
        noErrors = ((LocScopeEntry*)locScopeEntry)->checkUndefinedClass(gloScope) ? noErrors : false;
    return noErrors;
}

bool LocScopeEntry::checkUndefinedClass(GloScope* gloScope)
{
    bool noErrors = true;
    if(name != "")
    {
        std::string className = typeInfo->getClassName();
        if(className != "" && gloScope -> findClass(className) == NULL)
        {
            IssueError::UndefinedClass(typeInfo->getLocation(), className);
            noErrors = false;
        }
    }
    if(subLocScope != NULL)
    {
        noErrors = subLocScope -> checkUndefinedClass(gloScope) ? noErrors : false;
    }
    return noErrors;
}

bool GloScope::checkRedefinedClass()
{
    bool noErrors = true;
    std::map<std::string, YYLTYPE*> doesClassExistMap;
    for(auto gloScopeEntry : entries)
    {
        std::string className = ((GloScopeEntry*)gloScopeEntry) -> getClassName();
        if(doesClassExistMap.find(className) == doesClassExistMap.end())
        {
            doesClassExistMap[className] = ((GloScopeEntry*)gloScopeEntry) -> getLocation();
        }
        else
        {
            noErrors = false;
            IssueError::RedefinedClass(((GloScopeEntry*)gloScopeEntry) -> getLocation(), ((GloScopeEntry*)gloScopeEntry) -> getClassName(), doesClassExistMap[className]);
        }
    }
    return noErrors;
}

//main
bool GloScope::checkMain()
{
    bool noErrors = true;
    bool isFindMain = false;
    YYLTYPE* firstDefinedLocation; 
    for(auto gloScopeEntry : entries)
    {
        ClaScope* claScope = ((GloScopeEntry*)gloScopeEntry)->getClaDes()->getClaScope();
        for(auto claScopeEntry : claScope->getEntries())
        {
            if(((ClaScopeEntry*)claScopeEntry)->getCategory() == DC::CATEGORY::DC_FUN \
                && ((ClaScopeEntry*)claScopeEntry)->getName() == DC::MAIN)
            {
                if (isFindMain == true)
                {
                    noErrors = false;
                    IssueError::RedefinedMain(((ClaScopeEntry*)claScopeEntry) -> getLocation(), firstDefinedLocation);      
                }
                else
                {
                    isFindMain = true;
                    firstDefinedLocation = ((ClaScopeEntry*)claScopeEntry) -> getLocation();
                    FunDes *funDes = ((ClaScopeEntry*)claScopeEntry) -> getFunDes();
                    if(funDes->getIsStatic() == false)
                    {
                        noErrors = false;
                        IssueError::MainIsNotStatic(((ClaScopeEntry*)claScopeEntry) -> getLocation());
                    }
                }
            }
        }
    }
    if(isFindMain == false)
    {
        noErrors = false;
        IssueError::UndefinedMain();
    }
    return noErrors;
}
//check attributes and methods in class scope about redefined and having the same name with others
bool GloScope::checkAttributesAndMethods()
{
    bool noErrors = true;
    std::map<std::string, YYLTYPE*> doesAttributeOrMethodExistMap; 
    std::map<std::string, int> attributeOrMethodCategory; 
    for(auto gloScopeEntry : entries)
    {
        doesAttributeOrMethodExistMap.clear();
        attributeOrMethodCategory.clear();
        ClaScope* claScope = ((GloScopeEntry*)gloScopeEntry)->getClaDes()->getClaScope();
        for(auto claScopeEntry : claScope->getEntries())
        {
            std::string name =  ((ClaScopeEntry*)claScopeEntry)->getName();
            if(doesAttributeOrMethodExistMap.find(name) == doesAttributeOrMethodExistMap.end())
            {
                doesAttributeOrMethodExistMap[name] = ((ClaScopeEntry*)claScopeEntry) -> getLocation();
                attributeOrMethodCategory[name] = ((ClaScopeEntry*)claScopeEntry) -> getCategory();
            }
            else
            {
                noErrors = false;
                if(((ClaScopeEntry*)claScopeEntry) -> getCategory() == attributeOrMethodCategory[name])
                {
                    IssueError::RedefinedVarOrMethod(((ClaScopeEntry*)claScopeEntry) -> getLocation(),\
                     name, doesAttributeOrMethodExistMap[name], attributeOrMethodCategory[name]);
                }
                else
                {
                    IssueError::AttributeAndMethodWithTheSameName(((ClaScopeEntry*)claScopeEntry)->getLocation(),\
                     name, doesAttributeOrMethodExistMap[name]);
                }
            }
        }
    }
    return noErrors;
}

bool GloScope::checkRedefinedLocalVariables()
{
    bool noErrors = true;
    for(auto gloScopeEntry : entries)
    {
        std::vector<Entry*> claScopeEntries = ((GloScopeEntry*)gloScopeEntry) \
            -> getClaDes() -> getClaScope() -> getEntries();
        for(auto claScopeEntry : claScopeEntries)
        {
            if(((ClaScopeEntry*)claScopeEntry) -> getCategory() == DC::CATEGORY::CATEGORY::DC_FUN)
            {
                LocScope *locScope = ((ClaScopeEntry*)claScopeEntry) -> getFunDes() \
                    -> getForScope() -> getLocScopeEntry() -> getSubLocScope();
                if(locScope != NULL)
                    noErrors = locScope -> checkRedefinedLocalVariables() ? noErrors : false;
            }
                
        }
    }
    return noErrors;
}

bool LocScope::checkRedefinedLocalVariables()
{
    bool noErrors = true;
    std::map<std::string, YYLTYPE*> doesVariablesExist; 
    for(auto locScopeEntry : entries)
    {
        LocScope* subLocScope = ((LocScopeEntry*)locScopeEntry) -> getSubLocScope();
        if(subLocScope != NULL)
            noErrors = subLocScope -> checkRedefinedLocalVariables() ? noErrors : false;
        else
        {
            std::string name = ((LocScopeEntry*)locScopeEntry) -> getName();
            if(doesVariablesExist.find(name) == doesVariablesExist.end())
                doesVariablesExist[name] = ((LocScopeEntry*)locScopeEntry) -> getLocation();
            else
            {
                noErrors = false;
                IssueError::RedefinedLocalVariable(((LocScopeEntry*)locScopeEntry) -> getLocation(), name, \
                    doesVariablesExist[name]);
            }
        }
    }
    return noErrors;
}

/*
 * check stmt 
*/

//check undefined variables, note: we see fun as variable
bool TreeNode::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    return true;
}

bool Program::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    std::vector<Entry *> gloScopeEntries = gloScope.getEntries();
    for(int i=0; i < pvecClassDecl.size(); i++)
    {
        noErrors = pvecClassDecl[i] -> checkUndefinedVariables(gloScope, \
        ((GloScopeEntry*)gloScopeEntries[i])->getClaDes()->getClaScope()) \
        ? noErrors : true;
    }
    return noErrors;
}

bool ClassDecl::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    std::vector<Entry*> claScopeEntries = ((ClaScope*)currentScope)->getEntries();
    for(int i=0; i<pfields.size(); i++)
    {
        FunDes *funDes = claScopeEntries[i]->getFunDes();
        if(funDes != NULL)
            noErrors = pfields[i]->checkUndefinedVariables(gloScope,funDes->getForScope())\
            ? noErrors : false;
    }
    return noErrors;
}

bool FunDecl::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    return pstmtblock -> checkUndefinedVariables(gloScope, \
    ((ForScope*)currentScope)->getLocScopeEntry()->getSubLocScope());
}

bool StmtBlock::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    for(auto stmt : pstmts)
    {
        if(typeid(*stmt).name() == typeid(StmtBlock).name())
        {
            LocScope *subLocScope = ((LocScope*)currentScope)->nextSubLocScope();
            if(subLocScope != NULL)
            {
                noErrors = stmt->checkUndefinedVariables(gloScope, subLocScope ? noErrors : false;
            }
            else
            {
                IssueError::InternalError(__FILE__, __LINE__);
                return false;
            }
        }
        else
        {
            noErrors = stmt->checkUndefinedVariables(gloScope, currentScope) ? noErrors : false;
        }
    }
    return noErrors;
}

bool IfStmt::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr -> checkUndefinedVariables(gloScope, currentScope);
    if(pstmt1 != NULL)
        if(typeid(*pstmt1).name() == typeid(StmtBlock).name())
            noErrors = pstmt1 -> checkUndefinedVariables(gloScope, ((LocScope*)currentScope)->nextSubLocScope()) ? noErrors : false;
        else
            noErrors = pstmt1 -> checkUndefinedVariables(gloScope, currentScope) ? noErrors : false;
    if(pstmt2 != NULL)
        if(typeid(*pstmt2).name() == typeid(StmtBlock).name())
            noErrors = pstmt2 -> checkUndefinedVariables(gloScope, ((LocScope*)currentScope)->nextSubLocScope()) ? noErrors : false;
        else
            noErrors = pstmt2 -> checkUndefinedVariables(gloScope, currentScope) ? noErrors : false;
    return noErrors;
}

bool WhileStmt::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr -> checkUndefinedVariables(gloScope, currentScope);
    if(pstmt != NULL)
        if(typeid(*pstmt).name() == typeid(StmtBlock).name())
            noErrors = pstmt -> checkUndefinedVariables(gloScope, ((LocScope*)currentScope)->nextSubLocScope()) ? noErrors : false;
        else
            noErrors = pstmt -> checkUndefinedVariables(gloScope, currentScope) ? noErrors : false;
    return noErrors;
}

bool ForStmt::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr -> checkUndefinedVariables(gloScope, currentScope);
    if(pstmt != NULL)
        if(typeid(*pstmt).name() == typeid(StmtBlock).name())
            noErrors = pstmt -> checkUndefinedVariables(gloScope, ((LocScope*)currentScope)->nextSubLocScope()) ? noErrors : false;
        else
            noErrors = pstmt -> checkUndefinedVariables(gloScope, currentScope) ? noErrors : false;
    return noErrors;
}

bool ReturnStmt::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    return poptexpr != NULL ? poptexpr -> checkUndefinedVariables(gloScope, currentScope) : true;
}

bool BreakStmt::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    return true;
}

bool PrintStmt::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    for(auto expr : pexprs)
    {
        noErrors = expr -> checkUndefinedVariables(gloScope, currentScope) ? noErrors : false;
    }
    return noErrors;
}

bool AssignExpr::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = plvalue -> checkUndefinedVariables(gloScope, currentScope);
    noErrors = pexpr -> checkUndefinedVariables(gloScope, currentScope) ? noErrors : false;
    return noErrors;
}

bool ArithmeticExpr::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr1 -> checkUndefinedVariables(gloScope, currentScope);
    noErrors = pexpr2 -> checkUndefinedVariables(gloScope, currentScope) ? noErrors : false;
    return noErrors;
}

bool RelationExpr::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr1 -> checkUndefinedVariables(gloScope, currentScope);
    noErrors = pexpr2 -> checkUndefinedVariables(gloScope, currentScope) ? noErrors : false;
    return noErrors;
}

bool LogicalExpr::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr1 -> checkUndefinedVariables(gloScope, currentScope);
    noErrors = pexpr2 -> checkUndefinedVariables(gloScope, currentScope) ? noErrors : false;
    return noErrors;
}

bool FieldAccess::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    if(pexpr != NULL)
        noErrors = pexpr -> checkUndefinedVariables(gloScope, currentScope);
    noErrors = id -> checkUndefinedVariables(gloScope, currentScope) ? noErrors : false;
    return noErrors;
}

bool Id::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    //find id in loccal scope first
    while(true)
    {
        

    }

    //if not found, find the id in class scope


}

bool ArrayAccess::checkUndefinedVariables(GloScope* gloScope, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr1 -> checkUndefinedVariables(gloScope, currentScope);
    noErrors = pexpr2 -> checkUndefinedVariables(gloScope, currentScope) ? noErrors : false;
    return noErrors;
}


















//check whether dot(.) is used right, 




