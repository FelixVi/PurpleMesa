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

  /* comments as defined in 13.8 */
"--".*"\r\n"        { loc.lines(); loc.step(); }
"--".*"\n"          { loc.lines(); loc.step(); }

  /* reserved words as defined in 13.9 */
"abs"               { return yypm::PurpleMesa_parser::make_T_ABS(loc); }
"access"            { return yypm::PurpleMesa_parser::make_T_ACCESS(loc); }
"after"             { return yypm::PurpleMesa_parser::make_T_AFTER(loc); }
"alias"             { return yypm::PurpleMesa_parser::make_T_ALIAS(loc); }
"all"               { return yypm::PurpleMesa_parser::make_T_ALL(loc); }
"and"               { return yypm::PurpleMesa_parser::make_T_AND(loc); }
"architecture"      { return yypm::PurpleMesa_parser::make_T_ARCHITECTURE(loc); }
"array"             { return yypm::PurpleMesa_parser::make_T_ARRAY(loc); }
"assert"            { return yypm::PurpleMesa_parser::make_T_ASSERT(loc); }
"attribute"         { return yypm::PurpleMesa_parser::make_T_ATTRIBUTE(loc); }

"begin"             { return yypm::PurpleMesa_parser::make_T_BEGIN(loc); }
"block"             { return yypm::PurpleMesa_parser::make_T_BLOCK(loc); }
"body"              { return yypm::PurpleMesa_parser::make_T_BODY(loc); }
"buffer"            { return yypm::PurpleMesa_parser::make_T_BUFFER(loc); }
"bus"               { return yypm::PurpleMesa_parser::make_T_BUS(loc); }

"case"              { return yypm::PurpleMesa_parser::make_T_CASE(loc); }
"component"         { return yypm::PurpleMesa_parser::make_T_COMPONENT(loc); }
"configuration"     { return yypm::PurpleMesa_parser::make_T_CONFIGURATION(loc); }
"constant"          { return yypm::PurpleMesa_parser::make_T_CONSTANT(loc); }

"disconnect"        { return yypm::PurpleMesa_parser::make_T_DISCONNECT(loc); }
"downto"            { return yypm::PurpleMesa_parser::make_T_DOWNTO(loc); }

"else"              { return yypm::PurpleMesa_parser::make_T_ELSE(loc); }
"elsif"             { return yypm::PurpleMesa_parser::make_T_ELSIF(loc); }
"end"               { return yypm::PurpleMesa_parser::make_T_END(loc); }
"entity"            { return yypm::PurpleMesa_parser::make_T_ENTITY(loc); }
"exit"              { return yypm::PurpleMesa_parser::make_T_EXIT(loc); }

"file"              { return yypm::PurpleMesa_parser::make_T_FILE(loc); }
"for"               { return yypm::PurpleMesa_parser::make_T_FOR(loc); }
"function"          { return yypm::PurpleMesa_parser::make_T_FUNCTION(loc); }

"generate"          { return yypm::PurpleMesa_parser::make_T_GENERATE(loc); }
"generic"           { return yypm::PurpleMesa_parser::make_T_GENERIC(loc); }
"group"             { return yypm::PurpleMesa_parser::make_T_GROUP(loc); }
"guarded"           { return yypm::PurpleMesa_parser::make_T_GUARDED(loc); }

"if"                { return yypm::PurpleMesa_parser::make_T_IF(loc); }
"impure"            { return yypm::PurpleMesa_parser::make_T_IMPURE(loc); }
"in"                { return yypm::PurpleMesa_parser::make_T_IN(loc); }
"inertial"          { return yypm::PurpleMesa_parser::make_T_INERTIAL(loc); }
"inout"             { return yypm::PurpleMesa_parser::make_T_INOUT(loc); }
"is"                { return yypm::PurpleMesa_parser::make_T_IS(loc); }

"label"             { return yypm::PurpleMesa_parser::make_T_LABEL(loc); }
"library"           { return yypm::PurpleMesa_parser::make_T_LIBRARY(loc); }
"linkage"           { return yypm::PurpleMesa_parser::make_T_LINKAGE(loc); }
"literal"           { return yypm::PurpleMesa_parser::make_T_LITERAL(loc); }
"loop"              { return yypm::PurpleMesa_parser::make_T_LOOP(loc); }

