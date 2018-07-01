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
    if(checkUndefinedVariables(gloScope, NULL, gloScope) == false)
        return false;
    return checkBreak(false);
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
TypeInfo* Scope::getType(std::string idName, YYLTYPE *plocation)
{
    return NULL;
}

//plocation is not used
TypeInfo* ClaScope::getType(std::string idName, YYLTYPE *plocation)
{
    for(auto entry : entries)
    {
        if(((ClaScopeEntry*)entry) -> getName() == idName)
            return ((ClaScopeEntry*)entry) -> getTypeInfo();
    }
    return NULL;
}

TypeInfo* ForScope::getType(std::string idName, YYLTYPE *plocation)
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

TypeInfo* LocScope::getType(std::string idName, YYLTYPE *plocation)
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
        ? noErrors : true;
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
    bool noErrors = true;
    for(auto stmt : *pstmts)
    {
        if(typeid(*stmt).name() == typeid(StmtBlock).name())
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
        else
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
        TypeInfo* typeInfo = pexpr -> getType(gloScope, claDes, currentScope);
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
                if(((typeInfo = claDes -> getClaScope() -> getType(pid -> getidname(), pid -> getLocation()))!=NULL) \
                ||  (claDes -> getParentClaDes() != NULL \
                    && (typeInfo=claDes->getParentClaDes()->getClaScope()->getType(pid->getidname(), pid->getLocation()))!=NULL))
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
        TypeInfo* typeInfo = pexpr -> getType(gloScope, claDes, currentScope);
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
                if(((claDes -> getClaScope() -> getType(pid -> getidname(), pid -> getLocation()))!=NULL) \
                ||  (claDes -> getParentClaDes() != NULL \
                    && (claDes->getParentClaDes()->getClaScope()->getType(pid->getidname(), pid->getLocation()))!=NULL))
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
    bool noErrors = true;
    for(auto stmt : *pstmts)
    {
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
    IssueError::UnCorrectlyBreakUsed(plocation);
    return false;
}











//expr get type
TypeInfo* TreeNode::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return NULL;
}

TypeInfo* Id::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = NULL;
    //find id in loccal scope first
    while(true)
    {   
        if((typeInfo = currentScope -> getType(name, plocation)) != NULL)
            break;
        if((currentScope = currentScope -> getParentScope()) == NULL)
            break;
    }
    //if not found, find the id in class scope: this class first, then parent class
    
    if((typeInfo != NULL) \
    || ((typeInfo = claDes -> getClaScope() -> getType(name, plocation)) != NULL) \
    || (claDes -> getParentClaDes() != NULL \
        && (typeInfo=claDes->getParentClaDes()->getClaScope()->getType(name, plocation)) != NULL))
    {
        typeInfo -> setLocation(plocation);
        typeInfo -> setName(name);
        return typeInfo;
    }
    IssueError::UndefinedVariables(plocation, name);
    return NULL;
}

TypeInfo* AssignExpr::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return plvalue -> getType(gloScope, claDes, currentScope);
}

TypeInfo* ArithmeticExpr::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return pexpr1 -> getType(gloScope, claDes, currentScope);
}

TypeInfo* RelationExpr::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_BOOL);
    typeInfo -> setLocation(pexpr1 -> getLocation());
    typeInfo -> setName("anonymous variable");
    return typeInfo;
}

TypeInfo* LogicalExpr::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_BOOL);
    typeInfo -> setLocation(pexpr1 -> getLocation());
    typeInfo -> setName("anonymous variable");
    return typeInfo;
}

TypeInfo* FieldAccess::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pexpr == NULL)
        return pid -> getType(gloScope, claDes, currentScope);
    else
    {
        TypeInfo* typeInfo = pexpr -> getType(gloScope, claDes, currentScope);
        if(typeInfo == NULL)
            return NULL;
        else
        {
            if(typeInfo -> getClassName() == "")
            {
                IssueError::UnCorrectlyDotUsed(typeInfo->getLocation(), typeInfo->getName());
                return NULL;
            }
            else
            {
                ClaDes* claDes = gloScope -> findClass(typeInfo -> getClassName()) -> getClaDes();
                if(((typeInfo = claDes -> getClaScope() -> getType(pid -> getidname(), pid -> getLocation()))!=NULL) \
                ||  (claDes -> getParentClaDes() != NULL \
                    && (typeInfo=claDes->getParentClaDes()->getClaScope()->getType(pid->getidname(), pid->getLocation()))!=NULL))
                    return typeInfo;
            }
        }
    }
    return NULL;
}

TypeInfo* ArrayAccess::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return pexpr1 -> getType(gloScope, claDes, currentScope);
}

TypeInfo* Call::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    if(pexpr == NULL)
        return pid -> getType(gloScope, claDes, currentScope);
    else
    {
        TypeInfo* typeInfo = pexpr -> getType(gloScope, claDes, currentScope);
        if(typeInfo -> getClassName() == "")
        {
            IssueError::UnCorrectlyDotUsed(typeInfo->getLocation(), typeInfo->getName());
            return NULL;
        }
        else
        {
            ClaDes* claDes = gloScope -> findClass(typeInfo -> getClassName()) -> getClaDes();
            if(((typeInfo = claDes -> getClaScope() -> getType(pid -> getidname(), pid -> getLocation()))!=NULL) \
            ||  (claDes -> getParentClaDes() != NULL \
                && (typeInfo=claDes->getParentClaDes()->getClaScope()->getType(pid->getidname(), pid->getLocation()))!=NULL))
                return typeInfo;
        }
    }
    return NULL;
}

TypeInfo* This::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
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
    return typeInfo;
}

TypeInfo* ReadInteger::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_INT);
    typeInfo -> setName("ReadInteger");
    return typeInfo;
}

TypeInfo* ReadLine::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_INT);
    typeInfo -> setName("ReadLine");
    return typeInfo;
}

TypeInfo* Instanceof::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_BOOL);
    return typeInfo;
}

TypeInfo* NewExpr::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    return pid -> getType(gloScope, claDes, currentScope);
}

TypeInfo* NewArrayExpr::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo->setType(ptype->getType());
    switch(ptype->getType())
    {
        case(DC::TYPE::DC_NAMED):
            typeInfo->setClassName(((NamedType*)ptype)->getClassName());
            break;
        case(DC::TYPE::DC_ARRAY):
            Type* arrayType = ((ArrayType*)ptype)->getArrayType();
            if (arrayType->getType() == DC::TYPE::DC_NAMED)
            {
                typeInfo->setClassName(((NamedType*)arrayType)->getClassName());
            }
            typeInfo->setArrayType(arrayType->getType());
            typeInfo->setArrayLevel(((ArrayType*)ptype)->getArrayLevel());
            break;
    }
    typeInfo -> setName("newarray");
    return typeInfo;
}

TypeInfo* IntCon::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_INT);
    typeInfo -> setName(std::to_string(value));
    return typeInfo;
}

TypeInfo* BoolCon::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_BOOL);
    typeInfo -> setName(value == 1 ? "true" : "false");
    return typeInfo;
}

TypeInfo* StringCon::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_STRING);
    typeInfo -> setName(value);
    return typeInfo;
}

TypeInfo* NullCon::getType(GloScope* gloScope, ClaDes* claDes, Scope* currentScope)
{
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo -> setType(DC::TYPE::TYPE::DC_INT);
    typeInfo -> setName("null");
    return typeInfo;
}
// get location
YYLTYPE* TreeNode::getLocation()
{
    return NULL;
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





















//check whether dot(.) is used right, 




