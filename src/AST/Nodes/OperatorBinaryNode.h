#ifndef PURPLEMESA_OPERATORBINARYNODE_H
#define PURPLEMESA_OPERATORBINARYNODE_H

#include "AstNode.h"
#include "Traversals/Filters/AstTraversalFilters.h"
#include "Visitors/AstVisitor.h"

struct OperatorBinaryNode : AstNode
{
    OperatorBinaryNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}
    OperatorBinaryNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &filename) : AstNode(nt, parent, lineno, filename) {}

    std::string getString() const override
    {
        return "OPERATOR_BINARY";
    }

    void accept(AstVisitor &visitor, const AstVisitType &type) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this, type);
    }

    void setProperty(const std::string name, const std::string property) override {
        if (name == "operator")
            properties.insert(std::pair<std::string, std::string>(name, property));
        else
            throw std::invalid_argument("Property " + name + " does not exist in " + this->getString() + ".");
    }
};

#endif //PURPLEMESA_OPERATORBINARYNODE_H