"map"               { return yypm::PurpleMesa_parser::make_T_MAP(loc); }
"mod"               { return yypm::PurpleMesa_parser::make_T_MOD(loc); }

"nand"              { return yypm::PurpleMesa_parser::make_T_NAND(loc); }
"new"               { return yypm::PurpleMesa_parser::make_T_NEW(loc); }
"next"              { return yypm::PurpleMesa_parser::make_T_NEXT(loc); }
"nor"               { return yypm::PurpleMesa_parser::make_T_NOR(loc); }
"not"               { return yypm::PurpleMesa_parser::make_T_NOT(loc); }
"null"              { return yypm::PurpleMesa_parser::make_T_NULL(loc); }

"of"                { return yypm::PurpleMesa_parser::make_T_OF(loc); }
"on"                { return yypm::PurpleMesa_parser::make_T_ON(loc); }
"open"              { return yypm::PurpleMesa_parser::make_T_OPEN(loc); }
"or"                { return yypm::PurpleMesa_parser::make_T_OR(loc); }
"others"            { return yypm::PurpleMesa_parser::make_T_OTHERS(loc); }
"out"               { return yypm::PurpleMesa_parser::make_T_OUT(loc); }

"package"           { return yypm::PurpleMesa_parser::make_T_PACKAGE(loc); }
"port"              { return yypm::PurpleMesa_parser::make_T_PORT(loc); }
"postponed"         { return yypm::PurpleMesa_parser::make_T_POSTPONED(loc); }
"procedural"        { return yypm::PurpleMesa_parser::make_T_PROCEDURAL(loc); }
"procedure"         { return yypm::PurpleMesa_parser::make_T_PROCEDURE(loc); }
"process"           { return yypm::PurpleMesa_parser::make_T_PROCESS(loc); }
"protected"         { return yypm::PurpleMesa_parser::make_T_PROTECTED(loc); }
"pure"              { return yypm::PurpleMesa_parser::make_T_PURE(loc); }

"range"             { return yypm::PurpleMesa_parser::make_T_RANGE(loc); }
"record"            { return yypm::PurpleMesa_parser::make_T_RECORD(loc); }
"reference"         { return yypm::PurpleMesa_parser::make_T_REFERENCE(loc); }
"register"          { return yypm::PurpleMesa_parser::make_T_REGISTER(loc); }
"reject"            { return yypm::PurpleMesa_parser::make_T_REJECT(loc); }
"rem"               { return yypm::PurpleMesa_parser::make_T_REM(loc); }
"report"            { return yypm::PurpleMesa_parser::make_T_REPORT(loc); }
"return"            { return yypm::PurpleMesa_parser::make_T_RETURN(loc); }
"rol"               { return yypm::PurpleMesa_parser::make_T_ROL(loc); }
"ror"               { return yypm::PurpleMesa_parser::make_T_ROR(loc); }

"select"            { return yypm::PurpleMesa_parser::make_T_SELECT(loc); }
"severity"          { return yypm::PurpleMesa_parser::make_T_SEVERITY(loc); }
"signal"            { return yypm::PurpleMesa_parser::make_T_SIGNAL(loc); }
"shared"            { return yypm::PurpleMesa_parser::make_T_SHARED(loc); }
"sla"               { return yypm::PurpleMesa_parser::make_T_SLA(loc); }
"sll"               { return yypm::PurpleMesa_parser::make_T_SLL(loc); }
"sra"               { return yypm::PurpleMesa_parser::make_T_SRA(loc); }
"srl"               { return yypm::PurpleMesa_parser::make_T_SRL(loc); }
"subtype"           { return yypm::PurpleMesa_parser::make_T_SUBTYPE(loc); }

"then"              { return yypm::PurpleMesa_parser::make_T_THEN(loc); }
"to"                { return yypm::PurpleMesa_parser::make_T_TO(loc); }
"transport"         { return yypm::PurpleMesa_parser::make_T_TRANSPORT(loc); }
"type"              { return yypm::PurpleMesa_parser::make_T_TYPE(loc); }

"unaffected"        { return yypm::PurpleMesa_parser::make_T_UNAFFECTED(loc); }
"units"             { return yypm::PurpleMesa_parser::make_T_UNITS(loc); }
"until"             { return yypm::PurpleMesa_parser::make_T_UNTIL(loc); }
"use"               { return yypm::PurpleMesa_parser::make_T_USE(loc); }

