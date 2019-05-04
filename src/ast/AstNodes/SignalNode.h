#ifndef PURPLEMESA_SIGNALNODE_H
#define PURPLEMESA_SIGNALNODE_H

#include "AstNode.h"

struct SignalNode : AstNode
{
    SignalNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}
    SignalNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &filename) : AstNode(nt, parent, lineno, filename) {}

    std::string getString() const override
    {
        return "SIGNAL";
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this);
    }

    void setProperty(const std::string name, const std::string property) override {
        if (name == "identifier")
            properties.insert(std::pair<std::string, std::string>(name, property));
        else
            throw std::invalid_argument("Property does not exist in " + this->getString() + ".");
    }
};

#endif //PURPLEMESA_SIGNALNODE_H
