#ifndef PURPLEMESA_ENTITYNODE_H
#define PURPLEMESA_ENTITYNODE_H

#include "AstNode.h"

struct EntityNode : AstNode
{
    std::string getString() const override
    {
        return "ENTITY";
    }
};

struct EntityFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make() const override
    {
        return std::make_shared<EntityNode>();
    }
};

#endif //PURPLEMESA_ENTITYNODE_H
