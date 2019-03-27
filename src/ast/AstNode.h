#ifndef PURPLEMESA_ASTNODE_H
#define PURPLEMESA_ASTNODE_H

#include <memory>
#include <ostream>
#include <vector>
#include <iostream>
#include <map>

enum class AstNodeType
{
    TOP,
    ENTITY,
    PORT,
    ARCHITECTURE,
    PROCESS,
    IDENTIFIER,
    ASSIGN,
    LOGICAL_AND
};

struct AstNode
{
    virtual ~AstNode() = default;

    virtual std::string getString() const = 0;

    void dumpAst(std::string indent) {
        std::cout << indent << this->getString() << std::endl;

        for(auto const& child : children){
            child->dumpAst(indent + "  ");
        }
    }

    //list of child nodes
    std::vector<std::shared_ptr<AstNode>> children;

    void addChild(std::shared_ptr<AstNode> child) {
        children.push_back(std::move(child));
    }

    friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<AstNode> &node) {
        return os << node->getString();
    }
};

struct AstNodeFactory
{
    virtual std::shared_ptr<AstNode> make() const = 0;
};

#endif //PURPLEMESA_ASTNODE_H
