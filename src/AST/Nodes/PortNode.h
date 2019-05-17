#ifndef PURPLEMESA_PORTNODE_H
#define PURPLEMESA_PORTNODE_H

#include "AstNode.h"
#include "Traversals/Filters/AstTraversalFilters.h"
#include "Visitors/AstVisitor.h"

struct PortNode : AstNode
{
    PortNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}
    PortNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &filename) : AstNode(nt, parent, lineno, filename) {}

    std::string getString() const override
    {
        return "PORT";
    }

    void accept(AstVisitor &visitor, const AstVisitType &type) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this, type);
    }

    void setProperty(const std::string name, const std::string property) override {
        if (name == "identifier")
            properties.insert(std::pair<std::string, std::string>(name, property));
        else if (name == "direction")
            properties.insert(std::pair<std::string, std::string>(name, property));
        else if (name == "subtype")
            properties.insert(std::pair<std::string, std::string>(name, property));
        else if (name == "subtype_width")
            properties.insert(std::pair<std::string, std::string>(name, property));
        else
            throw std::invalid_argument("Property does not exist in " + this->getString() + ".");
    }
};

#endif //PURPLEMESA_PORTNODE_H
