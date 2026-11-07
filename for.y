%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void yyerror(char *s);
%}

%token FOR ID INC DEC GE LE NE NUM EQ INT

%left '+' '-'
%left '*' '/'

%%
    start:
            forstmt '\n' {printf("Valid FOR statement\n");}
            ;

    forstmt :
            FOR '(' init ';' condition ';' increment ')' body
            ;

    init :
        ID '=' expr
        | INT ID '=' expr
        ;
    
    condition:
            expr relop expr
            |
            ;

    increment:
            INC ID
            |ID INC
            |DEC ID
            |ID DEC
            | ID '=' expr
            ;

    body:
        '{' stmt_list '}'
        | stmt
        | ';'

    stmt_list:
            stmt_list stmt
            |
            ;

    stmt:
        ID '=' expr ';'
        | forstmt
        |
        ;

    expr:
        ID
        | NUM
        | expr '+' expr
        | expr '-' expr
        | expr '*' expr
        | expr '/' expr
        | '(' expr ')'
        ;

    relop:
        '<' | '>' | GE | LE | EQ | NE
        ;

%%

int main(){
    printf("Enter a for statement: ");
    yyparse();

    return 1;
}

void yyerror(char *s){
    printf("Invalid For statement\n");
    exit(0);
}