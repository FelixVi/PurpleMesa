#ifndef PURPLEMESA_TOPNODE_H
#define PURPLEMESA_TOPNODE_H

#include "AstNode.h"
#include "AstTraversals/Filters/AstTraversalFilters.h"
#include "AstVisitor.h"

struct TopNode : AstNode
{
    TopNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}
    TopNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &filename) : AstNode(nt, parent, lineno, filename) {}

    std::string getString() const override
    {
        return "TOP";
    }

    void accept(AstVisitor &visitor, const AstVisitType &type) override {
        if(visitor.getTraversalFilter()->passes(*this))
            visitor.visit(*this, type);
    }

    void setProperty(const std::string name, const std::string property) override {
        throw std::invalid_argument("Property does not exist in " + this->getString() + ".");
    }
};

#endif //PURPLEMESA_TOPNODE_H
