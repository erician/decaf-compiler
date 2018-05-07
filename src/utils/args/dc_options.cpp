#ifndef DC_UTILS_ARGS_DC_OPTIONS_H_
#include "utils/args/dc_options.h"
#endif

const std::string Options::PRINT_AST = "--print-ast"; 
const std::string Options::PRINT_SYM = "--print-sym";
const std::string Options::OUTPUT = "o";
const std::string Options::SRC_FILE = "src";
const std::string Options::LEX_GRAMM_ANALYSIS = "--lex-gramm-analysis";
const std::string Options::BUILD_SYMBOL_TABLE = "--build-symbol-table";
const std::string Options::CHECK_STATIC_SEMANTIC = "--check-static-semantic";

Options::Options()
{
    optionsDict[OUTPUT] = true;
    optionsDict[PRINT_SYM] = false;
    optionsDict[PRINT_AST] = false;
    optionsDict[LEX_GRAMM_ANALYSIS] = false;
    optionsDict[BUILD_SYMBOL_TABLE] = false;
    optionsDict[CHECK_STATIC_SEMANTIC] = false;
}

bool Options::doesHaveKey(std::string key)
{
    if (optionsDict.find(key) != optionsDict.end())
        return true;
    else
        return false;
}

bool Options::doesHaveValue(std::string key)
{
    if (doesHaveKey(key) == true)
        return optionsDict[key];
    else
        return false;
}

