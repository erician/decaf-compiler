/*************************************************************************
> File Name: nt_gentac.h
> Author: 
> Mail: 
> Created Time: 2016年12月16日 星期五 08时39分18秒
************************************************************************/

#include <vector>
#include <string>
#include "nt_buildsym.h"
#include "nt_genmips.h"
#ifndef _NT_GENTAC_H
#define _NT_GENTAC_H
class Functy;
class ClassInfo;
class Var;
class Fun;

class Instruction;
class Location;

class SaveFormal;

class LoadConstant;
class LoadStringConstant;
//class LoadLabel;
class Assign;
class Load;
class Store;
class BinaryOp;
class Label;
class Goto;
class IfZ;
class BeginFunc;
class Return;
class PushParam;
class RemoveParams;
class LCall;
class ACall;
class Break;

//map使用
class SaveVar;

class Functy
{
public:
    string functy_name;
    int number;    			//参考Fun类，number的作用
    vector<SaveFormal*> functy_formal;   //因为涉及到查找，单独拿出来
    vector<Instruction*> functy_code;
	int printed;
	Functy() {printed=0;/*表示没打印*/}
	void print();
	void genmips();
};
class ClassInfo
{
public:
    string classname;
    vector<Fun> vtable;
    vector<Var> varmember;
    int varmemberspace;     //变量成员所占的空间
	void print(vector<Functy> &vec_functy);
	void genmips();
};
class Fun
{
public:
    string funname;
    int number; 
	void print_vtable();
	void print_functy(vector<Functy> &vec_functy);
	void genmips();
                //同名的方法应该有编号
                //如，不同类的同名方法，函数名同，编号不同
                //重载继承的函数，函数名同，编号不同
                //要查看是否同名，可以从下往上搜索，这样找到同名的，
                //也找到了最大的编号
                //从0开始编号
                //发现这个编号也可以没有，因为是通过vtable访问的，
                //不会进入其他类的函数
                //有这个更清楚一些
};
class Var
{
public:
    string varname;
    int flag;   //父类和子类同名时使用，判断这个变量是父类的还是子类的
                //1代表父类,0代表自己的
    int offset; //所有变量空间都是4，
                //偏移，访问的时候用
};

class Location
{	  
  public:
    string variableName;
    int offset;

    Location(int offset, string name);
    string GetName();
    int GetOffset();
};

class Instruction {
    protected:
        string printed;

	  	string mipscode;
    public:
	Instruction();
    virtual ~Instruction() {}
	virtual void backpatch(string str);	
	virtual void Print();
	virtual void genmips(RegFile &regfile);
	virtual Location* getparam(){return NULL;}
};

  
class SaveFormal:public Instruction
{
public:
    Location *dst; //包括了偏移
    SaveFormal(Location *dst);
	void genmips(RegFile &regfile);
};

class LoadConstant: public Instruction {
    Location *dst;
    int val;
  public:
    LoadConstant(Location *dst, int val);
	void genmips(RegFile &regfile);
	//void Print();
};

class LoadStringConstant: public Instruction {
    Location *dst;
    string str;
  public:
    LoadStringConstant(Location *dst, string s);
	void genmips(RegFile &regfile);
};
/*这个好像用不到
class LoadLabel: public Instruction {
    Location *dst;
    string label;
  public:
    LoadLabel(Location *dst, string label);
};
*/

class Assign: public Instruction {
    Location *dst, *src;
  public:
    Assign(Location *dst, Location *src);
	void genmips(RegFile &regfile);
};

class Load: public Instruction {
    Location *dst, *src;
    int offset;
  public:
    Load(Location *dst, Location *src, int offset = 0);
	void genmips(RegFile &regfile);
};

class Store: public Instruction {
    Location *dst, *src;
    int offset;
  public:
    Store(Location *d, Location *s, int offset = 0);
	void genmips(RegFile &regfile);
};

class BinaryOp: public Instruction {
    
    string op;
    Location *dst, *op1, *op2;
  public:
    BinaryOp(string op, Location *dst, Location *op1, Location *op2);
	void genmips(RegFile &regfile);
};

class Label: public Instruction {
    string label;
  public:
    Label(string label);
	void genmips(RegFile &regfile);
};

class Goto: public Instruction {
    string label; 		//无条件跳转
  public:
    Goto(string label);
	void genmips(RegFile &regfile);
};

class IfZ: public Instruction {
    Location *test;
    string label;  	//测试后为0，要goto的lable
  public:
    IfZ(Location *test, string label);
    void backpatch(string str);
	void genmips(RegFile &regfile);
};

class BeginFunc: public Instruction {
    int frameSize;
  public:
    BeginFunc();
    // used to backpatch the instruction with frame size once known
    void SetFrameSize(int numBytesForAllLocalsAndTemps);
	//void genmips(RegFile &regfile);
};
class EndFunc:public Instruction {
	//返回使用
public:
	EndFunc(){printed="EndFunc";}
	void genmips(RegFile &regfile);
};

class Return: public Instruction {
    Location *val;
  public:
    Return(Location *val);
	void genmips(RegFile &regfile);
};   

class PushParam: public Instruction {
    //出栈入栈由调用函数自己维护
    Location *param;
  public:
    PushParam(Location *param);
	void genmips(RegFile &regfile);
	Location* getparam(){return param;}
}; 

class PopParams: public Instruction {
    int numBytes;
  public:
    PopParams(int numBytesOfParamsToRemove);
	void genmips(RegFile &regfile);
}; 

class LCall: public Instruction {
    string  label;    //库函数调用，函数名
    Location *dst;    //返回值,Print，dst为NULL
  public:
	vector<Instruction*> vec_param;
  public:
    LCall(Location *result,string label);
	void genmips(RegFile &regfile);
	void Print(); 		//重载print
};

class ACall: public Instruction {

    Location *dst, *methodAddr;		//函数名以及返回值
  public:
	vector<Instruction*> vec_param;  //参数
	string functy_name;
  public:
    ACall(Location *result, Location *methodAddr,string functy_name="");
	void genmips(RegFile &regfile);
	void Print(); 		//重载print
};
class Vtable:public Instruction
{
    string classname;
    Location *dst;
public:
    Vtable(string classname,Location* dst);
	void genmips(RegFile &regfile);
};
class Break:public Instruction
{
    string label;
public :
    Break(string str);
    void backpatch(string str);
	void genmips(RegFile &regfile);
};

class SaveVar
{
public:
    Scope *pscope;
    string varname;
    SaveVar(Scope *pscope,string varname);
	
};
//map比较使用
struct compare
{
    bool operator()(const SaveVar& s1,const SaveVar& s2)
    {
        if(s1.varname!=s2.varname)
        {
            return s1.varname<s2.varname;
        }
        else
        {
            return (long int)s1.pscope<(long int)s2.pscope;
        }
    }
};
string ntos(int i);
#endif
