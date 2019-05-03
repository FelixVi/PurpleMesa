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
};

#endif //PURPLEMESA_SENSITIVITYLISTNODE_H
