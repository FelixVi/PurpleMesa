#ifndef PURPLEMESA_ENTITYNODE_H
#define PURPLEMESA_ENTITYNODE_H

#include "AstNode.h"

struct EntityNode : AstNode
{
    EntityNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {}
    std::string getString() const override
    {
        return "ENTITY";
    }

    AstNodeType type() const override {
        return AstNodeType::ENTITY;
    }

    void accept(const AstVisitor &visitor) override {
        visitor.visit(*this);
    }
};

struct EntityFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make(std::shared_ptr<AstNode> parent) const override
    {
        return std::make_shared<EntityNode>(parent);
    }
};

#endif //PURPLEMESA_ENTITYNODE_H
