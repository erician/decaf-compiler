/*************************************************************************
	> File Name: nt_gentac.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年12月16日 星期五 09时06分18秒
 ************************************************************************/

#include<iostream>
#include<map>
#include<sstream>
#include "nt_class.h"
#include "nt_gentac.h"
#include "nt_buildsym.h"
using namespace std;


//tmp分配和lable分配,封装成函数
int temp_number=0;
int label_number=0;
//Scope* pscope;
//string varname;
map<SaveVar,Location*,compare> mymap;
vector<ClassInfo> *pvec_classinfo; //call 使用

string atemp()
{
    string str;
    stringstream ss;
    ss<<temp_number;
    temp_number++;
    ss>>str;
    return "_Temp"+str;
}
string alabel()
{  
    string str;
    stringstream ss;
    ss<<label_number;
    label_number++;
    ss>>str;
    return "_Label"+str;
}
string ntos(int i)
{
    string str;
    stringstream ss;
    ss<<i;
    ss>>str;
    return str;
}

void Program::gentac()
{
    pvec_classinfo=&vec_classinfo;
    mymap.clear();
    if(pdecllist!=NULL)
    {
        for(int i=0;i<pdecllist->size();i++)
        {
            (*pdecllist)[i]->gentac(vec_functy,vec_classinfo);
        }
    }
}
void Decl::gentac(vector<Functy> &vec_functy,vector<ClassInfo> &vec_classinfo)
{
    //nothing to do;
}
void Decl::gentac_var_functy(ClassInfo &classinfo,vector<Functy> &vec_functy)
{
    //nothing to do
}
void ClassDecl::gentac(vector<Functy> &vec_functy,vector<ClassInfo> &vec_classinfo)
{
    ClassInfo classinfo; //不管类有没有变量成员，都会入栈，方便管理
    //初始化
    classinfo.classname=pid->getidname();
    classinfo.varmemberspace=0;

    //先填父类的方法和变量
    if(base!=NULL)
    {
        //去继承基类的方法和变量名
    
        //基类的functy不用去管它，只要用classinfo找到名字即可
        string basename = base->getidname();
        for(int i=0;i<vec_classinfo.size();i++)
        {
            if(vec_classinfo[i].classname==basename)
            {
                //Class不会重名，第一个就是
                //基类变量成员空间
                classinfo.varmemberspace=vec_classinfo[i].varmemberspace;
                //复制基类变量成员，修改flag
                Var tmp_var;
                for(int j=0;j<(vec_classinfo[i].varmember).size();j++)
                {
                    tmp_var=(vec_classinfo[i].varmember)[j];
                    tmp_var.flag=1;
                    (classinfo.varmember).push_back(tmp_var);
                }
                //复制方法
                //子类可能会重载，
                //在加入子类方法时别忘了检查基类的方法
                //因为子类的方法可以覆盖父类的方法
                //
                for(int j=0;j<(vec_classinfo[i].vtable).size();j++)
                {//直接复制，没有问题
                    (classinfo.vtable).push_back(vec_classinfo[i].vtable[j]);
                }
                break;
            }
        }
    }
    //方法名应该先加入classinfo，不然在代码中如果调用函数，会找不到
    //先将构造函数加入虚函数表
    //没有重名，可以直接加入
    Fun fun;
    fun.funname=pid->getidname();
    fun.number = 0;
    classinfo.vtable.push_back(fun);
    //将方法加入classinfo
    GloScope *pgloscope;


    pgloscope = (GloScope*)pid->getpscope();

    ClaDes *pclades;
    pclades = pgloscope->getpclades();
    vector<ClaScope*> *pvec_clascope;
    pvec_clascope = pclades->get_pvec_clascope();
    for(int i=0;i<pvec_clascope->size();i++)
    {
        if((*pvec_clascope)[i]->getcategory()=="function")
        {
            fun.funname=(*pvec_clascope)[i]->getname();
            fun.number=-1;
            //在vec_functy内找同名的,从下找
            for(int j=vec_functy.size()-1;j>=0;j--)
            {
                if(fun.funname==vec_functy[j].functy_name)
                {
                    fun.number=vec_functy[j].number;
                    break;
                }
            }
            fun.number=fun.number+1;
            //查看是否有重载
            int flag=0;
            for(int j=0;j<(classinfo.vtable).size();j++)
            {
                if(fun.funname==(classinfo.vtable)[j].funname)
                {//与基函数重名，实现覆盖,只要修改number
                    (classinfo.vtable)[j].number = fun.number;
                    flag=1;
                    break;
                }
            }
               
            //没有覆盖
            if(flag==0)
            {
                fun.funname=fun.funname;  //函数名不加_,打印的时候再加
                classinfo.vtable.push_back(fun);
            }
        }
    }

    //先加入，知道不完整，在最后弹出，压入新的进行更新 
    vec_classinfo.push_back(classinfo);
    for(int i=0;i<pfields->size();i++)
    {
        (*pfields)[i]->gentac_var_functy(classinfo,vec_functy);   
    }
    vec_classinfo.pop_back();
    vec_classinfo.push_back(classinfo);
    //在这里加入类的初始化函数是合适的（暂时称它为构造函数）
    //约定：标号，函数名，寄存器名（即t）都是以“_”开头的字符串
    Functy functy;
    functy.functy_name = pid->getidname();
    //因为类不会重名，所以这个函数也不会重名，不用检查
    functy.number=0;
    //记录formal
    //这里没有formal，不记录
    //函数的标号可以由函数名打印，不记录

    //下面为对象分配空间，要考虑指向vtable的指针
    //所以，空间大小为varmemberspace+4
    //temp名后会有一个t，lable名后会有一个l
    Location *alloc_parm_t;
    alloc_parm_t = new Location(0,atemp());
    functy.functy_code.push_back(new LoadConstant(alloc_parm_t,classinfo.varmemberspace+4));
    //alloc
    Location *obj_t;
    obj_t=new Location(0,atemp());
	
	LCall *plcall;
	plcall = new LCall(obj_t,"_alloc");
	//alloc 参数
	(plcall->vec_param).push_back(new PushParam(alloc_parm_t));
    functy.functy_code.push_back(plcall);
    //先初始化指向vtable的指针
    Location *vtable_t;
    vtable_t = new Location(0,atemp());
    functy.functy_code.push_back(new Vtable(pid->getidname(),vtable_t));

    functy.functy_code.push_back(new Store(obj_t,vtable_t));
    //初始化变量成员，全为0
    Location *init_value_t;
    init_value_t = new Location(0,atemp());
    functy.functy_code.push_back(new LoadConstant(init_value_t,0));
    int cont=0;
    for(int i=0;i<(classinfo.varmember).size();i++)
    {
        cont = (classinfo.varmember)[i].offset+4;
        functy.functy_code.push_back(new Store(obj_t,init_value_t,cont));
    }
    functy.functy_code.push_back(new Return(obj_t));
	//EndFunc
	functy.functy_code.push_back(new EndFunc());
    //加入vec_functy
    vec_functy.push_back(functy);
}
void VarDecl::gentac_var_functy(ClassInfo &classinfo,vector<Functy> &vec_functy)
{
    //   子类变量成员名如果和父类变量成员名同名，按照decaf的文法 
    //   是无法访问父类的变量的，但是因为子类可以给父类赋值，
    //   所以还是要保留父类的变量，
    //   这样varmember要多加一个标志，是父类的还是子类的
    
    //   只处理classinfo
    Var var;
    var.varname = pid->getidname();
    int flag=0;
    for(int i=0;i<(classinfo.varmember).size();i++)
    {
        if(var.varname==(classinfo.varmember[i]).varname)
        {//基类中有同名的
            flag=1;
            break;
        }
    }
    var.flag = flag;
    //为了简单，bool是4个字节
    //这样，所有的变量都是四个字节了
    //记录变量的偏移
    var.offset = classinfo.varmemberspace;
    classinfo.varmemberspace+=4;
    classinfo.varmember.push_back(var);
    //在这里为varmember分配tmp
    Location *p;
    p=new Location(var.offset,var.varname);
    mymap[SaveVar(pid->getpscope(),pid->getidname())]=p;
	//cout<<pid->getpscope<<endl;
}
void FnDecl::gentac_var_functy(ClassInfo &classinfo,vector<Functy> &vec_functy)
{
    
    Functy functy;
    int number_tmp=-1;
    functy.functy_name = pid->getidname();
    //在vec_functy中查看是否有函数重名
    //因为functy没有变，这里得到的和在ClassDecl中得到的是一样的，不用修改
    for(int i=vec_functy.size()-1;i>=0;i--)
    {
        if(functy.functy_name==(vec_functy[i]).functy_name)
        {
            //倒着找，找到第一个便可以退出
            number_tmp=(vec_functy[i]).number;
            break;
        }
    }
    //编号加1
    //如果找不到同名函数，
    functy.number = number_tmp + 1;

    //处理formals,保存偏移
    //为formal分配好tmp，以后就会使用tmp运算
    //先加入this,偏移为0
    
    Location *pthis;
    pthis = new Location(0,atemp());
    functy.functy_formal.push_back(new SaveFormal(pthis));
    mymap[SaveVar(NULL,"this")]=pthis;
    
    if(pformals!=NULL)
    {
        int cont=4;
        for(int i=0;i<pformals->size();i++)
        {
            (*pformals)[i]->gentac_formal(cont,functy.functy_formal);
            cont=cont+4;
        }
    }

    //处理code,做了这么久才开始处理code。。。。。。。。
    //重点
    if(pstmtblock!=NULL)
    {
        pstmtblock->gentac_stmt(functy.functy_code);
    }
    functy.functy_code.push_back(new EndFunc());
    //this,函数结束后，this出来，防止重名
    mymap.erase(SaveVar(NULL,"this"));
    //加入vec_functy即可，因为已经加入过classinfo
    vec_functy.push_back(functy);
}

