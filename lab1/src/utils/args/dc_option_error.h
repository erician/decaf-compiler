#ifndef DC_UTILS_DC_OPTION_ERROR_H_
#define DC_UTILS_DC_OPTION_ERROR_H_

#include <iostream>
class OptionError
{
public:
    static void NotHaveThisOption(std::string option);
    static void NotWithValue(std::string option);
    static void NotHaveSourceFile();
};

#endif