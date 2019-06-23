#ifndef PURPLEMESA_ASTNODE_H
#define PURPLEMESA_ASTNODE_H

#include <memory>
#include <ostream>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

class AstVisitor;
#include "Visitors/AstVisitType.h"

extern int yylineno;
extern std::string filename;

enum class AstNodeType
{
    ARCHITECTURE,
    ASSIGN,
    BINARY_OPERATOR,
    ENTITYDECLARATION,
    GENERIC,
    IDENTIFIER,
    INTEGER,
    PORT,
    PROCESS,
    RANGE,
    SENSITIVITYLIST,
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

    friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<AstNode> &node);

    virtual void accept(AstVisitor &visitor, const AstVisitType &type) = 0;

    AstNodeType type() const;

    void addChild(std::shared_ptr<AstNode> child);

    const std::vector<std::shared_ptr<AstNode>> &getChildren() const { return children; }

    void deleteChild(std::shared_ptr<AstNode> object);

    const bool hasChildren() const { return !children.empty(); }

    const std::shared_ptr<AstNode> &getParent() const;

    //get and set node properties
    const std::string &getProperty(const std::string name);

    virtual void setProperty(const std::string name, const std::string property) = 0;

    int getLineno() const { return lineno; }

    const std::string getFilename() const;

    const std::map<std::string, std::string> &getProperties() const { return properties; }

    void setProperties(const std::map<std::string, std::string> &properties) { AstNode::properties = properties; }

    const std::string &getSourcepath() const { return sourcepath; }

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
