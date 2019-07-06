#include "PurpleMesa_parser_driver.h"
#include "PurpleMesa_parser.hpp"

extern std::string PurpleMesa_filename;
std::string PurpleMesa_filename = "";

PurpleMesa_parser_driver::PurpleMesa_parser_driver ()
        : trace_scanning (false), trace_parsing (false)
{}

PurpleMesa_parser_driver::~PurpleMesa_parser_driver ()
{
}

int PurpleMesa_parser_driver::parse (const std::string &f)
{
    ::PurpleMesa_filename = f;
    file = f;
    scan_begin ();
    yypm::PurpleMesa_parser parser (*this);
    parser.set_debug_level (trace_parsing);
    int res = parser.parse ();
    scan_end ();
    return res;
}

void PurpleMesa_parser_driver::error (const yypm::location& l, const std::string& m)
{
    std::cerr << "In " << file << " " << l << ": " << m << std::endl;
}

void PurpleMesa_parser_driver::error (const yypm::location& l, const std::string& m, const int lineno)
{
    std::cerr << "In " << file << ":" << lineno << " " << l << ": " << m << std::endl;
}

void PurpleMesa_parser_driver::error (const std::string& m)
{
    std::cerr << "In " << file << " " << m << std::endl;
}