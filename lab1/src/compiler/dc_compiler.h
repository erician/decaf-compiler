#include <iostream>
#include "../utils/args/dc_args.h"
#include "../core/dc_class.h"

class Compiler
{
private:
    Args &args;
    Program &program;
public:
    Compiler(Args &args, Program &program);
    void parseArgs();
};