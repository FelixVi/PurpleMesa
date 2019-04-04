#ifndef PURPLEMESA_IDENTIFIERNODE_H
#define PURPLEMESA_IDENTIFIERNODE_H

#include "AstNode.h"

struct IdentifierNode : AstNode
{
    IdentifierNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {}
    std::string getString() const override
    {
        return "IDENTIFIER";
    }

    AstNodeType type() const override {
        return AstNodeType::IDENTIFIER;
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes())visitor.visit(*this);
    }
};

struct IdentifierFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make(std::shared_ptr<AstNode> parent) const override {
        return std::make_shared<IdentifierNode>(parent);
    }
};

#endif //PURPLEMESA_IDENTIFIERNODE_H
