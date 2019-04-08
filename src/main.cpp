#include <iostream>
#include "vhdl_parser_driver.h"
#include "NodeFactory.h"
#include <memory>
#include <vector>

int
main (int argc, char *argv[])
{
    int res = 0;
    vhdl_driver driver;
    for (int i = 1; i < argc; ++i)
        if (argv[i] == std::string ("-p"))
            driver.trace_parsing = true;
        else if (argv[i] == std::string ("-s"))
            driver.trace_scanning = true;
        else if (!driver.parse (argv[i])){
            std::cout << std::endl << "Parsed successfully..." << std::endl;
        }
        else
            res = 1;
    return res;
}
