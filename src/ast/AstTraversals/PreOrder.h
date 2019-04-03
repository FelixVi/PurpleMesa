#ifndef PURPLEMESA_PREORDER_H
#define PURPLEMESA_PREORDER_H

#include "AstTraversal.h"

class PreOrderTraversal : public AstTraversal
{
public:
    void traverse(AstNode &node, AstVisitor &visitor) override {
        node.accept(visitor);

        for(auto const& child : node.getChildren()){
            child->accept(visitor);
        }
    }
};

#endif //PURPLEMESA_PREORDER_H
