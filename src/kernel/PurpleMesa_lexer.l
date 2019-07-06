%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "kernel/PurpleMesa_parser_driver.h"
# include "PurpleMesa_parser.hpp"

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

// The location of the current token.
static yypm::location loc;
%}
%option noyywrap nounput batch debug noinput
%option yylineno
id    [a-zA-Z][a-zA-Z_0-9\._]*
Digits   [0-9]+
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

  /* comments */
"--".*"\r\n"        { loc.lines(); loc.step(); }
"--".*"\n"          { loc.lines(); loc.step(); }

  /* commands */
"exit"              { return yypm::PurpleMesa_parser::make_T_EXIT(loc); }
"help"              { return yypm::PurpleMesa_parser::make_T_HELP(loc); }
"add_design_file"   { return yypm::PurpleMesa_parser::make_T_ADD_DESIGN_FILE(loc); }

{Digits}            {
                      errno = 0;
                      long n = strtol (yytext, NULL, 10);
                      if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
                      driver.error (loc, "integer is out of range");
                      return yypm::PurpleMesa_parser::make_INTEGER(n, loc);
                    }

{id}           { return yypm::PurpleMesa_parser::make_IDENTIFIER(yytext, loc); }
<<EOF>>        return yypm::PurpleMesa_parser::make_END(loc);
.              driver.error (loc, "invalid character");
%%

void
PurpleMesa_parser_driver::scan_begin ()
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
PurpleMesa_parser_driver::scan_end ()
{
    fclose (yyin);
}
