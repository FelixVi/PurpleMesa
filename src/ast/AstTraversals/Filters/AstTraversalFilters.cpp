#include <AstNode.h>

#include "AstTraversalFilters.h"


bool ShowPorts::passes(const AstNode &node) {
    if(node.type() == AstNodeType::PORT)
        return true;
    return false;
}

bool TraversalFilter::passes(const AstNode &node) {
    return true;
}
