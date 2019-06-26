#ifndef PURPLEMESA_CASENODE_H
#define PURPLEMESA_CASENODE_H


#include <AstNode.h>
#include "Traversals/Filters/AstTraversalFilters.h"
#include "Visitors/AstVisitor.h"

struct CaseNode : AstNode
{
    CaseNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {
    }
    CaseNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &filename) : AstNode(nt, parent, lineno, filename) {
    }

    std::string getString() const override
    {
        return "CASE";
    }

    void accept(AstVisitor &visitor, const AstVisitType &type) override {
        if(visitor.getTraversalFilter()->passes(*this))
            visitor.visit(*this, type);
    }

    void setProperty(const std::string name, const std::string property) override {
        throw std::invalid_argument("Property does not exist in " + this->getString() + ".");
    }
};

#endif //PURPLEMESA_CASENODE_H
