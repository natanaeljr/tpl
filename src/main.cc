#include "fmt/core.h"
#include "FlexLexer.h"


int main()
{
    yyFlexLexer lexer{};
    while (lexer.yylex() != 0)
        ;
    return 0;
}