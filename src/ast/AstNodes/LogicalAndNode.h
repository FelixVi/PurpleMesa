#ifndef PURPLEMESA_LOGICALANDNODE_H
#define PURPLEMESA_LOGICALANDNODE_H

#include "AstNode.h"

struct LogicalAndNode : AstNode
{
    LogicalAndNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}
    LogicalAndNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &filename) : AstNode(nt, parent, lineno, filename) {}

    std::string getString() const override
    {
        return "LOGICAL_AND";
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this);
    }
};

#endif //PURPLEMESA_LOGICALANDNODE_H
