#ifndef PURPLEMESA_ASTNODE_H
#define PURPLEMESA_ASTNODE_H

#include <memory>
#include <ostream>
#include <vector>
#include <iostream>
#include <map>
#include "AstVisitor.h"

extern int yylineno;
extern std::string filename;

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

class AstNode
{
public:
    virtual ~AstNode() = default;

    //creation of nodes
    AstNode(AstNodeType NodeType, const std::shared_ptr<AstNode> &parent)
        : Nodetype(NodeType), parent(parent), lineno(yylineno), filename(::filename) {}

    virtual std::string getString() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<AstNode> &node) {
        return os << node->getString();
    }

    virtual void accept(const AstVisitor &visitor) = 0;

    constexpr AstNodeType type() const {return Nodetype;}

    void addChild(std::shared_ptr<AstNode> child) {
        children.push_back(child);
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

    int getLineno() const {
        return lineno;
    }

    const std::string &getFilename() const {
        return filename;
    }

private:
    const AstNodeType Nodetype;
    //the parent node
    std::shared_ptr<AstNode> parent;

    //list of child nodes
    std::vector<std::shared_ptr<AstNode>> children;

    int lineno;
    std::string filename;
};

#endif //PURPLEMESA_ASTNODE_H
