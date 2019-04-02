#ifndef PURPLEMESA_PORTNODE_H
#define PURPLEMESA_PORTNODE_H

#include "AstNode.h"

struct PortNode : AstNode
{
    PortNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {}
    std::string getString() const override
    {
        return "PORT";
    }

    AstNodeType type() const override {
        return AstNodeType::PORT;
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this);
    }
};

struct PortFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make(std::shared_ptr<AstNode> parent) const override
    {
        return std::make_shared<PortNode>(parent);
    }
};

#endif //PURPLEMESA_PORTNODE_H
