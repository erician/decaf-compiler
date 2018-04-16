/*************************************************************************
	> File Name: nt_printsym.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年12月02日 星期五 22时25分50秒
 ************************************************************************/

#include<iostream>
#include<stack>
#include<vector>
#include<string>
#include "nt_buildsym.h"
#include "nt_class.h"
using namespace std;

void treenode::Print(int aline,int level)
{

}

void Program::printsym()
{
    cout<<endl;
    cout<<"GLOBAL SCOPE:"<<endl;
    for(int i=0;i<pvec_gloscope->size();i++)
        (*pvec_gloscope)[i]->printglosym();
    for(int i=0;i<pvec_gloscope->size();i++)
    {
        (*pvec_gloscope)[i]->printclasym();
    }
}
void GloScope::printglosym()
{
    cout<<"    ";
    cout<<category<<" "<<name<<" ";
    string parentname;
    parentname=pclades->getparentname();
    if(parentname!="")
    {
        cout<<": "<<parentname;
    }
    cout<<endl;
}
void GloScope::printclasym()
{
    cout<<"CLASS SCOPE OF "<<name<<endl;
    vector<ClaScope*> *pvec_clascope;
    pvec_clascope=pclades->get_pvec_clascope();
    for(int i=0;i<pvec_clascope->size();i++)
    {
         (*pvec_clascope)[i]->printsym();
    }
}
void ClaScope::printsym()
{
    cout<<"    ";
    if(category=="function")
    {
        if(pfundes->getisstatic())
            cout<<"static ";
    }
    cout<<category<<' '<<name<<":";
    string _typename;
    _typename=ptype->gettypename();
    
    if(_typename=="class")
    {
        cout<<_typename<<' '<<ptype->get_class_arraytypename();
    }
    else if(_typename=="[]")
    {
        int level;
        level=ptype->getarraylevel();
        cout<<_typename<<' '<<ptype->get_class_arraytypename()<<' ';
        for(int i=0;i<level;i++)
            cout<<"[]";
    }
    else
    {
        cout<<_typename;
    }
    cout<<endl;
    if(category=="function")
    {
        cout<<"        FORMAL SCOPE OF "<<name<<endl;
        
        vector<ForScope*> *pforscope;
        if(category=="function")
        {    
            pforscope=pfundes->getpforscope();
            for(int i=0;i<pforscope->size();i++)
            {
                (*pforscope)[i]->printsym();
            }
        }

        cout<<"            "<<"LOCALSCOPE"<<endl;
    
        vector<LocScope*> *pvec_locscope;
        pvec_locscope=(*pforscope)[0]->getlocscope();
        for(int i=0;i<pvec_locscope->size();i++)
        {
            if(i+1==pvec_locscope->size())
                (*pvec_locscope)[i]->printsym(0,1);  
            else
                (*pvec_locscope)[i]->printsym(0,0);      
        }
    }
}
void ForScope::printsym()
{
    cout<<"            ";
    cout<<"variable ";
    cout<<name<<' ';
    
    string _typename;
    _typename=ptype->gettypename();
    
    if(_typename=="class")
    {
        cout<<_typename<<' '<<ptype->get_class_arraytypename();
    }
    else if(_typename=="[]")
    {
        int level;
        level=ptype->getarraylevel();
        cout<<_typename<<' '<<ptype->get_class_arraytypename()<<' ';
        for(int i=0;i<level;i++)
            cout<<"[]";
    }
    else
    {
        cout<<_typename;
    }
    cout<<endl;
}
void LocScope::printsym(int level,int islast)
{
    if(name!="")
    {
    	cout<<"            ";
    	for(int i=0;i<=level;i++)
        	cout<<"    ";
    	cout<<category<<' '<<name<<' ';

    	string _typename;
    	_typename=ptype->gettypename();
    
    	if(_typename=="class")
    	{
        	cout<<_typename<<' '<<ptype->get_class_arraytypename();
    	}
    	else if(_typename=="[]")
    	{
        	int level;
        	level=ptype->getarraylevel();
        	cout<<_typename<<' '<<ptype->get_class_arraytypename()<<' ';
        	for(int i=0;i<level;i++)
            cout<<"[]";
    	}
    	else
    	{
        	cout<<_typename;
    	}
    	cout<<endl;
    }

    if(islast)
    for(int i=0;i<pvecvec_locscope->size();i++)
    {
       	for(int j=0;j<(*pvecvec_locscope)[i]->size();j++)
       	{
       	    if(j+1==(*pvecvec_locscope)[i]->size())
		(*((*pvecvec_locscope)[i]))[j]->printsym(level+1,1);            	
	else
                (*((*pvecvec_locscope)[i]))[j]->printsym(level+1,0);
        }
        
    }
}

