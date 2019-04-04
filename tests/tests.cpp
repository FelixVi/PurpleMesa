#include <vhdl_parser_driver.h>
#include "gtest/gtest.h"
#include "AstVisitors/AstPrintVisitor.h"
#include "AstTraversals/PreOrder.h"

TEST(VisitorTests, simple) {
    PreOrderTraversal t;
    AstPrintVisitor v;
    vhdl_driver driver;

    ASSERT_FALSE(driver.parse ("../tests/hdl/simple.vhd"));

    std::cout << "\n\nTraversing AST...\n";

    v.setFilter(AstTraversalFilter::ShowPorts);
    //v.setFilter(AstTraversalFilter::ShowAll);
    t.traverse(*driver.AST, v);

    std::cout << "\n\nEnd Traversing AST...\n";

    ASSERT_FALSE(0);
}

TEST(ParserTests, simple) {
    vhdl_driver driver;

    std::cout << "\n\n";

    ASSERT_FALSE(driver.parse ("../tests/hdl/simple.vhd"));
}

TEST(ASTTests, simple) {
    auto nf = NodeFactory();
    auto top = nf.make_node(AstNodeType::TOP, nullptr);
    auto child1 = nf.make_node(AstNodeType::ENTITY, top);
    auto child2 = nf.make_node(AstNodeType::IDENTIFIER, top);

    top->addChild(child1);
    top->addChild(child2);

    std::cout << "\n\n";
    top->dumpAst("");

    ASSERT_FALSE(0);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}