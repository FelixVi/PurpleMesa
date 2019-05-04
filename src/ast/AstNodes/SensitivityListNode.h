#ifndef PURPLEMESA_SENSITIVITYLISTNODE_H
#define PURPLEMESA_SENSITIVITYLISTNODE_H

#include "AstNode.h"

struct SensitivityListNode : AstNode
{
    SensitivityListNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}
    SensitivityListNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &filename) : AstNode(nt, parent, lineno, filename) {}

    std::string getString() const override
    {
        std::string myID = "SENSITIVITYLIST";

        return myID;
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this);
    }

    void setProperty(const std::string name, const std::string property) override {
        throw std::invalid_argument("Property does not exist in " + this->getString() + ".");
    }
};

#endif //PURPLEMESA_SENSITIVITYLISTNODE_H
