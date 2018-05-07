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

#ifndef DC_LEX_FLEX_H_
#include "lex/flex.h"
#endif

class IssueError
{
public:
    static void UnMachedChar(const YYLTYPE *pyylloc, char c);
    static void Printyyerror(const YYLTYPE *pyylloc, std::string str);
	static void UndefinedClass(const YYLTYPE *pyylloc, std::string idname);
	static void RedefinedClass(const YYLTYPE *pyylloc, std::string idname);
private:
    static void FlagErrorPlace(const YYLTYPE *pyylloc);
	static std::string ReplaceTabByBlank(std::string str);
	static void PrintLocation(const YYLTYPE *pyylloc);
};

#endif
