#include "PurpleMesa.h"
#include <AstNodes/TopNode.h>
#include <AstVisitors/AstPrintVisitor.h>
#include <AstTraversals/PreOrder.h>
#include <vhdl_parser_driver.h>

int autoidx = 1;

std::shared_ptr<TopNode> PurpleMesa::parseFile(const std::string &filename) {
    vhdl_driver driver;

    driver.parse(filename);
    return driver.AST;
}

void PurpleMesa::printAST(TopNode &AST) {
    AstPrintVisitor v;
    PreOrderTraversal t;

    v.setFilter(AstTraversalFilter::ShowAll);
    t.traverse(AST, v);
}
