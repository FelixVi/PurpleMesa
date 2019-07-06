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
static yyvhdl::location loc;
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
"abs"               { return yyvhdl::vhdl_parser::make_T_ABS(loc); }
"access"            { return yyvhdl::vhdl_parser::make_T_ACCESS(loc); }
"after"             { return yyvhdl::vhdl_parser::make_T_AFTER(loc); }
"alias"             { return yyvhdl::vhdl_parser::make_T_ALIAS(loc); }
"all"               { return yyvhdl::vhdl_parser::make_T_ALL(loc); }
"and"               { return yyvhdl::vhdl_parser::make_T_AND(loc); }
"architecture"      { return yyvhdl::vhdl_parser::make_T_ARCHITECTURE(loc); }
"array"             { return yyvhdl::vhdl_parser::make_T_ARRAY(loc); }
"assert"            { return yyvhdl::vhdl_parser::make_T_ASSERT(loc); }
"attribute"         { return yyvhdl::vhdl_parser::make_T_ATTRIBUTE(loc); }

"begin"             { return yyvhdl::vhdl_parser::make_T_BEGIN(loc); }
"block"             { return yyvhdl::vhdl_parser::make_T_BLOCK(loc); }
"body"              { return yyvhdl::vhdl_parser::make_T_BODY(loc); }
"buffer"            { return yyvhdl::vhdl_parser::make_T_BUFFER(loc); }
"bus"               { return yyvhdl::vhdl_parser::make_T_BUS(loc); }

"case"              { return yyvhdl::vhdl_parser::make_T_CASE(loc); }
"component"         { return yyvhdl::vhdl_parser::make_T_COMPONENT(loc); }
"configuration"     { return yyvhdl::vhdl_parser::make_T_CONFIGURATION(loc); }
"constant"          { return yyvhdl::vhdl_parser::make_T_CONSTANT(loc); }

"disconnect"        { return yyvhdl::vhdl_parser::make_T_DISCONNECT(loc); }
"downto"            { return yyvhdl::vhdl_parser::make_T_DOWNTO(loc); }

"else"              { return yyvhdl::vhdl_parser::make_T_ELSE(loc); }
"elsif"             { return yyvhdl::vhdl_parser::make_T_ELSIF(loc); }
"end"               { return yyvhdl::vhdl_parser::make_T_END(loc); }
"entity"            { return yyvhdl::vhdl_parser::make_T_ENTITY(loc); }
"exit"              { return yyvhdl::vhdl_parser::make_T_EXIT(loc); }

"file"              { return yyvhdl::vhdl_parser::make_T_FILE(loc); }
"for"               { return yyvhdl::vhdl_parser::make_T_FOR(loc); }
"function"          { return yyvhdl::vhdl_parser::make_T_FUNCTION(loc); }

"generate"          { return yyvhdl::vhdl_parser::make_T_GENERATE(loc); }
"generic"           { return yyvhdl::vhdl_parser::make_T_GENERIC(loc); }
"group"             { return yyvhdl::vhdl_parser::make_T_GROUP(loc); }
"guarded"           { return yyvhdl::vhdl_parser::make_T_GUARDED(loc); }

"if"                { return yyvhdl::vhdl_parser::make_T_IF(loc); }
"impure"            { return yyvhdl::vhdl_parser::make_T_IMPURE(loc); }
"in"                { return yyvhdl::vhdl_parser::make_T_IN(loc); }
"inertial"          { return yyvhdl::vhdl_parser::make_T_INERTIAL(loc); }
"inout"             { return yyvhdl::vhdl_parser::make_T_INOUT(loc); }
"is"                { return yyvhdl::vhdl_parser::make_T_IS(loc); }

"label"             { return yyvhdl::vhdl_parser::make_T_LABEL(loc); }
"library"           { return yyvhdl::vhdl_parser::make_T_LIBRARY(loc); }
"linkage"           { return yyvhdl::vhdl_parser::make_T_LINKAGE(loc); }
"literal"           { return yyvhdl::vhdl_parser::make_T_LITERAL(loc); }
"loop"              { return yyvhdl::vhdl_parser::make_T_LOOP(loc); }

"map"               { return yyvhdl::vhdl_parser::make_T_MAP(loc); }
"mod"               { return yyvhdl::vhdl_parser::make_T_MOD(loc); }

