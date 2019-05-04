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
    ENTITYDECLARATION,
    LOGICAL_AND,
    PORT,
    PROCESS,
    SENSITIVITYLIST,
    SIGNAL,
    TOP
};

class AstNode
{
public:
    virtual ~AstNode() = default;

    //creation of nodes
    AstNode(AstNodeType NodeType, const std::shared_ptr<AstNode> &parent)
        : Nodetype(NodeType), parent(parent), lineno(yylineno), sourcepath(::filename) {}

    //creation of nodes
    AstNode(AstNodeType NodeType, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &sourcepath)
            : Nodetype(NodeType), parent(parent), lineno(lineno), sourcepath(sourcepath) {}

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

    //get and set node properties
    const std::string &getProperty(const std::string name) {
        auto it = properties.find(name);
        if(it != properties.end())
            return it->second;
        else
            throw std::invalid_argument("Property " + name + " not set in " + this->getString() + ".");
    }

    virtual void setProperty(const std::string name, const std::string property) = 0;

    int getLineno() const {
        return lineno;
    }

    const std::string getFilename() const {
        std::string name = "";
        size_t i = sourcepath.rfind('/', sourcepath.length());
        if (i != std::string::npos) {
            name = sourcepath.substr(i+1, sourcepath.length() - i);
        }
        return name;
    }

    const std::map<std::string, std::string> &getProperties() const {
        return properties;
    }

    void setProperties(const std::map<std::string, std::string> &properties) {
        AstNode::properties = properties;
    }

    const std::string &getSourcepath() const {
        return sourcepath;
    }

protected:
    std::map<std::string, std::string> properties;
private:
    AstNodeType Nodetype;
    std::shared_ptr<AstNode> parent;
    std::vector<std::shared_ptr<AstNode>> children;

    int lineno;
    std::string sourcepath;
};

#endif //PURPLEMESA_ASTNODE_H
