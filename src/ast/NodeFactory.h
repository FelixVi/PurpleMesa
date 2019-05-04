#ifndef PURPLEMESA_NODEFACTORY_H
#define PURPLEMESA_NODEFACTORY_H

#include "AstNode.h"

#include "AssignNode.h"
#include "ArchitectureNode.h"
#include "EntityDeclarationNode.h"
#include "LogicalAndNode.h"
#include "ProcessNode.h"
#include "PortNode.h"
#include "SensitivityListNode.h"
#include "SignalNode.h"
#include "TopNode.h"

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
            case AstNodeType::ENTITYDECLARATION:
                return std::make_shared<EntityDeclarationNode>(AstNodeType::ENTITYDECLARATION, parent);
            case AstNodeType::PORT:
                return std::make_shared<PortNode>(AstNodeType::PORT, parent);
            case AstNodeType::ARCHITECTURE:
                return std::make_shared<ArchitectureNode>(AstNodeType::ARCHITECTURE, parent);
            case AstNodeType::PROCESS:
                return std::make_shared<ProcessNode>(AstNodeType::PROCESS, parent);
            case AstNodeType::SIGNAL:
                return std::make_shared<SignalNode>(AstNodeType::SIGNAL, parent);
            case AstNodeType::SENSITIVITYLIST:
                return std::make_shared<SensitivityListNode>(AstNodeType::SENSITIVITYLIST, parent);
        }
        throw "Invalid node type.";
    }

    static std::shared_ptr<AstNode> copy_node(const AstNode &src) {
        auto thisNode = std::shared_ptr<AstNode>();

        switch (src.type()) {
            case AstNodeType::ASSIGN:
                thisNode = std::make_shared<AssignNode>(AstNodeType::ASSIGN, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::LOGICAL_AND:
                thisNode = std::make_shared<LogicalAndNode>(AstNodeType::LOGICAL_AND, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::TOP:
                thisNode = std::make_shared<TopNode>(AstNodeType::TOP, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::ENTITYDECLARATION:
                thisNode = std::make_shared<EntityDeclarationNode>(AstNodeType::ENTITYDECLARATION, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::PORT:
                thisNode = std::make_shared<PortNode>(AstNodeType::PORT, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::ARCHITECTURE:
                thisNode = std::make_shared<ArchitectureNode>(AstNodeType::ARCHITECTURE, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::PROCESS:
                thisNode =  std::make_shared<ProcessNode>(AstNodeType::PROCESS, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::SIGNAL:
                thisNode = std::make_shared<SignalNode>(AstNodeType::SIGNAL, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::SENSITIVITYLIST:
                thisNode = std::make_shared<SensitivityListNode>(AstNodeType::SENSITIVITYLIST, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            default:
                throw "Invalid node type.";
        }

        thisNode->setProperties(src.getProperties());

        for(auto& child : src.getChildren()){
            thisNode->addChild(copy_node(*child));
        }

        return thisNode;
    }

};

#endif //PURPLEMESA_NODEFACTORY_H
