%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "vhdl_parser/vhdl_parser_driver.h"
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

  /* comments as defined in 13.8 */
"--".*"\r\n"        { loc.lines(); loc.step(); }
"--".*"\n"          { loc.lines(); loc.step(); }

  /* reserved words as defined in 13.9 */
"abs"               { return yy::vhdl_parser::make_T_ABS(loc); }
"access"            { return yy::vhdl_parser::make_T_ACCESS(loc); }
"after"             { return yy::vhdl_parser::make_T_AFTER(loc); }
"alias"             { return yy::vhdl_parser::make_T_ALIAS(loc); }
"all"               { return yy::vhdl_parser::make_T_ALL(loc); }
"and"               { return yy::vhdl_parser::make_T_AND(loc); }
"architecture"      { return yy::vhdl_parser::make_T_ARCHITECTURE(loc); }
"array"             { return yy::vhdl_parser::make_T_ARRAY(loc); }
"assert"            { return yy::vhdl_parser::make_T_ASSERT(loc); }
"attribute"         { return yy::vhdl_parser::make_T_ATTRIBUTE(loc); }

"begin"             { return yy::vhdl_parser::make_T_BEGIN(loc); }
"block"             { return yy::vhdl_parser::make_T_BLOCK(loc); }
"body"              { return yy::vhdl_parser::make_T_BODY(loc); }
"buffer"            { return yy::vhdl_parser::make_T_BUFFER(loc); }
"bus"               { return yy::vhdl_parser::make_T_BUS(loc); }

"case"              { return yy::vhdl_parser::make_T_CASE(loc); }
"component"         { return yy::vhdl_parser::make_T_COMPONENT(loc); }
"configuration"     { return yy::vhdl_parser::make_T_CONFIGURATION(loc); }
"constant"          { return yy::vhdl_parser::make_T_CONSTANT(loc); }

"disconnect"        { return yy::vhdl_parser::make_T_DISCONNECT(loc); }
"downto"            { return yy::vhdl_parser::make_T_DOWNTO(loc); }

"else"              { return yy::vhdl_parser::make_T_ELSE(loc); }
"elsif"             { return yy::vhdl_parser::make_T_ELSIF(loc); }
"end"               { return yy::vhdl_parser::make_T_END(loc); }
"entity"            { return yy::vhdl_parser::make_T_ENTITY(loc); }
"exit"              { return yy::vhdl_parser::make_T_EXIT(loc); }

"file"              { return yy::vhdl_parser::make_T_FILE(loc); }
"for"               { return yy::vhdl_parser::make_T_FOR(loc); }
"function"          { return yy::vhdl_parser::make_T_FUNCTION(loc); }

"generate"          { return yy::vhdl_parser::make_T_GENERATE(loc); }
"generic"           { return yy::vhdl_parser::make_T_GENERIC(loc); }
"group"             { return yy::vhdl_parser::make_T_GROUP(loc); }
"guarded"           { return yy::vhdl_parser::make_T_GUARDED(loc); }

"if"                { return yy::vhdl_parser::make_T_IF(loc); }
"impure"            { return yy::vhdl_parser::make_T_IMPURE(loc); }
"in"                { return yy::vhdl_parser::make_T_IN(loc); }
"inertial"          { return yy::vhdl_parser::make_T_INERTIAL(loc); }
"inout"             { return yy::vhdl_parser::make_T_INOUT(loc); }
"is"                { return yy::vhdl_parser::make_T_IS(loc); }

"label"             { return yy::vhdl_parser::make_T_LABEL(loc); }
"library"           { return yy::vhdl_parser::make_T_LIBRARY(loc); }
"linkage"           { return yy::vhdl_parser::make_T_LINKAGE(loc); }
"literal"           { return yy::vhdl_parser::make_T_LITERAL(loc); }
"loop"              { return yy::vhdl_parser::make_T_LOOP(loc); }

"map"               { return yy::vhdl_parser::make_T_MAP(loc); }
"mod"               { return yy::vhdl_parser::make_T_MOD(loc); }

"nand"              { return yy::vhdl_parser::make_T_NAND(loc); }
"new"               { return yy::vhdl_parser::make_T_NEW(loc); }
"next"              { return yy::vhdl_parser::make_T_NEXT(loc); }
"nor"               { return yy::vhdl_parser::make_T_NOR(loc); }
"not"               { return yy::vhdl_parser::make_T_NOT(loc); }
"null"              { return yy::vhdl_parser::make_T_NULL(loc); }

"of"                { return yy::vhdl_parser::make_T_OF(loc); }
"on"                { return yy::vhdl_parser::make_T_ON(loc); }
"open"              { return yy::vhdl_parser::make_T_OPEN(loc); }
"or"                { return yy::vhdl_parser::make_T_OR(loc); }
"others"            { return yy::vhdl_parser::make_T_OTHERS(loc); }
"out"               { return yy::vhdl_parser::make_T_OUT(loc); }

"package"           { return yy::vhdl_parser::make_T_PACKAGE(loc); }
"port"              { return yy::vhdl_parser::make_T_PORT(loc); }
"postponed"         { return yy::vhdl_parser::make_T_POSTPONED(loc); }
"procedural"        { return yy::vhdl_parser::make_T_PROCEDURAL(loc); }
"procedure"         { return yy::vhdl_parser::make_T_PROCEDURE(loc); }
"process"           { return yy::vhdl_parser::make_T_PROCESS(loc); }
"protected"         { return yy::vhdl_parser::make_T_PROTECTED(loc); }
"pure"              { return yy::vhdl_parser::make_T_PURE(loc); }

