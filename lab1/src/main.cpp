#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cstdio>
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
    Args args;
    if (args.parseArgs(argc, argv) == false)
        return -1;
    InitFlex();
    yyin =  fopen(args.get(Options::SRC_FILE).c_str(), "r");
    if (yyparse() == 0)
    {
        if (args.hasKey(Options::PRINT_AST))
            ast_root->Print(1, 0);
    }
}
