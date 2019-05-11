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
    node->setProperty("identifier", $2);
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

optional_sensitivitylist:
%empty
| "identifier" "," optional_sensitivitylist
  {
    auto signal = NodeFactory::make_node(AstNodeType::SIGNAL, current_node);
    signal->setProperty("identifier", $1);
    current_node->addChild(signal);
  }
| "identifier"
  {
    auto signal = NodeFactory::make_node(AstNodeType::SIGNAL, current_node);
signal->setProperty("identifier", $1);
    current_node->addChild(signal);
  }

formal_port_clause:
"port" "(" port_list ")" ";"

interface_mode:
"in"
  {
    current_node->setProperty("direction", "in");
  }
| "out"
  {
    current_node->setProperty("direction", "out");
  }

subtype_indication:
"std_logic"
  {
    current_node->setProperty("subtype", "std_logic");
  }
| "std_logic_vector"
  {
    // TODO
    // Parse range for vector
  }

port_list:
"identifier" ":" {
    auto node = NodeFactory::make_node(AstNodeType::PORT, current_node);
    node->setProperty("identifier", $1);
    current_node->addChild(node);
    current_node = node;
    }
interface_mode subtype_indication
  {
    current_node = current_node->getParent();
  }
endportassigns

endportassigns:
%empty
| ";" port_list

logicexpr:
"identifier" {
    auto rhs = NodeFactory::make_node(AstNodeType::SIGNAL, current_node);
    rhs->setProperty("identifier", $1);
    current_node->addChild(rhs);
}
| "identifier" "and" "identifier" {
    auto rhs = NodeFactory::make_node(AstNodeType::BINARY_OPERATOR, current_node);
    rhs->setProperty("operator", "and");
    auto c1 = NodeFactory::make_node(AstNodeType::SIGNAL, rhs);
    c1->setProperty("identifier", $1);
    auto c2 = NodeFactory::make_node(AstNodeType::SIGNAL, rhs);
    c2->setProperty("identifier", $3);
    rhs->addChild(c1);
    rhs->addChild(c2);
    current_node->addChild(rhs);
}

process_statement_part:
%empty
|"identifier" process_statement_part
| "identifier" "<="
  {
    auto node = NodeFactory::make_node(AstNodeType::ASSIGN, current_node);
    auto lhs = NodeFactory::make_node(AstNodeType::SIGNAL,node);
    lhs->setProperty("identifier", $1);
    node->addChild(lhs);
    current_node->addChild(node);
    current_node = node;
  }
logicexpr ";"
  {
    current_node = current_node->getParent();
  }
process_statement_part


process_statement:
optional_process_label "process" "("
  {
    auto node = NodeFactory::make_node(AstNodeType::PROCESS, current_node);
    current_node->addChild(node);
    current_node = node;

    auto snode = NodeFactory::make_node(AstNodeType::SENSITIVITYLIST, current_node);
    current_node->addChild(snode);
    current_node = snode;
  }
optional_sensitivitylist ")"
  {
    current_node = current_node->getParent();
  }
optional_is
process_declarative_part
"begin"
process_statement_part
"end" "process" "identifier" ";"
  {
    current_node = current_node->getParent();
  };

optional_is:
%empty
| "is"

optional_process_label:
%empty
| "identifier" ":"

process_declarative_part:
%empty

architecture_body:
"architecture" "identifier" "of" "identifier" "is"
  {
    auto node = NodeFactory::make_node(AstNodeType::ARCHITECTURE, current_node);
    node->setProperty("identifier", $2);
    node->setProperty("entity_name", $4);
    current_node->addChild(node);
    current_node = node;
  }
architecture_declarative_part
"begin"
architecture_statement_part

architecture_body_end
  {
    current_node = current_node->getParent();
  }

architecture_body_end:
"end" ";"
| "end" "architecture" ";"
| "end" "architecture" "identifier" ";"
| "end" "identifier" ";"

architecture_declarative_part:
%empty

architecture_statement_part:
%empty
| concurrent_statement architecture_statement_part

concurrent_statement:
process_statement

%%
void
yy::vhdl_parser::error (const location_type& l,
                          const std::string& m)
{
    driver.error (l, m, yylineno);
}