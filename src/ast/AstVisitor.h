#ifndef PURPLEMESA_ASTVISITOR_H
#define PURPLEMESA_ASTVISITOR_H

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
    virtual void visit(ArchitectureNode& node) const = 0;
    virtual void visit(AssignNode& node) const = 0;
    virtual void visit(EntityNode& node) const = 0;
    virtual void visit(IdentifierNode& node) const = 0;
    virtual void visit(LogicalAndNode& node) const = 0;
    virtual void visit(PortNode& node) const = 0;
    virtual void visit(ProcessNode& node) const = 0;
    virtual void visit(TopNode& node) const = 0;

    virtual void increaseLevel() = 0;
    virtual void decreaseLevel() = 0;
};

#endif //PURPLEMESA_ASTVISITOR_H
