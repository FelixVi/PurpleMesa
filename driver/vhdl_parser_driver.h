#ifndef VHDL_DRIVER_HH
# define VHDL_DRIVER_HH
# include <string>
# include <map>
#include <ostream>
# include "vhdl_parser.hpp"
// Tell Flex the lexer's prototype ...
# define YY_DECL \
  yy::vhdl_parser::symbol_type yylex (vhdl_driver& driver)
// ... and declare it for the parser's sake.
YY_DECL;

class vhdl_driver
{
public:
    vhdl_driver ();
    virtual ~vhdl_driver ();

    std::map<std::string, std::string> signals;

    friend std::ostream &operator<<(std::ostream &os, const std::map<std::string, std::string> &signals);

    int result;
    // Handling the scanner.
    void scan_begin ();
    void scan_end ();
    bool trace_scanning;
    // Run the parser on file F.
    // Return 0 on success.
    int parse (const std::string& f);
    // The name of the file being parsed.
    // Used later to pass the file name to the location tracker.
    std::string file;
    // Whether parser traces should be generated.
    bool trace_parsing;
    // Error handling.
    void error (const yy::location& l, const std::string& m);
    void error (const std::string& m);

    void dump_signals();
};
#endif // ! VHDL_DRIVER_HH
