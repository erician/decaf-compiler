/*************************************************************************
	> File Name: flex.h
	> Author: 
	> Mail: 
	> Created Time: Tue 29 Nov 2016 01:07:48 AM PST
 ************************************************************************/

#ifndef DC_LEX_FLEX_H_
#define DC_LEX_FLEX_H_
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>


extern int errornum;
extern int yylineno;
extern char *yytext;
extern std::vector<std::string> savedlines; //报错时候会用到
void InitFlex();
int yylex();

#endif

