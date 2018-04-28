%{
    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
    #include <string>
    #include <vector>

    #ifndef DC_LEX_FLEX_H_
    #include "lex/flex.h"
    #endif
    
    #ifndef DC_CORE_DC_CLASS_H_
    #include "core/dc_class.h"
    #endif

    #ifndef DC_CORE_DC_ERROR_H_
    #include "core/dc_error.h"
    #endif
    
    #include "yacc/y.tab.h"

    static void DoBeforeEachAction();
    #define YY_USER_ACTION DoBeforeEachAction();
    #define TAB_SIZE 4
    vector<string> savedlines;
    int lineno,colno;          //列号，需要自己来管理
    int errornum=0;
%}
/*说明：yylength，yytext可以直接使用*/
/*使用行号，需要自己初始化*/
/*regular definition*/        
LETTER  [A-Za-z]
DIGIT   [0-9]
ID      {LETTER}({LETTER}|{DIGIT}|_)*
INTCONSTANT ([0-9]+)|(((0x)|(0X))([0-9a-fA-F]+))
STRINGCONSTANT (\"[^\"\n]*\")
/*关键字*/
BOOL bool
BREAK break
CLASS class
ELSE else
EXTENDS extends
FOR for
IF if
INT int
NEW new
NEWARRAY newarray
NULL null
RETURN return 
STRING string
THIS this
VOID void
WHILE while
STATIC static
TRUE true
FALSE false
PRINT Print
READINTEGER ReadInteger
READLINE ReadLine
INSTANCEOF instanceof
/*运算符以及标点符号*/
PLUS \+
MINUS -
STAR \*
DIV \/
MOD %
GREATER >
LESS <
GREATEREQUAL >=
LESSEQUAL <=
EQUAL ==
NOTEQUAL !=
AND &&
OR \|\|
NOT !
ASSIGNOP =
SEMI ;
COMMA ,
DOT \.
LB \[
RB \]
LC \{
RC \}
LP \(
RP \)
AERROR .

%x COPY
%option stack

%%

<COPY>.*        {
                    savedlines.push_back(yytext);
                    colno=1;
                    yy_pop_state();
                    yyless(0);      //将整行全部退回
                }	
<COPY><<EOF>>   {  
                    yy_pop_state();             
                }

<*>\n           {   
                    colno = 1;lineno++;
                    if(YYSTATE == COPY)     //空行处理
                        savedlines.push_back("");
                    else
                        yy_push_state(COPY);
                }

<*>[\t]         {
                    colno += TAB_SIZE-1;
                }
[ ]             {//匹配前colno加1 
                    ;              
                }

{BOOL}    {return BOOL;}
{INT} 	  {return INT;}
{STRING}  {return STRING;}
{CLASS}   {return CLASS;}
{EXTENDS} {return EXTENDS;}
{NEW}     {return NEW;}
{NEWARRAY}     {return NEWARRAY;}
{THIS}    {return THIS;}
{IF}      {return IF;}
{ELSE}	  {return ELSE;}
{FOR}     {return FOR;}
{WHILE}   {return WHILE;}
{BREAK}   {return BREAK;}
{RETURN}  {return RETURN;}
{VOID}    {return VOID;}
{STATIC}  {return STATIC;}
{PRINT}         {return PRINT;}
{READINTEGER}   {return READINTEGER;}
{READLINE}  	{return READLINE;}
{INSTANCEOF}  	{return INSTANCEOF;}

{NULL}    	        {yylval.nullcon=0;return NULLCONSTANT;}
{TRUE}              {yylval.boolcon=1;return BOOLCONSTANT;}
{FALSE}             {yylval.boolcon=0;return BOOLCONSTANT;}
{INTCONSTANT}       {yylval.intcon=atoi(yytext);return INTCONSTANT;}      
{STRINGCONSTANT}    {strcpy(yylval.stringcon,yytext);return STRINGCONSTANT;}

{ID}                {strcpy(yylval.identifier,yytext);return ID;}

{PLUS} 	{return PLUS;}
{MINUS} {return MINUS;}
{STAR} 	{return STAR;}
{DIV} 	{return DIV;}
{MOD} 	{return MOD;}

{GREATER}       {return GREATER;}
{LESS}          {return LESS;}
{GREATEREQUAL}  {return GREATEREQUAL;}
{LESSEQUAL}     {return LESSEQUAL;}
{EQUAL}         {return EQUAL;}
{NOTEQUAL}      {return NOTEQUAL;}

{AND}  	{return AND;}
{OR} 	{return OR;}
{NOT} 	{return NOT;}
{ASSIGNOP} {return ASSIGNOP;}
{SEMI}  {return SEMI;}
{COMMA} {return COMMA;}
{DOT}   {return DOT;}
{LB}    {return LB;}
{RB}    {return RB;}
{LC}    {return LC;}
{RC}    {return RC;}
{LP}    {return LP;}
{RP}    {return RP;}


("//"[^\n]*)            			        {}
("/*"([^\*]|(\*)*[^\*/])*(\*)*"*/")   			{}

{AERROR}    {
		        errornum++;
                IssueError::UnMachedChar(&yylloc,yytext[0]);    
            }              
%%


/*yywrap返回1,表示对输入串的处理结束；返回0，继续扫描*/
int yywrap()
{
    return 1;
}
void InitFlex()
{
    yy_flex_debug = false;      //不使用-d选项，即不让flex在每个匹配后打印
    yy_push_state(COPY);        //先复制一行，再解析
    lineno = 1;
    colno  = 1;
}                     
static void DoBeforeEachAction()
{
    yylloc.first_line=yylloc.last_line = lineno;
    yylloc.first_column = colno;
    yylloc.last_column = colno+yyleng-1; /*yyleng当前匹配的字符串的长度*/
    colno = colno + yyleng; 
}
