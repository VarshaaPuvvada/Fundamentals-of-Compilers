%{
  int yywrap(void) {
    return 1;
  }
%}

%s A B C D DEAD
%%
<INITIAL>0 BEGIN B;
<INITIAL>1 BEGIN D;
<INITIAL>[^01\n] BEGIN DEAD;
<INITIAL>\n BEGIN INITIAL; { printf("Not Accepted\n"); }

<A>0 BEGIN B;
<A>1 BEGIN D;
<A>[^01\n] BEGIN DEAD;
<A>\n BEGIN INITIAL; { printf("Not Accepted\n"); }

<B>0 BEGIN A;
<B>1 BEGIN C;
<B>[^01\n] BEGIN DEAD;
<B>\n BEGIN INITIAL; { printf("Accepted\n"); }

<C>0 BEGIN D;
<C>1 BEGIN B;
<C>[^01\n] BEGIN DEAD;
<C>\n BEGIN INITIAL; { printf("Not Accepted\n"); }

<D>0 BEGIN C;
<D>1 BEGIN A;
<D>[^01\n] BEGIN DEAD;
<D>\n BEGIN INITIAL; { printf("Not Accepted\n"); }

<DEAD>[^01\n] BEGIN DEAD;
<DEAD>\n BEGIN INITIAL; { printf("Invalid\n"); }

%%
int main() {
  printf("Enter the String\n");
  yylex();
  return 0;
}
