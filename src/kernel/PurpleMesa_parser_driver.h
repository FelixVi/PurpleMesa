#ifndef PURPLEMESA_PURPLEMESA_PARSER_DRIVER_H
#define PURPLEMESA_PURPLEMESA_PARSER_DRIVER_H

# include <string>
# include <map>
# include <ostream>
# include "PurpleMesa_parser.hpp"

// Tell Flex the lexer's prototype ...
# define YY_DECL \
  yypm::PurpleMesa_parser::symbol_type yylex (PurpleMesa_parser_driver& driver)
// ... and declare it for the parser's sake.
YY_DECL;

class PurpleMesa_parser_driver {

public:
    PurpleMesa_parser_driver ();
    virtual ~PurpleMesa_parser_driver ();

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
    void error (const yypm::location& l, const std::string& m, const int lineno);
    void error (const yypm::location& l, const std::string& m);
    void error (const std::string& m);
};


#endif //PURPLEMESA_PURPLEMESA_PARSER_DRIVER_H