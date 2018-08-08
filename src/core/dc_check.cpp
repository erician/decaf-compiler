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
#include <queue>
#include <typeinfo>

bool noErrors = true;

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
    if(checkUndefinedVariables(gloScope, NULL, gloScope) == false)
        return false;
    if(checkBreak(false) == false)
        return false;
    resetStart(gloScope);
    return checkMismatchType(gloScope, NULL, gloScope);
}

/*reset all the attribute of start to 0 */
void Program::resetStart(GloScope *gloScope)
{
    bool noErrors = true;
    for(auto gloScopeEntry : gloScope->getEntries())
    {
        std::vector<Entry*> claScopeEntries = ((GloScopeEntry*)gloScopeEntry) \
            -> getClaDes() -> getClaScope() -> getEntries();
        for(auto claScopeEntry : claScopeEntries)
        {
            if(((ClaScopeEntry*)claScopeEntry) -> getCategory() == DC::CATEGORY::CATEGORY::DC_FUN)
            {
                LocScope *locScope = ((ClaScopeEntry*)claScopeEntry) -> getFunDes() \
                    -> getForScope() -> getLocScopeEntry() -> getSubLocScope();
                std::queue<LocScope*> locScopeQueue;
                locScopeQueue.push(locScope);
                LocScope *subLocScope;
                while(locScopeQueue.size() != 0)
                {
                    LocScope* locScope = locScopeQueue.front();
                    locScope->setStart(0);
                    locScopeQueue.pop();
                    for(auto locScopeEntry : locScope->getEntries())
                    {
                        if((subLocScope = ((LocScopeEntry*)locScopeEntry)->getSubLocScope()) != NULL)
                            locScopeQueue.push(subLocScope);
                    }
                }
            }
        }
    }
    return ;
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
        if(((LocScopeEntry*)entries[i])->getSubLocScope() != NULL)
        {
            start = i + 1;
            return ((LocScopeEntry*)entries[i])->getSubLocScope();
        }
    }
    start = entries.size();
    return NULL;
}

//findId
bool Scope::findId(std::string idName, YYLTYPE *plocation)
{
    return true;
}

//plocation is not used
bool ClaScope::findId(std::string idName, YYLTYPE *plocation)
{
    for(auto entry : entries)
    {
        if(((ClaScopeEntry*)entry) -> getName() == idName)
            return true;
    }
    return false;
}

bool ForScope::findId(std::string idName, YYLTYPE *plocation)
{
    for(auto entry : entries)
    {
        if(((ForScopeEntry*)entry) -> getName() == idName)
            return true;
    }
    return false;
}

bool LocScope::findId(std::string idName, YYLTYPE *plocation)
{
    for(auto entry : entries)
    {
        if(((LocScopeEntry*)entry) -> getName() == idName and \
            cmpYyltype(entry -> getLocation(), plocation) == 1)
            return true;
    }
    return false;
}

//get type
TypeInfo* Scope::getTypeInfo(std::string idName, YYLTYPE *plocation)
{
    return NULL;
}

//plocation is not used
TypeInfo* ClaScope::getTypeInfo(std::string idName, YYLTYPE *plocation)
{
    for(auto entry : entries)
    {
        if(((ClaScopeEntry*)entry) -> getName() == idName)
            return ((ClaScopeEntry*)entry) -> getTypeInfo();
    }
    return NULL;
}

TypeInfo* ForScope::getTypeInfo(std::string idName, YYLTYPE *plocation)
{
    for(auto entry : entries)
    {
        if(((ForScopeEntry*)entry) -> getName() == idName)
            return ((ForScopeEntry*)entry) -> getTypeInfo();
    }
    return NULL;
}

int LocScope::cmpYyltype(YYLTYPE *l1, YYLTYPE *l2)
{
    if(l1 -> first_line < l2 -> first_line)
        return 1;
    else if(l1 -> first_line > l2 -> first_line)
        return -1;
    else
        if(l1 -> first_column < l2 -> first_column)
            return 1;
    return -1;
}

TypeInfo* LocScope::getTypeInfo(std::string idName, YYLTYPE *plocation)
{
    for(auto entry : entries)
    {
        if(((LocScopeEntry*)entry) -> getName() == idName and \
            cmpYyltype(entry -> getLocation(), plocation) == 1)
            return ((LocScopeEntry*)entry) -> getTypeInfo();
    }
    return NULL;
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
bool TreeNode::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return true;
}

bool Id::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    //find id in loccal scope first
    while(true)
    {   
        if(currentScope -> findId(name, plocation) == true)
            return true;
        if((currentScope = currentScope -> getParentScope()) == NULL)
            break;
    }
    //if not found, find the id in class scope: this class first, then parent class
    if(claDes -> getClaScope() -> findId(name, plocation) == true)
        return true;
    if(claDes -> getParentClaDes() != NULL && \
        claDes -> getParentClaDes() -> getClaScope() -> findId(name, plocation))
        return true;
    IssueError::UndefinedVariables(plocation, name);
    return false;
}

