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
    std::shared_ptr<AstNode> current_node;
    extern int yylineno;
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


unit:
  {
    current_node = NodeFactory::make_node(AstNodeType::TOP, nullptr);
  }
declarations
  {
    assert(("Current Node at end of parse is not TOP", current_node->type() == AstNodeType::TOP));
    driver.AST = std::static_pointer_cast<TopNode>(current_node);
  }

declarations:
%empty                 {}
| declarations declaration {};

declaration:
"library" "identifier" ";" {}
| "use" "identifier" ";" {}
| entity_declaration
| architecture_body

entity_declaration:
"entity" "identifier" "is"
  {
    auto node = NodeFactory::make_node(AstNodeType::ENTITYDECLARATION, current_node);
    auto id   = NodeFactory::make_node(AstNodeType::IDENTIFIER, node, $2);
    node->addChild(id);
    current_node->addChild(node);
    current_node = node;
  }
entity_header entity_declaration_end
  {
    current_node = current_node->getParent();
  }

entity_declaration_end:
"end" ";"
| "end" "entity" ";"
| "end" "entity" "identifier" ";"
| "end" "identifier" ";"


entity_header:
%empty
| formal_port_clause

sensitivitylist:
%empty
| "identifier" {
    auto pn = std::dynamic_pointer_cast<ProcessNode>(current_node);
    pn->sensitivitylist.push_back($1);
}
endsensitivitylist

endsensitivitylist:
%empty
| "," sensitivitylist

formal_port_clause:
"port" "(" port_list ")" ";"

direction:
"in"
| "out"

port_list:
"identifier" ":" direction "std_logic" {
    auto node = NodeFactory::make_node(AstNodeType::PORT, current_node);
    current_node->addChild(node);
    }
endportassigns

endportassigns:
%empty
| ";" port_list

logicexpr:
"identifier" {
    auto rhs = NodeFactory::make_node(AstNodeType::IDENTIFIER, current_node);
    current_node->addChild(rhs);
}
| "identifier" "and" "identifier" {
    auto rhs = NodeFactory::make_node(AstNodeType::LOGICAL_AND, current_node);
    auto c1 = NodeFactory::make_node(AstNodeType::IDENTIFIER, rhs);
    auto c2 = NodeFactory::make_node(AstNodeType::IDENTIFIER, rhs);
    rhs->addChild(c1);
    rhs->addChild(c2);
    current_node->addChild(rhs);
}

processbody:
%empty
|"identifier" processbody
| "identifier" "<=" {
    auto node = NodeFactory::make_node(AstNodeType::ASSIGN, current_node);
    auto lhs = NodeFactory::make_node(AstNodeType::IDENTIFIER,node);
    node->addChild(lhs);
    current_node->addChild(node);
    current_node = node;
}
logicexpr ";" {
    current_node = current_node->getParent();
}
    processbody


process:
"identifier" ":" "process" "(" {
    auto node = NodeFactory::make_node(AstNodeType::PROCESS, current_node);
    current_node->addChild(node);
    current_node = node;
}
sensitivitylist ")" "begin" processbody "end" "process" "identifier" ";" {
    current_node = current_node->getParent();
};

archbody:
%empty
| "identifier" archbody
| "identifier" "assign" "identifier" archbody
| process

architecture_body:
"architecture" "identifier" "of" "identifier" "is" "begin"
  {
    auto node = NodeFactory::make_node(AstNodeType::ARCHITECTURE, current_node);
    current_node->addChild(node);
    current_node = node;
  }
archbody architecture_body_end
  {
    current_node = current_node->getParent();
  }

architecture_body_end:
"end" ";"
| "end" "architecture" ";"
| "end" "architecture" "identifier" ";"
| "end" "identifier" ";"

%%
void
yy::vhdl_parser::error (const location_type& l,
                          const std::string& m)
{
    driver.error (l, m, yylineno);
}