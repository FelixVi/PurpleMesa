#ifndef PURPLEMESA_ASTNODEBASE_H
#define PURPLEMESA_ASTNODEBASE_H

#include <memory>
#include <ostream>
#include <vector>
#include <iostream>
#include <map>
#include "AstVisitor.h"

enum class AstNodeType;

template <typename TNode>
class AstNodeBase
{
public:
    virtual ~AstNodeBase() = default;

    AstNodeBase<TNode>(std::shared_ptr<TNode> parent)
    :parent(parent)
    {}

    virtual std::string getString() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<TNode> &node) {
        return os << node->getString();
    }

    virtual void accept(const AstVisitor &visitor) = 0;

    virtual AstNodeType type() const = 0;

    void addChild(std::shared_ptr<TNode> child) {
        children.push_back(child);
    }

    const std::vector<std::shared_ptr<TNode>> &getChildren() const {
        return children;
    }

    const bool hasChildren() const {
        return !children.empty();
    }

    const std::shared_ptr<TNode> &getParent() const {
        return parent;
    }

private:
    //the parent node
    std::shared_ptr<TNode> parent;

    //list of child nodes
    std::vector<std::shared_ptr<TNode>> children;
};

#endif //PURPLEMESA_ASTNODEBASE_H
