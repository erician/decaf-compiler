%{
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#ifndef DC_YACC_BISON_H_
#include "yacc/bison.h"
#endif

#ifndef DC_CORE_DC_ERROR_H_
#include "core/dc_error.h"
#endif

#ifndef DC_YACC_LOCATION_H_
#include "yacc/location.h"
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
    FunDecl *fundecl;
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

    std::vector<Decl*> *decllist;
    std::vector<VarDecl*> *formals;
    std::vector<Decl*> *fields;

    std::vector<VarDecl*> *variables;

    std::vector<Stmt*> *stmts;

    std::vector<Expr*> *exprs;
    std::vector<Expr*> *actuals;
}
/*终结符的声明*/
%token BOOL BREAK CLASS ELSE EXTENDS FOR IF INT NEW NEWARRAY RETURN STRING THIS VOID WHILE STATIC PRINT READINTEGER READLINE INSTANCEOF 
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
%type <vardecl> VarDecl
%type <fundecl> FunDecl
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
%type <formals> Formals
%type <variables> Variables
%type <fields> Fields
%type <actuals> Actuals
%type <decl> Field
/*从Program开始*/ 

%start Program
%%
Program   :    DeclList     	{$$=new Program($1); program = $$;}
          ;    

DeclList  :    DeclList ClassDecl    {($$=$1)->push_back($2);}
          |    ClassDecl             {($$=new std::vector<Decl*>)->push_back($1);}
          ;

/*变量在声明时是没有初始化的*/
VarDecl   :    Type ID SEMI 	{$$=new VarDecl($1,(new Id($2,@2)));}     
          |    Type ID error SEMI {}
	  ;
        
Type      :    INT          {$$=new IntType();}
          |    BOOL         {$$=new BoolType();}
          |    STRING       {$$=new StringType();}
          |    NamedType	{$$=$1;}
          |    ArrayType    {$$=$1;}
          ;

NamedType :    CLASS ID      {$$=new NamedType(new Id($2,@2));}             
          ;

ArrayType :    Type LB RB    {$$=new ArrayType($1);}
          ;

FunDecl    :    Type ID LP Formals RP StmtBlock
                                {$$=new FunDecl(DC_NOTSTATIC,$1,new Id($2,@2),$4,$6);}
          |    VOID ID LP Formals RP StmtBlock
                                {$$=new FunDecl(DC_NOTSTATIC,(new VoidType()),new Id($2,@2),$4,$6);}
	      |    STATIC Type ID LP Formals RP StmtBlock
                                {$$=new FunDecl(DC_STATIC,$2,new Id($3,@3),$5,$7);}
	      |    STATIC VOID ID LP Formals RP StmtBlock
                                {$$=new FunDecl(DC_STATIC,(new VoidType()),new Id($3,@3),$5,$7);}
          ;

Formals   :   			    {$$=new std::vector<VarDecl*>;}
          | 	Variables   {$$=$1;}              
          ;
          
Variables :    Variables COMMA Type ID
                       		{($$=$1)->push_back(new VarDecl($3,new Id($4,@4)));}
          |     Type ID    	{($$=new std::vector<VarDecl*>)->push_back(new VarDecl($1,new Id($2,@2)));}
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
           |   Field            {($$=new std::vector<Decl*>)->push_back($1);}
           ;  

Field      :   VarDecl          {$$=$1;}		  
           |   FunDecl		    {$$=$1;}
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
           
StmtBlock  : LC Stmts RC        {$$=new StmtBlock($2);}
           | LC RC 		        {$$=new StmtBlock(NULL);}
           ;

Stmts      : Stmts Stmt         {($$=$1)->push_back($2);}
           | Stmt               {($$=new std::vector<Stmt*>)->push_back($1);}
           ;
           
Stmt       : OptExpr SEMI       {$$=$1;}
           | IfStmt		        {$$=$1;}
           | WhileStmt		    {$$=$1;}
           | ForStmt		    {$$=$1;}
           | BreakStmt		    {$$=$1;}
           | ReturnStmt		    {$$=$1;}
           | PrintStmt		    {$$=$1;}
           | StmtBlock		    {$$=$1;}
           | VarDecl            {$$=$1;}
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
           |  THIS              {$$=new This(@1);}
           |  Call		        {$$=$1;}
           |  LP Expr RP        {$$=$2;}
           |  ArithmeticExpr	{$$=$1;}
           |  RelationalExpr	{$$=$1;}
           |  LogicalExpr	    {$$=$1;}
    	   |  READINTEGER LP RP 
				{$$=new ReadInteger(@1);}
           |  READLINE LP RP    
				{$$=new ReadLine(@1);}
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
NewArrayExpr   : NEWARRAY LP Type COMMA Expr RP
                {$$=new NewArrayExpr($3,@3,$5);}
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
				{($$=new std::vector<Expr*>)->push_back($1);}
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
