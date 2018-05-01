#ifndef DC_UTILS_ARGS_DC_OPTIONS_H_
#define DC_UTILS_ARGS_DC_OPTIONS_H_

#include <iostream>
#include <map>

class Options
{
private:
    //option name and isHasValue
    std::map<std::string, bool> optionsDict;
public:
    static const std::string PRINT_AST;
    static const std::string OUTPUT;
    static const std::string SRC_FILE;
    static const std::string LEX_GRAMM_ANALYSIS;
public:
    Options();
    bool doesHaveKey(std::string key);
    bool doesHaveValue(std::string key);
};

#endif