#ifndef PURPLEMESA_ASTTRAVERSALFILTER_H
#define PURPLEMESA_ASTTRAVERSALFILTER_H

#include "AstNode.h"

struct TraversalFilter
{
    virtual ~TraversalFilter() = default;
    virtual bool passes(const AstNode& node) { return true; }
};

struct ShowAll : TraversalFilter {};

struct ShowPorts : TraversalFilter
{
    bool passes(const AstNode &node) override {
        if (node.type() == AstNodeType::PORT)
            return true;
        return false;
    }
};

#endif //PURPLEMESA_ASTTRAVERSALFILTERS_H
