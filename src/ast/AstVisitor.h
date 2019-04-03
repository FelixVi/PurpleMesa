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
    virtual void visit(ArchitectureNode& node) = 0;
    virtual void visit(AssignNode& node) = 0;
    virtual void visit(EntityNode& node) = 0;
    virtual void visit(IdentifierNode& node) = 0;
    virtual void visit(LogicalAndNode& node) = 0;
    virtual void visit(PortNode& node) = 0;
    virtual void visit(ProcessNode& node) = 0;
    virtual void visit(TopNode& node) = 0;
};

#endif //PURPLEMESA_ASTVISITOR_H