void VarDecl::gentac_formal(int off,vector<SaveFormal*> &formal)
{
    Location *p;
    p=new Location(off,atemp());
    mymap[SaveVar(pid->getpscope(),pid->getidname())]=p;
    formal.push_back(new SaveFormal(p));
}
Location* Stmt::gentac_stmt(vector<Instruction*> &functy_code)
{
    //nothing to do
	return NULL;
}
Location* StmtBlock::gentac_stmt(vector<Instruction*> &functy_code)
{
    //局部变量先不分配寄存器，当用到时再分配
    if(pstmts!=NULL)
    {
        for(int i=0;i<pstmts->size();i++)
        {
            (*pstmts)[i]->gentac_stmt(functy_code);
        }
    }
	return NULL;
}
Location* IfStmt::gentac_stmt(vector<Instruction*> &functy_code)
{
    Location *p;
    IfZ *ifz;
    if(pexpr!=NULL)
    {
        p=pexpr->gentac_stmt(functy_code);//返回的是dst
        ifz = new IfZ(p,"");
        functy_code.push_back(ifz);//回填
    }
    if(pstmt1!=NULL)
        pstmt1->gentac_stmt(functy_code);
    //如果pstmt1为空，同样需要回填
    //回填
    string label=alabel();
    functy_code.push_back(new Label(label));
    ifz->backpatch(label); //其实这个不用也行，直接在前面写好label

    if(pstmt2!=NULL)
    {
        pstmt2->gentac_stmt(functy_code);
    }
    return NULL;
}
Location* WhileStmt::gentac_stmt(vector<Instruction*> &functy_code)
{
    //判断的label
    string label1;
    label1=alabel();
    functy_code.push_back(new Label(label1));
    Location *p;
    IfZ *ifz;
    //第一次判断是否能进入
    if(pexpr!=NULL)
    {
        p=pexpr->gentac_stmt(functy_code);//返回的是dst
        ifz = new IfZ(p,"");
        functy_code.push_back(ifz);//回填
    }
    if(pstmt!=NULL)
        pstmt->gentac_stmt(functy_code);
    //无条件跳转到判断
    functy_code.push_back(new Goto(label1));
    //生成label
    string label2;
    label2=alabel();
    functy_code.push_back(new Label(label2));
    //回填if
    //回填break
    for(int i=functy_code.size()-1;;i--)
    {
        functy_code[i]->backpatch(label2);
        //到ifz时终止
        if(functy_code[i]==ifz)
            break;
    }
	return NULL;
}
Location* ForStmt::gentac_stmt(vector<Instruction*> &functy_code)
{
    if(poptexpr1!=NULL)
    {
        poptexpr1->gentac_stmt(functy_code);
    }
    string label1=alabel();
    functy_code.push_back(new Label(label1));
    //判断
    Location *p;
    IfZ *ifz;
    if(pexpr!=NULL)
    {
        p=pexpr->gentac_stmt(functy_code);
        ifz = new IfZ(p,"");
        functy_code.push_back(ifz);
    }
    if(pstmt!=NULL)
    {
        pstmt->gentac_stmt(functy_code);
    }
    if(poptexpr2!=NULL)
    {
        poptexpr2->gentac_stmt(functy_code);
    }
    //无条件跳转到判断
    functy_code.push_back(new Goto(label1));
    //生成label
    string label2=alabel();
    functy_code.push_back(new Label(label2));
    //回填if
    //回填break
    for(int i=functy_code.size()-1;;i--)
    {
        functy_code[i]->backpatch(label2);
        //到ifz时终止
        if(functy_code[i]==ifz)
            break;
    }
	return NULL;
}
Location* ReturnStmt::gentac_stmt(vector<Instruction*> &functy_code)
{
    Location *p;
    if(poptexpr!=NULL)
    {
        p=poptexpr->gentac_stmt(functy_code);
    }
    functy_code.push_back(new Return(p));
	return NULL;
}
Location* BreakStmt::gentac_stmt(vector<Instruction*> &functy_code)
{//这个要使用代码回填
    functy_code.push_back(new Break(""));
	return NULL;
}
Location* PrintStmt::gentac_stmt(vector<Instruction*> &functy_code)
{
    if(pexprs!=NULL)
    {
        //pexprs都是参数，变长参数
        //参数逆序入栈
        Location *p;
		LCall *plcall;
		plcall = new LCall(NULL,"_Print");

        for(int i=pexprs->size()-1;i>=0;i--)
        {
            p=(*pexprs)[i]->gentac_stmt(functy_code);
            //入栈
            (plcall->vec_param).push_back(new PushParam(p));
        }
        //call
        functy_code.push_back(plcall);        
    }
	return NULL;
}

