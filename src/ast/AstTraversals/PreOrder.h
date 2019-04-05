#ifndef PURPLEMESA_PREORDER_H
#define PURPLEMESA_PREORDER_H

#include "AstTraversal.h"

class PreOrderTraversal : public AstTraversal
{
public:
    void traverse(AstNode &node, AstVisitor &visitor) override {
        node.accept(visitor);

        auto children = node.getChildren();
        if(node.hasChildren()){
            visitor.increaseLevel();
            for(auto const& child : children){
                traverse(*child, visitor);
            }
            visitor.decreaseLevel();
        }
    }
};

#endif //PURPLEMESA_PREORDER_H
