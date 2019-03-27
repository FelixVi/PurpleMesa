#include "gtest/gtest.h"
#include "NodeFactory.h"

TEST(ASTTests, simple) {
    auto nf = NodeFactory();
    auto top = nf.make_node(AstNodeType::TOP);
    auto child1 = nf.make_node(AstNodeType::ENTITY);
    auto child2 = nf.make_node(AstNodeType::IDENTIFIER);

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
