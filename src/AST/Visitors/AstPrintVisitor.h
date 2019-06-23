#ifndef PURPLEMESA_ASTPRINTVISITOR_H
#define PURPLEMESA_ASTPRINTVISITOR_H

#include <Visitors/AstVisitor.h>

class AstPrintVisitor : public AstVisitor
{
public:
    void visit(AssignNode &node, const AstVisitType &type) override;

    void visit(ArchitectureNode &node, const AstVisitType &type) override;

    void visit(EntityDeclarationNode &node, const AstVisitType &type) override;

    void visit(GenericNode &node, const AstVisitType &type) override;

    void visit(IntegerNode &node, const AstVisitType &type) override;

    void visit(LiteralCharacterNode &node, const AstVisitType &type) override;

    void visit(OperatorBinaryNode &node, const AstVisitType &type) override;

    void visit(OperatorUnaryNode &node, const AstVisitType &type) override;

    void visit(PortNode &node, const AstVisitType &type) override;

    void visit(ProcessNode &node, const AstVisitType &type) override;

    void visit(RangeNode & node, const AstVisitType &type) override;

    void visit(SensitivityListNode & node, const AstVisitType &type) override;

    void visit(IdentifierNode &node, const AstVisitType &type) override;

    void visit(TopNode &node, const AstVisitType &type) override;

    void increaseLevel() override;

    void decreaseLevel() override;

private:
    std::string indent;
    bool hideLocation;

    void checkPasses(const AstVisitType& type) const;
};

#endif //PURPLEMESA_ASTPRINTVISITOR_H
