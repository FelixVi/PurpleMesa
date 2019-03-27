#ifndef PURPLEMESA_PROCESSNODE_H
#define PURPLEMESA_PROCESSNODE_H

#include "AstNode.h"

struct ProcessNode : AstNode
{
    std::string getString() const override
    {
        std::string myID = "PROCESS(";

        for(auto const& ID : sensitivitylist){
            myID += " " + ID;
        }

        myID += " )";

        return myID;
    }

    std::vector<std::string> sensitivitylist;
};

struct ProcessFactory : AstNodeFactory
{
    std::shared_ptr<AstNode> make() const override
    {
        return std::make_shared<ProcessNode>();
    }
};

#endif //PURPLEMESA_PROCESSNODE_H
