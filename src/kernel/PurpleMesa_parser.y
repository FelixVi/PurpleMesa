%skeleton "lalr1.cc" /* -*- C++ -*- */
%defines
%define parser_class_name {PurpleMesa_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.prefix {yypm}
%code requires
{
    class PurpleMesa_parser_driver;
}
// The parsing context.
%param { PurpleMesa_parser_driver& driver }
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
    #include "kernel/PurpleMesa_parser_driver.h"
    extern int yylineno;
}
%define api.token.prefix {TOK_}
%token
    END  0  "end of file"
    //reserved words as defined in 13.9
    T_ABS "abs"
    T_ACCESS "access"
    T_AFTER "after"
    T_ALIAS "alias"
    T_ALL "all"
    T_AND "and"
    T_ARCHITECTURE "architecture"
    T_ARRAY "array"
    T_ASSERT "assert"
    T_ATTRIBUTE "attribute"
    
    T_BEGIN "begin"
    T_BLOCK "block"
    T_BODY "body"
    T_BUFFER "buffer"
    T_BUS "bus"
    
    T_CASE "case"
    T_COMPONENT "component"
    T_CONFIGURATION "configuration"
    T_CONSTANT "constant"
    
    T_DISCONNECT "disconnect"
    T_DOWNTO "downto"
    
    T_ELSE "else"
    T_ELSIF "elsif"
    T_END "end"
    T_ENTITY "entity"
    T_EXIT "exit"
    
    T_FILE "file"
    T_FOR "for"
    T_FUNCTION "function"
    
    T_GENERATE "generate"
    T_GENERIC "generic"
    T_GROUP "group"
    T_GUARDED "guarded"
    
    T_IF "if"
    T_IMPURE "impure"
    T_IN "in"
    T_INERTIAL "inertial"
    T_INOUT "inout"
    T_IS "is"
    
    T_LABEL "label"
    T_LIBRARY "library"
    T_LINKAGE "linkage"
    T_LITERAL "literal"
    T_LOOP "loop"
    
    T_MAP "map"
    T_MOD "mod"
    
    T_NAND "nand"
    T_NEW "new"
    T_NEXT "next"
    T_NOR "nor"
    T_NOT "not"
    T_NULL "null"
    
    T_OF "of"
    T_ON "on"
    T_OPEN "open"
    T_OR "or"
    T_OTHERS "others"
    T_OUT "out"
    
    T_PACKAGE "package"
    T_PORT "port"
    T_POSTPONED "postponed"
    T_PROCEDURAL "procedural"
    T_PROCEDURE "procedure"
    T_PROCESS "process"
    T_PROTECTED "protected"
    T_PURE "pure"
    
    T_RANGE "range"
    T_RECORD "record"
    T_REFERENCE "reference"
    T_REGISTER "register"
    T_REJECT "reject"
    T_REM "rem"
    T_REPORT "report"
    T_RETURN "return"
    T_ROL "rol"
    T_ROR "ror"
    
    T_SELECT "select"
    T_SEVERITY "severity"
    T_SIGNAL "signal"
    T_SHARED "shared"
    T_SLA "sla"
    T_SLL "sll"
    T_SRA "sra"
    T_SRL "srl"
    T_SUBTYPE "subtype"
    
    T_THEN "then"
    T_TO "to"
    T_TRANSPORT "transport"
    T_TYPE "type"
    
    T_UNAFFECTED "unaffected"
    T_UNITS "units"
    T_UNTIL "until"
    T_USE "use"
    
    T_VARIABLE "variable"
    
    T_WAIT "wait"
    T_WHEN "when"
    T_WHILE "while"
    T_WITH "with"
    
    T_XNOR "xnor"
    T_XOR "xor"
    
    // compound delimiters as defined in 13.2
    T_ARROW               "=>"
    T_EXPONENTIATE        "**"
    T_VAR_ASSIGNMENT      ":="
    T_INEQUALITY          "/="
    T_GREATERTHANOREQUAL  ">="
    T_LESSTHANOREQUAL     "<="
    T_BOX                 "<>"
    
    //special characters as defined in 13.1c
    T_QUOTE         "quote"
    T_POUND         "#"
    T_AMPERSAND     "&"
    T_SINGLEQUOTE   "'"
    T_LPAREN        "("
    T_RPAREN        ")"
    T_STAR          "*"
    T_PLUS          "+"
    T_COMMA         ","
    T_MINUS         "-"
    T_DOT           "."
    T_FORWARDSLASH  "/"
    T_COLON         ":"
    T_SEMICOLON     ";"
    T_LESSTHAN      "<"
    T_EQUAL         "="
    T_GREATERTHAN   ">"
    T_LSQUAREPAREN  "["
    T_RSQUAREPAREN  "]"
    T_UNDERSCORE    "_"
    T_PIPE          "|"
    
    //more tokens not defined in standard
    // NATURAL "natural"
    //STD_LOGIC "std_logic"
    //STD_LOGIC_VECTOR "std_logic_vector"
;
%token <std::string> IDENTIFIER "identifier"
%token <int> INTEGER "integer"
%printer { yyoutput << $$; } <*>;

//TODO operator precedence
//%left "or"
//%left "and"
//%left "nor"
//%left "xor"
//%left "+" "-"

%%
%start unit;

//This is the starting point when parsing a file
//Create a TOP node to which file content is added as child nodes
unit:
    {
    }
  file_content
    {
    }

file_content:
  %empty

%%
void yypm::PurpleMesa_parser::error ( const location_type& l,
                              const std::string& m )
  {
    driver.error (l, m, yylineno);
  }