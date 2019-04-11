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

struct ArchitectureFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make(AstNodeType NodeType, std::shared_ptr<AstNode> parent) const override
    {
        return std::make_shared<ArchitectureNode>(NodeType, parent);
    }
};

#endif //PURPLEMESA_ARCHITECTURENODE_H
