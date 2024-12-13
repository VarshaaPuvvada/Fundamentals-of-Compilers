%{
#include<stdio.h>
int flag = 0;
int yylex();
void yyerror(const char *msg);
%}

%token NUMBER

%left '+' '-'
%left '*' '/' '%'

%%

Arithmetic_Expression:
    E { printf("\nResult = %d\n", $$); return 0; }
    ;

E:
    E '+' E { $$ = $1 + $3; }
    | E '-' E { $$ = $1 - $3; }
    | E '*' E { $$ = $1 * $3; }
    | E '/' E { $$ = $1 / $3; }
    | E '%' E { $$ = $1 % $3; }
    | '(' E ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
    ;

%%

void yyerror(const char *msg)
{
    printf("Expression invalid\n");
    flag = 1;
}

int main()
{
    printf("\nEnter any arithmetic expression which can have operations +, -, *, /, modulus:\n");
    yyparse();

    return 0;
}
