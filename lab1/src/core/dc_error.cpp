/*************************************************************************
	> File Name: error.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年12月05日 星期一 15时24分25秒
 ************************************************************************/
#ifndef DC_CORE_DC_CLASS_H_
#include "core/dc_class.h"
#endif 

#include <iostream>
#include <vector>
#include <string>

#include "yacc/y.tab.h"

#ifndef DC_LEX_FLEX_H_
#include "lex/flex.h"
#endif

#ifndef DC_CORE_DC_ERROR_H_
#include "core/dc_error.h"
#endif

void IssueError::flagErrorPlace(YYLTYPE *pyylloc)
{
    cout<<"    ";
    for(int i=0;i<pyylloc->first_column-1;i++)
        cout<<' ';
    cout<<'^'<<endl;
}
void IssueError::UnMachedChar(YYLTYPE *pyylloc,char c)
{
    cout<<pyylloc->first_line<<":"<<pyylloc->first_column<<": ";
    cout<<"error: "<<"\'"<<c<<"\' "<<"unmatched char "<<endl;
    cout<<"    "<<replaceTabByBlank(savedlines[pyylloc->first_line-1])<<endl;
    flagErrorPlace(pyylloc);
}
void IssueError::Printyyerror(YYLTYPE *pyylloc,std::string str)
{
    cout<<pyylloc->first_line<<":"<<pyylloc->first_column<<": ";
    cout<<"syntax error: "<<"\'"<<str<<"\' "<<endl;
    cout<<"    "<<replaceTabByBlank(savedlines[pyylloc->first_line-1])<<endl;
    flagErrorPlace(pyylloc);
}

std::string IssueError::replaceTabByBlank(std::string str)
{
    do{
        long long pos = str.find('\t');
        if (pos >= 0 || pos < str.length()){
            str = str.substr(0, pos) + "    " + str.substr(pos+1, str.length());
        }
        else{
            break;
        }
    }while(true);
    return str;
}