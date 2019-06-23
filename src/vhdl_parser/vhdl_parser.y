%skeleton "lalr1.cc" /* -*- C++ -*- */
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
    #include "vhdl_parser/vhdl_parser_driver.h"
    std::shared_ptr<AstNode> current_node;
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
      current_node = NodeFactory::make_node(AstNodeType::TOP, nullptr);
    }
  file_content
    {
      assert(("Current Node at end of parse is not TOP", current_node->type() == AstNodeType::TOP));
      driver.AST = std::static_pointer_cast<TopNode>(current_node);
    }

file_content:
  %empty
| file_content main_section

main_section:
  library_declaration
| entity_declaration
| architecture_body

library_declaration:
  "library" "identifier" ";"
| "use" "identifier" ";"

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
  | formal_generic_clause formal_port_clause

  formal_port_clause:
    "port" "(" port_list ")" ";"

  formal_generic_clause:
    "generic" "(" generic_list ")" ";"

  port_list:
    "identifier" ":"
      {
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

  generic_list:
    "identifier" ":" "identifier" ":=" "integer"
      {
        auto node = NodeFactory::make_node(AstNodeType::GENERIC, current_node);
        node->setProperty("identifier", $1);
        node->setProperty("type_identifier", $3);
        node->setProperty("default_value", std::to_string($5));
        current_node->addChild(node);
      }
    endgenericassigns

  endgenericassigns:
    %empty
  | ";" generic_list

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
    "identifier"
      {
        current_node->setProperty("subtype", $1);
        current_node->setProperty("subtype_width", "1");
      }
  | "identifier" "(" range_expression ")"
      {
        current_node->setProperty("subtype", $1);
        // current_node->setProperty("subtype_width", std::to_string($3 - $5 + 1));
      }

  range_expression:
    logicexpr "downto" logicexpr
      {
        auto node = NodeFactory::make_node(AstNodeType::RANGE, current_node);
        node->setProperty("type", "downto");
        current_node->addChild(node);
      }
  | logicexpr "to" logicexpr
      {
        auto node = NodeFactory::make_node(AstNodeType::RANGE, current_node);
        node->setProperty("type", "to");
        current_node->addChild(node);
      }

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
    }

  process_statement_part:
    %empty
  | "identifier" process_statement_part
  | "identifier" "<="
      {
        auto node = NodeFactory::make_node(AstNodeType::ASSIGN, current_node);
        auto lhs = NodeFactory::make_node(AstNodeType::IDENTIFIER,node);
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
  | "if" logiccondition "then" concurrent_statement_block "end" "if" ";" process_statement_part
  | "if" logiccondition "then" concurrent_statement_block "elsif" logiccondition "then" concurrent_statement_block "end" "if" ";" process_statement_part

  logiccondition:
    "identifier" "=" logicexpr
  | "identifier" "(" "identifier" ")" //to cover rising_edge
  | "(" logiccondition ")"
  | logiccondition logicoperator logiccondition

  logicexpr:
    "identifier"
      {
        auto rhs = NodeFactory::make_node(AstNodeType::IDENTIFIER, current_node);
        rhs->setProperty("identifier", $1);
        current_node->addChild(rhs);
      }
  | "integer"
      {
        auto node = NodeFactory::make_node(AstNodeType::INTEGER, current_node);
        node->setProperty("value", std::to_string($1));
        current_node->addChild(node);
      }
  | "'" "integer" "'"
  | "(" logicexpr ")"
  | logicoperator logicexpr
  | logicexpr logicoperator logicexpr
  | logicexpr "&" logicexpr //concatenation
  | "identifier" "(" logicexpr ")"
  | "identifier" "'" "(" logicexpr ")"
  | "identifier" "(" logicexpr "downto" logicexpr ")"
  | "identifier" "(" logicexpr "," logicexpr ")"
  | logicexpr numoperator logicexpr
      {
        auto node = NodeFactory::make_node(AstNodeType::BINARY_OPERATOR, current_node);
        node->setProperty("operator", "+");
        //auto c1 = NodeFactory::make_node(AstNodeType::SIGNAL, rhs);
        //c1->setProperty("identifier", $1);
        //auto c2 = NodeFactory::make_node(AstNodeType::SIGNAL, rhs);
        //c2->setProperty("identifier", $3);
        //node->addChild(c1);
        //node->addChild(c2);
        current_node->addChild(node);
      }

  logicoperator:
    "and"
  | "not"
  | "xor"

  numoperator:
    "+"
  | "-"
  | "**"

  optional_is:
    %empty
  | "is"

  optional_process_label:
    %empty
  | "identifier" ":"

  process_declarative_part:
    %empty
    | "variable" "identifier" ":" "identifier" ";" process_declarative_part
    | "variable" "identifier" ":" "identifier" "(" range_expression ")" ";" process_declarative_part

  optional_sensitivitylist:
  %empty
  | "identifier" "," optional_sensitivitylist
      {
        auto signal = NodeFactory::make_node(AstNodeType::IDENTIFIER, current_node);
        signal->setProperty("identifier", $1);
        current_node->addChild(signal);
      }
  | "identifier"
      {
        auto signal = NodeFactory::make_node(AstNodeType::IDENTIFIER, current_node);
        signal->setProperty("identifier", $1);
        current_node->addChild(signal);
      }

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
  | "signal" "identifier" ":" "identifier" "(" range_expression ")" ";" architecture_declarative_part
  | "signal" "identifier" ":" "identifier" ";" architecture_declarative_part
  | "signal" "identifier" ":" "identifier" ":=" "'" "integer" "'" ";" architecture_declarative_part
  
  | "attribute" "identifier" ":" "identifier" ";" architecture_declarative_part
  | "attribute" "identifier" "of" "identifier" ":" "signal" "is" "quote" "identifier" "quote" ";" architecture_declarative_part
  
  | "type" "identifier" "is" "array" "(" range_expression ")" "of" "identifier" "(" range_expression ")" ";" architecture_declarative_part

  architecture_statement_part:
    %empty
  | concurrent_statement architecture_statement_part
  | process_statement architecture_statement_part

  concurrent_statement:
    "identifier" "<=" assign_rhs
      {
        auto node = NodeFactory::make_node(AstNodeType::ASSIGN, current_node);
        auto lhs = NodeFactory::make_node(AstNodeType::IDENTIFIER,node);
        lhs->setProperty("identifier", $1);
        node->addChild(lhs);
        current_node->addChild(node);
        current_node = node;
      }
    ";"
      {
        current_node = current_node->getParent();
      }
  | "identifier" "(" logicexpr ")" "<=" assign_rhs ";"
  | "identifier" ":=" assign_rhs ";"
  | "if" logiccondition "then" concurrent_statement "end" "if" ";"
  
  assign_rhs:
    logicexpr
  
  concurrent_statement_block:
    %empty
  | concurrent_statement concurrent_statement_block

%%
void yy::vhdl_parser::error ( const location_type& l,
                              const std::string& m )
  {
    driver.error (l, m, yylineno);
  }
