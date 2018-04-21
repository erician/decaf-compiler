#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "dc_options.h"
#include "dc_option_error.h"

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

