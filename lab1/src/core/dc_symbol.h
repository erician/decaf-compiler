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

#ifndef _NT_BUILDSYM_H
#define _NT_BUILDSYM_H

enum CATEGORY{DC_CLASS, DC_FUN, DC_VAR};
enum TYPE{DC_INT, DC_BOOL, DC_STRING, DC_NAMED, DC_ARRAY, DC_VOID};

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

class Entry
{

};

class Scope
{

};

//GloScope
class GloScope:public Scope
{
private:
    std::vector<const GloScopeEntry *> entries;
public:
    GloScope();
    bool addEntry(GloScopeEntry* entry);
};

//GloScopeEntry
class GloScopeEntry: public Entry
{
private:
    std::string className;
    int category;
    ClaDes *claDes;
public:
    GloScopeEntry();
    GloScopeEntry(std::string className, ClaDes* claDes);
    bool setClassName(std::string);
    std::string getClassName();

    bool setCategory(int catagory);
    int getCategpry();

    bool setClaDes(const ClaDes* claDes);
    const ClaDes* getClaDes();
};

//ClaDes
class ClaDes:public Scope
{
private:
    //仅支持单继承
    string parentName;
    //parentClaDes可以在后面绑定，在创建该类的时候并不着急指定它的值.只要确定parentName
    ClaDes* parentClaDes;
    ClaScope* claScope;
public:
    ClaDes();
    
    bool setParentName(std::string parentName);
    std::string getParentName();

    bool setClaScope(const ClaScope* claScope);
    const ClaScope* getClaScope();

    bool setParentClaDes(const ClaDes* parentClaDes);
    const ClaDes* getParentClaDes();
};

//ClaScope
class ClaScope:public Scope
{
private:
    std::vector<ClaScopeEntry*> entries;
public:
    ClaScope();
    bool addEntry(ClaScopeEntry* entry);
};

//TypeInfo
class TypeInfo
{   
private:
    int type;
    std::string className;
    int arrayLevel;
public:
    TypeInfo();
    bool setType(int type);
    int getType();

    bool setArrayLevle(int level);
    int getArrayLevel();

    bool setClassName(std::string className);
    std::string getClassName();
};

//ClaScopeEntry
class ClaScopeEntry: public Entry
{
private:
    //func or var name
    std::string name;
    int category;
    TypeInfo *typeInfo;
    FunDes *funDes;
public:
    ClaScopeEntry();
    bool setName(std::string name);
    std::string getName();

    bool setCategory(int category);
    int  getCategory();
    
    bool setTypeInfo(TypeInfo *typeInfo);
    int getTypeInfo();
    
    bool setFunDes(FunDes *funDes);
    const FunDes* getFunDes();
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
