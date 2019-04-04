#ifndef PURPLEMESA_ARCHITECTURENODE_H
#define PURPLEMESA_ARCHITECTURENODE_H

#include "AstNode.h"

struct ArchitectureNode : AstNode
{
    ArchitectureNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {}
    std::string getString() const override
    {
        return "ARCHITECTURE";
    }

    AstNodeType type() const override {
        return AstNodeType::ARCHITECTURE;
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes())visitor.visit(*this);
    }
};

struct ArchitectureFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make(std::shared_ptr<AstNode> parent) const override
    {
        return std::make_shared<ArchitectureNode>(parent);
    }
};

#endif //PURPLEMESA_ARCHITECTURENODE_H
