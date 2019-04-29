#ifndef PURPLEMESA_ENTITYNODE_H
#define PURPLEMESA_ENTITYNODE_H

#include "AstNode.h"

struct EntityNode : AstNode
{
    EntityNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}

    std::string getString() const override
    {
        return "ENTITY";
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this);
    }
};

#endif //PURPLEMESA_ENTITYNODE_H
