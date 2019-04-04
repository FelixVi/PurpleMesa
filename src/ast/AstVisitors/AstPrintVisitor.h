#ifndef PURPLEMESA_ASTPRINTVISITOR_H
#define PURPLEMESA_ASTPRINTVISITOR_H

#include <AstVisitor.h>

class AstPrintVisitor : public AstVisitor
{
public:
    void visitFiltered(AssignNode &node) const override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visitFiltered(ArchitectureNode &node) const override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visitFiltered(EntityNode &node) const override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visitFiltered(IdentifierNode &node) const override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visitFiltered(LogicalAndNode &node) const override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visitFiltered(PortNode &node) const override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visitFiltered(ProcessNode &node) const override {
        std::cout << indent << node.getString() << std::endl;
    }

    void visitFiltered(TopNode &node) const override {
        std::cout << indent << node.getString() << std::endl;
    }

    void increaseLevel() override {
        indent += "  ";
    }

    void decreaseLevel() override {
        if(!indent.empty())
            indent.pop_back();
        if(!indent.empty())
            indent.pop_back();
    }

private:
    std::string indent;
};

#endif //PURPLEMESA_ASTPRINTVISITOR_H
