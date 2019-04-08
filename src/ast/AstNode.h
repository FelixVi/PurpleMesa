#ifndef PURPLEMESA_ASTNODE_H
#define PURPLEMESA_ASTNODE_H

#include <memory>
#include <ostream>
#include <vector>
#include <iostream>
#include <map>
#include "AstNodeBase.h"
#include "AstVisitor.h"

extern int yylineno;
extern std::string filename;

enum class AstNodeType
{
    NONE,
    ARCHITECTURE,
    ASSIGN,
    ENTITY,
    IDENTIFIER,
    LOGICAL_AND,
    PORT,
    PROCESS,
    TOP
};

class AstNode : public AstNodeBase<AstNode>
{
public:
    virtual ~AstNode() = default;

    AstNode(std::shared_ptr<AstNode> parent)
            : AstNodeBase<AstNode>(parent), lineno(yylineno), filename(::filename)
    {}

    std::string getString() const override {return "";}

    virtual void accept(const AstVisitor &visitor) override{}

    virtual AstNodeType type() const override {return AstNodeType::NONE;}

    int getLineno() const {
        return lineno;
    }

    const std::string &getFilename() const {
        return filename;
    }

private:
    int lineno;
    std::string filename;
};

struct AstNodeFactory
{
    virtual std::shared_ptr<AstNode> make(std::shared_ptr<AstNode> parent) const = 0;
};

#endif //PURPLEMESA_ASTNODE_H
