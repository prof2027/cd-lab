%{
    #include <stdio.h>
    #include <ctype.h>
    #include <string.h>
%}

%%

.*vais.*\n {printf("Invalid\n");}
.*Vais.*\n {printf("Invalid\n");}
.*VAIS.*\n {printf("Invalid\n");}
.*\n {printf("valid\n");}

%%

int main(){
    printf("Enter the string: ");
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}


// compile -> lex substr.l
// yacc -d substr.y
// gcc substr.tab.c lex.yy.c -o substr