bool Program::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    std::vector<Entry*> gloScopeEntries = gloScope -> getEntries();
    for(int i=0; i < pvecClassDecl -> size(); i++)
    {
        noErrors = (*pvecClassDecl)[i] -> checkUndefinedVariables( \
        gloScope,\
        ((GloScopeEntry*)gloScopeEntries[i])->getClaDes(), \
        ((GloScopeEntry*)gloScopeEntries[i])->getClaDes()->getClaScope()) \
        ? noErrors : false;
    }
    return noErrors;
}

bool ClassDecl::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    std::vector<Entry*> claScopeEntries = ((ClaScope*)currentScope)->getEntries();
    for(int i=0; i<pfields -> size(); i++)
    {
        FunDes *funDes = ((ClaScopeEntry*)claScopeEntries[i])->getFunDes();
        if(funDes != NULL)
            noErrors = (*pfields)[i]->checkUndefinedVariables(gloScope, claDes,funDes->getForScope())\
            ? noErrors : false;
    }
    return noErrors;
}

bool FunDecl::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return pstmtblock -> checkUndefinedVariables(gloScope, claDes, \
    ((ForScope*)currentScope)->getLocScopeEntry()->getSubLocScope());
}

bool StmtBlock::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pstmts == NULL)
        return true;
    bool noErrors = true;
    for(auto stmt : *pstmts)
    {
        if(stmt != NULL && typeid(*stmt).name() == typeid(StmtBlock).name())
        {
            LocScope *subLocScope = ((LocScope*)currentScope)->nextSubLocScope();
            if(subLocScope != NULL)
            {
                noErrors = stmt->checkUndefinedVariables(gloScope, claDes, subLocScope) ? noErrors : false;
            }
            else
            {
                IssueError::InternalError(__FILE__, __LINE__);
                return false;
            }
        }
        else if(stmt != NULL)
        {
            noErrors = stmt->checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
        }
    }
    return noErrors;
}

bool IfStmt::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr -> checkUndefinedVariables(gloScope, claDes, currentScope);
    currentScope = ((LocScope*)currentScope)->nextSubLocScope();
    if(pstmt1 != NULL)
        if(typeid(*pstmt1).name() == typeid(StmtBlock).name())
            noErrors = pstmt1 -> checkUndefinedVariables(gloScope, claDes, ((LocScope*)currentScope)->nextSubLocScope()) ? noErrors : false;
        else
            noErrors = pstmt1 -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
    if(pstmt2 != NULL)
        if(typeid(*pstmt2).name() == typeid(StmtBlock).name())
            noErrors = pstmt2 -> checkUndefinedVariables(gloScope, claDes, ((LocScope*)currentScope)->nextSubLocScope()) ? noErrors : false;
        else
            noErrors = pstmt2 -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
    return noErrors;
}

bool WhileStmt::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr -> checkUndefinedVariables(gloScope, claDes, currentScope);
    if(pstmt != NULL)
        if(typeid(*pstmt).name() == typeid(StmtBlock).name())
            noErrors = pstmt -> checkUndefinedVariables(gloScope, claDes, ((LocScope*)currentScope)->nextSubLocScope()) ? noErrors : false;
        else
            noErrors = pstmt -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
    return noErrors;
}

bool ForStmt::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr -> checkUndefinedVariables(gloScope, claDes, currentScope);
    if(poptexpr1 != NULL)
        noErrors = poptexpr1 -> checkUndefinedVariables(gloScope, claDes, currentScope)?noErrors:false;
    if(poptexpr2 != NULL)
        noErrors = poptexpr2 -> checkUndefinedVariables(gloScope, claDes, currentScope)?noErrors:false;
    if(pstmt != NULL)
        if(typeid(*pstmt).name() == typeid(StmtBlock).name())
            noErrors = pstmt -> checkUndefinedVariables(gloScope, claDes, ((LocScope*)currentScope)->nextSubLocScope()) ? noErrors : false;
        else
            noErrors = pstmt -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
    return noErrors;
}

bool ReturnStmt::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return poptexpr != NULL ? poptexpr -> checkUndefinedVariables(gloScope, claDes, currentScope) : true;
}

bool BreakStmt::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return true;
}

bool PrintStmt::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    for(auto expr : *pexprs)
    {
        noErrors = expr -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
    }
    return noErrors;
}

bool AssignExpr::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = plvalue -> checkUndefinedVariables(gloScope, claDes, currentScope);
    noErrors = pexpr -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
    return noErrors;
}

bool ArithmeticExpr::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr1 -> checkUndefinedVariables(gloScope, claDes, currentScope);
    noErrors = pexpr2 -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
    return noErrors;
}

