#ifndef PURPLEMESA_GENERICNODE_H
#define PURPLEMESA_GENERICNODE_H

#include "AstNode.h"
#include "Traversals/Filters/AstTraversalFilters.h"
#include "Visitors/AstVisitor.h"

struct GenericNode : AstNode
{
    GenericNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}
    GenericNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &filename) : AstNode(nt, parent, lineno, filename) {}

    std::string getString() const override
    {
        return "GENERIC";
    }

    void accept(AstVisitor &visitor, const AstVisitType &type) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this, type);
    }

    void setProperty(const std::string name, const std::string property) override {
        if (   name == "identifier"
            || name == "type_identifier"
            || name == "default_value")
        {
            properties.insert(std::pair<std::string, std::string>(name, property));
        }
        else
            throw std::invalid_argument("Property does not exist in " + this->getString() + ".");
    }
};

#endif //PURPLEMESA_GENERICNODE_H
