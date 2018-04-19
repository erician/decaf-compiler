#include <map>
#include <string>
#include <vector>
class OptionsWithValue;
class Args
{
private:
    OptionsWithValue optionsWithValue;
    std::map<std::string, std::string> argDict;
    std::map<std::string, std::string> parseArgs(int argc, char *argv[]);
    int parseArgsStartsWithSingleStrikethrough(char *option, char *value);
    int parseArgsStartsWithDoubleStrikethrough(char *option);
    std::string char_to_string(char ch);
public:
    Args(int argc, char *argv[]);
    void set(std::string, std::string value);
    std::string get(std::string key);
    bool hasKey(std::string key);
};

class OptionsWithValue
{
private:
    std::map<std::string, bool> optionsDict;
public:
    OptionsWithValue()
    {
        optionsDict["o"] = true;
    }
    bool hasKey(std::string key)
    {
        if (optionsDict.find(key) != optionsDict.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};