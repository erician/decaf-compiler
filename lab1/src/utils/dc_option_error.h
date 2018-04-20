#include <iostream>

class OptionError
{
public:
    static void NotHaveThisOption(std::string option);
    static void NotWithValue(std::string option);
    static void NotHaveSourceFile();
};