bool RelationExpr::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr1 -> checkUndefinedVariables(gloScope, claDes, currentScope);
    noErrors = pexpr2 -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
    return noErrors;
}

bool LogicalExpr::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr1 -> checkUndefinedVariables(gloScope, claDes, currentScope);
    noErrors = pexpr2 -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
    return noErrors;
}

bool FieldAccess::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pexpr == NULL)
        return pid -> checkUndefinedVariables(gloScope, claDes, currentScope);
    else
    {
        if(pexpr -> checkUndefinedVariables(gloScope, claDes, currentScope) == false)
            return false;
        TypeInfo* typeInfo = pexpr -> getTypeInfo(gloScope, claDes, currentScope);
        if(typeInfo == NULL)
            return false;
        else
        {
            if(typeInfo -> getClassName() == "")
            {
                IssueError::UnCorrectlyDotUsed(typeInfo -> getLocation(), typeInfo -> getName());
                return false;
            }
            else
            {
                ClaDes* claDes = gloScope -> findClass(typeInfo -> getClassName()) -> getClaDes();
                if(((typeInfo = claDes -> getClaScope() -> getTypeInfo(pid -> getidname(), pid -> getLocation()))!=NULL) \
                ||  (claDes -> getParentClaDes() != NULL \
                    && (typeInfo=claDes->getParentClaDes()->getClaScope()->getTypeInfo(pid->getidname(), pid->getLocation()))!=NULL))
                    return true;
                else
                    IssueError::ClassDoesNotHaveTheAttriOrMethod(typeInfo -> getClassName(), pid -> getLocation(), pid -> getidname());
            }
        }
    }   
    return false;
}

bool ArrayAccess::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr1 -> checkUndefinedVariables(gloScope, claDes, currentScope);
    noErrors = pexpr2 -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
    return noErrors;
}

bool Call::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    if(pactuals != NULL)
    {
        for(auto expr : *pactuals)
        {
            noErrors = expr -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
        }
    }

    if(pexpr == NULL)
        return pid -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
    else
    {
        if(pexpr -> checkUndefinedVariables(gloScope, claDes, currentScope) == false)
            return false;
        TypeInfo* typeInfo = pexpr -> getTypeInfo(gloScope, claDes, currentScope);
        if(typeInfo == NULL)
            return false;
        else
        {
            if(typeInfo -> getClassName() == "")
            {
                IssueError::UnCorrectlyDotUsed(typeInfo->getLocation(), typeInfo->getName());
                return false;
            }
            else
            {
                ClaDes* claDes = gloScope -> findClass(typeInfo -> getClassName()) -> getClaDes();
                if(((claDes -> getClaScope() -> getTypeInfo(pid -> getidname(), pid -> getLocation()))!=NULL) \
                ||  (claDes -> getParentClaDes() != NULL \
                    && (claDes->getParentClaDes()->getClaScope()->getTypeInfo(pid->getidname(), pid->getLocation()))!=NULL))
                    ;
                else
                {
                    IssueError::ClassDoesNotHaveTheAttriOrMethod(typeInfo -> getClassName(), pid -> getLocation(), pid -> getidname());
                    noErrors = false;
                }
            }
        }
    }   
    return noErrors;
}

bool Instanceof::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    if(pexpr != NULL)
        noErrors = pexpr -> checkUndefinedVariables(gloScope, claDes, currentScope);
    if(pid != NULL)
        noErrors = pid -> checkUndefinedVariables(gloScope, claDes, currentScope) ? noErrors : false;
    return noErrors;
}

bool NewExpr::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(gloScope -> findClass(pid -> getidname()) == NULL)
    {
        IssueError::UndefinedClass(pid -> getplocation(), pid -> getidname());
        return false;
    }
    return true;
}

bool NewArrayExpr::checkUndefinedVariables(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pexpr != NULL)
        return pexpr -> checkUndefinedVariables(gloScope, claDes, currentScope);
    return true;
}

//check break
bool TreeNode::checkBreak(bool isWhileOrForBlock)
{
    return true;
}

bool Program::checkBreak(bool isWhileOrForBlock)
{
    bool noErrors = true;
    for(auto classDecl : *pvecClassDecl)
    {
        noErrors = classDecl -> checkBreak(isWhileOrForBlock)?noErrors:false;
    }
    return noErrors;
}

bool ClassDecl::checkBreak(bool isWhileOrForBlock)
{
    bool noErrors = true;
    for(auto field : *pfields)
    {
        if(typeid(*field).name() == typeid(FunDecl).name())
            noErrors = field -> checkBreak(isWhileOrForBlock)?noErrors:false;
    }
    return noErrors;
}

bool FunDecl::checkBreak(bool isWhileOrForBlock)
{
    return pstmtblock -> checkBreak(isWhileOrForBlock);
}

