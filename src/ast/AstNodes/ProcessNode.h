#ifndef PURPLEMESA_PROCESSNODE_H
#define PURPLEMESA_PROCESSNODE_H

#include "AstNode.h"

struct ProcessNode : AstNode
{
    ProcessNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}
    ProcessNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &filename) : AstNode(nt, parent, lineno, filename) {}

    std::string getString() const override
    {
        std::string myID = "PROCESS(";

        for(auto const& ID : sensitivitylist){
            myID += " " + ID;
        }

        myID += " )";

        return myID;
    }

    void accept(const AstVisitor &visitor) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this);
    }

    std::vector<std::string> sensitivitylist;
};

#endif //PURPLEMESA_PROCESSNODE_H
