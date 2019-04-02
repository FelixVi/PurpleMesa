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
    std::map<AstNodeType , std::function<std::shared_ptr<AstNode>(std::shared_ptr<AstNode> parent)>> factories;
public:

    NodeFactory()
    {
        factories[AstNodeType::ASSIGN] = [](auto parent) {
            auto node = std::make_shared<AssignNode>(parent);
            return node;
        };

        factories[AstNodeType::LOGICAL_AND] = [](auto parent) {
            auto node = std::make_shared<LogicalAndNode>(parent);
            return node;
        };

        factories[AstNodeType::TOP] = [](auto parent) {
            auto node = std::make_shared<TopNode>(parent);
            return node;
        };

        factories[AstNodeType::ENTITY] = [](auto parent) {
            auto node = std::make_shared<EntityNode>(parent);
            return node;
        };

        factories[AstNodeType::PORT] = [](auto parent) {
            auto node = std::make_shared<PortNode>(parent);
            return node;
        };

        factories[AstNodeType::ARCHITECTURE] = [](auto parent) {
            auto node = std::make_shared<ArchitectureNode>(parent);
            return node;
        };

        factories[AstNodeType::PROCESS] = [](auto parent) {
            auto node = std::make_shared<ProcessNode>(parent);
            return node;
        };

        factories[AstNodeType::IDENTIFIER] = [](auto parent) {
            auto node = std::make_shared<IdentifierNode>(parent);
            return node;
        };
    }

    std::shared_ptr<AstNode> make_node(const AstNodeType &type, std::shared_ptr<AstNode> parent) {
        return factories[type](parent);
    }
};

#endif //PURPLEMESA_NODEFACTORY_H
