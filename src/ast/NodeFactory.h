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
            auto node = std::make_shared<AssignNode>(AstNodeType::ASSIGN, parent);
            return node;
        };

        factories[AstNodeType::LOGICAL_AND] = [](auto parent) {
            auto node = std::make_shared<LogicalAndNode>(AstNodeType::LOGICAL_AND, parent);
            return node;
        };

        factories[AstNodeType::TOP] = [](auto parent) {
            auto node = std::make_shared<TopNode>(AstNodeType::TOP, parent);
            return node;
        };

        factories[AstNodeType::ENTITY] = [](auto parent) {
            auto node = std::make_shared<EntityNode>(AstNodeType::ENTITY, parent);
            return node;
        };

        factories[AstNodeType::PORT] = [](auto parent) {
            auto node = std::make_shared<PortNode>(AstNodeType::PORT, parent);
            return node;
        };

        factories[AstNodeType::ARCHITECTURE] = [](auto parent) {
            auto node = std::make_shared<ArchitectureNode>(AstNodeType::ARCHITECTURE, parent);
            return node;
        };

        factories[AstNodeType::PROCESS] = [](auto parent) {
            auto node = std::make_shared<ProcessNode>(AstNodeType::PROCESS, parent);
            return node;
        };

        factories[AstNodeType::IDENTIFIER] = [](auto parent) {
            auto node = std::make_shared<IdentifierNode>(AstNodeType::IDENTIFIER, parent);
            return node;
        };
    }

    std::shared_ptr<AstNode> make_node(const AstNodeType &type, std::shared_ptr<AstNode> parent) {
        return factories[type](parent);
    }
};

#endif //PURPLEMESA_NODEFACTORY_H
