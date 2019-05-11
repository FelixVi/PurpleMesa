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
%option yylineno
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

"--".*\n       { loc.lines (yyleng); loc.step (); }
"library"      { return yy::vhdl_parser::make_LIBRARY(loc); }
"use"          { return yy::vhdl_parser::make_USE(loc); }
"port"         { return yy::vhdl_parser::make_PORT(loc); }
"entity"       { return yy::vhdl_parser::make_ENTITY(loc); }
"is"           { return yy::vhdl_parser::make_IS(loc); }
"end"          { return yy::vhdl_parser::make_T_END(loc); }
"std_logic"    { return yy::vhdl_parser::make_STD_LOGIC(loc); }
"std_logic_vector"    { return yy::vhdl_parser::make_STD_LOGIC_VECTOR(loc); }
"downto"    { return yy::vhdl_parser::make_DOWNTO(loc); }
"in"           { return yy::vhdl_parser::make_IN(loc); }
"out"          { return yy::vhdl_parser::make_OUT(loc); }
"architecture" { return yy::vhdl_parser::make_ARCHITECTURE(loc); }
"of"           { return yy::vhdl_parser::make_OF(loc); }
"begin"        { return yy::vhdl_parser::make_BEGIN(loc); }
"<="           { return yy::vhdl_parser::make_ASSIGN(loc); }
"process"      { return yy::vhdl_parser::make_PROCESS(loc); }
"and"          { return yy::vhdl_parser::make_AND(loc); }
","            { return yy::vhdl_parser::make_COMMA(loc); }
";"            { return yy::vhdl_parser::make_SEMICOLON(loc); }
":"            { return yy::vhdl_parser::make_COLON(loc); }
"("            { return yy::vhdl_parser::make_LPAREN(loc); }
")"            { return yy::vhdl_parser::make_RPAREN(loc); }

{int}          {
                 errno = 0;
                 long n = strtol (yytext, NULL, 10);
                 if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
                 driver.error (loc, "integer is out of range");
                 return yy::vhdl_parser::make_NUMBER(n, loc);
               }

{id}           { return yy::vhdl_parser::make_IDENTIFIER(yytext, loc); }
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
