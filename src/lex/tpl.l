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

int yyFlexLexer::yywrap()
{
    return 0;
}

int main()
{
    yyFlexLexer lexer{};
    while (lexer.yylex() != 0)
        ;
    return 0;
}