/*************************************************************************
	> File Name: nt_check.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年12月06日 星期二 18时39分03秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<string>
#include "nt_class.h"
#include "nt_buildsym.h"
#include "error.h"
using namespace std;
//checkdecl
Scope* Id::getpscope()
{
    return pscope;
}
void Id::checkdecl_class(Scope *pscope)
{
    string basename=name;
    string thisname;
    vector<Scope*> *pvec_scope;
    //GloScope *pgloscope;
    int num=pscope->getscopenum();


    switch(num)
    {
        case 1:
        {
            thisname=((GloScope*)pscope)->getname();
            pvec_scope=pscope->getparent();
            break;
        }
        case 2:
        {
            pscope=(GloScope*)pscope->getparent();
            thisname=((GloScope*)pscope)->getname();
            pvec_scope=pscope->getparent();
            break;
        }
        case 3:
        {
            pvec_scope=pscope->getparent();
            pscope=(GloScope*)(*pvec_scope)[0]->getparent();
            thisname=((GloScope*)pscope)->getname();
            pvec_scope=pscope->getparent();
            break;
        }
        case 4:
        {
            do
            {
                pvec_scope=pscope->getparent();
                pscope=(Scope*)(*pvec_scope)[0];
                num=pscope->getscopenum();
            }while(num==4);
            pvec_scope=pscope->getparent();
            pscope=(GloScope*)(*pvec_scope)[0]->getparent();
            thisname=((GloScope*)pscope)->getname();
            pvec_scope=pscope->getparent();
            break;
        }
    }
    //查找类
    vector<GloScope*> *pvec_gloscope;
    pvec_gloscope=(vector<GloScope*>*)pvec_scope;
    for(int i=0;i<pvec_gloscope->size();i++)
    {
        if((*pvec_gloscope)[i]->getname()==basename&&basename!=thisname)
            return;
    }   
    IssueError::UnDefined(plocation,basename);
}

void Id::checkdecl_var(vector<Scope*> *pvec_scope)
{//找到变量定义的位置后，用pscope指向它，方便检查type

 //4,不能内嵌函数，所以遇到同名即找到，有嵌套，也要检查
    do
    {
        for(int i=0;i<pvec_scope->size();i++)
        {
            if(name==(*pvec_scope)[i]->getname())
            {
                pscope = (*pvec_scope)[i];
                pscope->getptype();
                return;
            }
        }
        pvec_scope=(*pvec_scope)[0]->getparent();

    }while((*pvec_scope)[0]->getscopenum()==4);
    //3 形参名
    for(int i=0;i<pvec_scope->size();i++)
    {
        if(name==(*pvec_scope)[i]->getname())
        {
            pscope = (*pvec_scope)[i];
            return;
        }
    }
    pvec_scope=(*pvec_scope)[0]->getparent();
    //2
    for(int i=0;i<pvec_scope->size();i++)
    {
       if((name==(*pvec_scope)[i]->getname())&&(((ClaScope*)((*pvec_scope)[0]))->getcategory()=="variable"))
        {
			
            pscope = (*pvec_scope)[i];
			//cout<<name<<' '<<pscope<<endl;
            return;
        }
    
    }
    //1 第一层是类，不会在这一层中找到id
    
    //如果在自己的类中找不到function，在其基类第二层中寻找
    //指向这个类的指针
    GloScope *pgloscope;
    ClaDes *pclades;
    pgloscope = (GloScope*)(*pvec_scope)[0]->getparent();
    pclades = pgloscope->getpclades();
    //基类
    if(pclades->getparent()!=NULL) //没有基类
    {
        ClaDes *base_pclades;
        base_pclades = pclades->getparent();
        vector<ClaScope*> *pvec_clascope;
        pvec_clascope = base_pclades->get_pvec_clascope();
        for(int i=0;i<pvec_clascope->size();i++)
        {  
            if((name==(*pvec_clascope)[i]->getname())&&(((ClaScope*)((*pvec_clascope)[0]))->getcategory()=="variable"))
            {
                pscope = (*pvec_clascope)[i];
                return;
            }
        }
            
    }
    //打印错误，暂不支持声明，所以找不到即是未定义
    IssueError::UnDefined(plocation,name);
}
void Id::checkdecl_fun(vector<Scope*> *pvec_scope)
{//fun只能在2或基类的2中找到。至于支不支持递归，这里暂时支持
 //某个类的对象调用函数是无法检查的，只能检查fun(Actuals) 
    do
    {
        pvec_scope=(*pvec_scope)[0]->getparent();

    }while((*pvec_scope)[0]->getscopenum()==4);
    //3 形参名
    pvec_scope=(*pvec_scope)[0]->getparent();
    //2
    for(int i=0;i<pvec_scope->size();i++)
    {
        if((name==(*pvec_scope)[i]->getname())&&(((ClaScope*)((*pvec_scope)[0]))->getcategory()=="function"))
        {
            pscope = (*pvec_scope)[i];
            return;
        }
    }
    //如果在自己的类中找不到function，在其基类第二层中寻找
    //指向这个类的指针
    GloScope *pgloscope;
    ClaDes *pclades;
    pgloscope = (GloScope*)(*pvec_scope)[0]->getparent();
    pclades = pgloscope->getpclades();
    //基类
    if(pclades->getparent()!=NULL)
    {
        ClaDes *base_pclades;
        base_pclades = pclades->getparent();
        //cout<<base_pclades->getparentname()<<endl;

        vector<ClaScope*> *pvec_clascope;
        pvec_clascope = base_pclades->get_pvec_clascope();

        for(int i=0;i<pvec_clascope->size();i++)
        {
            if((name==(*pvec_clascope)[i]->getname())&&(((ClaScope*)((*pvec_clascope)[i]))->getcategory()=="function"))
            {
                pscope = (*pvec_clascope)[i];
                return;
            }
        }        
    }
    //打印错误，暂不支持声明，所以找不到即是未定义
    IssueError::UnDefined(plocation,name);
}

void Stmt::checkdecl_var(vector<Scope*>* pvec_scope)
{
   //nothing to to 
}

void IfStmt::checkdecl_var(vector<Scope*>* pvec_scope)
{
    pexpr->checkdecl_var(pvec_scope);
    if(pstmt1!=NULL)
        pstmt1->checkdecl_var(pvec_scope);
    if(pstmt2!=NULL)
        pstmt2->checkdecl_var(pvec_scope);
}
void WhileStmt::checkdecl_var(vector<Scope*>* pvec_scope)
{
    pexpr->checkdecl_var(pvec_scope);
    if(pstmt!=NULL)
        pstmt->checkdecl_var(pvec_scope);
}
void ForStmt::checkdecl_var(vector<Scope*>* pvec_scope)
{
    if(poptexpr1!=NULL)
        poptexpr1->checkdecl_var(pvec_scope);
    pexpr->checkdecl_var(pvec_scope);
    if(poptexpr2!=NULL)
        poptexpr2->checkdecl_var(pvec_scope);
    if(pstmt!=NULL)
        pstmt->checkdecl_var(pvec_scope);
}
void BreakStmt::checkdecl_var(vector<Scope*>* pvec_scope)
{
    //nothing to do really   
}
void ReturnStmt::checkdecl_var(vector<Scope*>* pvec_scope)
{//return返回类型在这里检查
 //其中不写return语句在任何情况下都对
    if(poptexpr!=NULL)
        poptexpr->checkdecl_var(pvec_scope);
    //下面检查return返回类型和函数定义的是否一致
    //包括void
    TYPE *p,*pfuntype;
    if(poptexpr!=NULL)
        p=poptexpr->checktype();
    else
        p=NULL;
    //获取返回类型
    do
    {
        pvec_scope=(*pvec_scope)[0]->getparent();
    }while((*pvec_scope)[0]->getscopenum()==4);
    //3 形参名
    pvec_scope=(*pvec_scope)[0]->getparent();
    //2 要找的函数一定是最后进入vector的那个size（）-1
    pfuntype = (*pvec_scope)[pvec_scope->size()-1]->getptype();
    string str;
    str="return type doesn't match.it should be "+pfuntype->gettypename();
    
    if(p!=NULL)
    {//类型不匹配
        if(p->gettypename()!=pfuntype->gettypename())
        {//这里包含没有返回值
            p->getplocation();
            IssueError::Dir_typeerror(p->getplocation(),str,p->gettypename());
            return ;
        }
    }
    else
    {//有无返回值
        if(pfuntype->gettypename()!="void")
        {//这里包含有返回值，而没去返回
            str="it is no return value.";
            IssueError::Dir_typeerror(plocation,str,"");
            return ;   
        }
    }
    //查看class和数组的类型是否匹配
    if(p!=NULL)
    if((p->gettypename()=="[]"||p->gettypename()=="class")&&(p->get_class_arraytypename()!=pfuntype->get_class_arraytypename()))
    {//这里也没有支持子给父赋值
        if(p->gettypename()=="[]")
        {
            str="return type does't match.it should be "+pfuntype->get_class_arraytypename()+" array,not "+p->get_class_arraytypename()+" array.";
            IssueError::Dir_typeerror(p->getplocation(),str,"");
        }
        else
        {
            str="return type does't match.it should be a "+pfuntype->get_class_arraytypename()+" object,not a "+p->get_class_arraytypename()+" object";
            IssueError::Dir_typeerror(p->getplocation(),str,"");
        }
        return ;
    }
}
void PrintStmt::checkdecl_var(vector<Scope*>* pvec_scope)
{
    if(pexprs!=NULL) //先判断一下
    for(int i=0;i<pexprs->size();i++)
        (*pexprs)[i]->checkdecl_var(pvec_scope);
}
void StmtBlock::checkdecl_var(vector<Scope*>* pvec_scope)
{//因为什么也不做，到这里就停止，所以checkdecl的方法是正确的
 //checktype也能用这种方法，在stmtblocks时什么也不做
    //nothing to do
    //because new var will be declared in this place
    //cout<<"StmtBlock"<<endl;
}
void Expr::checkdecl_var(vector<Scope*>* pvec_scope)
{
    //nothing to do
    
}
void AssignExpr::checkdecl_var(vector<Scope*>* pvec_scope)
{
    if(plvalue!=NULL)
        plvalue->checkdecl_var(pvec_scope);
    if(pexpr!=NULL)
        pexpr->checkdecl_var(pvec_scope);
}
void ArithmeticExpr::checkdecl_var(vector<Scope*>* pvec_scope)
{
    if(pexpr1!=NULL)
        pexpr1->checkdecl_var(pvec_scope);
    if(pexpr2!=NULL)
        pexpr2->checkdecl_var(pvec_scope);
}
void RelationExpr::checkdecl_var(vector<Scope*>* pvec_scope)
{
    if(pexpr1!=NULL)
        pexpr1->checkdecl_var(pvec_scope);
    if(pexpr2!=NULL)
        pexpr2->checkdecl_var(pvec_scope);
}
void LogicalExpr::checkdecl_var(vector<Scope*>* pvec_scope)
{
    if(pexpr1!=NULL)
        pexpr1->checkdecl_var(pvec_scope);
    if(pexpr2!=NULL)
        pexpr2->checkdecl_var(pvec_scope); 
}
void Lvalue::checkdecl_var(vector<Scope*>* pvec_scope)
{
    //nothing to do
}
void FieldAccess::checkdecl_var(vector<Scope*>* pvec_scope)
{
    if(pexpr!=NULL)
        pexpr->checkdecl_var(pvec_scope);
    if(pid!=NULL)
        pid->checkdecl_var(pvec_scope);
}
void ArrayAccess::checkdecl_var(vector<Scope*>* pvec_scope)
{
    if(pexpr1!=NULL)
        pexpr1->checkdecl_var(pvec_scope);
    if(pexpr2!=NULL)
        pexpr2->checkdecl_var(pvec_scope);
}
void Call::checkdecl_var(vector<Scope*>* pvec_scope)
{//在这里可以检查类中是否有这个方法
    if(pid!=NULL)
    {
        if(pexpr==NULL)
            pid->checkdecl_fun(pvec_scope);
        else
        {
            pexpr->checkdecl_var(pvec_scope);
            string classname;
            TYPE *p;
            p=pexpr->checktype();
            if(p!=NULL)
            {
            if(p->gettypename()!="class")
            {//不是class类型
                IssueError::Dir_typeerror(p->getplocation(),"illegal use of '.',it should be class type.",p->gettypename());
            }
            else
            {//检查class是否有这个方法
                classname = p->get_class_arraytypename();
                do
                {
                    pvec_scope=(*pvec_scope)[0]->getparent();

                }while((*pvec_scope)[0]->getscopenum()==4);
                //3 形参名
                pvec_scope=(*pvec_scope)[0]->getparent();
                //2
                GloScope *pgloscope;
                pgloscope = (GloScope*)(*pvec_scope)[0]->getparent();
                //1
                vector<GloScope*> *pvec_gloscope;
                pvec_gloscope = (vector<GloScope*>*)pgloscope->getparent();
                //0
                ClaDes *pclades;
                vector<ClaScope*> *pvec_clascope;
                int flag=1;
                for(int i=0;i<pvec_gloscope->size();i++)
                {
                    if((*pvec_gloscope)[i]->getname()==classname)
                    {
                        pclades = (*pvec_gloscope)[i]->getpclades();
                        //先访问自己的方法
                        pvec_clascope = pclades->get_pvec_clascope();
                        for(int j=0;j<(pvec_clascope)->size();j++)
                        {
                            if((*pvec_clascope)[j]->getname()==pid->getidname()&&(*pvec_clascope)[j]->getcategory()=="function")
                            {//找到，因为不支持重载，第一次找到即是
                                flag=0;
                                //设置pid->Scope
                                pid->pscope=(*pvec_clascope)[j];
                                break;
                            }
                        }
                        if(flag)
                        {
                            if(pclades->getparent()!=NULL)
                            {//继承
                                pclades = pclades->getparent();
                                pvec_clascope = pclades->get_pvec_clascope();
                                for(int j=0;j<(pvec_clascope)->size();j++)
                                {
                                    if((*pvec_clascope)[j]->getname()==pid->getidname()&&(*pvec_clascope)[j]->getcategory()=="function")
                                    {//找到，因为不支持重载，第一次找到即是
                                        flag=0;
                                        pid->pscope=(*pvec_clascope)[j];
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                if(flag==1)
                {
                    string str;
                    str=classname +" doesn't have the member of "+pid->getidname();
                    IssueError::Dir_typeerror(pid->getplocation(),str,"");
                }
            }}
    }   }
    //cout<<"end"<<endl;
    if(pactuals!=NULL)
    for(int i=0;i<pactuals->size();i++)
        (*pactuals)[i]->checkdecl_var(pvec_scope);
}
void This::checkdecl_var(vector<Scope*>* pvec_scope)
{
    //nothing to do
}
void ReadInteger::checkdecl_var(vector<Scope*>* pvec_scope)
{
    //nothing to do
}
void ReadLine::checkdecl_var(vector<Scope*>* pvec_scope)
{
    //nothing to do
}
void Instanceof::checkdecl_var(vector<Scope*>* pvec_scope)
{//查看某个表达式的结果是否为某个类的对象
 //所以，pid是一个类的声明
    if(pexpr!=NULL)
        pexpr->checkdecl_var(pvec_scope);
    if(pid!=NULL) //因为要找的是类，所以可以用【0】
        pid->checkdecl_class((*pvec_scope)[0]);

}
void NewExpr::checkdecl_var(vector<Scope*>* pvec_scope)
{//用来声明一个新的对象实例
    if(pid!=NULL)
        pid->checkdecl_class((*pvec_scope)[0]);
}
void NewArrayExpr::checkdecl_var(vector<Scope*>* pvec_scope)
{

    string _typename;
    _typename = ptype->gettypename();
    if(_typename=="class")
    {
        Id *pid_tmp;
        pid_tmp=ptype->getpid();
        pid_tmp->checkdecl_class((*pvec_scope)[0]);
    }
    else if(_typename=="[]")
    {
        Type *ptype_tmp;
        ptype_tmp=ptype->get_type_pointer();
        Id *pid_tmp;
        pid_tmp=ptype_tmp->getpid();
        pid_tmp->checkdecl_class((*pvec_scope)[0]);
    }

    if(pexpr!=NULL)
        pexpr->checkdecl_var(pvec_scope);
}

//checktype
TYPE* Stmt::checktype()
{
    return NULL;
    //nothing to do
}
TYPE* StmtBlock::checktype()
{
    return NULL;
    //nothing to do
}
TYPE* IfStmt::checktype()
{
    if(pexpr!=NULL)
    {
        TYPE *type;
        type = pexpr->checktype();
        if(type!=NULL)
        if(type->gettypename()!="bool")
        {
            IssueError::Dir_typeerror(type->getplocation(),"it should be bool type in the () of if()",type->gettypename());
        }
    }
    if(pstmt1!=NULL)
        pstmt1->checktype();
    if(pstmt2!=NULL)
        pstmt2->checktype();
    return NULL;
}

TYPE* WhileStmt::checktype()
{
    if(pexpr!=NULL)
    {
        TYPE *type;
        type = pexpr->checktype();
        if(type!=NULL)
        if(type->gettypename()!="bool")
        {
            IssueError::Dir_typeerror(type->getplocation(),"it should be bool type in the () of while()",type->gettypename());
        }
    }
    if(pstmt)
        pstmt->checktype();
    return NULL;
}
TYPE* ForStmt::checktype()
{
    if(poptexpr1!=NULL)
    {
        TYPE *type;
        type = poptexpr1->checktype();
        if(type!=NULL)
        if(type->gettypename()!="int")
        { 
            IssueError::Dir_typeerror(type->getplocation(),"it should be int type in the () of for(();;)",type->gettypename());
            
        }
    }
    if(poptexpr2!=NULL)
    {
        TYPE *type;
        type = poptexpr2->checktype();
        if(type!=NULL)
        if(type->gettypename()!="int")
        {
            IssueError::Dir_typeerror(type->getplocation(),"it should be int type in the () of for(;;())",type->gettypename());

        }

    }
    if(pexpr!=NULL)
    {
        TYPE *type;
        type = pexpr->checktype();
        if(type!=NULL)
        if(type->gettypename()!="bool")
        {
            IssueError::Dir_typeerror(type->getplocation(),"it should be bool type in the () of for(;();)",type->gettypename());
        }
    }
    if(pstmt)
    {
        pstmt->checktype();
    }
    return NULL;
}
TYPE* ReturnStmt::checktype()
{
    //在checkdecl中实现
    return NULL;
}
TYPE* BreakStmt::checktype()
{
    //单独实现
    return NULL;
}
TYPE* PrintStmt::checktype()
{
    //还不知道怎么实现
    return NULL;
}
TYPE* Expr::checktype()
{
    //nothing
    return NULL;
}


TYPE* AssignExpr::checktype()
{
//cout<<"ass"<<endl;
    //检查等号左边的是左值表达式
    //这个不用检查，由lvalue可以保证
    TYPE *p1;
    p1=plvalue->checktype();
    //plvalue->checktype();
    TYPE *p2;
    p2=pexpr->checktype();
    //查看类型是否匹配
    if(p1!=NULL&&p2!=NULL)
    {
        if(p1->gettypename()!=p2->gettypename())
        {
            //NULL可以给所有的类对象赋值
            if(p1->gettypename()=="class"&&p2->gettypename()=="null")
                ;
            else
            {
                string str("the types of the two operands are different. ");
                str=str+"the first is "+p1->gettypename()+",the second is "+p2->gettypename();
                IssueError::Dir_typeerror(p1->getplocation(),str,"");
                return NULL;
            }
        }
        else if(p1->gettypename()=="[]")
        {
            if(p1->get_class_arraytypename()!=p2->get_class_arraytypename())
            {
                string str("the types of the two operands are different. ");
                str=str+"the first is array of "+p1->get_class_arraytypename()+",the second is array of"+p2->get_class_arraytypename();
                IssueError::Dir_typeerror(p1->getplocation(),str,"");
                return NULL;
            }
        }
        else if(p1->gettypename()=="class")
        {//实现子对象给父对象赋值
            if(p1->get_class_arraytypename()!=p2->getclass_base())
            {
                cout<<p1->get_class_arraytypename()<<endl;
                cout<<p2->getclass_base()<<endl;
                string str("the types of the two operands are different. ");
                str=str+"the first is array of "+p1->get_class_arraytypename()+",the second is array of "+p2->get_class_arraytypename();
                IssueError::Dir_typeerror(p1->getplocation(),str,"");
                return NULL;
            }

        }
        return p1;
    }
    else
    {
        return NULL;
    }
}
TYPE* ArithmeticExpr::checktype()
{//数学运算，都应该是int类型
    TYPE *p1;
    p1=pexpr1->checktype();
    TYPE *p2;
    p2=pexpr2->checktype();
    //查看类型是否匹配
    if(p1!=NULL&&p2!=NULL)
    {
        if(p1->gettypename()!="int"||p2->gettypename()!="int")
        {
            string str("the types of two operands should be int.");
            str=str+"but the types are "+p1->gettypename()+"and"+p2->gettypename();
            IssueError::Dir_typeerror(p1->getplocation(),str,"");
            //IssueError::
            return NULL;
        }
        return p1;
    }
    else
    {
        return NULL;
    }
    
}
TYPE *RelationExpr::checktype()
{//关系运算都是int类型
    TYPE *p1;
    p1=pexpr1->checktype();
    TYPE *p2;
    p2=pexpr2->checktype();
    //查看类型是否匹配
    if(p1!=NULL&&p2!=NULL)
    {
        if(p1->gettypename()!="int"||p2->gettypename()!="int")
        {
            //IssueError::
            string str("the types of two operands should be int.");
            str=str+"but the types are "+p1->gettypename()+"and"+p2->gettypename();
            IssueError::Dir_typeerror(p1->getplocation(),str,"");
            return NULL;
        }
        TYPE *p;
        p=new TYPE("bool","",0);
        p->setplocation(p1->plocation);
        return p;
    }
    else
    {
        return NULL; 
    }
}
TYPE* LogicalExpr::checktype()
{//逻辑运算都是bool
    TYPE *p1;
    p1=pexpr1->checktype();
    TYPE *p2;
    p2=pexpr2->checktype();
    //查看类型是否匹配
    if(p1!=NULL&&p2!=NULL)
    {
        if(p1->gettypename()!="bool"||p2->gettypename()!="bool")
        {
            //IssueError::
            string str("the types of two operands should be bool.");
            str=str+"but the types are "+p1->gettypename()+"and"+p2->gettypename();
            IssueError::Dir_typeerror(p1->getplocation(),str,"");
            
            return NULL;
        }
        return p1;
    }
    else
    {
        return NULL;
    }
}
TYPE* FieldAccess::checktype()
{//错误的话返回NULL，调用函数遇到NULL不做处理，直接返回NULL
    Scope *p;
    p=pid->getpscope();  //
    if(p==NULL)
    {//这个变量没有定义
        return NULL;
    }
    if(pexpr==NULL)
    {//直接用变量名访问
        TYPE *p_re;
        p_re = p->getptype();  
        //p_re中的location是变量声明的位置
        //变量在文本中的位置在ID中，要的是这个
        p_re ->setplocation(pid->getplocation());
        //cout<<p_re->gettypename()<<endl;
        //cout<<pid->getidname()<<endl;
        return p_re;
    }
    else//带.
    {//判断点号前是一个对象
     //取出类名，依靠类名在符号表中找到类，判断类是否有这个变量成员
        TYPE *p1;
        p1=pexpr->checktype();
        if(p1==NULL)  //p1为null直接返回，下层错误，这时已经不好处理
        {
            return NULL;
        }
        else
        {//
            string _typename;
            _typename = p1->gettypename();
            if(_typename!="class")
            {//不是p类
                string str("illegal use of dot,it should be class type. ");
                IssueError::Dir_typeerror(p1->getplocation(),str,_typename);
                
                return NULL;
            }
            else
            {//查看类中是否有这个变量成员
                string classname;
                classname = p1->get_class_arraytypename();
                //使用类指针，获得类名，和classname比较
                GloScope *pcloscope;       
                pcloscope = (GloScope*)p->getparent();
                if(pcloscope->getname()!=classname)
                {//class A 对象访问了class B 的成员
                    //IssueError::
                    string str("the class");
                    str=str+classname + "does't have the member of "+pid->getidname();
                    IssueError::Dir_typeerror(p1->getplocation(),str,"");
            
                    return NULL;
                }
                return p->getptype(); //返回的是ID的类型
            }
        }   
    }
}
TYPE* ArrayAccess::checktype()
{
    if(pexpr2!=NULL)
    {
        TYPE *p1;
        p1=pexpr2->checktype();
        if(p1==NULL)
            return NULL;
        else if(p1->gettypename()!="int")
        {//数组下标不是整数
            //IssueError::
            string str("it should be int type int the [] ");
            IssueError::Dir_typeerror(p1->getplocation(),str,p1->gettypename());
            return NULL;
        }
    }
    TYPE *p2;   //后面返回时会用到
    if(pexpr1!=NULL)
    {
        p2 = pexpr1->checktype();
        if(p2==NULL)
            return NULL;
        else if(p2->gettypename()!="[]")
        {//[]前面不是数组类型
            //IssueError::
            string str("illegal use of [] ,it should be array type.");
            IssueError::Dir_typeerror(p2->getplocation(),str,p2->gettypename());
            return NULL;
        }
    }
    TYPE *p;
    p=new TYPE(p2->get_class_arraytypename(),"",0);
    return p;
}
TYPE* Call::checktype()
{//bug is here
    Scope *pscope;
    pscope = pid->getpscope();
    FunDes *pfundes;
    pfundes = ((ClaScope*)pscope)->pfundes;
    //形参域
    vector<ForScope*> *pforscope;
    pforscope = pfundes ->pforscope;
    TYPE *t1,*t2;
    int flag=1;
    string s1;
    string s2;
    if(pactuals!=NULL)
    for(int i=0;i<pactuals->size();i++)
    {
        t1=(*pactuals)[i]->checktype();
        t2=(*pforscope)[i+1]->getptype();
        if(t1==NULL)
            return NULL;

        if(t1->gettypename()!=t2->gettypename())
        {//类型不同
           //IssueError::
            s1=s1+" "+t1->gettypename();
            s2=s2+" "+t2->gettypename();
            if(t1->gettypename()=="class"&&t2->gettypename()=="null")
            {
             
            }
            else
            {
                flag=0;
            }
        }
        else if(t1->gettypename()=="[]"||t1->gettypename()=="class")
        {//数组，看数组类型是否一样
            
            if(t1->gettypename()=="[]")
            {
                s1=s1+" array "+t1->get_class_arraytypename(); 
                s2=s2+" array "+t2->get_class_arraytypename(); 
            }
            else
            {
                s1=s1+" class "+t1->get_class_arraytypename(); 
                s2=s2+" class "+t2->get_class_arraytypename(); 
            }
            if(t1->get_class_arraytypename()!=t2->get_class_arraytypename())
            {
                flag=0;
            }
        }
        else
        {
            s1=s1+" "+t1->gettypename();
            s2=s2+" "+t2->gettypename();
            
        }
    }
    if(flag)
    {//应该返回函数的返回类型
        TYPE *p;
        p=pscope->getptype();
        return p;
    }
    else
    {
        string str;
        str="to call the function,the actuals should be \("+s2+"),not the ("+s1+")";
        IssueError::Dir_typeerror(pid->getplocation(),str,"");
        return NULL;
    }
}


TYPE* IntCon::checktype()
{
    TYPE *p;
    p=new TYPE("int","",0);
    p->setplocation(plocation);
    return p;
}
TYPE* BoolCon::checktype()
{
    TYPE *p;
    p=new TYPE("bool","",0);
    p->setplocation(plocation);
    return p;
}
TYPE* StringCon::checktype()
{
    TYPE *p;
    p=new TYPE("string","",0);
    p->setplocation(plocation);
    return p;
}
TYPE* NullCon::checktype()
{
    TYPE *p;
    p=new TYPE("null","",0);
    p->setplocation(plocation);
    return p;
}
//checkbreak

void Stmt::stmt_checkbreak(int i)
{
		//nothing to do       
}
void StmtBlock::stmt_checkbreak(int i)
{
		if(pstmts!=NULL)
		for(int j=0;j<pstmts->size();j++)
		{
				(*pstmts)[j]->stmt_checkbreak(i);
		}
}
void IfStmt::stmt_checkbreak(int i)
{
		if(pstmt1!=NULL)
				pstmt1->stmt_checkbreak(i);
		if(pstmt2!=NULL)
				pstmt2->stmt_checkbreak(i);
}
void WhileStmt::stmt_checkbreak(int i)
{
		if(pstmt!=NULL)
				pstmt->stmt_checkbreak(1);
}
void ForStmt::stmt_checkbreak(int i)
{
		if(pstmt!=NULL)
				pstmt->stmt_checkbreak(1);
}
void BreakStmt::stmt_checkbreak(int i)
{
		//cout<<"break"<<endl;
		if(i==0)
		{
				string str="illegal use of break,you can only use it in 'for' or 'while' blocks";
				IssueError::Dir_typeerror(plocation,str,"");
		}
}


