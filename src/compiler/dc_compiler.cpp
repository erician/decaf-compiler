#ifndef DC_COMPILER_DC_COMPILER_H_
#include "dc_compiler.h"
#endif

#include <iostream>
#include <fstream>
#include <cstdio>

Compiler::Compiler(Args &args, Program &program):args(args),program(program)
{
}

void Compiler::parseArgs()
{

    if (args.hasKey(Options::PRINT_AST))
    {
        std::cout << "ass" << std::endl;
        program.printAst(1, 0);
    }

    if (args.hasKey(Options::PRINT_SYM))
    {
        program.buildSym();
        program.printSym(1, 0);
    }

    if (args.hasKey(Options::OUTPUT))
    {
        if (args.hasKey(Options::LEX_GRAMM_ANALYSIS))
        {
            freopen (args.get(Options::OUTPUT).c_str(), "w", stdout);
            program.printAst(1,0);
            fclose(stdout);
        }   
        else if(args.hasKey(Options::BUILD_SYMBOL_TABLE))
        {
            freopen (args.get(Options::OUTPUT).c_str(), "w", stdout);
            if(args.hasKey(Options::PRINT_SYM) == false)
            {
                program.buildSym();
            }
            program.printAst(1,0);
            fclose(stdout);
        }
    }

    if(args.doesOnlyHaveSrc())
    {
        program.buildSym();
        program.checkStaticSemantic();
    }
}