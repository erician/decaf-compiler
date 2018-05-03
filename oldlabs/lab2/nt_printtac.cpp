/*************************************************************************
	> File Name: nt_printtac.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年12月20日 星期二 09时10分20秒
 ************************************************************************/
#include "nt_class.h"
#include "nt_gentac.h"

#include<iostream>
using namespace std;
 

void Program::printtac()
{
    for(int i=0;i<vec_classinfo.size();i++)
    {
        vec_classinfo[i].print(vec_functy);
    }
}
void ClassInfo::print(vector<Functy> &vec_functy)
{
    //先打印vtable，vtable下面是functy
    //打印vtavle的label
    cout<<classname<<":"<<endl;
    //打印vtable的函数名，函数名格式"_"+funname+"_number"
    for(int i=0;i<vtable.size();i++)
    {
        vtable[i].print_vtable();
    }
    //打印functy
    for(int i=0;i<vtable.size();i++)
    {
        vtable[i].print_functy(vec_functy);
    }
}
void Fun::print_vtable()
{
    cout<<"    "<<"_"<<funname<<"_"<<ntos(number)<<endl;
}
void Fun::print_functy(vector<Functy> &vec_functy)
{
    for(int i=0;i<vec_functy.size();i++)
    {
        if(funname==vec_functy[i].functy_name&&number==vec_functy[i].number)
        {
            //输出过的函数不应该再次输出，弄个标记
            if(vec_functy[i].printed==0)
            {
                vec_functy[i].print();
                vec_functy[i].printed=1;
            }
        }
    }
}
void Functy::print()
{
    //先已标号的形式打印函数名，格式和vtable一样
    cout<<"_"<<functy_name<<"_"<<ntos(number)<<":"<<endl;
    //先打印formals，其实真正的代码并不会有这个
    //this是第一个
    for(int i=0;i<functy_formal.size();i++)
    {
        functy_formal[i]->Print();
    }
    for(int i=0;i<functy_code.size();i++)
    {
        functy_code[i]->Print();
    }
}
/*void LoadConstant::Print()
{
	cout<<val<<endl;	
}
*/
void Instruction::Print()
{
    cout<<"    "<<printed<<endl;
}
void LCall::Print()
{
    for(int i=0;i<vec_param.size();i++)
    {
        vec_param[i]->Print();
    }
    cout<<"    "<<printed<<endl;
}
void ACall::Print()
{
    for(int i=0;i<vec_param.size();i++)
    {
        vec_param[i]->Print();
    }
    cout<<"    "<<printed<<endl;
}

