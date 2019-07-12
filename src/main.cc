
#include "FlexLexer.h"
#include "parse.tab.hh"

#include "fmt/core.h"

int main()
{
    yy::parser parse;
    parse.parse();
}