Location* ArithmeticExpr::gentac_stmt(vector<Instruction*> &functy_code)
{
    if(pexpr1!=NULL&&pexpr2!=NULL)
    {
        Location *p1,*p2;
        p2=pexpr2->gentac_stmt(functy_code);
        p1=pexpr1->gentac_stmt(functy_code);
        Location *pdst;
        pdst = new Location(0,atemp());
        functy_code.push_back(new BinaryOp(opname,pdst,p1,p2));
        return pdst;
    }
    return NULL;
}
Location* RelationExpr::gentac_stmt(vector<Instruction*> &functy_code)
{
    if(pexpr1!=NULL&&pexpr2!=NULL)
    {
        Location *p1,*p2;
        p2=pexpr2->gentac_stmt(functy_code);
        p1=pexpr1->gentac_stmt(functy_code);
        Location *pdst;
        pdst = new Location(0,atemp());
        functy_code.push_back(new BinaryOp(opname,pdst,p1,p2));
        return pdst;
    }
    return NULL;
}
Location* LogicalExpr::gentac_stmt(vector<Instruction*> &functy_code)
{
    if(pexpr1!=NULL&&pexpr2!=NULL)
    {
        Location *p1,*p2;
        p2=pexpr2->gentac_stmt(functy_code);
        p1=pexpr1->gentac_stmt(functy_code);
        Location *pdst;
        pdst = new Location(0,atemp());
        functy_code.push_back(new BinaryOp(opname,pdst,p1,p2));
        return pdst;
    }
    return NULL;
}
Location* AssignExpr::gentac_stmt(vector<Instruction*> &functy_code)
{
    //在赋值前调用Lvalue的函数，判断被赋值的对象是否为成员变量
    //如果是成员变量，使用store，否则直接使用assign
    //数组的考虑
    if(pexpr!=NULL)
    {
		//这条语句肯定先做
        Location *psrc;
        psrc=pexpr->gentac_stmt(functy_code);
		//ARRAY
		Location *pdst;
        if((pdst=plvalue->IsArray(functy_code))!=NULL)
        {
            //写入的位置由IsArray提供
            functy_code.push_back(new Store(pdst,psrc,0));
			return pdst;
        }
		//不是数组
		pdst=plvalue->gentac_stmt(functy_code);
        //考虑是否是成员变量，是的话，写回内存
        if(plvalue->IsVarMem())
        {
            map<SaveVar,Location*,compare>::iterator it;
            it=mymap.find(SaveVar(NULL,"this"));
            functy_code.push_back(new Store(it->second,pdst,pdst->GetOffset()));
			return pdst;
        }
        //不是数组，不是成员变量
        functy_code.push_back(new Assign(pdst,psrc));
        return pdst;
    }
    return NULL;
}
int Lvalue::IsVarMem()
{
    return 0;
}
Location *Lvalue::IsArray(vector<Instruction*> &functy_code)
{
    return NULL;
}
Location* Lvalue::gentac_stmt(vector<Instruction*> &functy_code)
{
    return NULL;
}
int FieldAccess::IsVarMem()
{
    Scope *p=pid->getpscope();
    int num;
    num = p->getscopenum();
    if(num==2)
        return 1;   //变量成员
    else
        return 0;
}
Location* FieldAccess::gentac_stmt(vector<Instruction*> &functy_code)
{
    //查看map，是否已分配过tmp
    //如果找到，直接返回Location
    //如果没找到，分配tmp，并压入map
    //因为pexpr只能为this，所以不用去考虑pexpr
    //直接查找map
    map<SaveVar,Location*,compare>::iterator it;

    it=mymap.find(SaveVar(pid->getpscope(),pid->getidname()));
    if(it==mymap.end())
    {

        //因为formal和varmember都已经进入map，
        //所以这里只是局部变量进入map
        Location *p;
        p=new Location(0,atemp());
        mymap[SaveVar(pid->getpscope(),pid->getidname())]=p;
        return p;
    }
    else
    {
        return it->second;
    }
}

