#ifndef PURPLEMESA_IDENTIFIERNODE_H
#define PURPLEMESA_IDENTIFIERNODE_H

#include "AstNode.h"

struct IdentifierNode : AstNode
{
    std::string getString() const override
    {
        return "IDENTIFIER";
    }
};

struct IdentifierFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make() const override {
        return std::make_shared<IdentifierNode>();
    }
};

#endif //PURPLEMESA_IDENTIFIERNODE_H
