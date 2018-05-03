#ifndef DC_UTILS_PRINT_DC_PRINT_H_
#include "utils/print/dc_print.h"
#endif

void DC::UTILS::PRINT::printWhite(int aline,int level)
{
    if(aline)
    {
        std::cout<<std::endl;
        for(int i=0;i<level;i++)
            std::cout<<"    ";
    }
    else
    {
        std::cout<<" ";
    } 
} 