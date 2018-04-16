#include <cstring>
#include "dc_args.h"

Args::Args(int argc, char *argv[])
{
    argDict = parseArgs(argc, argv);
}

void Args::set(char key, std::string value)
{
    argDict[key] = value;
}

bool Args::has_key(char key)
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

std::string Args::get(char key)
{
    if (has_key(key) == true)
    {
        return argDict[key];
    }
    else
    {
        return NULL;
    }
}

std::map<char, std::string> Args::parseArgs(int argc, char *argv[])
{
    int i = 1;
    while (i < argc)
    {
        char *option = argv[i];
        if (option[0] == '-')
        {
            if (strlen(option) == 1)
            {
                argDict[option[1]] = std::string();
                if (optionsWithValue.has_key(option[1]))
                {
                    argDict[option[1]] = std::string(argv[i+1]);
                    i++;
                }
            }
            else
            {
                for (int j = 1; j < strlen(option); j++)
                {
                    set(option[j], std::string());
                }
            }
        }
        else
        {
            argDict['src'] = std::string(option);
        }
        i++;
    }
}