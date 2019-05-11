#include <vhdl_parser_driver.h>
#include "gtest/gtest.h"
#include "AstVisitors/AstPrintVisitor.h"
#include "AstVisitors/RTIL/RTILVisitor.h"
#include "AstTraversals/PreOrder.h"

TEST(VisitorTests, simple) {
    PreOrderTraversal t;
    AstPrintVisitor v;
    vhdl_driver driver;

    ASSERT_FALSE(driver.parse ("../tests/hdl/simple.vhd"));

    std::cout << "\n\nTraversing AST ports...\n";

    v.setFilter(AstTraversalFilter::ShowPorts);
    t.traverse(*driver.AST, v);

    std::cout << "End traversing AST ports...\n";


    std::cout << "\nTraversing AST...\n";

    v.setFilter(AstTraversalFilter::ShowAll);
    t.traverse(*driver.AST, v);

    std::cout << "End traversing AST...\n";

    std::cout << "\nCopy AST...\n";
    auto newAst = NodeFactory::copy_node(*driver.AST);

    RTILVisitor translator;
    t.traverse(*newAst, translator);

    ASSERT_FALSE(0);
}

TEST(ParserTests, simple) {
    vhdl_driver driver;

    std::cout << "\n\n";

    ASSERT_FALSE(driver.parse ("../tests/hdl/simple.vhd"));
}

TEST(ASTTests, simple) {
    PreOrderTraversal t;
    AstPrintVisitor v;

    auto nf = NodeFactory();
    auto top = nf.make_node(AstNodeType::TOP, nullptr);
    auto child1 = nf.make_node(AstNodeType::ENTITYDECLARATION, top);
    child1->setProperty("identifier", "testentity");
    auto child2 = nf.make_node(AstNodeType::SIGNAL, top);
    child2->setProperty("identifier", "testsignal");

    top->addChild(child1);
    top->addChild(child2);

    std::cout << "\n\n";
    v.setFilter(AstTraversalFilter::ShowAll);
    t.traverse(*top, v);

    ASSERT_FALSE(0);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}