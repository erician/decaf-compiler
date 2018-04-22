/*************************************************************************
	> File Name: nt_buildsym.h
	> Author: 
	> Mail: 
	> Created Time: Tue 29 Nov 2016 06:55:23 PM PST
 ************************************************************************/

#include <vector>
#include <string>
#include <stack>
#include "location.h"
using namespace std;
#ifndef _NT_BUILDSYM_H
#define _NT_BUILDSYM_H

class Type;
class Scope;
class GloScope;
class GloScopeEntry;
//注释一下，别自己都忘了, des全称是descriptor,意思是描述，是对该类型的一个基本描述
//详情可以参考编译原理p304
class ClaDes;
class ClaScope;
class ClaScopeEntry;

class FunDes;
class ForScope;
class LocScope;

/*
类型type：int，string,bool,namedtype(即定义的class),arraytype,void,
按照decaf语法的定于，应该支持任意维数组，只是最后一维的大小必须指定
类别category:class,var,fun
访问控制：所有的变量都是私有的，只能被该类或其子类访问，所有方法都是公共的
*/

class Type 
{
public:
    string _typename;
    string class_arraytypename;
    string class_base;  //基类指针的名字
    int arraylevel;
    const YYLTYPE *plocation;
	    
    TYPE(string s1,string s2,int s3,string s4="")
    {
        _typename = s1;
        class_arraytypename = s2;
        arraylevel = s3;
	class_base=s4;
    }
    TYPE(string s1,string s2,int s3,YYLTYPE *s4,string s5="")
    {
        _typename = s1;
        class_arraytypename = s2;
        arraylevel = s3;
	plocation=s4;
	class_base=s5;
    }
    int getlineno()
    {
	return plocation->first_line;
    }
    void setplocation(YYLTYPE *p)
    {
	plocation=p;
    }
	
    string gettypename()
    {
        return _typename;
    }
    string get_class_arraytypename()
    {
        return class_arraytypename;
    }
    string getclass_base()
    {
	return class_base;
    }
    int getarraylevel()
    {
        return arraylevel;
    }
    YYLTYPE* getplocation()
    {
	return plocation;
    }
        
};
class Scope
{
public:
    vector<Scope*> *pparent;
    int scopenum;       //便于查找时表示是那种类型
    YYLTYPE *plocation; //检查类型匹配是用于定位
    Scope()
    {
        pparent=NULL;
	plocation=NULL;
    };
    void setparent(vector<Scope*> *p,int num)
    {
        pparent=p;
        scopenum=num;
    }
    void setlocation(YYLTYPE *s1)	//又多了一个set
    {
	plocation=s1;
    }
    vector<Scope*> *getparent()
    {
	return pparent;
    }
    int getscopenum()
    {
	return scopenum;
    }
    virtual string getname()
    {
	return "";
    }
    virtual TYPE *getptype()
    {
	return NULL;
    }

};

class GloScope:public Scope
{
public:
    string name;
    string category;
    ClaDes *pclades;  
    GloScope(string s1,string s2,ClaDes* s3)
    {
        name=s1;
        category=s2;
        pclades=s3;
    }
    string getname()
    {
        return name;
    }
    ClaDes* getpclades()
    {
	return pclades;
    }
    TYPE *getptype()
    {
	return NULL;
    }

    void printglosym();
    void printclasym();
};

class Entry
{
};

class GloScopeEntry: public Entry
{
private:
    std::string className;
    std::string category;
    ClaDes *pClaDes;
public:
    GloScopeEntry(std::string className, std::string catagory, ClaDes *pClades);
    GloScopeEntry(std::string className, ClaDes *pClades);
    std::string getClassName();
    std::getCategpry();
    ClaDes *getPClaDes();
};

class ClaScopeEntry: public Entry
{
private:
    //func or var name
    std::string name;
    std::string category;
    Type *pType;
    FunDes *pFunDes;
public:
    ClaScopeEntry(std::string name, std::string category, Type *pType, FunDes *pFunDes);
    std::string getName();
    std::string category();
    const Type* getPType();
    const FunDes* getPFunDes();
};

class ClaDes:public Scope
{
public:
    //仅支持单继承
    string parentName;
    ClaDes& pParentClaDes;
    string className;
    vector<ClaScope*> *pvecClaScope;
    ClaDes(string className, string parentName, ClaDes *pParentClaDes, vector<ClaScope*> *pvecClaScope);

    ClaDes *getparent()
    {
        return pparent;
    }
    vector<ClaScope*>* get_pvec_clascope()
    {
        return pvec_clascope;
    }
    string getparentname()
    {
        return parentname;
    }

};
class ClaScope:public Scope
{
public:
    string name;
    string category;
    TYPE *ptype;
    FunDes* pfundes;
    ClaScope(string s1,string s2,TYPE *s3,FunDes *s4)
    {
        name = s1;
        category = s2;
        ptype = s3;
        pfundes = s4;
    }
    string getname()
    {
        return name;
    }
    string getcategory()
    {
	return category;
    }
    TYPE *getptype()
    {
	return ptype;
    }
    void printsym();
};
class FunDes:public Scope
{
public:
    int isstatic;
    int ismain;
    vector<ForScope*> *pforscope;
    FunDes(int s1,int s2,vector<ForScope*> *s3)
    {
        isstatic=s1;
        ismain=s2;
        pforscope=s3;
    }
    int getisstatic()
    {
        return isstatic;
    }
    vector<ForScope*> *getpforscope()
    {
	return pforscope;
    }
};
class ForScope:public Scope
{
public:
    string name;
    TYPE *ptype;
    vector<LocScope*> *pvec_locscope;
    ForScope(string s1,TYPE *s2,vector<LocScope*> *s3)
    {
        name=s1;
        ptype=s2;
        pvec_locscope=s3;
    }
    string getname()
    {
        return name;
    }
    vector<LocScope*> *getlocscope()
    {
	return pvec_locscope;
    }
    TYPE *getptype()
    {
	return ptype;
    }
    void printsym();
};

class LocScope:public Scope
{
public:
    string name;
    string category;
    TYPE *ptype;
    vector<vector<LocScope*>*> *pvecvec_locscope;
    LocScope(string s1,const char* s2,TYPE* s3,vector<vector<LocScope*>*> *s4)
    {
        name = s1;
        category = s2;
        ptype = s3;
        pvecvec_locscope = s4;
    }
    string getname()
    {
        return name;
    }
    TYPE *getptype()
    {
	return ptype;
    }
    void printsym(int level,int islast);
};
#endif