"nand"              { return yyvhdl::vhdl_parser::make_T_NAND(loc); }
"new"               { return yyvhdl::vhdl_parser::make_T_NEW(loc); }
"next"              { return yyvhdl::vhdl_parser::make_T_NEXT(loc); }
"nor"               { return yyvhdl::vhdl_parser::make_T_NOR(loc); }
"not"               { return yyvhdl::vhdl_parser::make_T_NOT(loc); }
"null"              { return yyvhdl::vhdl_parser::make_T_NULL(loc); }

"of"                { return yyvhdl::vhdl_parser::make_T_OF(loc); }
"on"                { return yyvhdl::vhdl_parser::make_T_ON(loc); }
"open"              { return yyvhdl::vhdl_parser::make_T_OPEN(loc); }
"or"                { return yyvhdl::vhdl_parser::make_T_OR(loc); }
"others"            { return yyvhdl::vhdl_parser::make_T_OTHERS(loc); }
"out"               { return yyvhdl::vhdl_parser::make_T_OUT(loc); }

"package"           { return yyvhdl::vhdl_parser::make_T_PACKAGE(loc); }
"port"              { return yyvhdl::vhdl_parser::make_T_PORT(loc); }
"postponed"         { return yyvhdl::vhdl_parser::make_T_POSTPONED(loc); }
"procedural"        { return yyvhdl::vhdl_parser::make_T_PROCEDURAL(loc); }
"procedure"         { return yyvhdl::vhdl_parser::make_T_PROCEDURE(loc); }
"process"           { return yyvhdl::vhdl_parser::make_T_PROCESS(loc); }
"protected"         { return yyvhdl::vhdl_parser::make_T_PROTECTED(loc); }
"pure"              { return yyvhdl::vhdl_parser::make_T_PURE(loc); }

"range"             { return yyvhdl::vhdl_parser::make_T_RANGE(loc); }
"record"            { return yyvhdl::vhdl_parser::make_T_RECORD(loc); }
"reference"         { return yyvhdl::vhdl_parser::make_T_REFERENCE(loc); }
"register"          { return yyvhdl::vhdl_parser::make_T_REGISTER(loc); }
"reject"            { return yyvhdl::vhdl_parser::make_T_REJECT(loc); }
"rem"               { return yyvhdl::vhdl_parser::make_T_REM(loc); }
"report"            { return yyvhdl::vhdl_parser::make_T_REPORT(loc); }
"return"            { return yyvhdl::vhdl_parser::make_T_RETURN(loc); }
"rol"               { return yyvhdl::vhdl_parser::make_T_ROL(loc); }
"ror"               { return yyvhdl::vhdl_parser::make_T_ROR(loc); }

"select"            { return yyvhdl::vhdl_parser::make_T_SELECT(loc); }
"severity"          { return yyvhdl::vhdl_parser::make_T_SEVERITY(loc); }
"signal"            { return yyvhdl::vhdl_parser::make_T_SIGNAL(loc); }
"shared"            { return yyvhdl::vhdl_parser::make_T_SHARED(loc); }
"sla"               { return yyvhdl::vhdl_parser::make_T_SLA(loc); }
"sll"               { return yyvhdl::vhdl_parser::make_T_SLL(loc); }
"sra"               { return yyvhdl::vhdl_parser::make_T_SRA(loc); }
"srl"               { return yyvhdl::vhdl_parser::make_T_SRL(loc); }
"subtype"           { return yyvhdl::vhdl_parser::make_T_SUBTYPE(loc); }

"then"              { return yyvhdl::vhdl_parser::make_T_THEN(loc); }
"to"                { return yyvhdl::vhdl_parser::make_T_TO(loc); }
"transport"         { return yyvhdl::vhdl_parser::make_T_TRANSPORT(loc); }
"type"              { return yyvhdl::vhdl_parser::make_T_TYPE(loc); }

"unaffected"        { return yyvhdl::vhdl_parser::make_T_UNAFFECTED(loc); }
"units"             { return yyvhdl::vhdl_parser::make_T_UNITS(loc); }
"until"             { return yyvhdl::vhdl_parser::make_T_UNTIL(loc); }
"use"               { return yyvhdl::vhdl_parser::make_T_USE(loc); }

