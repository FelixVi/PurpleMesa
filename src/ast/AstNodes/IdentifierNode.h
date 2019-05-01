#ifndef PURPLEMESA_IDENTIFIERNODE_H
#define PURPLEMESA_IDENTIFIERNODE_H

#include "AstNode.h"

struct IdentifierNode : AstNode
{
    IdentifierNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}
    IdentifierNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, std::string arg) : AstNode(nt, parent) {identifier=arg;}
    IdentifierNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &filename) : AstNode(nt, parent, lineno, filename) {}

    std::string getString() const override
    {
        return "IDENTIFIER " + identifier;
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this);
    }

    std::string identifier;
};

#endif //PURPLEMESA_IDENTIFIERNODE_H
