#ifndef PURPLEMESA_ASTNODE_H
#define PURPLEMESA_ASTNODE_H

#include <memory>
#include <ostream>
#include <vector>
#include <iostream>
#include <map>
#include "AstVisitor.h"

enum class AstNodeType
{
    ARCHITECTURE,
    ASSIGN,
    ENTITY,
    IDENTIFIER,
    LOGICAL_AND,
    PORT,
    PROCESS,
    TOP
};

struct AstNode
{
public:
    virtual ~AstNode() = default;

    AstNode(std::shared_ptr<AstNode> parent) {
        this->parent = parent;
    }

    virtual std::string getString() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<AstNode> &node) {
        return os << node->getString();
    }

    virtual void accept(const AstVisitor &visitor) = 0;

    void dumpAst(std::string indent) {
        std::cout << indent << this->getString() << std::endl;

        for(auto const& child : children){
            child->dumpAst(indent + "  ");
        }
    }

    virtual AstNodeType type() const = 0;

    void addChild(std::shared_ptr<AstNode> child) {
        children.push_back(std::move(child));
    }

    const std::vector<std::shared_ptr<AstNode>> &getChildren() const {
        return children;
    }

    const bool hasChildren() const {
        return !children.empty();
    }

    const std::shared_ptr<AstNode> &getParent() const {
        return parent;
    }

private:
    //the parent node
    std::shared_ptr<AstNode> parent;

    //list of child nodes
    std::vector<std::shared_ptr<AstNode>> children;
};

struct AstNodeFactory
{
    virtual std::shared_ptr<AstNode> make(std::shared_ptr<AstNode> parent) const = 0;
};

#endif //PURPLEMESA_ASTNODE_H
