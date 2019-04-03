#ifndef PURPLEMESA_LOGICALANDNODE_H
#define PURPLEMESA_LOGICALANDNODE_H

#include "AstNode.h"

struct LogicalAndNode : AstNode
{
    LogicalAndNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {}
    std::string getString() const override
    {
        return "LOGICAL_AND";
    }

    void accept(AstVisitor &visitor) override {
        visitor.visit(*this);
    }
};

struct LogicalAndFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make(std::shared_ptr<AstNode> parent) const override
    {
        return std::make_shared<LogicalAndNode>(parent);
    }
};

#endif //PURPLEMESA_LOGICALANDNODE_H
