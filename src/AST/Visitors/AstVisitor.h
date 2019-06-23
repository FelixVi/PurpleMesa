#ifndef PURPLEMESA_ASTVISITOR_H
#define PURPLEMESA_ASTVISITOR_H

#include <memory>
#include "AstVisitType.h"

class TraversalFilter;
class ShowAll;

class ArchitectureNode;
class AssignNode;
class BinaryOperatorNode;
class EntityDeclarationNode;
class GenericNode;
class IntegerNode;
class PortNode;
class ProcessNode;
class RangeNode;
class SensitivityListNode;
class IdentifierNode;
class TopNode;

enum class AstTraversalFilter
{
    ShowAll,
    ShowPorts
};

class AstVisitor
{
public:
    AstVisitor();

    virtual void visit(ArchitectureNode& node, const AstVisitType& type) = 0;
    virtual void visit(AssignNode& node, const AstVisitType& type) = 0;
    virtual void visit(BinaryOperatorNode& node, const AstVisitType& type) = 0;
    virtual void visit(EntityDeclarationNode& node, const AstVisitType& type) = 0;
    virtual void visit(GenericNode& node, const AstVisitType& type) = 0;
    virtual void visit(IntegerNode& node, const AstVisitType& type) = 0;
    virtual void visit(PortNode& node, const AstVisitType& type) = 0;
    virtual void visit(ProcessNode& node, const AstVisitType& type) = 0;
    virtual void visit(RangeNode& node, const AstVisitType& type) = 0;
    virtual void visit(SensitivityListNode& node, const AstVisitType& type) = 0;
    virtual void visit(IdentifierNode& node, const AstVisitType& type) = 0;
    virtual void visit(TopNode& node, const AstVisitType& type) = 0;

    virtual void increaseLevel() = 0;
    virtual void decreaseLevel() = 0;

    virtual bool isDoublePass(){return false;}

    void setFilter(const AstTraversalFilter filter);

    const std::unique_ptr<TraversalFilter> &getTraversalFilter() const {
        return traversalFilter;
    }

private:
    std::unique_ptr<TraversalFilter> traversalFilter;
};

#endif //PURPLEMESA_ASTVISITOR_H
