#include "dependency_parser_driver.h"
#include "dependency_parser.hpp"

extern std::string dep_filename;
std::string dep_filename = "";

dependency_driver::dependency_driver ()
        : trace_scanning (false), trace_parsing (true)
{}

dependency_driver::~dependency_driver ()
{
}

int dependency_driver::parse (const std::string &f)
{
    ::dep_filename = f;
    file = f;
    scan_begin ();
    yydep::dependency_parser parser (*this);
    parser.set_debug_level (trace_parsing);
    int res = parser.parse ();
    scan_end ();
    return res;
}

void dependency_driver::error (const yydep::location& l, const std::string& m)
{
    std::cerr << "In " << file << " " << l << ": " << m << std::endl;
}

void dependency_driver::error (const yydep::location& l, const std::string& m, const int lineno)
{
    std::cerr << "In " << file << ":" << lineno << " " << l << ": " << m << std::endl;
}

void dependency_driver::error (const std::string& m)
{
    std::cerr << "In " << file << " " << m << std::endl;
}