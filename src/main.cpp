#include <iostream>
#include "vhdl_parser_driver.h"
#include "NodeFactory.h"
#include <memory>
#include <vector>

int
main (int argc, char *argv[])
{
    std::cout << std::endl << "Creating factory..." << std::endl;
    NodeFactory nf;
    auto N_assign = nf.make_node(AstNodeType::ASSIGN);
    auto N_and = nf.make_node(AstNodeType::LOGICAL_AND);
    auto N_andtwo = nf.make_node(AstNodeType::LOGICAL_AND);
    auto N_top = nf.make_node(AstNodeType::TOP);

    N_assign->addChild(N_and);
    N_and->addChild(N_andtwo);
    N_assign->dumpAst("");

    std::cout << "Node output: " << N_assign << "\n";
    std::cout << N_assign;

    std::cout << std::endl << "Done creating nodes..." << std::endl;

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
