#ifndef PURPLEMESA_TOPNODE_H
#define PURPLEMESA_TOPNODE_H

#include "AstNode.h"

struct TopNode : AstNode
{
    TopNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}

    std::string getString() const override
    {
        return "TOP";
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this);
    }
};

struct TopFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make(AstNodeType NodeType, std::shared_ptr<AstNode> parent) const override
    {
        return std::make_shared<TopNode>(NodeType, parent);
    }
};

#endif //PURPLEMESA_TOPNODE_H
