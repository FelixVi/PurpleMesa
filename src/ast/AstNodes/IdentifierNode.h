#ifndef PURPLEMESA_IDENTIFIERNODE_H
#define PURPLEMESA_IDENTIFIERNODE_H

#include "AstNode.h"

struct IdentifierNode : AstNode
{
    IdentifierNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}

    std::string getString() const override
    {
        return "IDENTIFIER";
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this);
    }
};

struct IdentifierFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make(AstNodeType NodeType, std::shared_ptr<AstNode> parent) const override {
        return std::make_shared<IdentifierNode>(NodeType, parent);
    }
};

#endif //PURPLEMESA_IDENTIFIERNODE_H
