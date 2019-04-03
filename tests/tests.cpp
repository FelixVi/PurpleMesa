#include <vhdl_parser_driver.h>
#include "gtest/gtest.h"
#include "AstVisitors/AstPrintVisitor.h"

TEST(VisitorTests, simple) {
    AstPrintVisitor v;

    auto nf = NodeFactory();
    std::vector<std::shared_ptr<AstNode>> nodes;
    auto top = nf.make_node(AstNodeType::TOP, nullptr);
    nodes.push_back(top);
    auto child1 = nf.make_node(AstNodeType::ENTITY, top);
    nodes.push_back(child1);
    auto child2 = nf.make_node(AstNodeType::IDENTIFIER, top);
    nodes.push_back(child2);

    for(auto& node : nodes)
        node->accept(v);

    std::cout << "\n\n";

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