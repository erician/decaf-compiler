/*************************************************************************
	> File Name: bison.h
	> Author: 
	> Mail: 
	> Created Time: Tue 29 Nov 2016 01:05:29 AM PST
 ************************************************************************/

#ifndef _BISON_H
#define _BISON_H
#include "../lex/flex.h"
#include "../core/dc_class.h"
void yyerror (char const *msg);
int yyparse();
Program *ast_root = NULL;
#endif
