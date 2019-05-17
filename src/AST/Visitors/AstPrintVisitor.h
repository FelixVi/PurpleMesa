#ifndef PURPLEMESA_ASTPRINTVISITOR_H
#define PURPLEMESA_ASTPRINTVISITOR_H

#include <Visitors/AstVisitor.h>

class AstPrintVisitor : public AstVisitor
{
public:
    void visit(AssignNode &node, const AstVisitType &type) override;

    void visit(ArchitectureNode &node, const AstVisitType &type) override;

    void visit(EntityDeclarationNode &node, const AstVisitType &type) override;

    void visit(SignalNode &node, const AstVisitType &type) override;

    void visit(BinaryOperatorNode &node, const AstVisitType &type) override;

    void visit(PortNode &node, const AstVisitType &type) override;

    void visit(ProcessNode &node, const AstVisitType &type) override;

    void visit(TopNode &node, const AstVisitType &type) override;

    void visit(SensitivityListNode & node, const AstVisitType &type) override;

    void increaseLevel() override;

    void decreaseLevel() override;

private:
    std::string indent;
    bool hideLocation;

    void checkPasses(const AstVisitType& type) const;
};

#endif //PURPLEMESA_ASTPRINTVISITOR_H
