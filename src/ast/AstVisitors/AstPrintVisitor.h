#ifndef PURPLEMESA_ASTPRINTVISITOR_H
#define PURPLEMESA_ASTPRINTVISITOR_H

#include <AstVisitor.h>

class AstPrintVisitor : public AstVisitor
{
public:
    void visit(AssignNode &node) const override {
        std::cout << indent << node.getString();
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(ArchitectureNode &node) const override {
        std::cout << indent << node.getString();
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(EntityDeclarationNode &node) const override {
        std::cout << indent << node.getString();
        std::cout << " " << node.getProperty("identifier");
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(SignalNode &node) const override {
        std::cout << indent << node.getString();
        std::cout << " " << node.getProperty("identifier");
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(LogicalAndNode &node) const override {
        std::cout << indent << node.getString();
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(PortNode &node) const override {
        std::cout << indent << node.getString();
        std::cout << " " << node.getProperty("identifier");
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(ProcessNode &node) const override {
        std::cout << indent << node.getString();
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(TopNode &node) const override {
        std::cout << indent << node.getString();
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(SensitivityListNode & node) const override {
        std::cout << indent << node.getString();
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
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
    bool hideLocation;
};

#endif //PURPLEMESA_ASTPRINTVISITOR_H
