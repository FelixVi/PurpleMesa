#include "vhdl_parser_driver.h"
#include "vhdl_parser.hpp"

vhdl_driver::vhdl_driver ()
        : trace_scanning (false), trace_parsing (false)
{}

vhdl_driver::~vhdl_driver ()
{
}

int vhdl_driver::parse (const std::string &f)
{
    //top  = std::make_unique<AST::AstNode>(AstNodeType::DESIGN, nullptr, nullptr, nullptr);
    file = f;
    scan_begin ();
    yy::vhdl_parser parser (*this);
    parser.set_debug_level (trace_parsing);
    int res = parser.parse ();
    scan_end ();
    //top->dumpAst("");
    return res;
}

void vhdl_driver::error (const yy::location& l, const std::string& m)
{
    std::cerr << l << ": " << m << std::endl;
}

void vhdl_driver::error (const std::string& m)
{
    std::cerr << m << std::endl;
}