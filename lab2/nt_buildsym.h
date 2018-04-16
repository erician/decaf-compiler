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


class TYPE;
class Scope;
class GloScope;
class ClaDes;
class ClaScope;
class FunDes;
class ForScope;
class LocScope;
//类型type：int，string,bool,namedtype,arraytype;;类别category:Class,Var,Fun;
class TYPE 
{
public:
    string _typename;
    string class_arraytypename;
    string class_base;  //基类指针的名字
    int arraylevel;
    YYLTYPE *plocation;
	    
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
class ClaDes:public Scope
{
public:
    string parentname;
    ClaDes* pparent;
    vector<ClaScope*> *pvec_clascope;
    ClaDes(string s1,ClaDes *s2,vector<ClaScope*> *s3)
    {
        parentname=s1;
        pparent = s2;
     
   pvec_clascope = s3;
    }
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
