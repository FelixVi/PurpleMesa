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

    void accept(AstVisitor &visitor) override {
        visitor.visit(*this);
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
