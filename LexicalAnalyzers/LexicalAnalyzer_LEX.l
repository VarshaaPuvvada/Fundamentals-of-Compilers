%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<ctype.h>
%}

%%
"+"|"-"|"*"|"/"|">"|"<"|">="|"<="|"=="|"=" {printf("Operator: %s\n", yytext);}

"if"|"else"|"while"|"do"|"break"|"continue"|"int"|"float"|"double"|"return"|"char"|"case"|"switch"|"void"|"printf" {printf("Keyword: %s\n", yytext);}

";" {printf("Semicolon: %s\n", yytext);}

" "|","|"("|")"|"{"|"}"|"["|"]"|"\t" {printf("Seperator: %s\n", yytext);}

[0-9]+ {printf("Number: %s\n", yytext);}

[a-zA-Z_][a-zA-Z0-9_]* {printf("Identifier: %s\n", yytext);}

\"[^\"]*\" {printf("String Literal: %s\n", yytext);}

. {printf("Unrecognized token: %s\n", yytext);}
%%

int main()
{
    printf("Enter a code to perform lexical analysis:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
