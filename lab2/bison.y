%{
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#ifndef _BISON_H
#include "nt_class.h"
#include "location.h"
#include "error.h"
#include "bison.h"
#endif

%}
%locations

%union{
    int nullcon;
    int boolcon;
    int intcon;
    char stringcon[100+1];
    char identifier[100+1];
    Program *program;
    Id *id;
    Decl *decl;
    VarDecl *vardecl;
    FnDecl *fndecl;
    ClassDecl *classdecl;

    Type *type;
    IntType *inttype;
    BoolType *booltype;
    StringType *stringtype;
    VoidType *voidtype;
    NamedType *nametype;
    ArrayType *arraytype;

    StmtBlock *stmtblock;
    Stmt *stmt;
    IfStmt *ifstmt;
    WhileStmt *whilestmt;
    ForStmt *forstmt;
    ReturnStmt *returnstmt;
    BreakStmt *breakstmt;
    PrintStmt *printstmt;

    Expr *expr;
    AssignExpr *assignexpr;
    ArithmeticExpr *arithmeticexpr;
    RelationExpr *relationexpr;
    LogicalExpr *logicalexpr;
    Lvalue *lvalue;
    FieldAccess *fieldaccess;
    ArrayAccess *arrayaccess;
    Call *call;
    This *_this;
    ReadInteger *readinteger;
    ReadLine *readline;
    Instanceof *instanceof;
    NewExpr *newexpr;
    NewArrayExpr *newarrayexpr;

    Constant *constant;
    IntCon *intconstant;
    BoolCon *boolconstant;
    StringCon *stringconstant;
    NullCon *nullconstant;

    vector<Decl*> *decllist;
    vector<VarDecl*> *formals;
    vector<Decl*> *fields;

    vector<VarDecl*> *variables;
    vector<VarDecl*> *vardecls;

    vector<Stmt*> *stmts;

    vector<Expr*> *exprs;
    vector<Expr*> *actuals;
}
/*终结符的声明*/
%token BOOL BREAK CLASS ELSE EXTENDS FOR IF INT NEW RETURN STRING THIS VOID WHILE STATIC PRINT READINTEGER READLINE INSTANCEOF 
%token <nullcon> NULLCONSTANT
%token <boolcon> BOOLCONSTANT
%token <intcon>  INTCONSTANT 
%token <stringcon> STRINGCONSTANT
%token <identifier> ID
%token  SEMI COMMA  LC RC

/*c语言=右结合*/
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%right  ASSIGNOP
%left   OR
%left   AND
%left   GREATER LESS GREATEREQUAL LESSEQUAL EQUAL NOTEQUAL 
%left   PLUS MINUS
%left   STAR DIV MOD
/*!和单目-，c语言是右结合*/
%right  NOT UMINUS
/*( ) [ ] .*/
%left   LP RP LB RB DOT
/*非终结符的声明*/
%type <program> Program
%type <decl> Decl
%type <vardecl> VarDecl
%type <fndecl> FnDecl
%type <classdecl> ClassDecl

%type <type> Type
%type <nametype> NamedType
%type <arraytype> ArrayType

%type <stmtblock> StmtBlock
%type <stmt> Stmt
%type <ifstmt> IfStmt
%type <whilestmt> WhileStmt
%type <forstmt> ForStmt
%type <returnstmt> ReturnStmt
%type <breakstmt> BreakStmt
%type <printstmt> PrintStmt

%type <expr> Expr
%type <assignexpr> AssignExpr
%type <arithmeticexpr> ArithmeticExpr
%type <relationexpr> RelationalExpr
%type <logicalexpr> LogicalExpr
%type <expr> OptExpr
%type <lvalue> LValue
%type <fieldaccess> FieldAccess
%type <call> Call
%type <arrayaccess> ArrayAccess
%type <constant> Constant 
%type <newexpr> NewExpr
%type <newarrayexpr> NewArrayExpr

%type <decllist> DeclList
%type <exprs> Exprs 
%type <stmts> Stmts
%type <vardecls> VarDecls
%type <formals> Formals
%type <variables> Variables
%type <fields> Fields
%type <actuals> Actuals
%type <decl> Field
/*从Program开始*/ 

%start Program
%%
Program   :    DeclList     	{$$=new Program($1);if(errornum==0){$$->Print(1,0);$$->buildsym();$$->printsym();/*$$->gentac();$$->printtac();$$->genmips();*/}}
          ;

DeclList  :    DeclList Decl    {($$=$1)->push_back($2);}
          |    Decl             {($$=new vector<Decl*>)->push_back($1);}
          ;
/*按照类的思想，变量在声明时是没有初值的*/
Decl      :    VarDecl          {$$=$1;}
          |    FnDecl           {$$=$1;}
          |    ClassDecl	    {$$=$1;}
          ;
