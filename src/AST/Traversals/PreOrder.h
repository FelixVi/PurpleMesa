#ifndef PURPLEMESA_PREORDER_H
#define PURPLEMESA_PREORDER_H

#include "AstTraversal.h"

class PreOrderTraversal : public AstTraversal
{
public:
    void traverse(AstNode &node, AstVisitor &visitor) override {
        //std::cout << "Trying to visit: " << node.getLineno() << std::endl;
        if(visitor.isDoublePass())
        {
            node.accept(visitor, AstVisitType::TRANSLATE_PRE);

            if(node.hasChildren()){
                for(auto const& child : node.getChildren()){
                    traverse(*child, visitor);
                }
            }

            node.accept(visitor, AstVisitType::TRANSLATE_POST);
        }
        else
        {
            node.accept(visitor, AstVisitType::SINGLE);

            if(node.hasChildren()){
                visitor.increaseLevel();
                for(auto const& child : node.getChildren()){
                    traverse(*child, visitor);
                }
                visitor.decreaseLevel();
            }
        }
    }
};

#endif //PURPLEMESA_PREORDER_H
