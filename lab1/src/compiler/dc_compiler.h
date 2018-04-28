#ifndef DC_COMPILER_DC_COMPILER_H_
#define DC_COMPILER_DC_COMPILER_H_

#include <iostream>

#ifndef DC_UTILS_ARGS_DC_ARGS_H_
#include "utils/args/dc_args.h"
#endif

#ifndef DC_CORE_DC_CLASS_H_
#include "core/dc_class.h"
#endif

class Compiler
{
private:
    Args &args;
    Program &program;
public:
    Compiler(Args &args, Program &program);
    void parseArgs();
};

#endif