/*************************************************************************
	> File Name: nt_buildsym.h
	> Author: 
	> Mail: 
	> Created Time: Tue 29 Nov 2016 06:55:23 PM PST
 ************************************************************************/
#ifndef DC_CORE_DC_SYMBOL_H_
#define DC_CORE_DC_SYMBOL_H_

#include <iostream>
#include <vector>
#include <stack>
#include <string>

#ifndef DC_YACC_LOCATION_H_
#include "yacc/location.h"
#endif

#ifndef DC_CORE_DC_ENUM_H_
#include "core/dc_enum.h"
#endif

class TypeInfo;
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
class ForScopeEntry;

class LocScope;
class LocScopeEntry;

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
    std::vector<Entry *> entries;
public:
    GloScope();
    bool addEntry(Entry* entry);
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
    int getCategory();

    bool setClaDes(ClaDes* claDes);
    const ClaDes* getClaDes();
};
//ClaDes
class ClaDes:public Scope
{
private:
    //仅支持单继承
    std::string parentName;
    //parentClaDes可以在后面绑定，在创建该类的时候并不着急指定它的值.只要确定parentName
    ClaDes* parentClaDes;
    ClaScope* claScope;
public:
    ClaDes();
    
    bool setParentName(std::string parentName);
    std::string getParentName();

    bool setClaScope(ClaScope* claScope);
    const ClaScope* getClaScope();

    bool setParentClaDes(ClaDes* parentClaDes);
    const ClaDes* getParentClaDes();
};

//ClaScope
class ClaScope:public Scope
{
private:
    std::vector<Entry*> entries;
public:
    ClaScope();
    bool addEntry(Entry* entry);
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

    bool setArrayLevel(int level);
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
    const TypeInfo* getTypeInfo();
    
    bool setFunDes(FunDes *funDes);
    const FunDes* getFunDes();
};
//function descriptor
class FunDes:public Scope
{
public:
    FunDes();
    bool setIsStatic(bool isStatic);
    bool getIsStatic();

    bool setIsMain(bool isMain);
    bool getIsMain();

    bool setForScope(ForScope *forScope);
    const ForScope* getForScope();
    
private:
    bool isStatic;
    bool isMain;
    ForScope *forScope;
    
    std::vector<ForScope*> *pforscope;
};
//formal scope
class ForScope:public Scope
{
private:
    std::vector<Entry*> entries;
    LocScopeEntry *locScopeEntry;
public:
    ForScope();
    bool addEntry(Entry* entry);
    
    bool setLocScopeEntry(Entry *locScopeEntry);
    const LocScopeEntry* getLocScopeEntry();
};
//formal scope entry
class ForScopeEntry: public Entry
{
private:
    std::string name;
    TypeInfo *typeInfo;
public:
    ForScopeEntry();
    bool setName(std::string name);
    std::string getName();
    
    bool setTypeInfo(TypeInfo *typeInfo);
    const TypeInfo* getTypeInfo();
    
};
//local scope
class LocScope:public Scope
{
private:
    std::vector<Entry*> entries;
public:
    LocScope();
    bool addEntry(Entry* entry);
};
//local scope entry
class LocScopeEntry: public Entry
{
private:
    std::string name;
    int category;
    TypeInfo *typeInfo;
    LocScope *subLocScope;
public:
    LocScopeEntry();
    bool setName(std::string name);
    std::string getName();

    bool setCategory(int category);
    int  getCategory();
    
    bool setTypeInfo(TypeInfo *typeInfo);
    const TypeInfo* getTypeInfo();
    
    bool setSubLocScope(LocScope *subLocScope);
    const LocScope* getSubLocScope();
};


#endif
