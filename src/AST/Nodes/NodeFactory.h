#ifndef PURPLEMESA_NODEFACTORY_H
#define PURPLEMESA_NODEFACTORY_H

//class AstNode;
#include "AstNode.h"

#include "AssignNode.h"
#include "ArchitectureNode.h"
#include "BinaryOperatorNode.h"
#include "EntityDeclarationNode.h"
#include "GenericNode.h"
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
            case AstNodeType::ARCHITECTURE:
                return std::make_shared<ArchitectureNode>(AstNodeType::ARCHITECTURE, parent);
            case AstNodeType::ASSIGN:
                return std::make_shared<AssignNode>(AstNodeType::ASSIGN, parent);
            case AstNodeType::BINARY_OPERATOR:
                return std::make_shared<BinaryOperatorNode>(AstNodeType::BINARY_OPERATOR, parent);
            case AstNodeType::ENTITYDECLARATION:
                return std::make_shared<EntityDeclarationNode>(AstNodeType::ENTITYDECLARATION, parent);
            case AstNodeType::GENERIC:
                return std::make_shared<GenericNode>(AstNodeType::GENERIC, parent);
            case AstNodeType::PORT:
                return std::make_shared<PortNode>(AstNodeType::PORT, parent);
            case AstNodeType::PROCESS:
                return std::make_shared<ProcessNode>(AstNodeType::PROCESS, parent);
            case AstNodeType::SENSITIVITYLIST:
                return std::make_shared<SensitivityListNode>(AstNodeType::SENSITIVITYLIST, parent);
            case AstNodeType::SIGNAL:
                return std::make_shared<SignalNode>(AstNodeType::SIGNAL, parent);
            case AstNodeType::TOP:
                return std::make_shared<TopNode>(AstNodeType::TOP, parent);
        }
        throw "Invalid node type.";
    }

    static std::shared_ptr<AstNode> copy_node(const AstNode &src) {
        auto thisNode = std::shared_ptr<AstNode>();

        switch (src.type()) {
            case AstNodeType::ARCHITECTURE:
                thisNode = std::make_shared<ArchitectureNode>(AstNodeType::ARCHITECTURE, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::ASSIGN:
                thisNode = std::make_shared<AssignNode>(AstNodeType::ASSIGN, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::BINARY_OPERATOR:
                thisNode = std::make_shared<BinaryOperatorNode>(AstNodeType::BINARY_OPERATOR, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::ENTITYDECLARATION:
                thisNode = std::make_shared<EntityDeclarationNode>(AstNodeType::ENTITYDECLARATION, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::GENERIC:
                thisNode = std::make_shared<GenericNode>(AstNodeType::GENERIC, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::PORT:
                thisNode = std::make_shared<PortNode>(AstNodeType::PORT, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::PROCESS:
                thisNode =  std::make_shared<ProcessNode>(AstNodeType::PROCESS, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::SENSITIVITYLIST:
                thisNode = std::make_shared<SensitivityListNode>(AstNodeType::SENSITIVITYLIST, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::SIGNAL:
                thisNode = std::make_shared<SignalNode>(AstNodeType::SIGNAL, src.getParent(), src.getLineno(), src.getSourcepath());
                break;
            case AstNodeType::TOP:
                thisNode = std::make_shared<TopNode>(AstNodeType::TOP, src.getParent(), src.getLineno(), src.getSourcepath());
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
