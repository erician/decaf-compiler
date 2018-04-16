/*************************************************************************
	> File Name: flex.h
	> Author: 
	> Mail: 
	> Created Time: Tue 29 Nov 2016 01:07:48 AM PST
 ************************************************************************/

#ifndef _FLEX_H
#define _FLEX_H
#include <cstdio>
#include <vector>
#include <string>
using namespace std;
extern int errornum;
extern int yylineno;
extern char *yytext;
extern vector<string> savedlines; //报错时候会用到
void InitFlex();
int yylex();

#endif