"variable"          { return yyvhdl::vhdl_parser::make_T_VARIABLE(loc); }

"wait"              { return yyvhdl::vhdl_parser::make_T_WAIT(loc); }
"when"              { return yyvhdl::vhdl_parser::make_T_WHEN(loc); }
"while"             { return yyvhdl::vhdl_parser::make_T_WHILE(loc); }
"with"              { return yyvhdl::vhdl_parser::make_T_WITH(loc); }

"xnor"              { return yyvhdl::vhdl_parser::make_T_XNOR(loc); }
"xor"               { return yyvhdl::vhdl_parser::make_T_XOR(loc); }

  /* special characters as defined in 13.1c */
"\""                { return yyvhdl::vhdl_parser::make_T_QUOTE(loc); }
"#"                 { return yyvhdl::vhdl_parser::make_T_POUND(loc); }
"&"                 { return yyvhdl::vhdl_parser::make_T_AMPERSAND(loc); }
"'"                 { return yyvhdl::vhdl_parser::make_T_SINGLEQUOTE(loc); }
"("                 { return yyvhdl::vhdl_parser::make_T_LPAREN(loc); }
")"                 { return yyvhdl::vhdl_parser::make_T_RPAREN(loc); }
"*"                 { return yyvhdl::vhdl_parser::make_T_STAR(loc); }
"+"                 { return yyvhdl::vhdl_parser::make_T_PLUS(loc); }
","                 { return yyvhdl::vhdl_parser::make_T_COMMA(loc); }
"-"                 { return yyvhdl::vhdl_parser::make_T_MINUS(loc); }
"."                 { return yyvhdl::vhdl_parser::make_T_DOT(loc); }
"/"                 { return yyvhdl::vhdl_parser::make_T_FORWARDSLASH(loc); }
":"                 { return yyvhdl::vhdl_parser::make_T_COLON(loc); }
";"                 { return yyvhdl::vhdl_parser::make_T_SEMICOLON(loc); }
"<"                 { return yyvhdl::vhdl_parser::make_T_LESSTHAN(loc); }
"="                 { return yyvhdl::vhdl_parser::make_T_EQUAL(loc); }
">"                 { return yyvhdl::vhdl_parser::make_T_GREATERTHAN(loc); }
"["                 { return yyvhdl::vhdl_parser::make_T_LSQUAREPAREN(loc); }
"]"                 { return yyvhdl::vhdl_parser::make_T_RSQUAREPAREN(loc); }
"_"                 { return yyvhdl::vhdl_parser::make_T_UNDERSCORE(loc); }
"|"                 { return yyvhdl::vhdl_parser::make_T_PIPE(loc); }

  /* compound delimiters as defined in 13.2 */
"=>"                { return yyvhdl::vhdl_parser::make_T_ARROW(loc); }
"**"                { return yyvhdl::vhdl_parser::make_T_EXPONENTIATE(loc); }
":="                { return yyvhdl::vhdl_parser::make_T_VAR_ASSIGNMENT(loc); }
"/="                { return yyvhdl::vhdl_parser::make_T_INEQUALITY(loc); }
">="                { return yyvhdl::vhdl_parser::make_T_GREATERTHANOREQUAL(loc); }
"<="                { return yyvhdl::vhdl_parser::make_T_LESSTHANOREQUAL(loc); }
"<>"                { return yyvhdl::vhdl_parser::make_T_BOX(loc); }

  /* more tokens not defined in standard */

  /* "natural"           { return yyvhdl::vhdl_parser::make_NATURAL(loc); } */
  /* "std_logic"         { return yyvhdl::vhdl_parser::make_STD_LOGIC(loc); } */
  /* "std_logic_vector"  { return yyvhdl::vhdl_parser::make_STD_LOGIC_VECTOR(loc); } */


{Digits}            {
                      errno = 0;
                      long n = strtol (yytext, NULL, 10);
                      if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
                      driver.error (loc, "integer is out of range");
                      return yyvhdl::vhdl_parser::make_INTEGER(n, loc);
                    }

{id}           { return yyvhdl::vhdl_parser::make_IDENTIFIER(yytext, loc); }
.              driver.error (loc, "invalid character");
<<EOF>>        return yyvhdl::vhdl_parser::make_END(loc);
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
