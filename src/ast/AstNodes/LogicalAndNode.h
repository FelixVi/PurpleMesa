#ifndef PURPLEMESA_LOGICALANDNODE_H
#define PURPLEMESA_LOGICALANDNODE_H

#include "AstNode.h"

struct LogicalAndNode : AstNode
{
    std::string getString() const override
    {
        return "LOGICAL_AND";
    }
};

struct LogicalAndFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make() const override
    {
        return std::make_shared<LogicalAndNode>();
    }
};

#endif //PURPLEMESA_LOGICALANDNODE_H
