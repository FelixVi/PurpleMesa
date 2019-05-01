#ifndef PURPLEMESA_NODEFACTORY_H
#define PURPLEMESA_NODEFACTORY_H

#include "AstNode.h"
#include "TopNode.h"
#include "IdentifierNode.h"
#include "ProcessNode.h"
#include "PortNode.h"
#include "EntityDeclarationNode.h"
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
            case AstNodeType::ENTITYDECLARATION:
                return std::make_shared<EntityDeclarationNode>(AstNodeType::ENTITYDECLARATION, parent);
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

    static std::shared_ptr<AstNode> make_node(const AstNodeType &type, std::shared_ptr<AstNode> parent, std::string arg) {
        switch (type) {
//            case AstNodeType::ASSIGN:
//                return std::make_shared<AssignNode>(AstNodeType::ASSIGN, parent);
//            case AstNodeType::LOGICAL_AND:
//                return std::make_shared<LogicalAndNode>(AstNodeType::LOGICAL_AND, parent);
//            case AstNodeType::TOP:
//                return std::make_shared<TopNode>(AstNodeType::TOP, parent);
//            case AstNodeType::ENTITYDECLARATION:
//                return std::make_shared<EntityDeclarationNode>(AstNodeType::ENTITYDECLARATION, parent);
//            case AstNodeType::PORT:
//                return std::make_shared<PortNode>(AstNodeType::PORT, parent);
//            case AstNodeType::ARCHITECTURE:
//                return std::make_shared<ArchitectureNode>(AstNodeType::ARCHITECTURE, parent);
//            case AstNodeType::PROCESS:
//                return std::make_shared<ProcessNode>(AstNodeType::PROCESS, parent);
            case AstNodeType::IDENTIFIER:
                return std::make_shared<IdentifierNode>(AstNodeType::IDENTIFIER, parent, arg);
        }
        throw "Make node with single string argument not supported for this type.";
    }

    static std::shared_ptr<AstNode> copy_node(const AstNode &src) {
        auto thisNode = std::shared_ptr<AstNode>();

        switch (src.type()) {
            case AstNodeType::ASSIGN:
                thisNode = std::make_shared<AssignNode>(AstNodeType::ASSIGN, src.getParent(), src.getLineno(), src.getFilename());
                break;
            case AstNodeType::LOGICAL_AND:
                thisNode = std::make_shared<LogicalAndNode>(AstNodeType::LOGICAL_AND, src.getParent(), src.getLineno(), src.getFilename());
                break;
            case AstNodeType::TOP:
                thisNode = std::make_shared<TopNode>(AstNodeType::TOP, src.getParent(), src.getLineno(), src.getFilename());
                break;
            case AstNodeType::ENTITYDECLARATION:
                thisNode = std::make_shared<EntityDeclarationNode>(AstNodeType::ENTITYDECLARATION, src.getParent(), src.getLineno(), src.getFilename());
                break;
            case AstNodeType::PORT:
                thisNode = std::make_shared<PortNode>(AstNodeType::PORT, src.getParent(), src.getLineno(), src.getFilename());
                break;
            case AstNodeType::ARCHITECTURE:
                thisNode = std::make_shared<ArchitectureNode>(AstNodeType::ARCHITECTURE, src.getParent(), src.getLineno(), src.getFilename());
                break;
            case AstNodeType::PROCESS:
                thisNode =  std::make_shared<ProcessNode>(AstNodeType::PROCESS, src.getParent(), src.getLineno(), src.getFilename());
                break;
            case AstNodeType::IDENTIFIER:
                thisNode = std::make_shared<IdentifierNode>(AstNodeType::IDENTIFIER, src.getParent(), src.getLineno(), src.getFilename());
                break;
            default:
                throw "Invalid node type.";
        }


        for(auto& child : src.getChildren()){
            thisNode->addChild(copy_node(*child));
        }

        return thisNode;
    }

};

#endif //PURPLEMESA_NODEFACTORY_H
