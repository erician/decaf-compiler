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
public:
    Options();
    bool doesHaveKey(std::string key);
    bool doesHaveValue(std::string key);
};
