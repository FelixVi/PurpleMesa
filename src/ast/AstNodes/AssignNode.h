#ifndef PURPLEMESA_ASSIGNNODE_H
#define PURPLEMESA_ASSIGNNODE_H

#include "AstNode.h"

struct AssignNode : AstNode
{
    AssignNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {}
    std::string getString() const override
    {
        return "ASSIGN";
    }

    void accept(AstVisitor &visitor) override {
        visitor.visit(*this);
    }
};

struct AssignFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make(std::shared_ptr<AstNode> parent) const override {
        return std::make_shared<AssignNode>(parent);
    }
};

#endif //PURPLEMESA_ASSIGNNODE_H