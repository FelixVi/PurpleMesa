#ifndef PURPLEMESA_RTILVISITOR_H
#define PURPLEMESA_RTILVISITOR_H

#include <AstVisitor.h>

class RTILVisitor : public AstVisitor
{
public:
    void visit(AssignNode &node, const AstVisitType &type) override {

    }

    void visit(ArchitectureNode &node, const AstVisitType &type) override {

    }

    void visit(EntityDeclarationNode &node, const AstVisitType &type) override {
        if(type==AstVisitType::TRANSLATE_PRE) {
            std::cout << indent;
            std::cout << "module \\" << node.getProperty("identifier") << "\n";
            increaseLevel();
        }
        if(type==AstVisitType::TRANSLATE_POST) {
            decreaseLevel();
            std::cout << indent;
            std::cout << "end\n";
        }
    }

    void visit(SignalNode &node, const AstVisitType &type) override {

    }

    void visit(BinaryOperatorNode &node, const AstVisitType &type) override {
        if(type==AstVisitType::TRANSLATE_PRE) {
            std::cout << "\n";
            std::cout << indent;
            std::cout << "attribute \\src \"" << node.getFilename() << ":" << node.getLineno() << "\"" << "\n";
            std::cout << indent;
            std::cout << "cell ";
            std::cout << "$";
            std::cout << node.getProperty("operator") << "\n";
            increaseLevel();
        }
        if(type==AstVisitType::TRANSLATE_POST) {
            decreaseLevel();
            std::cout << indent;
            std::cout << "end\n";
        }
    }

    void visit(PortNode &node, const AstVisitType &type) override {
        if(type==AstVisitType::TRANSLATE_PRE)
        {
            std::cout << "\n";

            std::cout << indent;
            std::cout << "attribute \\src \"" << node.getFilename() << ":" << node.getLineno() << "\"" << "\n";
            std::cout << indent;
            std::cout << "wire ";

            if (node.getProperty("subtype") == "std_logic_vector")
                std::cout << "width " << node.getProperty("subtype_width")<< " ";
            if (node.getProperty("direction") == "in")
                std::cout << "input ";
            else if (node.getProperty("direction") == "out")
                std::cout << "output ";
            else
                throw std::invalid_argument("Invalid direction.");
            std::cout << "\\" + node.getProperty("identifier") + "\n";
        }
    }

    void visit(ProcessNode &node, const AstVisitType &type) override {

    }

    void visit(TopNode &node, const AstVisitType &type) override {

    }

    void visit(SensitivityListNode & node, const AstVisitType &type) override {

    }

    bool isDoublePass() override {
        return true;
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

#endif //PURPLEMESA_RTILVISITOR_H
