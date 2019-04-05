%skeleton "lalr1.cc" /* -*- C++ -*- */
%require ""
%defines
%define parser_class_name {vhdl_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%code requires
{
    #include "NodeFactory.h"
    #include <memory>
    #include <map>
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
#include "vhdl_parser_driver.h"
NodeFactory nf = NodeFactory();
std::shared_ptr<AstNode> current_ast;
std::vector<std::shared_ptr<AstNode>> ast_stack;
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
unit: {
    current_ast = nf.make_node(AstNodeType::TOP, nullptr);
    ast_stack.clear();
    ast_stack.push_back(current_ast);
} assignments {
    driver.AST = std::static_pointer_cast<TopNode>(current_ast);
}

assignments:
%empty                 {}
| assignments assignment {};

sensitivitylist:
%empty
| "identifier" {
    auto pn = std::dynamic_pointer_cast<ProcessNode>(ast_stack.back());
    pn->sensitivitylist.push_back($1);
}
endsensitivitylist

endsensitivitylist:
%empty
| "," sensitivitylist

ports:
"port" "(" portassigns ")" ";" {}

direction:
"in"
| "out"

portassigns:
"identifier" ":" direction "std_logic" {
    auto node = nf.make_node(AstNodeType::PORT, ast_stack.back());
    ast_stack.back()->addChild(node);
    }
endportassigns

endportassigns:
%empty
| ";" portassigns

logicexpr:
"identifier" {
    auto rhs = nf.make_node(AstNodeType::IDENTIFIER, ast_stack.back());
    ast_stack.back()->addChild(rhs);
}
| "identifier" "and" "identifier" {
    auto rhs = nf.make_node(AstNodeType::LOGICAL_AND, ast_stack.back());
    auto c1 = nf.make_node(AstNodeType::IDENTIFIER, rhs);
    auto c2 = nf.make_node(AstNodeType::IDENTIFIER, rhs);
    rhs->addChild(c1);
    rhs->addChild(c2);
    ast_stack.back()->addChild(rhs);
}

processbody:
%empty
|"identifier" processbody
| "identifier" "<=" {
    auto node = nf.make_node(AstNodeType::ASSIGN, ast_stack.back());
    auto lhs = nf.make_node(AstNodeType::IDENTIFIER,node);
    node->addChild(lhs);
    ast_stack.back()->addChild(node);
    ast_stack.push_back(node);
}
logicexpr ";" processbody

process:
"identifier" ":" "process" "(" {
    auto node = nf.make_node(AstNodeType::PROCESS, ast_stack.back());
    ast_stack.back()->addChild(node);
    ast_stack.push_back(node);
}
sensitivitylist ")" "begin" processbody "end" "process" "identifier" ";"

archbody:
%empty
|"identifier" archbody
| "identifier" "assign" "identifier" archbody
| process

architecture:
"architecture" "identifier" "of" "identifier" "is" "begin" {
    auto node = nf.make_node(AstNodeType::ARCHITECTURE, ast_stack.back());
    ast_stack.back()->addChild(node);
    ast_stack.push_back(node);
} archbody "end" "identifier" ";" {
    ast_stack.pop_back();
};

entity:
"entity" "identifier" "is" {
    auto node = nf.make_node(AstNodeType::ENTITY, ast_stack.back());
    ast_stack.back()->addChild(node);
    ast_stack.push_back(node);
}
ports entityend ";"{
    ast_stack.pop_back();
};

entityend:
"end"
| "end" "identifier"

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