/*变量的声明时是没有初始化的*/
VarDecl   :    Type ID SEMI 	{$$=new VarDecl($1,(new Id($2,@2)));}     
          |    Type ID error SEMI {}
	  ;
        
Type      :    INT          {$$=new IntType("int");}
          |    BOOL         {$$=new BoolType("bool");}
          |    STRING       {$$=new StringType("string");}
          |    NamedType	{$$=$1;}
          |    ArrayType    {$$=$1;}
          ;

NamedType :    CLASS ID      {$$=new NamedType("class",new Id($2,@2));}             
          ;

ArrayType :    Type LB RB    {$$=new ArrayType("[]",$1);}
          ;

FnDecl    :    Type ID LP Formals RP StmtBlock
                                {$$=new FnDecl(0,$1,new Id($2,@2),$4,$6);}
          |    VOID ID LP Formals RP StmtBlock
                                {$$=new FnDecl(0,(new VoidType("void")),new Id($2,@2),$4,$6);}
	      |    STATIC Type ID LP Formals RP StmtBlock
                                {$$=new FnDecl(1,$2,new Id($3,@3),$5,$7);}
	      |    STATIC VOID ID LP Formals RP StmtBlock
                                {$$=new FnDecl(1,(new VoidType("void")),new Id($3,@3),$5,$7);}
          ;

Formals   :   			    {$$=new vector<VarDecl*>;}
          | 	Variables   {$$=$1;}              
          ;
          
Variables :    Variables COMMA Type ID
                       		{($$=$1)->push_back(new VarDecl($3,new Id($4,@4)));}
          |     Type ID    	{($$=new vector<VarDecl*>)->push_back(new VarDecl($1,new Id($2,@2)));}
          ;
          
ClassDecl :    CLASS ID EXTENDS ID LC Fields RC              
                             	{$$=new ClassDecl(new Id($2,@2),new Id($4,@4),$6);}
          |    CLASS ID EXTENDS ID LC RC
                      	        {$$=new ClassDecl(new Id($2,@2),new Id($4,@4),NULL);}    
	      |    CLASS ID LC Fields RC
                                {$$=new ClassDecl(new Id($2,@2),NULL,$4);}
	      |    CLASS ID LC RC
                                {$$=new ClassDecl(new Id($2,@2),NULL,NULL);}
          ;

Fields     :   Fields Field	    {($$=$1)->push_back($2);}
           |   Field            {($$=new vector<Decl*>)->push_back($1);}
           ;  

Field      :   VarDecl          {$$=$1;}		  
           |   FnDecl		    {$$=$1;}
           ;
/*原型声明暂不支持*/
/*            
Prototypes : Prototypes Prototype    {  }
           | Prototype               {  }
           ;
            
Prototype  : Type T_Identifier LP Formals RP SEMI
                                     {  }
           | T_Void T_Identifier LP Formals RP SEMI
                                     {  }
           ;                
*/    
StmtBlock  : LC VarDecls Stmts RC  
				{$$=new StmtBlock($2,$3);}
           | LC VarDecls RC        
				{$$=new StmtBlock($2,NULL);}
     	   | LC Stmts RC        
				{$$=new StmtBlock(NULL,$2);}
           | LC RC 		{$$=new StmtBlock(NULL,NULL);}
           ;
           
VarDecls   : VarDecls VarDecl  	{($$=$1)->push_back($2);}
           | VarDecl            {($$=new vector<VarDecl*>)->push_back($1);}
           ;

Stmts      : Stmts Stmt         {($$=$1)->push_back($2);}
           | Stmt               {($$=new vector<Stmt*>)->push_back($1);}
           ;
           
Stmt       : OptExpr SEMI       {$$=$1;}
           | IfStmt		        {$$=$1;}
           | WhileStmt		    {$$=$1;}
           | ForStmt		    {$$=$1;}
           | BreakStmt		    {$$=$1;}
           | ReturnStmt		    {$$=$1;}
           | PrintStmt		    {$$=$1;}
           | StmtBlock		    {$$=$1;}
           ;
          
           
IfStmt     : IF LP Expr RP Stmt %prec LOWER_THAN_ELSE
                                {$$=new IfStmt($3,$5,"",NULL);}
           | IF LP Expr RP Stmt ELSE Stmt
                                {$$=new IfStmt($3,$5,"else",$7);}
           ;
                                     
          
WhileStmt  : WHILE LP Expr RP Stmt
                                {$$=new WhileStmt($3,$5);}
           ;
           
ForStmt    : FOR LP OptExpr SEMI Expr SEMI OptExpr RP Stmt
                                {$$=new ForStmt($3,$5,$7,$9);}
           ;
           
ReturnStmt : RETURN OptExpr SEMI  
																{$$=new ReturnStmt($2,@1);
																//为了获得return位置，当optexpr为NULL时，确定return的位置
																}
           ;
        
