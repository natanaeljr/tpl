/**
 * \file scanner.ll
 * \brief Lexical Scanner written in Flex grammar.
 */

%{ /*** C/C++ Declarations ***/

#include <string>

#include "tpl/scanner.h"

/* import the parser's token type into a local typedef */
typedef tpl::Parser::token token;
typedef tpl::Parser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

%}

/***************************************************************************************/

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "TplFlexLexer" */
%option prefix="Tpl"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. disable this for release
 * versions. */
%option debug

/* no support for include files is planned */
%option yywrap nounput

/* enables the use of start condition stacks */
%option stack

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

/***************************************************************************************/
/*** Regular Expressions Part ***/

DECIMAL         0|[1-9][0-9]*
OCTAL           0[0-7]+
HEXADECIMAL     0(x|X)[a-fA-F0-9]
INTEGER         {DECIMAL}|{OCTAL}|{HEXADECIMAL}
FLOAT           {DECIMAL}*"."{DECIMAL}+f

/***************************************************************************************/

%%

%{
/* code to place at the beginning of yylex() */
    // reset location
    yylloc->step();
%}

[_A-Za-z][A-Za-z0-9_]+ {
    yylval->stringVal = new std::string(yytext, yyleng);
    return token::ID;
}

= {
    return token::ASSIGN;
}

[ \t\r]+ {
/* gobble up white-spaces */
    yylloc->step();
}

\n {
/* gobble up end-of-lines */
    yylloc->lines(yyleng); yylloc->step();
    return token::EOL;
}

. {
/* pass all other characters up to bison */
    return static_cast<token_type>(*yytext);
}

%% /*** End of Regular Expressions Part ***/

/***************************************************************************************/

namespace tpl {

Scanner::Scanner(std::istream* in,
		 std::ostream* out)
    : TplFlexLexer(in, out)
{
}

Scanner::~Scanner()
{
}

void Scanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

}

/* This implementation of TplFlexLexer::yylex() is required to fill the
 * vtable of the class TplFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int TplFlexLexer::yylex()
{
    std::cerr << "in TplFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int TplFlexLexer::yywrap()
{
    return 1;
}
