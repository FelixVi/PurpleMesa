#ifndef PURPLEMESA_ENTITYDECLARATIONNODE_H
#define PURPLEMESA_ENTITYDECLARATIONNODE_H

#include "AstNode.h"
#include "AstTraversals/Filters/AstTraversalFilters.h"
#include "AstVisitor.h"

struct EntityDeclarationNode : AstNode
{
    EntityDeclarationNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent) : AstNode(nt, parent) {}
    EntityDeclarationNode(AstNodeType nt, const std::shared_ptr<AstNode> &parent, int lineno, const std::string &filename) : AstNode(nt, parent, lineno, filename) {}

    std::string getString() const override
    {
        return "ENTITY DECLARATION";
    }

    void accept(AstVisitor &visitor, const AstVisitType &type) override {
        if(visitor.getTraversalFilter()->passes(*this))visitor.visit(*this, type);
    }

    void setProperty(const std::string name, const std::string property) override {
        if (name == "identifier")
                properties.insert(std::pair<std::string, std::string>(name, property));
        else
            throw std::invalid_argument("Property does not exist in " + this->getString() + ".");
    }
};

#endif //PURPLEMESA_ENTITYDECLARATIONNODE_H
