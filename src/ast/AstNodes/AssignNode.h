#ifndef PURPLEMESA_ASSIGNNODE_H
#define PURPLEMESA_ASSIGNNODE_H

#include "AstNode.h"

struct AssignNode : AstNode
{
    AssignNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}

    std::string getString() const override
    {
        return "ASSIGN";
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this);
    }
};

#endif //PURPLEMESA_ASSIGNNODE_H
