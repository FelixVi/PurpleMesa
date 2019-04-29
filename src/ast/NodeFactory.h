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
public:
    static std::shared_ptr<AstNode> make_node(const AstNodeType &type, std::shared_ptr<AstNode> parent) {
        switch (type) {
            case AstNodeType::ASSIGN:
                return std::make_shared<AssignNode>(AstNodeType::ASSIGN, parent);
            case AstNodeType::LOGICAL_AND:
                return std::make_shared<LogicalAndNode>(AstNodeType::LOGICAL_AND, parent);
            case AstNodeType::TOP:
                return std::make_shared<TopNode>(AstNodeType::TOP, parent);
            case AstNodeType::ENTITY:
                return std::make_shared<EntityNode>(AstNodeType::ENTITY, parent);
            case AstNodeType::PORT:
                return std::make_shared<PortNode>(AstNodeType::PORT, parent);
            case AstNodeType::ARCHITECTURE:
                return std::make_shared<ArchitectureNode>(AstNodeType::ARCHITECTURE, parent);
            case AstNodeType::PROCESS:
                return std::make_shared<ProcessNode>(AstNodeType::PROCESS, parent);
            case AstNodeType::IDENTIFIER:
                return std::make_shared<IdentifierNode>(AstNodeType::IDENTIFIER, parent);
        }
        throw "Invalid node type.";
    }
};

#endif //PURPLEMESA_NODEFACTORY_H
