#ifndef PURPLEMESA_ASTTRAVERSAL_H
#define PURPLEMESA_ASTTRAVERSAL_H

#include "AstTraversals/Filters/AstTraversalFilters.h"

struct AstTraversal
{
    virtual void traverse(AstNode &node, AstVisitor &visitor) = 0;

    void setFilter(const AstTraversalFilter filter)
    {
        switch(filter){
            case AstTraversalFilter::ShowAll:
                traversalFilter = std::make_unique<ShowAll>();
                break;
            case AstTraversalFilter::ShowPorts:
                traversalFilter = std::make_unique<ShowPorts>();
                break;
            default:
                throw std::runtime_error("Unsupported AST traversal filter.");
        }
    }
private:
    std::unique_ptr<TraversalFilter> traversalFilter;
};

#endif //PURPLEMESA_ASTTRAVERSAL_H
