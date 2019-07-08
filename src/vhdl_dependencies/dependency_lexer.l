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
"abs"               { return yydep::dependency_parser::make_T_ABS(loc); }
"access"            { return yydep::dependency_parser::make_T_ACCESS(loc); }
"after"             { return yydep::dependency_parser::make_T_AFTER(loc); }
"alias"             { return yydep::dependency_parser::make_T_ALIAS(loc); }
"all"               { return yydep::dependency_parser::make_T_ALL(loc); }
"and"               { return yydep::dependency_parser::make_T_AND(loc); }
"architecture"      { return yydep::dependency_parser::make_T_ARCHITECTURE(loc); }
"array"             { return yydep::dependency_parser::make_T_ARRAY(loc); }
"assert"            { return yydep::dependency_parser::make_T_ASSERT(loc); }
"attribute"         { return yydep::dependency_parser::make_T_ATTRIBUTE(loc); }

"begin"             { return yydep::dependency_parser::make_T_BEGIN(loc); }
"block"             { return yydep::dependency_parser::make_T_BLOCK(loc); }
"body"              { return yydep::dependency_parser::make_T_BODY(loc); }
"buffer"            { return yydep::dependency_parser::make_T_BUFFER(loc); }
"bus"               { return yydep::dependency_parser::make_T_BUS(loc); }

"case"              { return yydep::dependency_parser::make_T_CASE(loc); }
"component"         { return yydep::dependency_parser::make_T_COMPONENT(loc); }
"configuration"     { return yydep::dependency_parser::make_T_CONFIGURATION(loc); }
"constant"          { return yydep::dependency_parser::make_T_CONSTANT(loc); }

"disconnect"        { return yydep::dependency_parser::make_T_DISCONNECT(loc); }
"downto"            { return yydep::dependency_parser::make_T_DOWNTO(loc); }

"else"              { return yydep::dependency_parser::make_T_ELSE(loc); }
"elsif"             { return yydep::dependency_parser::make_T_ELSIF(loc); }
"end"               { return yydep::dependency_parser::make_T_END(loc); }
"entity"            { return yydep::dependency_parser::make_T_ENTITY(loc); }
"exit"              { return yydep::dependency_parser::make_T_EXIT(loc); }

"file"              { return yydep::dependency_parser::make_T_FILE(loc); }
"for"               { return yydep::dependency_parser::make_T_FOR(loc); }
"function"          { return yydep::dependency_parser::make_T_FUNCTION(loc); }

"generate"          { return yydep::dependency_parser::make_T_GENERATE(loc); }
"generic"           { return yydep::dependency_parser::make_T_GENERIC(loc); }
"group"             { return yydep::dependency_parser::make_T_GROUP(loc); }
"guarded"           { return yydep::dependency_parser::make_T_GUARDED(loc); }

"if"                { return yydep::dependency_parser::make_T_IF(loc); }
"impure"            { return yydep::dependency_parser::make_T_IMPURE(loc); }
"in"                { return yydep::dependency_parser::make_T_IN(loc); }
"inertial"          { return yydep::dependency_parser::make_T_INERTIAL(loc); }
"inout"             { return yydep::dependency_parser::make_T_INOUT(loc); }
"is"                { return yydep::dependency_parser::make_T_IS(loc); }

"label"             { return yydep::dependency_parser::make_T_LABEL(loc); }
"library"           { return yydep::dependency_parser::make_T_LIBRARY(loc); }
"linkage"           { return yydep::dependency_parser::make_T_LINKAGE(loc); }
"literal"           { return yydep::dependency_parser::make_T_LITERAL(loc); }
"loop"              { return yydep::dependency_parser::make_T_LOOP(loc); }

"map"               { return yydep::dependency_parser::make_T_MAP(loc); }
"mod"               { return yydep::dependency_parser::make_T_MOD(loc); }

"nand"              { return yydep::dependency_parser::make_T_NAND(loc); }
"new"               { return yydep::dependency_parser::make_T_NEW(loc); }
"next"              { return yydep::dependency_parser::make_T_NEXT(loc); }
"nor"               { return yydep::dependency_parser::make_T_NOR(loc); }
"not"               { return yydep::dependency_parser::make_T_NOT(loc); }
"null"              { return yydep::dependency_parser::make_T_NULL(loc); }

"of"                { return yydep::dependency_parser::make_T_OF(loc); }
"on"                { return yydep::dependency_parser::make_T_ON(loc); }
"open"              { return yydep::dependency_parser::make_T_OPEN(loc); }
"or"                { return yydep::dependency_parser::make_T_OR(loc); }
"others"            { return yydep::dependency_parser::make_T_OTHERS(loc); }
"out"               { return yydep::dependency_parser::make_T_OUT(loc); }

"package"           { return yydep::dependency_parser::make_T_PACKAGE(loc); }
"port"              { return yydep::dependency_parser::make_T_PORT(loc); }
"postponed"         { return yydep::dependency_parser::make_T_POSTPONED(loc); }
"procedural"        { return yydep::dependency_parser::make_T_PROCEDURAL(loc); }
"procedure"         { return yydep::dependency_parser::make_T_PROCEDURE(loc); }
"process"           { return yydep::dependency_parser::make_T_PROCESS(loc); }
"protected"         { return yydep::dependency_parser::make_T_PROTECTED(loc); }
"pure"              { return yydep::dependency_parser::make_T_PURE(loc); }

