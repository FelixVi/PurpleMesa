#ifndef PURPLEMESA_ASTPRINTVISITOR_H
#define PURPLEMESA_ASTPRINTVISITOR_H

#include <AstVisitor.h>

class AstPrintVisitor : public AstVisitor
{
public:
    void visit(AssignNode &node, const AstVisitType &type) override {
        checkPasses(type);
        std::cout << indent << node.getString();
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(ArchitectureNode &node, const AstVisitType &type) override {
        checkPasses(type);
        std::cout << indent << node.getString();
        if (!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(EntityDeclarationNode &node, const AstVisitType &type) override {
        checkPasses(type);
        std::cout << indent << node.getString();
        std::cout << " " << node.getProperty("identifier");
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(SignalNode &node, const AstVisitType &type) override {
        checkPasses(type);
        std::cout << indent << node.getString();
        std::cout << " " << node.getProperty("identifier");
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(LogicalAndNode &node, const AstVisitType &type) override {
        checkPasses(type);
        std::cout << indent << node.getString();
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(PortNode &node, const AstVisitType &type) override {
        checkPasses(type);
        std::cout << indent << node.getString();
        std::cout << " " << node.getProperty("identifier");
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(ProcessNode &node, const AstVisitType &type) override {
        checkPasses(type);
        std::cout << indent << node.getString();
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(TopNode &node, const AstVisitType &type) override {
        checkPasses(type);
        std::cout << indent << node.getString();
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
    }

    void visit(SensitivityListNode & node, const AstVisitType &type) override {
        checkPasses(type);
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
    void checkPasses(const AstVisitType& type) const{
        if(!(type==AstVisitType::SINGLE))
            throw std::invalid_argument("AstPrintVisitor requires single visit.");
    };
};

#endif //PURPLEMESA_ASTPRINTVISITOR_H
