/*************************************************************************
	> File Name: error.h
	> Author: 
	> Mail: 
	> Created Time: 2016年12月05日 星期一 15时22分39秒
 ************************************************************************/
#ifndef DC_CORE_DC_ERROR_H_
#define DC_CORE_DC_ERROR_H_

#include <iostream>

#ifndef DC_YACC_LOCATION_H_
#include "yacc/location.h"
#endif

class IssueError
{
private:
    static void flagErrorPlace(YYLTYPE *pyylloc);
	static std::string replaceTabByBlank(std::string str);

public:
    static void UnMachedChar(YYLTYPE *pyylloc,char c);
    static void Printyyerror(YYLTYPE *pyylloc,std::string str);
	
};

#endif
