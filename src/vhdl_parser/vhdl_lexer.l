%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "vhdl_parser_driver.h"
# include "vhdl_parser.hpp"

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

// The location of the current token.
static yy::location loc;
%}
%option noyywrap nounput batch debug noinput
id    [a-zA-Z][a-zA-Z_0-9\._]*
int   [0-9]+
blank [ \t]

%{
// Code run each time a pattern is matched.
# define YY_USER_ACTION  loc.columns (yyleng);
%}

%%

%{
// Code run each time yylex is called.
loc.step ();
%}

{blank}+   loc.step ();
[\n]+      loc.lines (yyleng); loc.step ();

"--".*\n       { printf("COMMENT\n"); loc.lines (yyleng); loc.step (); }
"library"      { printf("LIBRARY\n"); return yy::vhdl_parser::make_LIBRARY(loc); }
"use"          { printf("USE\n"); return yy::vhdl_parser::make_USE(loc); }
"port"         { printf("PORT\n"); return yy::vhdl_parser::make_PORT(loc); }
"entity"       { printf("ENTITY\n"); return yy::vhdl_parser::make_ENTITY(loc); }
"is"           { printf("IS\n"); return yy::vhdl_parser::make_IS(loc); }
"end"          { printf("END\n"); return yy::vhdl_parser::make_T_END(loc); }
"std_logic"    { printf("STD_LOGIC\n"); return yy::vhdl_parser::make_STD_LOGIC(loc); }
"in"           { printf("IN\n"); return yy::vhdl_parser::make_IN(loc); }
"out"          { printf("OUT\n"); return yy::vhdl_parser::make_OUT(loc); }
"architecture" { printf("ARCHITECTURE\n"); return yy::vhdl_parser::make_ARCHITECTURE(loc); }
"of"           { printf("OF\n"); return yy::vhdl_parser::make_OF(loc); }
"begin"        { printf("BEGIN\n"); return yy::vhdl_parser::make_BEGIN(loc); }
"<="           { printf("<=\n"); return yy::vhdl_parser::make_ASSIGN(loc); }
"process"      { printf("PROCESS\n"); return yy::vhdl_parser::make_PROCESS(loc); }
"and"          { printf("AND\n"); return yy::vhdl_parser::make_AND(loc); }
","            { printf(",\n"); return yy::vhdl_parser::make_COMMA(loc); }
";"            { printf("SEMICOLON\n"); return yy::vhdl_parser::make_SEMICOLON(loc); }
":"            { printf("COLON\n"); return yy::vhdl_parser::make_COLON(loc); }
"("            { printf("(\n"); return yy::vhdl_parser::make_LPAREN(loc); }
")"            { printf(")\n"); return yy::vhdl_parser::make_RPAREN(loc); }

{int}          {
                 errno = 0;
                 long n = strtol (yytext, NULL, 10);
                 if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
                 driver.error (loc, "integer is out of range");
                 return yy::vhdl_parser::make_NUMBER(n, loc);
               }

{id}           { printf("ID\n"); return yy::vhdl_parser::make_IDENTIFIER(yytext, loc); }
.              driver.error (loc, "invalid character");
<<EOF>>        return yy::vhdl_parser::make_END(loc);
%%

void
vhdl_driver::scan_begin ()
{
    yy_flex_debug = trace_scanning;
    if (file.empty () || file == "-")
        yyin = stdin;
    else if (!(yyin = fopen (file.c_str (), "r")))
    {
        error ("cannot open " + file + ": " + strerror(errno));
        exit (EXIT_FAILURE);
    }
}



void
vhdl_driver::scan_end ()
{
    fclose (yyin);
}