"variable"          { return yypm::PurpleMesa_parser::make_T_VARIABLE(loc); }

"wait"              { return yypm::PurpleMesa_parser::make_T_WAIT(loc); }
"when"              { return yypm::PurpleMesa_parser::make_T_WHEN(loc); }
"while"             { return yypm::PurpleMesa_parser::make_T_WHILE(loc); }
"with"              { return yypm::PurpleMesa_parser::make_T_WITH(loc); }

"xnor"              { return yypm::PurpleMesa_parser::make_T_XNOR(loc); }
"xor"               { return yypm::PurpleMesa_parser::make_T_XOR(loc); }

  /* special characters as defined in 13.1c */
"\""                { return yypm::PurpleMesa_parser::make_T_QUOTE(loc); }
"#"                 { return yypm::PurpleMesa_parser::make_T_POUND(loc); }
"&"                 { return yypm::PurpleMesa_parser::make_T_AMPERSAND(loc); }
"'"                 { return yypm::PurpleMesa_parser::make_T_SINGLEQUOTE(loc); }
"("                 { return yypm::PurpleMesa_parser::make_T_LPAREN(loc); }
")"                 { return yypm::PurpleMesa_parser::make_T_RPAREN(loc); }
"*"                 { return yypm::PurpleMesa_parser::make_T_STAR(loc); }
"+"                 { return yypm::PurpleMesa_parser::make_T_PLUS(loc); }
","                 { return yypm::PurpleMesa_parser::make_T_COMMA(loc); }
"-"                 { return yypm::PurpleMesa_parser::make_T_MINUS(loc); }
"."                 { return yypm::PurpleMesa_parser::make_T_DOT(loc); }
"/"                 { return yypm::PurpleMesa_parser::make_T_FORWARDSLASH(loc); }
":"                 { return yypm::PurpleMesa_parser::make_T_COLON(loc); }
";"                 { return yypm::PurpleMesa_parser::make_T_SEMICOLON(loc); }
"<"                 { return yypm::PurpleMesa_parser::make_T_LESSTHAN(loc); }
"="                 { return yypm::PurpleMesa_parser::make_T_EQUAL(loc); }
">"                 { return yypm::PurpleMesa_parser::make_T_GREATERTHAN(loc); }
"["                 { return yypm::PurpleMesa_parser::make_T_LSQUAREPAREN(loc); }
"]"                 { return yypm::PurpleMesa_parser::make_T_RSQUAREPAREN(loc); }
"_"                 { return yypm::PurpleMesa_parser::make_T_UNDERSCORE(loc); }
"|"                 { return yypm::PurpleMesa_parser::make_T_PIPE(loc); }

  /* compound delimiters as defined in 13.2 */
"=>"                { return yypm::PurpleMesa_parser::make_T_ARROW(loc); }
"**"                { return yypm::PurpleMesa_parser::make_T_EXPONENTIATE(loc); }
":="                { return yypm::PurpleMesa_parser::make_T_VAR_ASSIGNMENT(loc); }
"/="                { return yypm::PurpleMesa_parser::make_T_INEQUALITY(loc); }
">="                { return yypm::PurpleMesa_parser::make_T_GREATERTHANOREQUAL(loc); }
"<="                { return yypm::PurpleMesa_parser::make_T_LESSTHANOREQUAL(loc); }
"<>"                { return yypm::PurpleMesa_parser::make_T_BOX(loc); }

  /* more tokens not defined in standard */

  /* "natural"           { return yypm::PurpleMesa_parser::make_NATURAL(loc); } */
  /* "std_logic"         { return yypm::PurpleMesa_parser::make_STD_LOGIC(loc); } */
  /* "std_logic_vector"  { return yypm::PurpleMesa_parser::make_STD_LOGIC_VECTOR(loc); } */


{Digits}            {
                      errno = 0;
                      long n = strtol (yytext, NULL, 10);
                      if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
                      driver.error (loc, "integer is out of range");
                      return yypm::PurpleMesa_parser::make_INTEGER(n, loc);
                    }

{id}           { return yypm::PurpleMesa_parser::make_IDENTIFIER(yytext, loc); }
.              driver.error (loc, "invalid character");
<<EOF>>        return yypm::PurpleMesa_parser::make_END(loc);
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
