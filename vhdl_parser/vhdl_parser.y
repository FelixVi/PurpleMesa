%skeleton "lalr1.cc" /* -*- C++ -*- */
%require ""
%defines
%define parser_class_name {vhdl_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%code requires
        {
# include <string>
                class vhdl_driver;
        }
// The parsing context.
%param { vhdl_driver& driver }
%locations
%initial-action
{
// Initialize the initial location.
@$.begin.filename = @$.end.filename = &driver.file;
};
%define parse.trace
%define parse.error verbose
%code
{
# include "vhdl_parser_driver.h"
}
%define api.token.prefix {TOK_}
%token
        END  0  "end of file"
LIBRARY "library"
USE "use"
LINECOMMENT "--"
ASSIGN  "<="
LPAREN  "("
RPAREN  ")"
COMMA  ","
SEMICOLON  ";"
COLON  ":"
PORT "port"
ENTITY "entity"
IS "is"
T_END "end"
STD_LOGIC "std_logic"
IN "in"
OUT "out"
ARCHITECTURE "architecture"
OF "of"
BEGIN "begin"
PROCESS "process"
AND "and"
;
%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%printer { yyoutput << $$; } <*>;
%%
%start unit;
unit: assignments { };

assignments:
%empty                 {}
| assignments assignment {};

list:
%empty
| "identifier"
| "identifier" "," list

ports:
"port" "(" portassigns ")" ";" {}

direction:
"in"
| "out"

portassigns:
"identifier" ":" direction "std_logic" { driver.signals[$1] = "std_logic"; }
| "identifier" ":" direction  "std_logic" ";" portassigns { driver.signals[$1] = "std_logic"; }

logicexpr:
"identifier"
| "identifier" "and" "identifier"

processbody:
%empty
|"identifier" processbody
| "identifier" "<=" logicexpr ";" processbody

process:
"identifier" ":" "process" "(" list ")" "begin" processbody "end" "process" "identifier" ";"

archbody:
%empty
|"identifier" archbody
| "identifier" "assign" "identifier" archbody
| process

architecture:
"architecture" "identifier" "of" "identifier" "is" "begin" archbody "end" "identifier" ";"

entity:
"entity" "identifier" "is" ports "end" "identifier" ";"  {}
| "entity" "identifier" "is" ports "end" ";"  {}

assignment:
"library" "identifier" ";" {}
| "use" "identifier" ";" {}
| entity
| architecture

%%
void
yy::vhdl_parser::error (const location_type& l,
                          const std::string& m)
{
    driver.error (l, m);
}