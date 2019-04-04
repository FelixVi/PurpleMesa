#ifndef PURPLEMESA_ASTVISITOR_H
#define PURPLEMESA_ASTVISITOR_H

#include "AstTraversals/Filters/AstTraversalFilters.h"

class ArchitectureNode;
class AssignNode;
class EntityNode;
class IdentifierNode;
class LogicalAndNode;
class PortNode;
class ProcessNode;
class TopNode;

class AstVisitor
{
public:
    void visit(ArchitectureNode& node) const {if(traversalFilter->passes())visitFiltered(node);}
    void visit(AssignNode& node) const {if(traversalFilter->passes())visitFiltered(node);}
    void visit(EntityNode& node) const {if(traversalFilter->passes())visitFiltered(node);}
    void visit(IdentifierNode& node) const {if(traversalFilter->passes())visitFiltered(node);}
    void visit(LogicalAndNode& node) const {if(traversalFilter->passes())visitFiltered(node);}
    void visit(PortNode& node) const {if(traversalFilter->passes())visitFiltered(node);}
    void visit(ProcessNode& node) const {if(traversalFilter->passes())visitFiltered(node);}
    void visit(TopNode& node) const {if(traversalFilter->passes())visitFiltered(node);}

    virtual void visitFiltered(ArchitectureNode& node) const = 0;
    virtual void visitFiltered(AssignNode& node) const = 0;
    virtual void visitFiltered(EntityNode& node) const = 0;
    virtual void visitFiltered(IdentifierNode& node) const = 0;
    virtual void visitFiltered(LogicalAndNode& node) const = 0;
    virtual void visitFiltered(PortNode& node) const = 0;
    virtual void visitFiltered(ProcessNode& node) const = 0;
    virtual void visitFiltered(TopNode& node) const = 0;

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
private:
    std::unique_ptr<TraversalFilter> traversalFilter;
};

#endif //PURPLEMESA_ASTVISITOR_H
