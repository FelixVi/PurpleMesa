#include <NodeFactory.h>
#include <Visitors/AstPrintVisitor.h>
#include <Traversals/PreOrder.h>
#include "vhdl_parser/vhdl_parser_driver.h"
#include "gtest/gtest.h"
#include "Visitors/RTIL/RTILVisitor.h"
#include "Passes/BindArchPass.h"
#include "PurpleMesa.h"
#include "AstNode.h"

TEST(VisitorTests, simple) {
    PreOrderTraversal t;
    AstPrintVisitor v;
    PurpleMesa PM;

    auto AST = PM.parseFile("../tests/hdl/simple.vhd");

    std::cout << "\n\nTraversing AST ports...\n";

    v.setFilter(AstTraversalFilter::ShowPorts);
    t.traverse(*AST, v);

    std::cout << "End traversing AST ports...\n";


    std::cout << "\nTraversing AST...\n";

    PM.printAST(*AST);

    std::cout << "End traversing AST...\n";

    std::cout << "\nCopy AST...\n";
    auto newAst = NodeFactory::copy_node(*AST);

    std::cout << "Starting RTIL translation of AST copy...\n";

    std::static_pointer_cast<TopNode>(newAst)->run();

    auto pass = BindArchPass();
    pass.run();

    //TODO
    //Need to handle configuration here
    for(auto const& arch : newAst->getChildren()){
        if(arch->type() == AstNodeType::ARCHITECTURE){
            for(auto const& entity : newAst->getChildren()) {
                if (entity->type() == AstNodeType::ENTITYDECLARATION) {
                    entity->addChild(arch);
                    newAst->deleteChild(arch);
                }
            }
        }
    }

    RTILVisitor translator;
    t.traverse(*newAst, translator);

    ASSERT_FALSE(0);
}

TEST(FIFOTests, simple) {
    PreOrderTraversal t;
    AstPrintVisitor v;
    PurpleMesa PM;

    auto AST = PM.parseFile("../tests/hdl/fifo_async.vhd");

    std::cout << "\n\nTraversing AST ports...\n";

    v.setFilter(AstTraversalFilter::ShowPorts);
    t.traverse(*AST, v);

    std::cout << "End traversing AST ports...\n";


    std::cout << "\nTraversing AST...\n";

    PM.printAST(*AST);

    std::cout << "End traversing AST...\n";

    std::cout << "\nCopy AST...\n";
    auto newAst = NodeFactory::copy_node(*AST);

    std::cout << "Starting RTIL translation of AST copy...\n";

    std::static_pointer_cast<TopNode>(newAst)->run();

    auto pass = BindArchPass();
    pass.run();

    //TODO
    //Need to handle configuration here
    for(auto const& arch : newAst->getChildren()){
        if(arch->type() == AstNodeType::ARCHITECTURE){
            for(auto const& entity : newAst->getChildren()) {
                if (entity->type() == AstNodeType::ENTITYDECLARATION) {
                    entity->addChild(arch);
                    newAst->deleteChild(arch);
                }
            }
        }
    }

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