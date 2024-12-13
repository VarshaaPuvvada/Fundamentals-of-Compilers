%{
  int yywrap(void){
    return 1;
  }
%}

%s A B C DEAD
%%
<INITIAL>0 BEGIN A;
<INITIAL>1 BEGIN B;
<INITIAL>[^01\n] BEGIN DEAD;
<INITIAL>\n BEGIN INITIAL;{printf("Not Accepted\n");} 
<A>0 BEGIN A;
<A>1 BEGIN B;
<A>[^01\n] BEGIN DEAD;
<A>\n BEGIN INITIAL;{printf("Not Accepted\n");}
<B>0 BEGIN A;
<B>1 BEGIN C;
<B>[^01\n] BEGIN DEAD;
<B>\n  BEGIN INITIAL;{printf("Not Accepted\n");}
<C>0 BEGIN A;
<C>1 BEGIN C;
<C>[^01\n] BEGIN DEAD;
<C>\n BEGIN INITIAL;{printf("Accepted\n");}
<DEAD>[^\n] BEGIN DEAD;
<DEAD>\n BEGIN INITIAL; {printf("Invalid\n");} 
%%
int main()
{
  printf("Enter the String\n");
  yylex();
  return 0;
}
