#ifndef PURPLEMESA_TOPNODE_H
#define PURPLEMESA_TOPNODE_H

#include "AstNode.h"

struct TopNode : AstNode
{
    std::string getString() const override
    {
        return "TOP";
    }
};

struct TopFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make() const override
    {
        return std::make_shared<TopNode>();
    }
};

#endif //PURPLEMESA_TOPNODE_H
