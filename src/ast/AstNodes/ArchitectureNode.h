#ifndef PURPLEMESA_ARCHITECTURENODE_H
#define PURPLEMESA_ARCHITECTURENODE_H

#include "AstNode.h"

struct ArchitectureNode : AstNode
{
    std::string getString() const override
    {
        return "ARCHITECTURE";
    }
};

struct ArchitectureFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make() const override
    {
        return std::make_shared<ArchitectureNode>();
    }
};

#endif //PURPLEMESA_ARCHITECTURENODE_H
