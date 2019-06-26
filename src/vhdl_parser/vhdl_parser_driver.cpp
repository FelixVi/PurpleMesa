#include "vhdl_parser_driver.h"
#include "vhdl_parser.hpp"

extern std::string filename;
std::string filename = "";

vhdl_driver::vhdl_driver ()
        : trace_scanning (false), trace_parsing (true)
{}

vhdl_driver::~vhdl_driver ()
{
}

int vhdl_driver::parse (const std::string &f)
{
    ::filename = f;
    file = f;
    scan_begin ();
    yy::vhdl_parser parser (*this);
    parser.set_debug_level (trace_parsing);
    int res = parser.parse ();
    scan_end ();
    return res;
}

void vhdl_driver::error (const yy::location& l, const std::string& m)
{
    std::cerr << "In " << file << " " << l << ": " << m << std::endl;
}

void vhdl_driver::error (const yy::location& l, const std::string& m, const int lineno)
{
    std::cerr << "In " << file << ":" << lineno << " " << l << ": " << m << std::endl;
}

void vhdl_driver::error (const std::string& m)
{
    std::cerr << "In " << file << " " << m << std::endl;
}