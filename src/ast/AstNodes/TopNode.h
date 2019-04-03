#ifndef PURPLEMESA_TOPNODE_H
#define PURPLEMESA_TOPNODE_H

#include "AstNode.h"

struct TopNode : AstNode
{
    TopNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {

    }
    std::string getString() const override
    {
        return "TOP";
    }
};

struct TopFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make(std::shared_ptr<AstNode> parent) const override
    {
        return std::make_shared<TopNode>(parent);
    }
};

#endif //PURPLEMESA_TOPNODE_H
