#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <fstream>
#include "core/dc_class.h"
#include "utils/dc_args.h"
using namespace std;
extern Program *ast_root;
extern int yyparse();
extern FILE *yyin;
extern void InitFlex();
int main(int argc,char *argv[])
{
    InitFlex();
    if (yyparse() == 0)
    {
        ast_root->Print(1, 0);
    }

}
