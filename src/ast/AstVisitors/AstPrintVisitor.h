#ifndef PURPLEMESA_ASTPRINTVISITOR_H
#define PURPLEMESA_ASTPRINTVISITOR_H

#include <AstVisitor.h>

class AstPrintVisitor : public AstVisitor
{
public:
    void visit(AssignNode &node) override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visit(ArchitectureNode &node) override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visit(EntityNode &node) override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visit(IdentifierNode &node) override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visit(LogicalAndNode &node) override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visit(PortNode &node) override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visit(ProcessNode &node) override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visit(TopNode &node) override {
        std::cout << indent << node.getString() << std::endl;
    }
private:
    std::string indent;
};

#endif //PURPLEMESA_ASTPRINTVISITOR_H
