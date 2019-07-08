#ifndef DEPENDENCY_DRIVER_HH
# define DEPENDENCY_DRIVER_HH
# include <string>
# include <map>
# include <ostream>
# include "vhdl_parser.hpp"

// Tell Flex the lexer's prototype ...
# define YY_DECL \
  yydep::dependency_parser::symbol_type yydeplex (dependency_driver& driver)
// ... and declare it for the parser's sake.
YY_DECL;

class dependency_driver
{
public:
    dependency_driver ();
    virtual ~dependency_driver ();

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
    void error (const yyvhdl::location& l, const std::string& m, const int lineno);
    void error (const yyvhdl::location& l, const std::string& m);
    void error (const std::string& m);
};
#endif // ! DEPENDENCY_DRIVER_HH
