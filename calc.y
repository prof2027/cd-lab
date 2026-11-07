%{
    #include <stdio.h>
    #include <stdlib.h>
    
    int yylex();
    void yyerror(char *s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%% 
    start :
            expression '\n'     {printf("Result = %d\n",$1);}
            ;

    expression :
                expression '+' expression {$$=$1+$3;}
                | expression '-' expression {$$=$1-$3;}
                | expression '*' expression {$$=$1*$3;}
                | expression '/' expression {
                                            if($3 == 0){
                                                printf("Division by zero is not possible\n");
                                                exit(0);
                                            }
                                            else{
                                                $$ = $1/$3;
                                            }
                                        }
                | '-' expression %prec UMINUS {$$=-$2;}
                | '(' expression ')' {$$=$2;}
                | NUMBER              {$$=$1;}

                ;

%%

int main(){
    printf("Enter an expression: ");
    yyparse();
    return 0;
}


void yyerror(char * s) {
    printf("Invalid Expression\n");
    exit(0);
}