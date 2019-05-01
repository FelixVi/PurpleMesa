#ifndef PURPLEMESA_ENTITYDECLARATIONNODE_H
#define PURPLEMESA_ENTITYDECLARATIONNODE_H

#include "AstNode.h"

struct EntityDeclarationNode : AstNode
{
    EntityDeclarationNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}
    EntityDeclarationNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &filename) : AstNode(nt, parent, lineno, filename) {}

    std::string getString() const override
    {
        return "ENTITY DECLARATION";
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this);
    }
};

#endif //PURPLEMESA_ENTITYDECLARATIONNODE_H
