#ifndef DC_UTILS_ARGS_DC_ARGS_H_
#define DC_UTILS_ARGS_DC_ARGS_H_

#include <iostream>
#include <map>
#include <vector>
#include <string>

#ifndef DC_UTILS_ARGS_DC_OPTIONS_H_
#include "utils/args/dc_options.h"
#endif

#ifndef DC_UTILS_ARGS_DC_OPTION_ERROR_H_
#include "utils/args/dc_option_error.h"
#endif

class Args
{
private:
    Options allOptions;
    std::map<std::string, std::string> argDict;
    int parseArgsStartsWithSingleStrikethrough(char *option, char *value);
    int parseArgsStartsWithDoubleStrikethrough(char *option);
    std::string char_to_string(char ch);
public:
    Args(){}
    bool parseArgs(int argc, char *argv[]);
    void set(std::string, std::string value);
    std::string get(std::string key);
    bool hasKey(std::string key);
};

#endif