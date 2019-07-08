%skeleton "lalr1.cc" /* -*- C++ -*- */
%defines
%define parser_class_name {dependency_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.prefix {yydep};
%code requires
{
    class dependency_driver;
}
// The parsing context.
%param { dependency_driver& driver }
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
    #include "vhdl_dependencies/dependency_parser_driver.h"
    extern int yylineno;
}
%define api.token.prefix {TOK_}
%token
    END  0  "end of file"
    //reserved words as defined in 13.9
    T_LIBRARY "library"
    T_USE "use"
    T_SEMICOLON     ";"
;
%token <std::string> IDENTIFIER "identifier"
%printer { yyoutput << $$; } <*>;

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

file_content: %empty
  | design_unit ..design_unit..

design_unit:
    context_clause library_unit

library_unit:
    ..skipped_code..

context_clause:
    ..context_item..

library_content:
    "identifier"

use_content:
    "identifier"

skipped_code:
    "identifier"

//these are the ones we're interested in
context_item:
    library_clause
  | use_clause

library_clause:
    "library" library_content ..comma_library_content.. ";"

use_clause:
    "use" use_content ..comma_use_content.. ";"

//Following rules are for 0 or 1 occurences ( .rule. )

//Following rules are for 0 or more occurences ( .. rule .. )
..design_unit..: %empty
  | design_unit ..design_unit..

..comma_library_content..: %empty
  | "," library_content ..comma_library_content..

..comma_use_content..: %empty
  | "," use_content ..comma_use_content..

..context_item..: %empty
  | context_item ..context_item..

..skipped_code..: %empty
  | skipped_code ..skipped_code.. ";"

%%
void yydep::dependency_parser::error ( const location_type& l,
                              const std::string& m )
  {
    driver.error (l, m, yylineno);
  }
