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

struct EntityFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make(AstNodeType NodeType, std::shared_ptr<AstNode> parent) const override
    {
        return std::make_shared<EntityNode>(NodeType, parent);
    }
};

#endif //PURPLEMESA_ENTITYNODE_H
