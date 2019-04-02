#ifndef PURPLEMESA_ASTVISITOR_H
#define PURPLEMESA_ASTVISITOR_H

class AssignNode;
class TopNode;

class AstVisitor
{
public:
    virtual void visit(AssignNode& node) = 0;
    virtual void visit(TopNode& node) = 0;
};

#endif //PURPLEMESA_ASTVISITOR_H
