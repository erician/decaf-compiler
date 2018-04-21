#include <iostream>
#include "dc_compiler.h"

Compiler::Compiler(Args &args, Program &program):args(args),program(program)
{
}

void Compiler::parseArgs()
{
    if (args.hasKey(Options::PRINT_AST))
    {
        program.printAst(1, 0);
    }
}