bool StmtBlock::checkBreak(bool isWhileOrForBlock)
{
    if(pstmts == NULL)
        return true;
    bool noErrors = true;
    for(auto stmt : *pstmts)
    {
        if(stmt != NULL)
            noErrors = stmt -> checkBreak(isWhileOrForBlock)?noErrors:false;
    }
    return noErrors;
}

bool IfStmt::checkBreak(bool isWhileOrForBlock)
{
    bool noErrors = true;
    if(pstmt1 != NULL)
        noErrors = pstmt1 -> checkBreak(isWhileOrForBlock);
    if(pstmt2 != NULL)
        noErrors = pstmt2 -> checkBreak(isWhileOrForBlock)?noErrors:false;
    return noErrors; 
}

bool WhileStmt::checkBreak(bool isWhileOrForBlock)
{
    return pstmt -> checkBreak(true);
}

bool ForStmt::checkBreak(bool isWhileOrForBlock)
{
    return pstmt -> checkBreak(true);
}

bool BreakStmt::checkBreak(bool isWhileOrForBlock)
{
    if(isWhileOrForBlock == true)
        return true;
    IssueError::UnCorrectlyBreakUsed(getLocation());
    return false;
}

// mismatch type
bool TreeNode::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return true;
}

bool TreeNode::cmpTypeInfo(TypeInfo* typeInfo1, TypeInfo* typeInfo2)
{
    if(typeInfo1->getType() != typeInfo2 -> getType())
        return false;
    switch(typeInfo1 -> getType())
    {
        case DC::TYPE::TYPE::DC_NAMED:
            if(typeInfo1 -> getClassName() != typeInfo2 -> getClassName())
                return false;
            break;
        case DC::TYPE::TYPE::DC_ARRAY:
            if(typeInfo1 -> getArrayType() != typeInfo2 -> getArrayType() \
            || typeInfo1 -> getArrayLevel() != typeInfo2 -> getArrayLevel())
                return false;
            break;
        default:
            break;
    }
    return true;
}

bool TreeNode::checkExprType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope, Expr* pexpr, TypeInfo* properTypeInfo)
{
    TypeInfo *typeInfo = pexpr -> getTypeInfo(gloScope, claDes, currentScope);
    if(cmpTypeInfo(typeInfo, properTypeInfo) == false)
    {
        IssueError::MismatchType(typeInfo->getTypeName(), typeInfo->getLocation(), \
        properTypeInfo->getTypeName(), properTypeInfo->getLocation());
        return false;
    }
    return true;
}

bool Program::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    std::vector<Entry*> gloScopeEntries = gloScope -> getEntries();
    for(int i=0; i < pvecClassDecl -> size(); i++)
    {
        noErrors = (*pvecClassDecl)[i] -> checkMismatchType( \
        gloScope,\
        ((GloScopeEntry*)gloScopeEntries[i])->getClaDes(), \
        ((GloScopeEntry*)gloScopeEntries[i])->getClaDes()->getClaScope()) \
        ? noErrors : false;
    }
    return noErrors;
}

bool ClassDecl::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    std::vector<Entry*> claScopeEntries = ((ClaScope*)currentScope)->getEntries();
    for(int i=0; i<pfields -> size(); i++)
    {
        FunDes *funDes = ((ClaScopeEntry*)claScopeEntries[i])->getFunDes();
        if(funDes != NULL)
            noErrors = (*pfields)[i]->checkMismatchType(gloScope, claDes,funDes->getForScope())\
            ? noErrors : false;
    }
    return noErrors;
}

bool FunDecl::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return pstmtblock -> checkMismatchType(gloScope, claDes, \
    ((ForScope*)currentScope)->getLocScopeEntry()->getSubLocScope());
}

bool StmtBlock::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pstmts == NULL)
        return true;
    bool noErrors = true;
    for(auto stmt : *pstmts)
    {
        if(stmt != NULL && typeid(*stmt).name() == typeid(StmtBlock).name())
        {
            LocScope *subLocScope = ((LocScope*)currentScope)->nextSubLocScope();
            if(subLocScope != NULL)
            {
                noErrors = stmt->checkMismatchType(gloScope, claDes, subLocScope) ? noErrors : false;
            }
            else
            {
                IssueError::InternalError(__FILE__, __LINE__);
                return false;
            }
        }
        else if(stmt != NULL)
        {
            noErrors = stmt->checkMismatchType(gloScope, claDes, currentScope) ? noErrors : false;
        }
    }
    return noErrors;
}

