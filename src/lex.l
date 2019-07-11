%{
#include "tpl/token.h"
%}

%option yylineno
%option noyywrap

string \"[^\n"]+\"

%%

[ \t]    /* ignore white spaces */

{string} {printf("got a string: %s", YYText());}

%%
