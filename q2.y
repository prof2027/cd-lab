%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void yyerror(char *s);
%}


%token LETTER DIGIT


%%
    start :
        variable '\n' {printf("Valid Variable\n");}
        ;

    variable :
        LETTER
        | variable LETTER
        | variable DIGIT
        ;
%%

int main(){
    printf("Enter a variable:" );
    yyparse();
    return 0;
}

void yyerror(char *s){
    printf("Invalid Variable\n");
    exit(0);
}