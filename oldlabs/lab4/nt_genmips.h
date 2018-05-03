/*************************************************************************
	> File Name: nt_genmips.h
	> Author: 
	> Mail: 
	> Created Time: 2016年12月22日 星期四 02时16分19秒
 ************************************************************************/

#ifndef _NT_GENMIPS_H
#define _NT_GENMIPS_H
#include <map>
class Reg
{
public:
    string regname;
    int notreal;
    //notreal是不是伪寄存器-1不是，其他分别对应$a0,$a1,$a2
    Reg(string regname,int notreal=-1);
};

class RegFile
{
    //处理的是通用寄存器
public:
    vector<Reg> comregs;
    vector<int> busy;
	map<string,int> tmp_reg;
	int a_busy[3];
    RegFile();
	void clear();
	string check_or_alloc_reg(string tmp);
	void check_notreg(string);
	void set_abusy(int number);
	void do_before_func();
	void do_after_func();
};
#endif
