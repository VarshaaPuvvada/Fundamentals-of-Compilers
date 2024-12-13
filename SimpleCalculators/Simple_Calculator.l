%{
#include<stdio.h>
#include "y.tab.h"
extern int yylval;
%}

%%

[a-zA-Z] {
    yylval = *yytext;  
    return VAR;
}

[0-9]+ {
    yylval = atoi(yytext);  
    return NUM;
}

[\n] return 0;

. return *yytext;

%%

int yywrap() {
    return 1;
}