Location* ArrayAccess::IsArray(vector<Instruction*> &functy_code)
{
    if(pexpr2!=NULL&&pexpr1!=NULL)
    {
        Location* p1,*p2;
        p2=pexpr2->gentac_stmt(functy_code);
        p1=pexpr1->gentac_stmt(functy_code);
		//p2要先做一次乘法，乘以4才得到地址
		Location *p2mul4,*pcon4;
		pcon4 = new Location(0,atemp());
		functy_code.push_back(new LoadConstant(pcon4,4));

		p2mul4 = new Location(0,atemp());
		functy_code.push_back(new BinaryOp("*",p2mul4,p2,pcon4));
        //p1,p2做加法
        Location *pdst1;
        pdst1 = new Location(0,atemp());
        functy_code.push_back(new BinaryOp("+",pdst1,p1,p2mul4));
        return pdst1;
    }
    return NULL;
}
Location* ArrayAccess::gentac_stmt(vector<Instruction*> &functy_code)
{
    if(pexpr2!=NULL&&pexpr1!=NULL)
    {
        Location* p1,*p2;
        p2=pexpr2->gentac_stmt(functy_code);
        p1=pexpr1->gentac_stmt(functy_code);
		//p2要先做一次乘法，乘以4才得到地址
		Location *p2mul4,*pcon4;
		pcon4 = new Location(0,atemp());
		functy_code.push_back(new LoadConstant(pcon4,4));

		p2mul4 = new Location(0,atemp());
		functy_code.push_back(new BinaryOp("*",p2mul4,p2,pcon4));
        //p1,p2做加法,结果在pdst1
        Location *pdst1;
        pdst1 = new Location(0,atemp());
        functy_code.push_back(new BinaryOp("+",pdst1,p1,p2mul4));
        //Load
        Location *pdst2;
        pdst2 = new Location(0,atemp());
        functy_code.push_back(new Load(pdst2,pdst1));
        return pdst2;
    }
    return NULL;
}
Location* Call::gentac_stmt(vector<Instruction*> &functy_code)
{
	ACall *pacall;
	vector<Location*> save_act;	
	if(pactuals!=NULL)
    {
		//actual的计算应该在最前面
        Location *p;
		for(int i=0;i<pactuals->size();i++)
        {
            p=(*pactuals)[i]->gentac_stmt(functy_code);
			save_act.push_back(p);
            //(pacall->vec_param).push_back(new PushParam(p));
        }
    }
    //调用函数
    if(pexpr==NULL)
    {
        //调用这个类自己的函数
        //用this访问，需要获取函数名
        string funname;
        funname = pid->getidname();
        //获取this
        map<SaveVar,Location*,compare>::iterator it;
        it=mymap.find(SaveVar(NULL,"this"));
        //this 入栈,挪到后面
        //functy_code.push_back(new PushParam(it->second));
        //this 首址存放的是指向Vtable的指针，获取这个指针
        Location *pvtable;
        pvtable = new Location(0,atemp());
        functy_code.push_back(new Load(pvtable,it->second,0));
        //得到函数在vtable中的偏移，通过查找classinfo找到
        //类不会重名
        ClassInfo classinfo;
        //新加入的
        classinfo =(*pvec_classinfo)[pvec_classinfo->size()-1];
        int cont=0;
        for(int i=0;i<classinfo.vtable.size();i++)
        {
            if(funname==classinfo.vtable[i].funname)
            {
                //不会重名，第一个就是
                Location *pfun;
                pfun = new Location(0,atemp());
                functy_code.push_back(new Load(pfun,pvtable,cont));

                Location *pdst;
                pdst = new Location(0,atemp());
				pacall = new ACall(pdst,pfun);
                functy_code.push_back(pacall);
				//我可以在这里处理参数
 				if(save_act.size()!=0)
    			{
        			//逆序压入实参,后面入this
			        for(int i=save_act.size()-1;i>=0;i--)
        			{
            			//p=(*pactuals)[i]->gentac_stmt(functy_code);
            			(pacall->vec_param).push_back(new PushParam(save_act[i]));
        			}
    			}
				(pacall->vec_param).push_back(new PushParam(it->second));
                return pdst;
            }
            cont+=4;
        }
    }
    else
    {
        //其他类的函数
        //函数名
        string funname;
        funname = pid->getidname();
        //类名,使用pid获取
        GloScope *pgloscope;
        Scope *pscope;
        pscope = pid->getpscope();
        pgloscope = (GloScope*)pscope->getparent();
        string classname;
        classname = pgloscope->getname();
        //obj Location
        Location *pobj;
        pobj = pexpr->gentac_stmt(functy_code);
        //this 入栈,在后面
        //functy_code.push_back(new PushParam(pobj));
        //vtacle
        Location *pvtable;
        pvtable = new Location(0,atemp());
        functy_code.push_back(new Load(pvtable,pobj,0));

        //得到函数在vtable中的偏移，通过查找vec_classinfo找到
        ClassInfo classinfo;
        for(int i=0;i<pvec_classinfo->size();i++)
        {
            if((*pvec_classinfo)[i].classname==classname)
            {
                classinfo =(*pvec_classinfo)[i];
                break;
            }
        }
        int cont=0;
        for(int i=0;i<classinfo.vtable.size();i++)
        {
            if(funname==classinfo.vtable[i].funname)
            {
                //不会重名，第一个就是
                Location *pfun;
                pfun = new Location(0,atemp());
                functy_code.push_back(new Load(pfun,pvtable,cont));

                Location *pdst;
                pdst = new Location(0,atemp());
				pacall = new ACall(pdst,pfun);
				functy_code.push_back(pacall);
				//我可以在这里处理参数
 				if(save_act.size()!=0)
    			{
        			//逆序压入实参,后面入this
			        for(int i=save_act.size()-1;i>=0;i--)
        			{
            			//p=(*pactuals)[i]->gentac_stmt(functy_code);
            			(pacall->vec_param).push_back(new PushParam(save_act[i]));
        			}
    			}
				(pacall->vec_param).push_back(new PushParam(pobj));
                return pdst;
            }
            cont+=4;
        }
    }
    return NULL;
}
Location* ReadInteger::gentac_stmt(vector<Instruction*> &functy_code)
{
    //没有参数,vec_param为空
    Location *p;
    p = new Location(0,atemp());
    functy_code.push_back(new LCall(p,"_ReadInteger"));
    return p;
}
Location* ReadLine::gentac_stmt(vector<Instruction*> &functy_code)
{
    //应该有一个参数
    Location *p;
    p = new Location(0,atemp());
	
	Location *buffer;
	buffer = new Location(0,atemp());
	
	
	LCall *plcall;
	plcall = new LCall(p,"_ReadLine");
	(plcall->vec_param).push_back(new PushParam(buffer));
    functy_code.push_back(plcall);
    return p;
}
Location* Instanceof::gentac_stmt(vector<Instruction*> &functy_code)
{
    
    return NULL;
}
Location* NewExpr::gentac_stmt(vector<Instruction*> &functy_code)
{
    // new A();
    //只要知道类的名字即可，可由pid得到
    //无形参
    Location *p;
    p = new Location(0,atemp());
	
	ACall *pacall;
	pacall = new ACall(p,NULL,pid->getidname());
	//pacall->functy_name = pid->getidname();
    functy_code.push_back(pacall);
    return p;
}
Location* NewArrayExpr::gentac_stmt(vector<Instruction*> &functy_code)
{
    //这里只支持一维数组
    //因为所有的类型都是4个字节，所ptype不再重要
    if(pexpr!=NULL)
    {
        Location *psrc1,*psrc2,*pdst1,*pdst2;
        psrc1 = pexpr->gentac_stmt(functy_code);
        //计算空间
        psrc2 = new Location(0,atemp());
        functy_code.push_back(new LoadConstant(psrc2,4));
        pdst1 = new Location(0,atemp());
        functy_code.push_back(new BinaryOp("*",pdst1,psrc1,psrc2));
        //使用alloc分配空间
        //有参数
        pdst2 = new Location(0,atemp());
		LCall *plcall;
		plcall = new LCall(pdst2,"_alloc");
		//alloc的参数
		(plcall->vec_param).push_back(new PushParam(pdst1));
        functy_code.push_back(plcall);
        return pdst2;
    }
    return NULL;
}

