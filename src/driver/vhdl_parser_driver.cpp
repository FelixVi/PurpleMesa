#include "vhdl_parser_driver.h"
#include "vhdl_parser.hpp"

vhdl_driver::vhdl_driver ()
        : trace_scanning (false), trace_parsing (false)
{}

vhdl_driver::~vhdl_driver ()
{
}

int
vhdl_driver::parse (const std::string &f)
{
    file = f;
    scan_begin ();
    yy::vhdl_parser parser (*this);
    parser.set_debug_level (trace_parsing);
    int res = parser.parse ();
    scan_end ();
    return res;
}

void
vhdl_driver::error (const yy::location& l, const std::string& m)
{
    std::cerr << l << ": " << m << std::endl;
}

void
vhdl_driver::error (const std::string& m)
{
    std::cerr << m << std::endl;
}

std::ostream &operator<<(std::ostream &os, const std::map<std::string, std::string> &signals) {
    for(std::map<std::string, std::string>::const_iterator it = signals.begin();
            it != signals.end(); ++it)
    {
        os << it->first << " " << it->second << "\n";
    }
    return os;
}

void vhdl_driver::dump_signals() {
    std::cout << signals << std::endl;
}