%{
    #include <stdlib.h>
    #include "for.tab.h"

    
%}

%% 

"for"                   {return FOR;}
"int"                   {return INT;}
">="                    {return GE;}
"<="                    {return LE;}
"=="                    {return EQ;}
"!="                    {return NE;}
"++"                    {return INC;}
"--"                    {return DEC;}
[a-zA-z_][a-zA-z0-9_]*  {return ID;}
[0-9]+                  {return NUM;}
[ \t]                   ;
\n                      {return '\n';}
.                       {return yytext[0];}

%%

int yywrap(){
    return 1;
}
