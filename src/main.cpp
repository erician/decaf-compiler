#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <fstream>
#include "compiler/dc_compiler.h"

extern Program *program;
extern int errornum;
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
    if (yyin != 0)
    {
        yyparse();
        if ( errornum == 0)
        {   
            Compiler compiler(args, *program);
            compiler.parseArgs();
        }
    }
    else
    {
        std::cout<<args.get(Options::SRC_FILE)<<" doesn\'t exist"<<std::endl;
    }
}