BreakStmt  : BREAK SEMI         {$$=new BreakStmt(@1);
																	//获得break位置
																}             
           ;
       

PrintStmt  : PRINT LP Exprs RP SEMI 
                                {$$=new PrintStmt($3);}
           ;
           
Expr       :  AssignExpr        {$$=$1;}
           |  Constant		    {$$=$1;}
           |  LValue		    {$$=$1;}
           |  THIS              {$$=new This();}
           |  Call		        {$$=$1;}
           |  LP Expr RP        {$$=$2;}
           |  ArithmeticExpr	{$$=$1;}
           |  RelationalExpr	{$$=$1;}
           |  LogicalExpr	    {$$=$1;}
    	   |  READINTEGER LP RP 
				{$$=new ReadInteger();}
           |  READLINE LP RP    
				{$$=new ReadLine();}
	       |  INSTANCEOF LP Expr COMMA ID RP 
				{$$=new Instanceof($3,new Id($5,@5));}
           |  NewExpr
                {$$=$1;} 
           |  NewArrayExpr
				{$$=$1;}
		   ;

/*NEW ID LP RP 是声明一个对象，这点很像java,如Box mybox = new Box(); 但是，decaf不支持这种，它支持：Box mybox; mybox = new Box(); */
/*NEW TYPE LB EXPR RB 是声明一个数组，如int[12]*/
          
NewExpr        : NEW ID LP RP 
                {$$=new NewExpr(new Id($2,@2));}
               ;
NewArrayExpr   : NEW Type LB Expr RB 
                {$$=new NewArrayExpr($2,$4);}
               ;

AssignExpr     : LValue ASSIGNOP Expr     
                {$$=new AssignExpr($1,$3);} 
               ;
   
ArithmeticExpr : Expr PLUS Expr 
				{$$=new ArithmeticExpr($1,"+",$3);}
               | Expr MINUS Expr       
				{$$=new ArithmeticExpr($1,"-",$3);}
               | Expr STAR Expr     
				{$$=new ArithmeticExpr($1,"*",$3);}
               | Expr DIV Expr      
				{$$=new ArithmeticExpr($1,"/",$3);}
               | Expr MOD Expr       
				{$$=new ArithmeticExpr($1,"%",$3);}
               | MINUS Expr %prec UMINUS
				{$$=new ArithmeticExpr(NULL,"-",$2);}
               ;
                         
RelationalExpr : Expr GREATER Expr
                {$$=new RelationExpr($1,">",$3);}
               | Expr LESS Expr
                {$$=new RelationExpr($1,"<",$3);}
               | Expr GREATEREQUAL Expr
                {$$=new RelationExpr($1,">=",$3);}
               | Expr LESSEQUAL Expr
                {$$=new RelationExpr($1,"<=",$3);}
               | Expr EQUAL Expr
                {$$=new RelationExpr($1,"==",$3);}
               | Expr NOTEQUAL Expr
                {$$=new RelationExpr($1,"!=",$3);}
               ;

LogicalExpr    : Expr AND Expr
                {$$=new LogicalExpr($1,"&&",$3);}
               | Expr OR Expr 
                {$$=new LogicalExpr($1,"||",$3);}
               | NOT Expr       
                {$$=new LogicalExpr(NULL,"!",$2);}
               ;               


Exprs      : Exprs COMMA Expr         
				{($$=$1)->push_back($3);}
           | Expr               
				{($$=new vector<Expr*>)->push_back($1);}
           ; 

OptExpr    : Expr		{$$=$1;}
           |            {$$=NULL;}
           ;
            
LValue     : FieldAccess    {$$=$1;}
           | ArrayAccess 	{$$=$1;}
           ; 

FieldAccess : ID           	{$$=new FieldAccess(NULL,new Id($1,@1));}
            | Expr DOT ID	{$$=new FieldAccess($1,new Id($3,@3));}
            ;

Call       : ID LP Actuals RP 
                            {$$=new Call(NULL,new Id($1,@1),$3);} 
           | Expr DOT ID LP Actuals RP
                            {$$=new Call($1,new Id($3,@3),$5);}
           ;

ArrayAccess : Expr LB Expr RB   {$$=new ArrayAccess($1,$3);}
            ;
           
Actuals    : Exprs 		{$$=$1;}
           |            {$$=NULL;}
           ;
           
Constant   : INTCONSTANT    {$$=new IntCon($1,@1);}
           | BOOLCONSTANT	{$$=new BoolCon($1,@1);}
           | STRINGCONSTANT	{$$=new StringCon($1,@1);}
           | NULLCONSTANT	{$$=new NullCon($1,@1);}
           ;
%%

void yyerror(const char* msg) 
{
    errornum++;   
    IssueError::Printyyerror(&yylloc,yytext);
}
