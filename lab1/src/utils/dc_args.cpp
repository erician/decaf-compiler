#include <cstring>
#include "dc_args.h"

Args::Args(int argc, char *argv[])
{
    argDict = parseArgs(argc, argv);
}

void Args::set(std::string key, std::string value)
{
    argDict[key] = value;
}

bool Args::hasKey(std::string key)
{
    if (argDict.find(key) != argDict.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string Args::get(std::string key)
{
    if (hasKey(key) == true)
    {
        return argDict[key];
    }
    else
    {
        return NULL;
    }
}

std::map<std::string, std::string> Args::parseArgs(int argc, char *argv[])
{
    int i = 1;
    int addend = 0;
    while (i < argc)
    {
        char *option = argv[i];
        if (option[0] == '-')
        {
            if (strlen(option) >= 2 and option[1] == '-')
            {
                addend = parseArgsStartsWithDoubleStrikethrough(option);
            }
            else
            {
                addend = parseArgsStartsWithSingleStrikethrough(option, argv[i+1]);
            }
        }
        else
        {
            argDict["src"] = std::string(option);
            addend = 1;
        }
        i += addend;
    }
}

int Args::parseArgsStartsWithSingleStrikethrough(char *option, char *value)
{
    if (strlen(option) == 2)
    {
        argDict[char_to_string(option[1])] = std::string();
        if (optionsWithValue.hasKey(char_to_string(option[1])))
        {
            argDict[char_to_string(option[1])] = std::string(value);
            return 2;
        }
    }
    else
    {
        for (int j = 1; j < strlen(option); j++)
        {
            set(char_to_string(option[j]), std::string());
        }
        return 1;
    }
}
int Args::parseArgsStartsWithDoubleStrikethrough(char *option)
{
    set(std::string(option), std::string());
    return 1;
}

std::string char_to_string(char ch)
{
    char a[2] = {ch, '\0'};
    return std::string(a);
}