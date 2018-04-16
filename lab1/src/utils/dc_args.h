#include <map>
#include <string>
#include <vector>
class OptionsWithValue;
class Args
{
private:
    OptionsWithValue optionsWithValue;
    std::map<char, std::string> argDict;  
    std::map<char, std::string> parseArgs(int argc, char *argv[]);
public:
    Args(int argc, char *argv[]);
    void set(char key, std::string value);
    std::string get(char key);
    bool has_key(char key);
};

class OptionsWithValue
{
private:
    std::map<char, bool> optionsDict;
public:
    OptionsWithValue()
    {
        optionsDict['o'] = true;
    }
    bool has_key(char key)
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