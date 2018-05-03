/*************************************************************************
	> File Name: nt_genmips.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年12月20日 星期二 21时00分15秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include"nt_class.h"
#include"nt_gentac.h"
#include"nt_genmips.h"
using namespace std;
//这个是可以直接打印出来的，不用再保存了
vector<string> *pvec_data;
int stringnum=0;
string astring_name()
{
    return "string"+ntos(stringnum++);
}
Reg::Reg(string name,int s2)
{
    regname=name;
    notreal=s2;  
}
RegFile::RegFile()
{
    comregs.push_back(Reg("$s0"));
    comregs.push_back(Reg("$s1"));
    comregs.push_back(Reg("$s2"));
    comregs.push_back(Reg("$s3"));
    comregs.push_back(Reg("$s4"));
    comregs.push_back(Reg("$s5"));
    comregs.push_back(Reg("$s6"));
    comregs.push_back(Reg("$s7"));
    comregs.push_back(Reg("$t0"));
    comregs.push_back(Reg("$t1"));
    comregs.push_back(Reg("$t2"));
    comregs.push_back(Reg("$t3"));
    comregs.push_back(Reg("$t4"));
    comregs.push_back(Reg("$t5"));
    comregs.push_back(Reg("$t6"));
    comregs.push_back(Reg("$t7"));
    comregs.push_back(Reg("$t8"));
    comregs.push_back(Reg("$t9"));
    //初始化均未使用
    for(int i=0;i<18;i++)
        busy.push_back(0);
    for(int i=0;i<3;i++)
        a_busy[i]=0;
}
void RegFile::clear()
{
    //分别代表$a0-$a2
    for(int i=0;i<3;i++)
        a_busy[i]=0;
}
string RegFile::check_or_alloc_reg(string tmp)
{
    map<string,int>::iterator it;
    it=tmp_reg.find(tmp);
    if(it==tmp_reg.end())
    {
        //没有保存在寄存器文件
        //分配寄存器
        for(int i=0;i<busy.size();i++)
        {
            if(busy[i]==0)
            {
                //空闲寄存器
                busy[i]=1;
                tmp_reg[tmp]=i;
                if(comregs[i].notreal==-1)
                    return comregs[i].regname;
                else
                {
                    //伪寄存器
                    for(int i=0;i<3;i++)
                    {
                        if(a_busy[i]==0)
                        {
                            comregs[i].notreal=i;
                            a_busy[i]=1;
                            return "$a"+ntos(i);
                        }
                    }
                }
            }
        }
        //寄存器没有剩余，不够用
        //使用伪寄存器，变量代替寄存器
        //使用$a0,$a1,$a2参与运算，最后再将结果保存在内存中
        for(int i=0;i<3;i++)
        {
            if(a_busy[i]==0)
            {
                string nr_regname;  
                //伪寄存器名称
                nr_regname = "reg_"+ntos(comregs.size());
                comregs.push_back(Reg(nr_regname,i));
                tmp_reg[tmp]=busy.size();
                busy.push_back(1);
                //入.data
                string data_reg;
                data_reg = nr_regname+": .word 0";  //初始值为0
                pvec_data->push_back(data_reg);
                //进入map
                //返回$ai
                a_busy[i]=1;
                return "$a"+ntos(i);
            }
        }
    }
    else
    {
        //已经分配寄存器
        if(comregs[it->second].notreal==-1)
            return comregs[it->second].regname;
        else
        {
            for(int i=0;i<3;i++)
            {
                if(a_busy[i]==0)
                {
                    
                    cout<<"    lw "<<"$a"+ntos(i)<<", "<<comregs[it->second].regname<<endl;
                    a_busy[i]=1;
                    return "$a"+ntos(i);
                }
            }
        }
    }
    return "";
}
void RegFile::check_notreg(string tmp)
{
    map<string,int>::iterator it;
    it=tmp_reg.find(tmp);
    if(it!=tmp_reg.end())
    {
        if(comregs[it->second].notreal!=-1)
        {
            
            cout<<"    sw "<<"$a"<<ntos(comregs[it->second].notreal)<<", "<<comregs[it->second].regname<<endl;
        }
    }
    else
    {
        cout<<"error"<<endl;
    }
}
void RegFile::set_abusy(int num)
{
    if(a_busy[num]==1)
        cout<<"error"<<endl;
    else
        a_busy[num]=1;
}
void RegFile::do_before_func()
{
    int cont=0;
    for(int i=0;i<18;i++)
    {
        if(busy[i]==1)
            cont++;
    }
    
    //入栈，保存s
    cout<<"    addi "<<"$sp"<<", "<<"$sp"<<", "<<"-"<<cont*4+4<<endl;

    cout<<"    sw "<<"$ra"<<", "<<"0($sp)"<<endl;
    cont=4;
    for(int i=0;i<18;i++)
    if(busy[i]==1)
    {
        cout<<"    sw "<<comregs[i].regname<<", "<<cont<<"($sp)"<<endl;
        cont+=4;
    }
}
void RegFile::do_after_func()
{
    int cont=0;
    for(int i=0;i<18;i++)
    {
        if(busy[i]==1)
            cont++;
    }

    //入栈，保存sp

    cout<<"    lw "<<"$ra"<<", "<<"0($sp)"<<endl;
    int cont2;
    cont2=4;
    for(int i=0;i<18;i++)
    if(busy[i]==1)
    {
        
        cout<<"    lw "<<comregs[i].regname<<", "<<cont2<<"($sp)"<<endl;
        cont2+=4;
    }
    
    cout<<"    addi "<<"$sp"<<", "<<"$sp"<<", "<<cont*4+4<<endl;
}
void Program::genmips()
{
    pvec_data = &vec_data;
    cout<<"        .text"<<endl;
	cout<<"    j main"<<endl;
    for(int i=0;i<vec_functy.size();i++)
    {
        vec_functy[i].genmips();
    }
    //输出.data
    cout<<"        .data"<<endl;
    //string
    for(int i=0;i<vec_data.size();i++)
    {
        cout<<vec_data[i]<<endl;
    }
    //vtable
    for(int i=0;i<vec_classinfo.size();i++)
    {
        vec_classinfo[i].genmips();
    }
    //notreal
    
    

}
void ClassInfo::genmips()
{
    cout<<classname<<":"<<endl;
    for(int i=0;i<vtable.size();i++)
        vtable[i].genmips();
}
void Fun::genmips()
{
	if(funname!="main")
	    cout<<"    .word"<<"    "<<"_"<<funname<<"_"<<number<<endl;
	else
		cout<<"    .word"<<"    "<<funname<<endl;
}
void Functy::genmips()
{
    //每个functy都有一个regfile,用完后由函数释放
    RegFile regfile;
    cout<<endl;
    if(functy_name=="main")
        cout<<functy_name<<":"<<endl;
    else
        cout<<"_"<<functy_name<<"_"<<number<<":"<<endl;
    //先处理formal，调入寄存器
    for(int i=0;i<functy_formal.size();i++)
    {
        functy_formal[i]->genmips(regfile);
    }
    for(int i=0;i<functy_code.size();i++)
    {
        functy_code[i]->genmips(regfile);
    }    
    cout<<endl;
}
void SaveFormal::genmips(RegFile &regfile)
{
    regfile.clear();
    
    cout<<"    lw "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<dst->GetOffset()<<"($sp)"<<endl;
    //主要是为了赋值而考虑，如果只是访问伪寄存器的值，前面正确
    //如果要给寄存器赋值，还要将$ai中的值写入内存
    regfile.check_notreg(dst->GetName());
}
void Instruction::genmips(RegFile &regfile)
{
    //nothing to do
}
void LoadConstant::genmips(RegFile &regfile)
{
    regfile.clear();
    
    cout<<"    li "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<val<<endl;
    regfile.check_notreg(dst->GetName());
}
void LoadStringConstant::genmips(RegFile &regfile)
{
    regfile.clear();
    string stringname;
    stringname = astring_name();
    string data_string;
    data_string = stringname+": .asciiz "+str;
    pvec_data->push_back(data_string);
    //la字符串的地址
    
    cout<<"    la "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<stringname<<endl;
    regfile.check_notreg(dst->GetName());
}
void Assign::genmips(RegFile &regfile)
{
    regfile.clear();
    
    cout<<"    add "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(src->GetName())<<", "<<"$zero"<<endl;
    regfile.check_notreg(dst->GetName());
}
void Load::genmips(RegFile &regfile)
{
    regfile.clear();
    
    cout<<"    lw "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<offset<<"("<<regfile.check_or_alloc_reg(src->GetName())<<")"<<endl;
    regfile.check_notreg(dst->GetName());
}
void Store::genmips(RegFile &regfile)
{
    regfile.clear();
    
    cout<<"    sw "<<regfile.check_or_alloc_reg(src->GetName())<<", "<<offset<<"("<<regfile.check_or_alloc_reg(dst->GetName())<<")"<<endl;
}
void BinaryOp::genmips(RegFile &regfile)
{
    regfile.clear();
    if(op=="+")
    {
        cout<<"    add "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    else if(op=="-")
    {
        cout<<"    sub "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    else if(op=="*")
    {
        //只支持低位
        cout<<"    mul "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    else if(op=="/")
    {
        cout<<"    div "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    else if(op=="%")
    {
        cout<<"    rem "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    else if(op=="<")
    {
        cout<<"    slt "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    else if(op==">")
    {
        cout<<"    sgt "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    else if(op=="<=")
    {
        cout<<"    sle "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    else if(op==">=")
    {
        cout<<"    sge "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    else if(op=="seq")
    {
        cout<<"    seq "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    else if(op=="sne")
    {
        cout<<"    sne "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    else if(op=="and")
    {
        cout<<"    and "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    else if(op=="or")
    {
        cout<<"    or "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<regfile.check_or_alloc_reg(op1->GetName())<<", "<<regfile.check_or_alloc_reg(op2->GetName())<<endl;
    }
    //暂时没有支持！和-，这个要修改nt_gentac.cpp的466行
    regfile.check_notreg(dst->GetName());
}
void Label::genmips(RegFile &regfile)
{
    cout<<label<<":"<<endl;
}
void Goto::genmips(RegFile &regfile)
{
    
    cout<<"    j "<<label<<endl;
}
void IfZ::genmips(RegFile &regfile)
{
    //等于0跳转
	regfile.clear();
	//cout<<test->GetName()<<endl;   
    cout<<"    beqz "<<regfile.check_or_alloc_reg(test->GetName())<<", "<<label<<endl;
}
void EndFunc::genmips(RegFile &regfile)
{
    
    cout<<"    jr "<<"$ra"<<endl;
}
void Return::genmips(RegFile &regfile)
{
    regfile.clear();
    
    cout<<"    add "<<"$v0"<<", "<<regfile.check_or_alloc_reg(val->GetName())<<", "<<"$zero"<<endl;
}
void PushParam::genmips(RegFile &regfile)
{
    regfile.clear();
    
    cout<<"    addi "<<"$sp"<<", "<<"$sp"<<", "<<"4"<<endl;
    
    cout<<"    sw "<<regfile.check_or_alloc_reg(param->GetName())<<", "<<"0($sp)"<<endl;
}
void PopParams::genmips(RegFile &regfile)
{
    
    cout<<"    addi "<<"$sp"<<", "<<"$sp"<<", "<<"-4"<<endl;
}
void LCall::genmips(RegFile &regfile)
{
    regfile.clear();
    regfile.set_abusy(0);

    if(label=="_alloc")
    {
        
        cout<<"    li "<<"$v0"<<", "<<"9"<<endl;

        
        cout<<"    add "<<"$a0"<<", "<<regfile.check_or_alloc_reg((vec_param[0]->getparam())->GetName())<<", "<<"$zero"<<endl;

        
        cout<<"    syscall"<<endl;

        
        cout<<"    add "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<"$v0"<<", "<<"$zero"<<endl;
    }
    else if(label=="_Print")
    {
        
        cout<<"    li "<<"$v0"<<", "<<"1"<<endl;

        
        cout<<"    add "<<"$a0"<<", "<<regfile.check_or_alloc_reg((vec_param[0]->getparam())->GetName())<<", "<<"$zero"<<endl;

        
        cout<<"    syscall"<<endl;
    }
    else if(label=="_ReadInteger")
    {
        
        cout<<"    li "<<"$v0"<<", "<<"5"<<endl;

        
        cout<<"    syscall"<<endl;

        
        cout<<"    add "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<"$v0"<<", "<<"$zero"<<endl;
    }
    else if(label=="_ReadLine")
    {
        
        cout<<"    li "<<"$v0"<<", "<<"9"<<endl;

        
        cout<<"    li "<<"$a0"<<", "<<"1001"<<endl;

        
        cout<<"    syscall"<<endl;

        
        cout<<"    add "<<regfile.check_or_alloc_reg((vec_param[0]->getparam())->GetName())<<", "<<"$v0"<<", "<<"$zero"<<endl;

        
        cout<<"    li "<<"$v0"<<", "<<"8";

        
        cout<<"    add "<<"$a0"<<", "<<regfile.check_or_alloc_reg((vec_param[0]->getparam())->GetName())<<", "<<"$zero"<<endl;

        
        cout<<"    li "<<"$a1"<<", "<<"1001"<<endl;//最多1001个字符

        
        cout<<"    syscall"<<endl;

        
        cout<<"    add "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<"$v0"<<", "<<"$zero"<<endl;
    }
    //
    if(dst!=NULL)
        regfile.check_notreg(dst->GetName());
}

void ACall::genmips(RegFile &regfile)
{
    regfile.clear();
    regfile.do_before_func();
    int numbytes;
    numbytes = 4*vec_param.size();
	if(numbytes!=0)
	{
    	
    	cout<<"    addi "<<"$sp"<<", "<<"$sp"<<", "<<"-"<<numbytes<<endl;
	}
    int cont=0;
    for(int i=vec_param.size()-1;i>=0;i--)
    {
        
        cout<<"    sw "<<regfile.check_or_alloc_reg((vec_param[i]->getparam())->GetName())<<", "<<cont<<"($sp)"<<endl;
        cont+=4;
    }
	if(methodAddr!=NULL)
	{
    	
    	cout<<"    jalr "<<regfile.check_or_alloc_reg(methodAddr->GetName())<<endl;
	}
	else
	{
		
    	cout<<"    jal "<<"_"<<functy_name<<"_0"<<endl;
	}
	if(numbytes!=0)
	{
    	
    	cout<<"    addi "<<"$sp"<<", "<<"$sp"<<", "<<numbytes<<endl;
	}
    regfile.do_after_func();
    
    cout<<"    add "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<"$v0"<<", "<<"$zero"<<endl;
    regfile.check_notreg(dst->GetName());
}
void Vtable::genmips(RegFile &regfile)
{
    regfile.clear();
    //la获取label的地址
    
    cout<<"    la "<<regfile.check_or_alloc_reg(dst->GetName())<<", "<<classname<<endl;
}
void Break::genmips(RegFile &regfile)
{
    
    cout<<"    j "<<label<<endl;
}
