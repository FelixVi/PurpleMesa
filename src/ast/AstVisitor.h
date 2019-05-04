#ifndef PURPLEMESA_ASTVISITOR_H
#define PURPLEMESA_ASTVISITOR_H

#include "AstTraversals/Filters/AstTraversalFilters.h"

class ArchitectureNode;
class AssignNode;
class EntityDeclarationNode;
class SignalNode;
class LogicalAndNode;
class PortNode;
class ProcessNode;
class TopNode;
class SensitivityListNode;

class AstVisitor
{
public:
    virtual void visit(ArchitectureNode& node) const = 0;
    virtual void visit(AssignNode& node) const = 0;
    virtual void visit(EntityDeclarationNode& node) const = 0;
    virtual void visit(SignalNode& node) const = 0;
    virtual void visit(LogicalAndNode& node) const = 0;
    virtual void visit(PortNode& node) const = 0;
    virtual void visit(ProcessNode& node) const = 0;
    virtual void visit(TopNode& node) const = 0;
    virtual void visit(SensitivityListNode& node) const = 0;

    virtual void increaseLevel() = 0;
    virtual void decreaseLevel() = 0;

    void setFilter(const AstTraversalFilter filter)
    {
        switch(filter){
            case AstTraversalFilter::ShowAll:
                traversalFilter = std::make_unique<ShowAll>();
                break;
            case AstTraversalFilter::ShowPorts:
                traversalFilter = std::make_unique<ShowPorts>();
                break;
            default:
                throw std::runtime_error("Unsupported AST traversal filter.");
        }
    }

    const std::unique_ptr<TraversalFilter> &getTraversalFilter() const {
        return traversalFilter;
    }

private:
    std::unique_ptr<TraversalFilter> traversalFilter = std::make_unique<ShowAll>();
};

#endif //PURPLEMESA_ASTVISITOR_H