bool IfStmt::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    //typeInfo will never be NULL, because we have already checked the undefined variables 
    noErrors = pexpr->checkMismatchType(gloScope, claDes, currentScope);
    noErrors = checkExprType(gloScope, claDes, currentScope, pexpr, \
               (new TypeInfo()) -> withType(DC::TYPE::TYPE::DC_BOOL)) ? noErrors : false;
    currentScope = ((LocScope*)currentScope)->nextSubLocScope();
    if(pstmt1 != NULL)
        if(typeid(*pstmt1).name() == typeid(StmtBlock).name())
            noErrors = pstmt1 -> checkMismatchType(gloScope, claDes, ((LocScope*)currentScope)->nextSubLocScope()) ? noErrors : false;
        else
            noErrors = pstmt1 -> checkMismatchType(gloScope, claDes, currentScope) ? noErrors : false;
    if(pstmt2 != NULL)
        if(typeid(*pstmt2).name() == typeid(StmtBlock).name())
            noErrors = pstmt2 -> checkMismatchType(gloScope, claDes, ((LocScope*)currentScope)->nextSubLocScope()) ? noErrors : false;
        else
            noErrors = pstmt2 -> checkMismatchType(gloScope, claDes, currentScope) ? noErrors : false;
    return noErrors;
}

bool WhileStmt::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr->checkMismatchType(gloScope, claDes, currentScope);
    noErrors = checkExprType(gloScope, claDes, currentScope, pexpr, \
               (new TypeInfo()) -> withType(DC::TYPE::TYPE::DC_BOOL)) ? noErrors : false;
    if(pstmt != NULL)
        if(typeid(*pstmt).name() == typeid(StmtBlock).name())
            noErrors = pstmt -> checkMismatchType(gloScope, claDes, ((LocScope*)currentScope)->nextSubLocScope()) ? noErrors : false;
        else
            noErrors = pstmt -> checkMismatchType(gloScope, claDes, currentScope) ? noErrors : false;
    return noErrors;
}

bool ForStmt::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    noErrors = pexpr->checkMismatchType(gloScope, claDes, currentScope);
    noErrors = checkExprType(gloScope, claDes, currentScope, pexpr, \
               (new TypeInfo()) -> withType(DC::TYPE::TYPE::DC_BOOL)) ? noErrors : false;
    if(poptexpr1 != NULL)
        noErrors = poptexpr1 -> checkMismatchType(gloScope, claDes, currentScope)?noErrors:false;
    if(poptexpr2 != NULL)
        noErrors = poptexpr2 -> checkMismatchType(gloScope, claDes, currentScope)?noErrors:false;
    if(pstmt != NULL)
        if(typeid(*pstmt).name() == typeid(StmtBlock).name())
            noErrors = pstmt -> checkMismatchType(gloScope, claDes, ((LocScope*)currentScope)->nextSubLocScope()) ? noErrors : false;
        else
            noErrors = pstmt -> checkMismatchType(gloScope, claDes, currentScope) ? noErrors : false;
    return noErrors;
}

bool ReturnStmt::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    Scope* forScope = currentScope;
    do
    {
        forScope = forScope -> getParentScope();
    }while(forScope -> getParentScope() != NULL);
    TypeInfo* properTypeInfo = NULL;
    for(auto entry : claDes -> getClaScope() -> getEntries())
    {
        if(((ClaScopeEntry*)entry) -> getCategory() == DC::CATEGORY::CATEGORY::DC_FUN)
        {
            if(((ClaScopeEntry*)entry) -> getFunDes() -> getForScope() == forScope)
            {
                properTypeInfo = ((ClaScopeEntry*)entry) -> getTypeInfo();
                break;
            }
        }
    }
    if(poptexpr == NULL)
    {
        TypeInfo* typeInfo = (new TypeInfo()) -> withType(DC::TYPE::TYPE::DC_VOID);
        typeInfo -> setLocation(getLocation());
        if(cmpTypeInfo(typeInfo, properTypeInfo) == false)
        {
            IssueError::MismatchReturnType(typeInfo->getTypeName(), typeInfo->getLocation(), \
                                           properTypeInfo->getTypeName(), properTypeInfo->getLocation());
            return false;
        }
    }
    else
    {
        if(poptexpr -> checkMismatchType(gloScope, claDes, currentScope) == false)
            return false;
        TypeInfo* typeInfo = poptexpr ->getTypeInfo(gloScope, claDes, currentScope); 
        if(cmpTypeInfo(typeInfo, properTypeInfo) == false)
        {
            IssueError::MismatchReturnType(typeInfo->getTypeName(), typeInfo->getLocation(), \
                                           properTypeInfo->getTypeName(), properTypeInfo->getLocation());
            return false;
        }
    }
    return true;
}

bool PrintStmt::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    bool noErrors = true;
    for(auto expr : *pexprs)
    {
        noErrors = expr -> checkMismatchType(gloScope, claDes, currentScope) ? noErrors : false;
    }
    return noErrors;
}

bool AssignExpr::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(plvalue -> checkMismatchType(gloScope, claDes, currentScope) == false \
    ||  pexpr -> checkMismatchType(gloScope, claDes, currentScope) == false)
        return false;
    return checkExprType(gloScope, claDes, currentScope, pexpr, \
                             plvalue -> getTypeInfo(gloScope, claDes, currentScope));
}

