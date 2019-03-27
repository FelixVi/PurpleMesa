#ifndef PURPLEMESA_PORTNODE_H
#define PURPLEMESA_PORTNODE_H

#include "AstNode.h"

struct PortNode : AstNode
{
    std::string getString() const override
    {
        return "PORT";
    }
};

struct PortFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make() const override
    {
        return std::make_shared<PortNode>();
    }
};

#endif //PURPLEMESA_PORTNODE_H
