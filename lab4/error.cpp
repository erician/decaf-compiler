/*************************************************************************
	> File Name: error.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年12月05日 星期一 15时24分25秒
 ************************************************************************/
#include<string>
#include<vector>
#include<iostream>
#include "nt_class.h"
#include "y.tab.h"
#include "flex.h"
#include "error.h"
using namespace std;
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
    cout<<"    "<<savedlines[pyylloc->first_line-1]<<endl;
    flag_errorplace(pyylloc);
}
void IssueError::UnDefined(YYLTYPE *pyylloc,string idname)
{
    cout<<pyylloc->first_line<<":"<<pyylloc->first_column<<": ";
    cout<<"error: "<<"\'"<<idname<<"\' "<<"undeclared "<<endl;
    cout<<"    "<<savedlines[pyylloc->first_line-1]<<endl;

    flag_errorplace(pyylloc);
}
void IssueError::Printyyerror(YYLTYPE *pyylloc,string str)
{
    cout<<pyylloc->first_line<<":"<<pyylloc->first_column<<": ";
    cout<<"syntax error: "<<"\'"<<str<<"\' "<<endl;
    cout<<"    "<<savedlines[pyylloc->first_line-1]<<endl;
    flag_errorplace(pyylloc);
}
void IssueError::Redefinition(YYLTYPE *pyylloc,string str)
{
    cout<<pyylloc->first_line<<":"<<pyylloc->first_column<<": ";
    cout<<"error: "<<"redefinition of"<<"\'"<<str<<"\' "<<endl;
    cout<<"    "<<savedlines[pyylloc->first_line-1]<<endl;
    flag_errorplace(pyylloc);
    
}
void IssueError::Dir_typeerror(YYLTYPE *pyylloc,string str,string wrongtype)
{
    cout<<pyylloc->first_line<<":"<<pyylloc->first_column<<": ";
    cout<<"type error: "<<str<<endl;
    if(wrongtype!="")
    	cout<<" not the "<<'\''<<wrongtype<<'\''<<endl;
    cout<<"    "<<savedlines[pyylloc->first_line-1]<<endl;
    flag_errorplace(pyylloc);
}