bool ArithmeticExpr::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pexpr1 -> checkMismatchType(gloScope, claDes, currentScope) == false \
    ||  pexpr2 -> checkMismatchType(gloScope, claDes, currentScope) == false)
        return false;
    return checkExprType(gloScope, claDes, currentScope, pexpr1, (new TypeInfo())->withType(DC::TYPE::TYPE::DC_INT)) \
    ? checkExprType(gloScope, claDes, currentScope, pexpr2, (new TypeInfo())->withType(DC::TYPE::TYPE::DC_INT)) : false;
}

bool RelationExpr::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pexpr1 -> checkMismatchType(gloScope, claDes, currentScope) == false \
    ||  pexpr2 -> checkMismatchType(gloScope, claDes, currentScope) == false)
        return false;
    return checkExprType(gloScope, claDes, currentScope, pexpr1, (new TypeInfo())->withType(DC::TYPE::TYPE::DC_INT)) \
    ? checkExprType(gloScope, claDes, currentScope, pexpr2, (new TypeInfo())->withType(DC::TYPE::TYPE::DC_INT)) : false;
}

bool LogicalExpr::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pexpr1 -> checkMismatchType(gloScope, claDes, currentScope) == false \
    ||  pexpr2 -> checkMismatchType(gloScope, claDes, currentScope) == false)
        return false;
    return checkExprType(gloScope, claDes, currentScope, pexpr1, (new TypeInfo())->withType(DC::TYPE::TYPE::DC_BOOL)) \
    ? checkExprType(gloScope, claDes, currentScope, pexpr2, (new TypeInfo())->withType(DC::TYPE::TYPE::DC_BOOL)) : false;
}

bool Call::checkActualsAndFormalsMatch(GloScope* gloScope, ClaDes* claDes, Scope* currentScope, std::vector<Entry*> formals)
{
    int actualsShoudAddValue = 1;
    if((pactuals == NULL && formals.size()-actualsShoudAddValue!=0) \
    ||  (pactuals!=NULL && pactuals->size() != formals.size() - actualsShoudAddValue))
    {
        noErrors = false;
        IssueError::ActualsAndFormalsNumMismatch(formals.size()-actualsShoudAddValue, pactuals==NULL?0:pactuals->size(), pid->getLocation());
        return false;
    }
    if(pactuals != NULL && pactuals->size() != 0)
    {
        for(int i=0; i<pactuals->size(); i++)
        {
            if(cmpTypeInfo(((ForScopeEntry*)formals[i+actualsShoudAddValue])->getTypeInfo(), (*pactuals)[i]->getTypeInfo(gloScope, claDes, currentScope)) == false)
            {
                noErrors = false;
                IssueError::ActualsAndFormalsTypeMismatch((*pactuals)[i]->getTypeInfo(gloScope, claDes, currentScope)->getTypeName(), \
                                                          (*pactuals)[i]->getTypeInfo(gloScope, claDes, currentScope)->getLocation(), \
                                                          ((ForScopeEntry*)formals[i+actualsShoudAddValue])->getTypeInfo()->getTypeName(),\
                                                          ((ForScopeEntry*)formals[i+actualsShoudAddValue])->getTypeInfo()->getLocation());
            }
        }
    }
    return noErrors;
}

bool Call::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    ClaDes* objectClaDes = NULL;
    TypeInfo* typeInfo = NULL;
    if(pexpr == NULL)
        objectClaDes = claDes;
    else
    {
        if(pexpr -> checkMismatchType(gloScope, claDes, currentScope) == false)
            return false;
        typeInfo = pexpr -> getTypeInfo(gloScope, claDes, currentScope);
        if(typeInfo -> getClassName() == "")
        {
            IssueError::UnCorrectlyDotUsed(typeInfo->getLocation(), typeInfo->getName());
            return false;
        }
        objectClaDes = gloScope -> findClass(typeInfo -> getClassName()) -> getClaDes();
    }
    ClaScope* claScope = objectClaDes -> getClaScope() -> getTypeInfo(pid -> getidname(), pid -> getLocation())!=NULL \
                            ? objectClaDes -> getClaScope() : objectClaDes->getParentClaDes()->getClaScope();
    for(auto entry : claScope -> getEntries())
    {
        if(((ClaScopeEntry*)entry) -> getName() == pid -> getidname())
        {
            return checkActualsAndFormalsMatch(gloScope, claDes, currentScope, \
                    ((ClaScopeEntry*)entry)->getFunDes()->getForScope()->getEntries());
        }
    }
    return false;
}

bool FieldAccess::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pexpr == NULL)
        return pid -> getTypeInfo(gloScope, claDes, currentScope);
    else
    {
        if(pexpr -> checkMismatchType(gloScope, claDes, currentScope) == false)
            return false;
        TypeInfo* typeInfo = pexpr -> getTypeInfo(gloScope, claDes, currentScope);
        if(typeInfo == NULL)
            return false;
        else
        {
            if(typeInfo -> getClassName() == "")
            {
                IssueError::UnCorrectlyDotUsed(typeInfo->getLocation(), typeInfo->getName());
                return false;
            }
        }
    }
    return true;
}

