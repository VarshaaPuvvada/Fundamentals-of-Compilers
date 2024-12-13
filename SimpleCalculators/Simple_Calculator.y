%{
#include<stdio.h>
#include<stdlib.h>

int yylex();
void yyerror(const char *msg);

%}

%token NUM VAR
%left '+' '-'
%left '*' '/' '%'
%right NEGATIVE

%%

S: E { printf("\n"); }
;

E: E '+' E { printf("+"); }
 | E '*' E { printf("*"); }
 | E '-' E { printf("-"); }
 | E '/' E { printf("/"); }
 | '(' E ')' 
 | '-' E %prec NEGATIVE { printf("-"); }
 | NUM { printf("%d", yylval); }
 | VAR { printf("%c", yylval); }
;

%%

int main() {
    return yyparse();
}

void yyerror(const char *msg) {
    printf("Error: %s\n", msg);
}
