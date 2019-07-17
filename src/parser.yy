/**
 * \file parser.yy
 * \brief Parser written in Bison grammar.
 */

%{
#include <cstdio>
%}

/***************************************************************************************/

/* Require bison 2.3 or later */
%require "2.3"
/* Generate parser in C++ */
%language "c++"
/* Add debug output code to generated parser. disable this for release versions. */
%debug
/* Start symbol is named "start" */
// %start start
/* Write out a header file containing the token defines */
%defines
/* use newer C++ skeleton file */
%skeleton "lalr1.cc"
/* namespace to enclose parser in */
%name-prefix "tpl"
/* set the parser's class identifier */
%define parser_class_name {Parser}

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

/***************************************************************************************/

/* yylval declaration */
%union {
    int integerVal;
    double doubleVal;
    std::string* stringVal;
    class Node* calcnode;
}

/* Tokens */
%token END 0 "end of file"
%token EOL   "end of line"
%token ASSIGN       "="
%token <integerVal> INTEGER  "integer"
%token <doubleVal>  DOUBLE   "double"
%token <stringVal>  STRING   "string"
%token <stringVal>  ID       "id"

/* Nonterminal Symbols */
/* %type <calcnode>  constant variable */

/* clean symbols resources */
%destructor { delete $$; } STRING ID

/***************************************************************************************/

%{

#include "tpl/driver.h"
#include "tpl/scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

/***************************************************************************************/

%% /* Grammar Rules */

schema: ID ASSIGN
    | END

%% /* End of Grammar Rules */

/***************************************************************************************/

void tpl::Parser::error(const Parser::location_type& l, const std::string& m)
{
    driver.error(l, m);
}