//load constant
Location* IntCon::gentac_stmt(vector<Instruction*> &functy_code)
{
    Location *p;
    p=new Location(0,atemp());
    functy_code.push_back(new LoadConstant(p,value));
	//cout<<value<<endl;
    return p;
}
Location* BoolCon::gentac_stmt(vector<Instruction*> &functy_code)
{
    Location *p;
    p=new Location(0,atemp());
    functy_code.push_back(new LoadConstant(p,value));
    return p;
}
Location* StringCon::gentac_stmt(vector<Instruction*> &functy_code)
{
    Location *p;
    p=new Location(0,atemp());
    functy_code.push_back(new LoadStringConstant(p,value));
    return p;
}
Location* NullCon::gentac_stmt(vector<Instruction*> &functy_code)
{
    Location *p;
    p=new Location(0,atemp());
    functy_code.push_back(new LoadConstant(p,value));
    return p;
}
/////////////////////////
Location::Location(int off,string name)
{
    variableName=name;
    offset=off;
}
string Location::GetName()
{
    return variableName;
}
int Location::GetOffset()
{
    return offset;
}
Instruction::Instruction()
{
    printed="";
}
void Instruction::backpatch(string str)
{
    //nothing to do
}
SaveFormal::SaveFormal(Location *s1)
{
    if(s1==NULL)
    {
        cout<<"error"<<endl;
        return ;
    }
    dst=s1;
    //
    printed=dst->GetName()+":"+ntos(dst->GetOffset());
}
LoadConstant::LoadConstant(Location *s1,int s2)
{
    if(s1==NULL)
    {
        cout<<"error"<<endl;
        return ;
    } 
    dst=s1;
    val=s2;
    //打印
    printed=dst->GetName()+"="+ntos(val);
	//cout<<printed<<endl;
}
LoadStringConstant::LoadStringConstant(Location *s1,string s2)
{
    if(s1==NULL)
    {
        cout<<"error"<<endl;
        return ;
    } 

    dst=s1;
    str=s2;
    //
    printed=dst->GetName()+"="+str;
}
Assign::Assign(Location *s1,Location *s2)
{
    if(s1==NULL||s2==NULL)
    {
        cout<<"error"<<endl;
        return ;
    } 
    dst=s1;
    src=s2;
    //
    printed=dst->GetName()+"="+src->GetName();
}
Load::Load(Location* s1,Location *s2,int s3)
{
    if(s1==NULL||s2==NULL)
    {
        cout<<"error"<<endl;
        return ;
    } 
    dst=s1;
    src=s2;
    offset=s3;
    //如果offset为0，就加0
    printed=dst->GetName()+"="+"*("+src->GetName()+"+"+ntos(offset)+")";
}
Store::Store(Location *s1,Location *s2,int s3)
{ 
    if(s1==NULL||s2==NULL)
    {
        cout<<"error"<<endl;
        return ;
    }
    dst=s1;
    src=s2;
    offset=s3;
    //如果offset为0，就加0
    printed="*("+dst->GetName()+"+"+ntos(offset)+")="+src->GetName(); 
}
BinaryOp::BinaryOp(string s1,Location *s2,Location *s3,Location *s4)
{
    if(s2==NULL||s3==NULL||s4==NULL)
    {
        cout<<"error"<<endl;
        return ;
    }
    dst=s2;
    op1=s3;
    op2=s4;
    op=s1;
    printed=dst->GetName()+"="+op1->GetName()+op+op2->GetName();
}
Label::Label(string s1)
{
    label=s1;
    printed=s1+":";
}
Goto::Goto(string s1)
{
    label=s1;
    printed="Goto "+label;
}
IfZ::IfZ(Location *s1,string s2)
{  
    if(s1==NULL)
    {
        cout<<"error"<<endl;
        return ;
    }
    test=s1;
    label=s2;
    printed="IfZ "+test->GetName()+" Goto "+label;
}
void IfZ::backpatch(string str)
{
    if(label=="")
	{
    	label=str;
		printed="IfZ "+test->GetName()+" Goto "+label;
	}	
}
BeginFunc::BeginFunc()
{
    
}
Return::Return(Location *s1)
{  
    //可以返回空
    val=s1;
    if(val!=NULL)
        printed="Return "+val->GetName();
    else
        printed="Return ";
}
PushParam::PushParam(Location *s1)
{ 
    if(s1==NULL)
    {
        cout<<"error"<<endl;
        return ;
    }
    param=s1;
    printed="PushParam "+param->GetName();
}
PopParams::PopParams(int s1)
{
    numBytes=s1;
    printed="PopParams "+ntos(numBytes);
}
LCall::LCall(Location* s1,string s2)
{
    //dst可以为空
    label=s2;
    dst=s1;
    //所有函数后没有括号，传参用push
    if(dst!=NULL)
        printed=dst->GetName()+"=LCall "+label;
    else
        printed="LCall "+label;
}
ACall::ACall(Location *s1,Location *s2,string funname)
{
	functy_name = funname;
    //dst可以为空
    dst=s1;
    methodAddr=s2;
	
    if(dst!=NULL)
	{
		if(methodAddr!=NULL)
	        printed=dst->GetName()+"=ACall "+methodAddr->GetName();
		else
			printed=dst->GetName()+"=ACall "+"_"+functy_name+"_0";
	}
    else
	{
		if(methodAddr!=NULL)
        	printed="ACall "+methodAddr->GetName();
		else
			printed="ACall _"+functy_name+"_0";
	}
}
Vtable::Vtable(string s1,Location *s2)
{
    if(s2==NULL)
    {
        cout<<"error"<<endl;
        return ;
    }
    classname=s1;
    dst=s2;
    printed=dst->GetName()+"=VTBL<"+classname+">";
}
Break::Break(string str)
{
    label=str;
    printed="Goto "+label;
}
void Break::backpatch(string str)
{
    if(label=="")  //为空才回填
	{
        label=str;
		printed="Goto "+label;
	}
}
SaveVar::SaveVar(Scope *s1,string s2)
{
    pscope=s1;
    varname=s2;
}

