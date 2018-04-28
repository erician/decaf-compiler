/*************************************************************************
	> File Name: bison.h
	> Author: 
	> Mail: 
	> Created Time: Tue 29 Nov 2016 01:05:29 AM PST
 ************************************************************************/

#ifndef DC_YACC_BISON_H_
#define DC_YACC_BISON_H_

#ifndef DC_LEX_FLEX_H_
#include "lex/flex.h"
#endif

#ifndef DC_CORE_DC_CLASS_H_
#include "core/dc_class.h"
#endif

#define DC_STATIC 1
#define DC_NOTSTATIC 0
void yyerror (char const *msg);
int yyparse();
Program *program = NULL;

#endif
