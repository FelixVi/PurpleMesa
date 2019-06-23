#ifndef PURPLEMESA_RTILVISITOR_H
#define PURPLEMESA_RTILVISITOR_H

#include <Visitors/AstVisitor.h>

class RTILVisitor : public AstVisitor
{
public:
    void visit(ArchitectureNode &node, const AstVisitType &type) override;

    void visit(AssignNode &node, const AstVisitType &type) override;

    void visit(BinaryOperatorNode &node, const AstVisitType &type) override;

    void visit(EntityDeclarationNode &node, const AstVisitType &type) override;

    void visit(GenericNode &node, const AstVisitType &type) override;

    void visit(IntegerNode &node, const AstVisitType &type) override;

    void visit(PortNode &node, const AstVisitType &type) override;

    void visit(ProcessNode &node, const AstVisitType &type) override;

    void visit(RangeNode & node, const AstVisitType &type) override;

    void visit(SensitivityListNode & node, const AstVisitType &type) override;

    void visit(IdentifierNode &node, const AstVisitType &type) override;

    void visit(TopNode &node, const AstVisitType &type) override;

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
