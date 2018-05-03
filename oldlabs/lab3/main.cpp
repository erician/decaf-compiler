#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

using namespace std;
int yyparse();
void yyerror(const char* msg);
void InitFlex();
/*变长参数错误处理函数,当发现错误时，将会调用这个函数*/
int main()
{
    InitFlex();
    //printf(">");
    return yyparse(); //启动文法分析
}
