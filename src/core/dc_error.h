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
	//class
	static void UndefinedClass(const YYLTYPE *pyylloc, std::string idname);
	static void RedefinedClass(const YYLTYPE *pyylloc, std::string idname, const YYLTYPE *firstDefinedLocation);
	//main
	static void UndefinedMain();
	static void RedefinedMain(const YYLTYPE *pyylloc, const YYLTYPE *firstDefinedLocation);
	static void MainIsNotStatic(const YYLTYPE *pyylloc);
	//attribute and method
	static void RedefinedVarOrMethod(const YYLTYPE *pyylloc, std::string idname, const YYLTYPE *firstDefinedLocation, int category);
	static void AttributeAndMethodWithTheSameName(const YYLTYPE *pyylloc, std::string idname, const YYLTYPE *firstDefinedLocation);
	//local variable
	static void RedefinedLocalVariable(const YYLTYPE *pyylloc, std::string idname, const YYLTYPE *firstDefinedLocation);
	//undefined variables
	static void UndefinedVariables(const YYLTYPE *pyylloc, std::string idname);
	static void ClassDoesNotHaveTheAttriOrMethod(std::string classname, const YYLTYPE *pyylloc, std::string idname);
	//DOT(.) used unorrectly
	static void UnCorrectlyDotUsed(const YYLTYPE *pyylloc, std::string idname);
	//not used
	static void UnCorrectlyDotUsedToAccessStaticMethod(const YYLTYPE *pyylloc, std::string idname);
	//break is not in the right place
	static void UnCorrectlyBreakUsed(const YYLTYPE *pyylloc);
	//mismatch type
	static void MismatchType(std::string typeName1, const YYLTYPE *pyylloc1, \
							 std::string typeName2, const YYLTYPE *pyylloc2);
	static void MismatchReturnType(std::string typeName1, const YYLTYPE *pyylloc1, \
							 std::string typeName2, const YYLTYPE *pyylloc2);
	static void ArrayAccessMismatchType(std::string typeName1, const YYLTYPE *pyylloc1, \
							 std::string typeName2, const YYLTYPE *pyylloc2);
	static void ActualsAndFormalsNumMismatch(int formalsNum, int actualsNum, const YYLTYPE *pyylloc);
	static void ActualsAndFormalsTypeMismatch(std::string typeName1, const YYLTYPE *pyylloc1, \
							 std::string typeName2, const YYLTYPE *pyylloc2);
	//not array type used the []
	static void UnCorrectlyBracketsUsed(std::string idname, const YYLTYPE *pyylloc);
	//internal error
	static void InternalError(const std::string filename, int lineno);
private:
    static void FlagErrorPlace(const YYLTYPE *pyylloc);
	static std::string ReplaceTabByBlank(std::string str);
	static void PrintLocation(const YYLTYPE *pyylloc);
};

#endif
