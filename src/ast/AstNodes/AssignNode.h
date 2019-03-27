#ifndef PURPLEMESA_ASSIGNNODE_H
#define PURPLEMESA_ASSIGNNODE_H

#include "AstNode.h"

struct AssignNode : AstNode
{
    std::string getString() const override
    {
        return "ASSIGN";
    }
};

struct AssignFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make() const override {
        return std::make_shared<AssignNode>();
    }
};

#endif //PURPLEMESA_ASSIGNNODE_H