bool ArrayAccess::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pexpr1 -> checkMismatchType(gloScope, claDes, currentScope) == false \
    || pexpr2 -> checkMismatchType(gloScope, claDes, currentScope) == false)
        return false;
    TypeInfo* typeInfo = NULL;
    if((typeInfo = pexpr2 -> getTypeInfo(gloScope, claDes, currentScope)) -> getType() != DC::TYPE::TYPE::DC_INT)
    {
        IssueError::ArrayAccessMismatchType(typeInfo->getTypeName(), typeInfo->getLocation(), "int", NULL);
        return false;
    }
    if((typeInfo = pexpr1 -> getTypeInfo(gloScope, claDes, currentScope))->getType() != DC::TYPE::TYPE::DC_ARRAY)
    {
        IssueError::UnCorrectlyBracketsUsed(typeInfo->getName(), typeInfo->getLocation());
        return false;
    }
    return true;
}

bool NewArrayExpr::checkMismatchType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pexpr -> checkMismatchType(gloScope, claDes, currentScope) == false)
        return false;
    TypeInfo* typeInfo = NULL;
    if((typeInfo = pexpr -> getTypeInfo(gloScope, claDes, currentScope)) -> getType() != DC::TYPE::TYPE::DC_INT)
    {
        IssueError::MismatchType(typeInfo -> getTypeName(), typeInfo -> getLocation(), \
                                "int", NULL);
        return false;
    }
    return true;
}

//expr get type
TypeInfo* TreeNode::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return new TypeInfo();
}

TypeInfo* Id::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = NULL;
    //find id in loccal scope first
    while(true)
    {   
        if((typeInfo = currentScope -> getTypeInfo(name, plocation)) != NULL)
            break;
        if((currentScope = currentScope -> getParentScope()) == NULL)
            break;
    }
    //if not found, find the id in class scope: self class first, then parent class
    if((typeInfo != NULL) \
    || ((typeInfo = claDes -> getClaScope() -> getTypeInfo(name, plocation)) != NULL) \
    || (claDes -> getParentClaDes() != NULL \
        && (typeInfo=claDes->getParentClaDes()->getClaScope()->getTypeInfo(name, plocation)) != NULL))
    {
        typeInfo -> setLocation(plocation);
        typeInfo -> setName(name);
        return typeInfo;
    }
    IssueError::InternalError(__FILE__, __LINE__);
    return new TypeInfo();
}

TypeInfo* AssignExpr::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return plvalue -> getTypeInfo(gloScope, claDes, currentScope);
}

TypeInfo* ArithmeticExpr::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return pexpr1 -> getTypeInfo(gloScope, claDes, currentScope);
}

TypeInfo* RelationExpr::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo* typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_BOOL);
    typeInfo -> setLocation(pexpr1 -> getLocation());
    typeInfo -> setName("anonymous variable");
    return typeInfo;
}

//never return NULL, even something wrong
TypeInfo* LogicalExpr::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo* typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_BOOL);
    typeInfo -> setLocation(pexpr1 -> getLocation());
    typeInfo -> setName("anonymous variable");
    return typeInfo;
}

TypeInfo* FieldAccess::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pexpr == NULL)
        return pid -> getTypeInfo(gloScope, claDes, currentScope);
    else
    {
        TypeInfo* typeInfo = pexpr -> getTypeInfo(gloScope, claDes, currentScope);
        ClaDes* objectClaDes = gloScope -> findClass(typeInfo -> getClassName()) -> getClaDes();
        if(((typeInfo = objectClaDes -> getClaScope() -> getTypeInfo(pid -> getidname(), pid -> getLocation()))!=NULL) \
        ||  (objectClaDes -> getParentClaDes() != NULL \
            && (typeInfo=objectClaDes->getParentClaDes()->getClaScope()->getTypeInfo(pid->getidname(), pid->getLocation()))!=NULL))
        {
            typeInfo -> setLocation(pexpr->getLocation());
            return typeInfo;
        }
    }
    IssueError::InternalError(__FILE__, __LINE__);
    return new TypeInfo();
}

TypeInfo* ArrayAccess::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo* typeInfo = new TypeInfo(pexpr1 -> getTypeInfo(gloScope, claDes, currentScope));
    if(typeInfo -> getArrayLevel() == 1)
    {
        typeInfo -> setType(typeInfo->getArrayType());
    }
    return typeInfo;
}

