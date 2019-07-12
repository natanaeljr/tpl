%{
#include "parse.tab.hh"
%}

%option noyywrap

string \"[^\n"]+\"

%%

[ \t]    /* ignore white spaces */

{string} {printf("got a string: %s", YYText()); return yy::parser::symbol_type (yy::parser::token::STRING, YYText()) }

%%
