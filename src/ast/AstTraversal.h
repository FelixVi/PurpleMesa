#ifndef PURPLEMESA_ASTTRAVERSAL_H
#define PURPLEMESA_ASTTRAVERSAL_H

struct AstTraversal
{
    virtual void traverse(AstNode &node, AstVisitor &visitor) = 0;
};

#endif //PURPLEMESA_ASTTRAVERSAL_H
