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
    NodeFactory nf = NodeFactory();
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
unit: {
    current_node = nf.make_node(AstNodeType::TOP, nullptr);
    std::cout << "Hello" << driver.file << "\n";
} assignments {
    assert(("Current Node at end of parse is not TOP", current_node->type() == AstNodeType::TOP));
    driver.AST = std::static_pointer_cast<TopNode>(current_node);
}

assignments:
%empty                 {}
| assignments assignment {};

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

ports:
"port" "(" portassigns ")" ";" {}

direction:
"in"
| "out"

portassigns:
"identifier" ":" direction "std_logic" {
    auto node = nf.make_node(AstNodeType::PORT, current_node);
    current_node->addChild(node);
    std::cout << "LOC of port: " << $1 << " : " << @1 << "\n";
    }
endportassigns

endportassigns:
%empty
| ";" portassigns

logicexpr:
"identifier" {
    auto rhs = nf.make_node(AstNodeType::IDENTIFIER, current_node);
    current_node->addChild(rhs);
}
| "identifier" "and" "identifier" {
    auto rhs = nf.make_node(AstNodeType::LOGICAL_AND, current_node);
    auto c1 = nf.make_node(AstNodeType::IDENTIFIER, rhs);
    auto c2 = nf.make_node(AstNodeType::IDENTIFIER, rhs);
    rhs->addChild(c1);
    rhs->addChild(c2);
    current_node->addChild(rhs);
}

processbody:
%empty
|"identifier" processbody
| "identifier" "<=" {
    auto node = nf.make_node(AstNodeType::ASSIGN, current_node);
    auto lhs = nf.make_node(AstNodeType::IDENTIFIER,node);
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
    auto node = nf.make_node(AstNodeType::PROCESS, current_node);
    current_node->addChild(node);
    current_node = node;
    std::cout << "LOC of process: " << $1 << " : " << @1 << "\n";
}
sensitivitylist ")" "begin" processbody "end" "process" "identifier" ";" {
    current_node = current_node->getParent();
    std::cout << "LOC of process end: " << $1 << " : " << @1 << "\n";
};

archbody:
%empty
|"identifier" archbody
| "identifier" "assign" "identifier" archbody
| process

architecture:
"architecture" "identifier" "of" "identifier" "is" "begin" {
    auto node = nf.make_node(AstNodeType::ARCHITECTURE, current_node);
    current_node->addChild(node);
    current_node = node;
} archbody "end" "identifier" ";" {
    current_node = current_node->getParent();
    std::cout << "LOC of architecture end: " << $2 << " : " << @2 << "    " << yylineno << "\n";
};

entity:
"entity" "identifier" "is" {
    auto node = nf.make_node(AstNodeType::ENTITY, current_node);
    current_node->addChild(node);
    current_node = node;
}
ports entityend ";"{
    current_node = current_node->getParent();
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
    driver.error (l, m, yylineno);
}