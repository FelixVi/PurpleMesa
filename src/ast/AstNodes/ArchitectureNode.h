#ifndef PURPLEMESA_ARCHITECTURENODE_H
#define PURPLEMESA_ARCHITECTURENODE_H

#include "AstNode.h"

struct ArchitectureNode : AstNode
{
    ArchitectureNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}

    std::string getString() const override
    {
        return "ARCHITECTURE";
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this);
    }
};

#endif //PURPLEMESA_ARCHITECTURENODE_H
