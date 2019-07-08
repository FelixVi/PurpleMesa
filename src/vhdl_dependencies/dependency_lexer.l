%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "vhdl_dependencies/dependency_parser_driver.h"
# include "dependency_parser.hpp"

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

// The location of the current token.
static yydep::location loc;
%}
%option noyywrap nounput batch debug noinput
%option yylineno
id    [.][.]*
blank [ \t]

%{
// Code run each time a pattern is matched.
# define YY_USER_ACTION  loc.columns (yyleng);
%}

%%

%{
// Code run each time yylex is called.
loc.step();
%}

{blank}+            { loc.step(); }
"\r\n"              { loc.lines(); loc.step(); }
"\n"                { loc.lines(); loc.step(); }

  /* comments as defined in 13.8 */
"--".*"\r\n"        { loc.lines(); loc.step(); }
"--".*"\n"          { loc.lines(); loc.step(); }

  /* reserved words as defined in 13.9 */
"library"           { return yydep::dependency_parser::make_T_LIBRARY(loc); }
"use"               { return yydep::dependency_parser::make_T_USE(loc); }

  /* special characters as defined in 13.1c */
";"                 { return yydep::dependency_parser::make_T_SEMICOLON(loc); }

  /* more tokens not defined in standard */

  /* "natural"           { return yydep::dependency_parser::make_NATURAL(loc); } */
  /* "std_logic"         { return yydep::dependency_parser::make_STD_LOGIC(loc); } */
  /* "std_logic_vector"  { return yydep::dependency_parser::make_STD_LOGIC_VECTOR(loc); } */
{id}           { return yydep::dependency_parser::make_IDENTIFIER(yytext, loc); }
<<EOF>>        return yydep::dependency_parser::make_END(loc);
%%

void
dependency_driver::scan_begin ()
{
    yy_flex_debug = trace_scanning;
    if (file.empty () || file == "-")
        yyin = stdin;
    else if (!(yyin = fopen (file.c_str (), "r")))
    {
        error ("cannot open " + file + ": " + strerror(errno));
        exit (EXIT_FAILURE);
    }
    yylineno = 1;
    loc.initialize();
}



void
dependency_driver::scan_end ()
{
    fclose (yyin);
}
