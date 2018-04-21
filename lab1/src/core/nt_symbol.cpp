#include "nt_symbol.h"

GloScope::GloScope(std::string className, std::string catagory, ClaDes *pClades)
{
    this->className = className;
    this->catagory = catagory;
    this->pClades = pClades;
}
std::string GloScope::getClassName() const
{
    return className;
}

std::string GloScope::getCategory() const
{
    return category;
}

const ClaDes *getPClades() const
{
    return pClades;
}




ClaDes::ClaDes(string className, string parentName, ClaDes *pParentClaDes, vector<ClaScope*> *pvecClaScope)
{
    this->className = className;
    this->parentName = parentName;
    this->pParentClaDes = pParentClaDes;
    this->pvecClaScope = pvecClaScope;
}