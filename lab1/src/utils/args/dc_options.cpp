#include "dc_options.h"

const std::string Options::PRINT_AST = "--print-ast"; 
const std::string Options::OUTPUT = "o";
const std::string Options::SRC_FILE = "src";
const std::string Options::LEX_GRAMM_ANALYSIS = "--lex-gramm-analysis";

Options::Options()
{
    optionsDict[OUTPUT] = true;
    optionsDict[PRINT_AST] = false;
    optionsDict[LEX_GRAMM_ANALYSIS] = true;
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