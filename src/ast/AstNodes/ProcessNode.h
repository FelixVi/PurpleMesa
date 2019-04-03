#ifndef PURPLEMESA_PROCESSNODE_H
#define PURPLEMESA_PROCESSNODE_H

#include "AstNode.h"

struct ProcessNode : AstNode
{
    ProcessNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {}
    std::string getString() const override
    {
        std::string myID = "PROCESS(";

        for(auto const& ID : sensitivitylist){
            myID += " " + ID;
        }

        myID += " )";

        return myID;
    }

    void accept(AstVisitor &visitor) override {
        visitor.visit(*this);
    }

    std::vector<std::string> sensitivitylist;
};

struct ProcessFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make(std::shared_ptr<AstNode> parent) const override
    {
        return std::make_shared<ProcessNode>(parent);
    }
};

#endif //PURPLEMESA_PROCESSNODE_H
