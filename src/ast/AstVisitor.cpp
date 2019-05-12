#include <AstTraversals/Filters/AstTraversalFilters.h>
#include "AstVisitor.h"

void AstVisitor::setFilter(const AstTraversalFilter filter) {
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

AstVisitor::AstVisitor() {
    traversalFilter = std::make_unique<ShowAll>();
}
