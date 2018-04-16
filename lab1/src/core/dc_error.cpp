/*************************************************************************
	> File Name: error.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年12月05日 星期一 15时24分25秒
 ************************************************************************/
#include<string>
#include<vector>
#include<iostream>
#include "dc_class.h"
#include "../yacc/y.tab.h"
#include "../lex/flex.h"
#include "dc_error.h"
using namespace std;

string replace_tab_by_blank(string str);

void IssueError::flag_errorplace(YYLTYPE *pyylloc)
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
    cout<<"    "<<replace_tab_by_blank(savedlines[pyylloc->first_line-1])<<endl;
    flag_errorplace(pyylloc);
}
void IssueError::Printyyerror(YYLTYPE *pyylloc,string str)
{
    cout<<pyylloc->first_line<<":"<<pyylloc->first_column<<": ";
    cout<<"syntax error: "<<"\'"<<str<<"\' "<<endl;
    cout<<"    "<<replace_tab_by_blank(savedlines[pyylloc->first_line-1])<<endl;
    flag_errorplace(pyylloc);
}
string replace_tab_by_blank(string str)
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