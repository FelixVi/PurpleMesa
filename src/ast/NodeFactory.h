#ifndef PURPLEMESA_NODEFACTORY_H
#define PURPLEMESA_NODEFACTORY_H

#include "AstNode.h"
#include "TopNode.h"
#include "IdentifierNode.h"
#include "ProcessNode.h"
#include "PortNode.h"
#include "EntityNode.h"
#include "AssignNode.h"
#include "ArchitectureNode.h"
#include "LogicalAndNode.h"
#include <functional>
#include <memory>

class NodeFactory
{
    std::map<AstNodeType , std::function<std::shared_ptr<AstNode>()>> factories;
public:

    NodeFactory()
    {
        factories[AstNodeType::ASSIGN] = [] {
            auto node = std::make_shared<AssignNode>();
            return node;
        };

        factories[AstNodeType::LOGICAL_AND] = [] {
            auto node = std::make_shared<LogicalAndNode>();
            return node;
        };

        factories[AstNodeType::TOP] = [] {
            auto node = std::make_shared<TopNode>();
            return node;
        };

        factories[AstNodeType::ENTITY] = [] {
            auto node = std::make_shared<EntityNode>();
            return node;
        };

        factories[AstNodeType::PORT] = [] {
            auto node = std::make_shared<PortNode>();
            return node;
        };

        factories[AstNodeType::ARCHITECTURE] = [] {
            auto node = std::make_shared<ArchitectureNode>();
            return node;
        };

        factories[AstNodeType::PROCESS] = [] {
            auto node = std::make_shared<ProcessNode>();
            return node;
        };

        factories[AstNodeType::IDENTIFIER] = [] {
            auto node = std::make_shared<IdentifierNode>();
            return node;
        };
    }

    std::shared_ptr<AstNode> make_node(const AstNodeType &type) {
        return factories[type]();
    }
};

#endif //PURPLEMESA_NODEFACTORY_H
