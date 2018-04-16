/*************************************************************************
	> File Name: location.h
	> Author: 
	> Mail: 
	> Created Time: 2016年12月05日 星期一 16时44分01秒
 ************************************************************************/

#ifndef _LOCATION_H
#define _LOCATION_H
# define YYLTYPE_IS_DECLARED 1
struct YYLTYPE;
struct YYLTYPE
{
public:
    int first_line;    /* 第一行   */
    int first_column;  /* 第一列   */
    int last_line;     /* 最后一行 */
    int last_column;   /* 最后一列 */
    YYLTYPE(const YYLTYPE &loc)
    {
        first_line=loc.first_line;
        first_column=loc.first_column;
        last_line=loc.last_line;
        last_column=loc.last_column;
    }
    YYLTYPE()
    {
        
    }
};
typedef struct YYLTYPE YYLTYPE;

#endif
