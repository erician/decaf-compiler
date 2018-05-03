/*************************************************************************
	> File Name: error.h
	> Author: 
	> Mail: 
	> Created Time: 2016年12月05日 星期一 15时22分39秒
 ************************************************************************/

#ifndef _ERROR_H
#define _ERROR_H
class IssueError
{
public:
    static void flag_errorplace(YYLTYPE *pyylloc);
    static void UnMachedChar(YYLTYPE *pyylloc,char c);
    static void UnDefined(YYLTYPE *pyylloc,string idname);
    static void Printyyerror(YYLTYPE *pyylloc,string str);
    static void Redefinition(YYLTYPE *pyylloc,string str);
    static void Dir_typeerror(YYLTYPE *pyylloc,string str,string wrongtype);
};

#endif
