#ifndef PURPLEMESA_ASTTRAVERSALFILTER_H
#define PURPLEMESA_ASTTRAVERSALFILTER_H

#include <AstNode.h>

class AstNode;

enum class AstTraversalFilter
{
    ShowAll,
    ShowPorts
};

struct TraversalFilter
{
    virtual ~TraversalFilter() = default;
    virtual bool passes(const AstNode& node);
};

struct ShowAll : TraversalFilter
{
};

struct ShowPorts : TraversalFilter
{
    bool passes(const AstNode &node) override;
};

#endif //PURPLEMESA_ASTTRAVERSALFILTERS_H