"range"             { return yydep::dependency_parser::make_T_RANGE(loc); }
"record"            { return yydep::dependency_parser::make_T_RECORD(loc); }
"reference"         { return yydep::dependency_parser::make_T_REFERENCE(loc); }
"register"          { return yydep::dependency_parser::make_T_REGISTER(loc); }
"reject"            { return yydep::dependency_parser::make_T_REJECT(loc); }
"rem"               { return yydep::dependency_parser::make_T_REM(loc); }
"report"            { return yydep::dependency_parser::make_T_REPORT(loc); }
"return"            { return yydep::dependency_parser::make_T_RETURN(loc); }
"rol"               { return yydep::dependency_parser::make_T_ROL(loc); }
"ror"               { return yydep::dependency_parser::make_T_ROR(loc); }

"select"            { return yydep::dependency_parser::make_T_SELECT(loc); }
"severity"          { return yydep::dependency_parser::make_T_SEVERITY(loc); }
"signal"            { return yydep::dependency_parser::make_T_SIGNAL(loc); }
"shared"            { return yydep::dependency_parser::make_T_SHARED(loc); }
"sla"               { return yydep::dependency_parser::make_T_SLA(loc); }
"sll"               { return yydep::dependency_parser::make_T_SLL(loc); }
"sra"               { return yydep::dependency_parser::make_T_SRA(loc); }
"srl"               { return yydep::dependency_parser::make_T_SRL(loc); }
"subtype"           { return yydep::dependency_parser::make_T_SUBTYPE(loc); }

"then"              { return yydep::dependency_parser::make_T_THEN(loc); }
"to"                { return yydep::dependency_parser::make_T_TO(loc); }
"transport"         { return yydep::dependency_parser::make_T_TRANSPORT(loc); }
"type"              { return yydep::dependency_parser::make_T_TYPE(loc); }

"unaffected"        { return yydep::dependency_parser::make_T_UNAFFECTED(loc); }
"units"             { return yydep::dependency_parser::make_T_UNITS(loc); }
"until"             { return yydep::dependency_parser::make_T_UNTIL(loc); }
"use"               { return yydep::dependency_parser::make_T_USE(loc); }

"variable"          { return yydep::dependency_parser::make_T_VARIABLE(loc); }

"wait"              { return yydep::dependency_parser::make_T_WAIT(loc); }
"when"              { return yydep::dependency_parser::make_T_WHEN(loc); }
"while"             { return yydep::dependency_parser::make_T_WHILE(loc); }
"with"              { return yydep::dependency_parser::make_T_WITH(loc); }

"xnor"              { return yydep::dependency_parser::make_T_XNOR(loc); }
"xor"               { return yydep::dependency_parser::make_T_XOR(loc); }

  /* special characters as defined in 13.1c */
"\""                { return yydep::dependency_parser::make_T_QUOTE(loc); }
"#"                 { return yydep::dependency_parser::make_T_POUND(loc); }
"&"                 { return yydep::dependency_parser::make_T_AMPERSAND(loc); }
"'"                 { return yydep::dependency_parser::make_T_SINGLEQUOTE(loc); }
"("                 { return yydep::dependency_parser::make_T_LPAREN(loc); }
")"                 { return yydep::dependency_parser::make_T_RPAREN(loc); }
"*"                 { return yydep::dependency_parser::make_T_STAR(loc); }
"+"                 { return yydep::dependency_parser::make_T_PLUS(loc); }
","                 { return yydep::dependency_parser::make_T_COMMA(loc); }
"-"                 { return yydep::dependency_parser::make_T_MINUS(loc); }
"."                 { return yydep::dependency_parser::make_T_DOT(loc); }
"/"                 { return yydep::dependency_parser::make_T_FORWARDSLASH(loc); }
":"                 { return yydep::dependency_parser::make_T_COLON(loc); }
";"                 { return yydep::dependency_parser::make_T_SEMICOLON(loc); }
"<"                 { return yydep::dependency_parser::make_T_LESSTHAN(loc); }
"="                 { return yydep::dependency_parser::make_T_EQUAL(loc); }
">"                 { return yydep::dependency_parser::make_T_GREATERTHAN(loc); }
"["                 { return yydep::dependency_parser::make_T_LSQUAREPAREN(loc); }
"]"                 { return yydep::dependency_parser::make_T_RSQUAREPAREN(loc); }
"_"                 { return yydep::dependency_parser::make_T_UNDERSCORE(loc); }
"|"                 { return yydep::dependency_parser::make_T_PIPE(loc); }

  /* compound delimiters as defined in 13.2 */
"=>"                { return yydep::dependency_parser::make_T_ARROW(loc); }
"**"                { return yydep::dependency_parser::make_T_EXPONENTIATE(loc); }
":="                { return yydep::dependency_parser::make_T_VAR_ASSIGNMENT(loc); }
"/="                { return yydep::dependency_parser::make_T_INEQUALITY(loc); }
">="                { return yydep::dependency_parser::make_T_GREATERTHANOREQUAL(loc); }
"<="                { return yydep::dependency_parser::make_T_LESSTHANOREQUAL(loc); }
"<>"                { return yydep::dependency_parser::make_T_BOX(loc); }

  /* more tokens not defined in standard */

  /* "natural"           { return yydep::dependency_parser::make_NATURAL(loc); } */
  /* "std_logic"         { return yydep::dependency_parser::make_STD_LOGIC(loc); } */
  /* "std_logic_vector"  { return yydep::dependency_parser::make_STD_LOGIC_VECTOR(loc); } */


{Digits}            {
                      errno = 0;
                      long n = strtol (yytext, NULL, 10);
                      if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
                      driver.error (loc, "integer is out of range");
                      return yydep::dependency_parser::make_INTEGER(n, loc);
                    }

{id}           { return yydep::dependency_parser::make_IDENTIFIER(yytext, loc); }
.              driver.error (loc, "invalid character");
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