TypeInfo* Call::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pexpr == NULL)
        return pid -> getTypeInfo(gloScope, claDes, currentScope);
    else
    {
        TypeInfo *typeInfo = pexpr -> getTypeInfo(gloScope, claDes, currentScope);
        ClaDes* objectClaDes = gloScope -> findClass(typeInfo -> getClassName()) -> getClaDes();
        if(((typeInfo = objectClaDes -> getClaScope() -> getTypeInfo(pid -> getidname(), pid -> getLocation()))!=NULL) \
        ||  (objectClaDes -> getParentClaDes() != NULL \
            && (typeInfo=objectClaDes->getParentClaDes()->getClaScope()->getTypeInfo(pid->getidname(), pid->getLocation()))!=NULL))
        {
                
            typeInfo->setLocation(pexpr->getLocation());
            return typeInfo;
        }
    }
    IssueError::InternalError(__FILE__, __LINE__);
    return new TypeInfo();
}

TypeInfo* This::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_NAMED);
    for(auto entry : gloScope -> getEntries())
    {
        if(((GloScopeEntry*)entry) -> getClaDes() == claDes)
        {
            typeInfo -> setClassName(((GloScopeEntry*)entry) -> getClassName());
            break;
        }
    }
    typeInfo -> setName("this");
    typeInfo -> setLocation(getLocation());
    return typeInfo;
}

TypeInfo* ReadInteger::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_INT);
    typeInfo -> setName("ReadInteger");
    typeInfo -> setLocation(getLocation());
    return typeInfo;
}

TypeInfo* ReadLine::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_INT);
    typeInfo -> setName("ReadLine");
    typeInfo -> setLocation(getLocation());
    return typeInfo;
}

TypeInfo* Instanceof::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_BOOL);
    typeInfo -> setLocation(getLocation());
    return typeInfo;
}

TypeInfo* NewExpr::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo->setType(DC::TYPE::TYPE::DC_NAMED);
    typeInfo->setClassName(pid -> getidname());
    typeInfo->setLocation(getLocation());
    return typeInfo;
}

TypeInfo* NewArrayExpr::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = getTypeInfoFromType(ptype);
    if(typeInfo -> getType() != DC::TYPE::TYPE::DC_ARRAY){
        typeInfo -> setArrayLevel(1);
        typeInfo -> setArrayType(typeInfo -> getType());
    }
    typeInfo -> setType(DC::TYPE::TYPE::DC_ARRAY);
    typeInfo -> setName("newarray");
    typeInfo -> setLocation(getLocation());
    return typeInfo;
}

TypeInfo* IntCon::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_INT);
    typeInfo -> setName(std::to_string(value));
    typeInfo -> setLocation(getLocation());
    return typeInfo;
}

TypeInfo* BoolCon::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_BOOL);
    typeInfo -> setName(value == 1 ? "true" : "false");
    typeInfo -> setLocation(getLocation());
    return typeInfo;
}

TypeInfo* StringCon::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_STRING);
    typeInfo -> setName(value);
    typeInfo -> setLocation(getLocation());
    return typeInfo;
}

TypeInfo* NullCon::getTypeInfo(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_INT);
    typeInfo -> setName("null");
    typeInfo -> setLocation(getLocation());
    return typeInfo;
}
// get location
YYLTYPE* TreeNode::getLocation()
{
    return NULL;
}

YYLTYPE* ReturnStmt::getLocation()
{
    return plocation;
}

YYLTYPE* BreakStmt::getLocation()
{
    return plocation;
}

YYLTYPE* Id::getLocation()
{
    return plocation;
}

YYLTYPE* AssignExpr::getLocation()
{
    return plvalue -> getLocation();
}

YYLTYPE* ArithmeticExpr::getLocation()
{
    return pexpr1 -> getLocation();
}

YYLTYPE* RelationExpr::getLocation()
{
    return pexpr1 -> getLocation();
}

YYLTYPE* LogicalExpr::getLocation()
{
    return pexpr1 -> getLocation();
}

YYLTYPE* FieldAccess::getLocation()
{
    return pexpr!=NULL?pexpr->getLocation():pid->getLocation();
}

YYLTYPE* ArrayAccess::getLocation()
{
    return pexpr1 -> getLocation();
}

YYLTYPE* Call::getLocation()
{
    return pexpr!=NULL?pexpr->getLocation():pid->getLocation();
}

YYLTYPE* This::getLocation()
{
    return plocation;
}

YYLTYPE* ReadInteger::getLocation()
{
    return plocation;
}

YYLTYPE* ReadLine::getLocation()
{
    return plocation;
}

YYLTYPE* Instanceof::getLocation()
{
    return pexpr -> getLocation();
}

YYLTYPE* NewExpr::getLocation()
{
    return pid -> getLocation();
}

YYLTYPE* NewArrayExpr::getLocation()
{
    return plocation;
}

YYLTYPE* IntCon::getLocation()
{
    return plocation;
}

YYLTYPE* BoolCon::getLocation()
{
    return plocation;
}

YYLTYPE* StringCon::getLocation()
{
    return plocation;
}

YYLTYPE* NullCon::getLocation()
{
    return plocation;
}


