/*************************************************************************
	> File Name: nt_buildsym.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 29 Nov 2016 07:23:43 PM PST
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <string>
#include <stack>
#include <vector>
#include "nt_class.h"
#include "error.h"
#include "y.tab.h"
using namespace std;
//一些下面要用的函数
string Id::getidname()
{
    return name;
}

string Type::gettypename()
{
    return _typename;
}

string Type::get_named_id_name()
{
	return 0;
}

Type* Type::get_type_pointer()
{
	return 0;
}

Id *Type::getpid()
{
    return 0;
}

//ArrayType
const Type* ArrayType::getPType()
{
    return ptype;
}
int ArrayType::getArrayLevel()
{
    level = 1;
    Type *type = this->ptype;
    while(type->getType() == DC_ARRAY)
    {
        level++;
        type = type->getPType()
    }
    return level;
}

void Program::buildSym()
{     
    for(int i=0; i<pvecClassDecl->size(); i++)
    {
        gloScope.addEntry((*pvecClassDecl)[i]->buildSym()); 
    }
}

void ClassDecl::buildSym()
{
    ClaDes *claDes = new ClaDes();
    if(pParentId==NULL)
    {
        //"" means it doesnot have parent
        claDes->setParentName("");
    }
    else
    {
        claDes->setParentName(pParentId.getidname());
    }
    if (pfields->size() != 0)
    {
        ClaScope *claScope = new claScope();
        for(int i=0; i<pfields->size(); i++)
        {
            claScope->addEntry((*pfields)[i]->buildSym());
        }
        claDes.setClaScope(claScope);
    }
    return new GloScopeEntry(pid->getidname(), claDes);
}

void VarDecl::buildSym()
{
    vector<ClaScope*> *pvec_clascope;
    pvec_clascope=(vector<ClaScope*>*)pst->top();

    string idname;
    idname = pid->getidname();

    //查看变量名与变量名是否重名，变量名与函数名是否重名
    for(int i=0;i<pvec_clascope->size();i++)
    {
        if(idname==(*pvec_clascope)[i]->getname())
        {
            IssueError::Redefinition(pid->getplocation(),idname);
            break;
        }
    }

    //查看类型

    string _typename;
    _typename=ptype->gettypename();
    TYPE *pscope_type;
    Type *p=ptype;      //多维数组使用
    if(_typename=="class")
    {
        string classidname;
        classidname=ptype->get_named_id_name();
        //先不对类是否存在进行检查,以后会做
	//下面获取基类名
	//1 pgloscope
    vector<GloScope*> *pvec_gloscope;
	ClaDes *pclades;
	pvec_gloscope = (vector<GloScope*>*)pgloscope->getparent();
	//0
	int flag=1; //类不存在标志
	for(int i=0;i<pvec_gloscope->size();i++)
	{//类名不会重名，找到第一个就是
	    if((*pvec_gloscope)[i]->getname()==classidname)
	    {
		flag=0;
		pclades=(*pvec_gloscope)[i]->getpclades();
		break;
	    }
	}
	string base_name;
	if(flag==0)
	    base_name = pclades->getparentname();
	else
	    base_name = "";
        pscope_type=new TYPE(_typename,classidname,0,base_name);    
        
    }
    else if(_typename=="[]")
    {//数组类型：子对象给父对象赋值已实现
        //数组层数
        int arraylevel=0;
        
        while(p->gettypename()=="[]")
        {
            arraylevel+=1;
            p=p->get_type_pointer();
        }
        string arraytype;
        if(p->gettypename()=="class")
            arraytype=p->get_named_id_name();
        else
            arraytype = p->gettypename();

        pscope_type=new TYPE(_typename,arraytype,arraylevel);
    }
    else
    {
        pscope_type=new TYPE(_typename,"",0);
    }

    ClaScope *pclascope;
    pscope_type->setplocation(pid->getplocation());
    pclascope = new ClaScope(idname,"variable",pscope_type,NULL);
    
    //设置parent
    //pst->pop();
    //vector<Scope*> *tmp=pst->top();
    //pst->push((vector<Scope*>*)pvec_clascope);
    pclascope->setparent((vector<Scope*>*)pgloscope,2);
    //设置location
    pclascope->setlocation(pid->getplocation());
    //入栈
	//设置id的scope
	pid->setpscope((Scope*)pclascope);
    pvec_clascope->push_back(pclascope);
    //检查类是否已定义
    if(_typename=="class")
    {
        Id *pid_tmp;
        pid_tmp=ptype->getpid();
        pid_tmp->checkdecl_class(pclascope);
    }
    else if(_typename=="[]")
    {
        Type *ptype_tmp;
        ptype_tmp=ptype->get_type_pointer();
        if(p->gettypename()=="class")
        {
            Id *pid_tmp;
            pid_tmp = ptype_tmp->getpid();
            pid_tmp->checkdecl_class(pclascope);        
        }
    }
}
void FnDecl::buildSym()
{
    ClaScopeEntry *claScopeEntry = new ClaScopeEntry();
    claScopeEntry->setCategory(DC_Fun);
    claScopeEntry->setName(pid->getidname());
    
    TypeInfo *typeInfo = new TypeInfo();
    typeInfo->setType(ptype->getType());
    switch(ptype->getType())
    {
        case(DC_NAMED):
            typeInfo->setClassName(ptype->getClassName());
            break;
        case(DC_ARRAY):
            typeInfo->setArrayLevel(ptype->getArrayLevel());
            break;
        default:
            break;
    }
    claScopeEntry->setTypeInfo(typeInfo);

    FunDes *pfundes;
    //形参域
    vector<ForScope*> *pvec_forscope;
    pvec_forscope = new vector<ForScope*>;
    if(idname=="main")
        pfundes = new FunDes(isstatic,1,pvec_forscope);
    else
        pfundes = new FunDes(isstatic,0,pvec_forscope);

    ClaScope *pclascope;
    pscope_type->setplocation(pid->getplocation());
    pclascope = new ClaScope(idname,"function",pscope_type,pfundes);

    //设置parent
    //pst->pop();
    //vector<Scope*> *tmp=pst->top();
    //pst->push((vector<Scope*>*)pvec_clascope);
    pclascope->setparent((vector<Scope*>*)pgloscope,2);
    //设置location
    pclascope->setlocation(pid->getplocation());
    //入栈
    pvec_clascope->push_back(pclascope);
    //类检查
    if(_typename=="class")
    {
        Id *pid_tmp;
        pid_tmp=ptype->getpid();
        pid_tmp->checkdecl_class(pclascope);
    }
    else if(_typename=="[]")
    {
        Type *ptype_tmp;
        ptype_tmp=ptype->get_type_pointer();
        if(p->gettypename()=="class")
        {
            Id *pid_tmp;
            pid_tmp = ptype_tmp->getpid();
            pid_tmp->checkdecl_class(pclascope);        
        }
    }

    pst->push((vector<Scope*>*)pvec_forscope);
    //局部域
    vector<LocScope*> *pvec_locscope;
    pvec_locscope = new vector<LocScope*>;

    //先把this指针加上,等一下再处理
    ForScope *pforscope;
    pforscope = new ForScope(string("this"),new TYPE(string("class"),string(""),0),pvec_locscope);

    pforscope->setparent((vector<Scope*>*)pvec_clascope,3);
    pvec_forscope->push_back(pforscope);

    for(int i=0;i<pformals->size();i++)
    {
        (*pformals)[i]->buildformals(pst,pvec_locscope,pvec_clascope);
    }
    
    pst->push((vector<Scope*>*)pvec_locscope);
    pstmtblock->buildlocal(pvec_locscope,(vector<Scope*>*)pvec_forscope);  //从0开始
    //这里checkbreak,会导致错误的行序号不是递增的
    pstmtblock->stmt_checkbreak();
    pst->pop();
    pst->pop();
}

void VarDecl::buildformals(stack<vector<Scope*>*> *pst,vector<LocScope*> *pvec_locscope,vector<ClaScope*>* pvec_clascope)
{
//cout<<"formal"<<endl;
    vector<ForScope*> *pvec_forscope;
    pvec_forscope = (vector<ForScope*>*)pst->top();
    
    string idname;
    idname = pid->getidname();
    //检查形参是否重名
    for(int i=0;i<pvec_forscope->size();i++)
    {
        if(idname==(*pvec_forscope)[i]->getname())
        { 
            IssueError::Redefinition(pid->getplocation(),idname);
            break; 
        }
    }
    //查看类型,这个有点重复
    string _typename;
    _typename=ptype->gettypename();
    TYPE *pscope_type;
    Type *p=ptype;
    if(_typename=="class")
    {
        string classidname;
        classidname=ptype->get_named_id_name();
        //先不对类是否存在进行检查
        pscope_type=new TYPE(_typename,classidname,0);    
    }
    else if(_typename=="[]")
    {
        //数组层数
        int arraylevel=0;
        
        while(p->gettypename()=="[]")
        {
            arraylevel+=1;
            p=p->get_type_pointer();
        }
        string arraytype;
        if(p->gettypename()=="class")
            arraytype=p->get_named_id_name();
        else
            arraytype = p->gettypename();

        pscope_type=new TYPE(_typename,arraytype,arraylevel);
    }
    else
    {
        pscope_type=new TYPE(_typename,"",0);
    }
    
    ForScope *pforscope;
    pscope_type->setplocation(pid->getplocation());
    pforscope = new ForScope(idname,pscope_type,pvec_locscope);
    //设置parent
    //pst->pop();
    //vector<Scope*> *tmp=pst->top();
    //pst->push((vector<Scope*>*)pvec_forscope);
    pforscope->setparent((vector<Scope*>*)pvec_clascope,3);
    //设置location
    pforscope->setlocation(pid->getplocation());
	//设置pscope
	pid->setpscope((Scope*)pforscope);
	//入栈
    pvec_forscope->push_back(pforscope);
    //类检查
    if(_typename=="class")
    {
        Id *pid_tmp;
        pid_tmp=ptype->getpid();
        pid_tmp->checkdecl_class(pforscope);
    }
    else if(_typename=="[]")
    {
        Type *ptype_tmp;
        ptype_tmp=ptype->get_type_pointer();
        if(p->gettypename()=="class")
        {
            Id *pid_tmp;
            pid_tmp = ptype_tmp->getpid();
            pid_tmp->checkdecl_class(pforscope);        
        }
    }
}
void VarDecl::buildlocal(vector<LocScope*> *pvec_locscope,vector<vector<LocScope*>*> *pvecvec_locscope,vector<Scope*> *pvec_for_loc_scope)
{
//cout<<"local"<<endl;
    string idname;
    idname = pid->getidname();

    //查看局部作用域里是否重名
    for(int i=0;i<pvec_locscope->size();i++)
    {
        if(idname==(*pvec_locscope)[i]->getname())
        {
            IssueError::Redefinition(pid->getplocation(),idname);
            break;
        }
    }

    //查看类型

    string _typename;
    _typename=ptype->gettypename();
    TYPE *pscope_type;
    Type *p=ptype;
    if(_typename=="class")
    {
        string classidname;
        classidname=ptype->get_named_id_name();
        //先不对类是否存在进行检查
	//找到基类名
	vector<Scope*> *pvec_scope;
	pvec_scope=pvec_for_loc_scope;
	//担心(*pvec_scope)[0]是空的,先用pvec_for_loc_scope判断
	if((*pvec_for_loc_scope)[0]->getscopenum()==4)
	{
	    do
	    {
	        pvec_scope=(*pvec_scope)[0]->getparent();
	    }while((*pvec_scope)[0]->getscopenum()==4);
	}
	//3
	pvec_scope=(*pvec_scope)[0]->getparent();
	//2
	GloScope *pgloscope;
	ClaDes *pclades;
	//1
	pgloscope=(GloScope*)(*pvec_scope)[0]->getparent();
	//0
	vector<GloScope*> *pvec_gloscope;
	pvec_gloscope = (vector<GloScope*>*)pgloscope->getparent();
	//找类	
	int flag=1; //类不存在标志
	for(int i=0;i<pvec_gloscope->size();i++)
	{//类名不会重名，找到第一个就是
	    if((*pvec_gloscope)[i]->getname()==classidname)
	    {
		flag=0;
		pclades=(*pvec_gloscope)[i]->getpclades();
		break;
	    }
	}
	string base_name;
	if(flag==0)
	    base_name = pclades->getparentname();
	else
	    base_name = "";
        pscope_type=new TYPE(_typename,classidname,0,base_name); 
    }
    else if(_typename=="[]")
    {
        //数组层数
        int arraylevel=0;
        
        while(p->gettypename()=="[]")
        {
            arraylevel+=1;
            p=p->get_type_pointer();
        }
        string arraytype;
        if(p->gettypename()=="class")
        arraytype=p->get_named_id_name();
        else
            arraytype = p->gettypename();

        pscope_type=new TYPE(_typename,arraytype,arraylevel);
    }
    else
    {
        pscope_type=new TYPE(_typename,"",0);
    }

    LocScope *plocscope;
    pscope_type->setplocation(pid->getplocation());
    plocscope=new LocScope(idname,"variable",pscope_type,pvecvec_locscope);
    //设置parent
    plocscope->setparent(pvec_for_loc_scope,4);
    //设置location
    plocscope->setlocation(pid->getplocation());
    //入栈
    pvec_locscope->push_back(plocscope);
    //类检查，这个比较重复
    if(_typename=="class")
    {
        Id *pid_tmp;
        pid_tmp=ptype->getpid();
        pid_tmp->checkdecl_class(plocscope);
    }
    else if(_typename=="[]")
    {
        Type *ptype_tmp;
        ptype_tmp=ptype->get_type_pointer();
        if(p->gettypename()=="class")
        {
            Id *pid_tmp;
            pid_tmp = ptype_tmp->getpid();
            pid_tmp->checkdecl_class(plocscope);        
        }
    }
}
void Stmt::buildlocal(vector<LocScope*> *pvec_locscope,vector<Scope*> *pvec_for_loc_scope)
{

}
void StmtBlock::buildlocal(vector<LocScope*> *pvec_locscope,vector<Scope*> *pvec_for_loc_scope)
{
//cout<<"stmtblock"<<endl;
    vector<vector<LocScope*>*> *pvecvec_locscope;
    pvecvec_locscope = new vector<vector<LocScope*>*>;

    //先做vardecls，方便变量是否定义的检查，可能代码会比较繁琐
    if(pstmts!=NULL)
    for(int i=0;i<pstmts->size();i++)
    {
        vector<LocScope*> *pvec_locscope_ano;
        pvec_locscope_ano = new vector<LocScope*>;
        pvecvec_locscope->push_back(pvec_locscope_ano);
    }
    //vardecls
    if(pvardecls!=NULL)
    {
        for(int i=0;i<pvardecls->size();i++)
        {
            
            (*pvardecls)[i]->buildlocal(pvec_locscope,pvecvec_locscope,pvec_for_loc_scope);
        }
    }
    if(pvardecls==NULL)
    {  
        //保存一个空项，用来指向下一个局部作用域
        LocScope *plocscope;
        plocscope=new LocScope("","",NULL,pvecvec_locscope); 
        plocscope->setparent(pvec_for_loc_scope,4);
        pvec_locscope->push_back(plocscope);
    }
    //stmt
    if(pstmts!=NULL)
    for(int i=0;i<pstmts->size();i++)
    {
        //第一遍
        //在每个语句中，检查变量的使用前是否定义
        (*pstmts)[i]->checkdecl_var((vector<Scope*>*)pvec_locscope);
        //第二遍
        //检查类型一致
        (*pstmts)[i]->checktype();
        //    
        //创建符号表
        (*pstmts)[i]->buildlocal((*pvecvec_locscope)[i],(vector<Scope*>*)pvec_locscope);
    }
}
void IfStmt::buildlocal(vector<LocScope*> *pvec_locscope,vector<Scope*> *pvec_for_loc_scope)
{
    vector<vector<LocScope*>*> *pvecvec_locscope;
    pvecvec_locscope = new vector<vector<LocScope*>*>;
    
    vector<LocScope*> *pvec_locscope_ano1,*pvec_locscope_ano2;
    if(pstmt1!=NULL)
    {
        pvec_locscope_ano1 = new vector<LocScope*>;
        pvecvec_locscope->push_back(pvec_locscope_ano1);
    }
    if(pstmt2!=NULL)
    {
    	pvec_locscope_ano2 = new vector<LocScope*>;
        pvecvec_locscope->push_back(pvec_locscope_ano2);
    }
    //保存一个空项，用来指向下一个局部作用域
    LocScope *plocscope;
    plocscope=new LocScope("","",NULL,pvecvec_locscope); 
    plocscope->setparent(pvec_for_loc_scope,4);
    pvec_locscope->push_back(plocscope);
    //stmt
    if(pstmt1!=NULL)
    {
        pstmt1->buildlocal(pvec_locscope_ano1,pvec_for_loc_scope);
    }
    if(pstmt2!=NULL)
    {
    	pstmt2->buildlocal(pvec_locscope_ano2,(vector<Scope*>*)pvec_locscope);
    }
}
void WhileStmt::buildlocal(vector<LocScope*> *pvec_locscope,vector<Scope*> *pvec_for_loc_scope)
{
    vector<vector<LocScope*>*> *pvecvec_locscope;
    pvecvec_locscope = new vector<vector<LocScope*>*>;

    vector<LocScope*> *pvec_locscope_ano1;
    pvec_locscope_ano1 = new vector<LocScope*>; 
    pvecvec_locscope->push_back(pvec_locscope_ano1);
    //保存一个空项，用来指向下一个局部作用域
    LocScope *plocscope;
    plocscope=new LocScope("","",NULL,pvecvec_locscope); 
    plocscope->setparent(pvec_for_loc_scope,4);
    pvec_locscope->push_back(plocscope);
    //Stmt    
    pstmt->buildlocal(pvec_locscope_ano1,pvec_for_loc_scope);
}
void ForStmt::buildlocal(vector<LocScope*> *pvec_locscope,vector<Scope*>* pvec_for_loc_scope)
{
    vector<vector<LocScope*>*> *pvecvec_locscope;
    pvecvec_locscope = new vector<vector<LocScope*>*>;
   
    vector<LocScope*> *pvec_locscope_ano1;
    pvec_locscope_ano1 = new vector<LocScope*>;
    pvecvec_locscope->push_back(pvec_locscope_ano1);
    //保存一个空项，用来指向下一个局部作用域
    LocScope *plocscope;
    plocscope=new LocScope("","",NULL,pvecvec_locscope);
    plocscope->setparent(pvec_for_loc_scope,4);
    pvec_locscope->push_back(plocscope);
    //Stmt
    pstmt->buildlocal(pvec_locscope_ano1,pvec_for_loc_scope);
}