"range"             { return yy::vhdl_parser::make_T_RANGE(loc); }
"record"            { return yy::vhdl_parser::make_T_RECORD(loc); }
"reference"         { return yy::vhdl_parser::make_T_REFERENCE(loc); }
"register"          { return yy::vhdl_parser::make_T_REGISTER(loc); }
"reject"            { return yy::vhdl_parser::make_T_REJECT(loc); }
"rem"               { return yy::vhdl_parser::make_T_REM(loc); }
"report"            { return yy::vhdl_parser::make_T_REPORT(loc); }
"return"            { return yy::vhdl_parser::make_T_RETURN(loc); }
"rol"               { return yy::vhdl_parser::make_T_ROL(loc); }
"ror"               { return yy::vhdl_parser::make_T_ROR(loc); }

"select"            { return yy::vhdl_parser::make_T_SELECT(loc); }
"severity"          { return yy::vhdl_parser::make_T_SEVERITY(loc); }
"signal"            { return yy::vhdl_parser::make_T_SIGNAL(loc); }
"shared"            { return yy::vhdl_parser::make_T_SHARED(loc); }
"sla"               { return yy::vhdl_parser::make_T_SLA(loc); }
"sll"               { return yy::vhdl_parser::make_T_SLL(loc); }
"sra"               { return yy::vhdl_parser::make_T_SRA(loc); }
"srl"               { return yy::vhdl_parser::make_T_SRL(loc); }
"subtype"           { return yy::vhdl_parser::make_T_SUBTYPE(loc); }

"then"              { return yy::vhdl_parser::make_T_THEN(loc); }
"to"                { return yy::vhdl_parser::make_T_TO(loc); }
"transport"         { return yy::vhdl_parser::make_T_TRANSPORT(loc); }
"type"              { return yy::vhdl_parser::make_T_TYPE(loc); }

"unaffected"        { return yy::vhdl_parser::make_T_UNAFFECTED(loc); }
"units"             { return yy::vhdl_parser::make_T_UNITS(loc); }
"until"             { return yy::vhdl_parser::make_T_UNTIL(loc); }
"use"               { return yy::vhdl_parser::make_T_USE(loc); }

"variable"          { return yy::vhdl_parser::make_T_VARIABLE(loc); }

"wait"              { return yy::vhdl_parser::make_T_WAIT(loc); }
"when"              { return yy::vhdl_parser::make_T_WHEN(loc); }
"while"             { return yy::vhdl_parser::make_T_WHILE(loc); }
"with"              { return yy::vhdl_parser::make_T_WITH(loc); }

"xnor"              { return yy::vhdl_parser::make_T_XNOR(loc); }
"xor"               { return yy::vhdl_parser::make_T_XOR(loc); }

  /* special characters as defined in 13.1c */
"\""                { return yy::vhdl_parser::make_T_QUOTE(loc); }
"#"                 { return yy::vhdl_parser::make_T_POUND(loc); }
"&"                 { return yy::vhdl_parser::make_T_AMPERSAND(loc); }
"'"                 { return yy::vhdl_parser::make_T_SINGLEQUOTE(loc); }
"("                 { return yy::vhdl_parser::make_T_LPAREN(loc); }
")"                 { return yy::vhdl_parser::make_T_RPAREN(loc); }
"*"                 { return yy::vhdl_parser::make_T_STAR(loc); }
"+"                 { return yy::vhdl_parser::make_T_PLUS(loc); }
","                 { return yy::vhdl_parser::make_T_COMMA(loc); }
"-"                 { return yy::vhdl_parser::make_T_MINUS(loc); }
"."                 { return yy::vhdl_parser::make_T_DOT(loc); }
"/"                 { return yy::vhdl_parser::make_T_FORWARDSLASH(loc); }
":"                 { return yy::vhdl_parser::make_T_COLON(loc); }
";"                 { return yy::vhdl_parser::make_T_SEMICOLON(loc); }
"<"                 { return yy::vhdl_parser::make_T_LESSTHAN(loc); }
"="                 { return yy::vhdl_parser::make_T_EQUAL(loc); }
">"                 { return yy::vhdl_parser::make_T_GREATERTHAN(loc); }
"["                 { return yy::vhdl_parser::make_T_LSQUAREPAREN(loc); }
"]"                 { return yy::vhdl_parser::make_T_RSQUAREPAREN(loc); }
"_"                 { return yy::vhdl_parser::make_T_UNDERSCORE(loc); }
"|"                 { return yy::vhdl_parser::make_T_PIPE(loc); }

  /* compound delimiters as defined in 13.2 */
"=>"                { return yy::vhdl_parser::make_T_ARROW(loc); }
"**"                { return yy::vhdl_parser::make_T_EXPONENTIATE(loc); }
":="                { return yy::vhdl_parser::make_T_VAR_ASSIGNMENT(loc); }
"/="                { return yy::vhdl_parser::make_T_INEQUALITY(loc); }
">="                { return yy::vhdl_parser::make_T_GREATERTHANOREQUAL(loc); }
"<="                { return yy::vhdl_parser::make_T_LESSTHANOREQUAL(loc); }
"<>"                { return yy::vhdl_parser::make_T_BOX(loc); }

  /* more tokens not defined in standard */

  /* "natural"           { return yy::vhdl_parser::make_NATURAL(loc); } */
  /* "std_logic"         { return yy::vhdl_parser::make_STD_LOGIC(loc); } */
  /* "std_logic_vector"  { return yy::vhdl_parser::make_STD_LOGIC_VECTOR(loc); } */


{Digits}            {
                      errno = 0;
                      long n = strtol (yytext, NULL, 10);
                      if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
                      driver.error (loc, "integer is out of range");
                      return yy::vhdl_parser::make_INTEGER(n, loc);
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
    yylineno = 1;
    loc.initialize();
}



void
vhdl_driver::scan_end ()
{
    fclose (yyin);
}
