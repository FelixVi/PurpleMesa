#ifndef PURPLEMESA_ASTPRINTVISITOR_H
#define PURPLEMESA_ASTPRINTVISITOR_H

#include <AstVisitor.h>

class AstPrintVisitor : public AstVisitor
{
public:
    void visit(AssignNode &node) override {

    }

    void visit(TopNode &node) override {

    }
};

#endif //PURPLEMESA_ASTPRINTVISITOR_H
