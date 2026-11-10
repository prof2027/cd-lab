
%{
#include <stdio.h>

int single = 0, multi = 0;
%}

%%
"//"[^\n]* {
    single++;
    printf("Single-line comment: %s\n", yytext);
}

"/*"([^*]|\*+[^*/])*\*+"/" {
    multi++;
    printf("Multi-line comment: %s\n", yytext);
}

.|\n ;
%%

int main()
{
    printf("Enter C code (Ctrl+D to stop):\n");
    yylex();

    printf("\nTotal single-line comments: %d\n", single);
    printf("Total multi-line comments: %d\n", multi);

    return 0;
}

int yywrap()
{
    return 1;
}
