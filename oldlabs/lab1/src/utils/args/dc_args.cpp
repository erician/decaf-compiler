#ifndef DC_UTILS_ARGS_DC_ARGS_H_
#include "utils/args/dc_args.h"
#endif

#include <cstring>

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

bool Args::parseArgs(int argc, char *argv[])
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
                addend = parseArgsStartsWithSingleStrikethrough(option, i+1<argc?(argv[i+1]):NULL);
            }
        }
        else
        {
            argDict["src"] = std::string(option);
            addend = 1;
        }
        if (addend == -1)
            return false;
        i += addend;
    }
    if(hasKey(Options::SRC_FILE) == false)
    {
        OptionError::NotHaveSourceFile();
        return false;
    }
    return true;
}

int Args::parseArgsStartsWithSingleStrikethrough(char *option, char *value)
{
    if (strlen(option) == 2)
    {
        if (allOptions.doesHaveKey(char_to_string(option[1])))
        {
            if (allOptions.doesHaveValue(char_to_string(option[1])))
            {
                if (value != NULL)
                {
                    argDict[char_to_string(option[1])] = std::string(value);
                    return 2;
                }
                else
                {
                    OptionError::NotWithValue(std::string(option));
                    return -1;
                }
            }
            else
            {
                argDict[char_to_string(option[1])] = std::string();
                return 1;
            }
        }
        else
        {
            OptionError::NotHaveThisOption(std::string(option));
            return -1;
        }
    }
    else
    {
        for (int j = 1; j < strlen(option); j++)
        { 
            if (allOptions.doesHaveKey(char_to_string(option[j])))
            {
                if (allOptions.doesHaveValue(char_to_string(option[j])) == false)
                {
                    set(char_to_string(option[j]), std::string());
                }
                else
                {
                    OptionError::NotWithValue(char_to_string(option[j]));
                    return -1;
                }
            }
            else
            {
                OptionError::NotHaveThisOption(char_to_string(option[j]));
                return -1;
            }
            
        }
        return 1;
    }
}

int Args::parseArgsStartsWithDoubleStrikethrough(char *option)
{
    if (allOptions.doesHaveKey(std::string(option)))
    {
        set(std::string(option), std::string());
        return 1;
    }
    else
    {   OptionError::NotHaveThisOption(std::string(option));
        return -1;
    }
    return 1;
}

std::string Args::char_to_string(char ch)
{
    char a[2] = {ch, '\0'};
    return std::string(a);
}