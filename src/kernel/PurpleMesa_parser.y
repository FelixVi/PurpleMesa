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
std::cout << "PurpleMesa> ";
};
%define parse.trace
%define parse.error verbose
%code
{
    #include "kernel/PurpleMesa_parser_driver.h"
    extern int yypmlineno;

    void pmprint(const std::string &s){
        std::cout << s << "\n" << "PurpleMesa> ";
    }
}
%define api.token.prefix {TOK_}
%token
    END  0  "end of file"

    T_HELP "help"
    T_ADD_DESIGN_FILE   "add_design_file"
    T_EXIT "exit"
;
%token <std::string> IDENTIFIER "identifier"
%token <int> INTEGER "integer"

%type <std::string> filename

%printer { yyoutput << $$; } <*>;

%%
%start unit;

//This is the starting point when parsing a file
unit:
    {
    }
  commands
| "exit" {pmprint("EXIT");}
    {
    }

commands:
    command commands
|   command "exit" {std::cout << "BYE" << "\n"; return 0;}

command:
  %empty
| "help" {pmprint("HELP!!!");}
| "add_design_file" filename
{
    if($2 != "")
        pmprint("Adding file " + $2);
}

filename:
    "identifier"
{
    if (FILE *file = fopen($1.c_str(), "r")) {
        fclose(file);
        $$ = $1;
    } else {
        pmprint("Cannot open file " + $1);
        $$ = "";
    };
}

%%

void yypm::PurpleMesa_parser::error ( const location_type& l,
                              const std::string& m )
  {
    driver.error (l, m, yypmlineno);
  }