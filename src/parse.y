%{
#include <stdio.h>
#include "parse.tab.hh"

extern FILE* yyin;

#define YYSTYPE yy::parser::semantic_type
#define YYLTYPE yy::parser::location_type

int  yylex (YYSTYPE*, YYLTYPE*);
void yyerror (char const *);
%}

%language "c++"

%token IDENTIFIER STRING DECIMAL HEXADECIMAL OCTAL

%union {
  int ival;
  double dval;
}


%%

schema:
      %empty
    | statement
;

statement:
      declaration       { printf("declaration: %d", @1.begin.line); }
;

declaration:
      IDENTIFIER '=' type
;

type:
      IDENTIFIER        { printf("ID: %d", @1.begin.line); }
    | '[' type ']'      { printf("[type]: %d", @1.begin.line); }

%%
