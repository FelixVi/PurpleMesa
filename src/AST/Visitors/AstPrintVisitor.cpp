#include "AstPrintVisitor.h"

#include <iostream>

#include "ArchitectureNode.h"
#include "AssignNode.h"
#include "CaseNode.h"
#include "EntityDeclarationNode.h"
#include "GenericNode.h"
#include "IdentifierNode.h"
#include "IntegerNode.h"
#include "LiteralCharacterNode.h"
#include "OperatorBinaryNode.h"
#include "OperatorUnaryNode.h"
#include "PortNode.h"
#include "ProcessNode.h"
#include "RangeNode.h"
#include "ReduceBoolNode.h"
#include "SensitivityListNode.h"
#include "TopNode.h"

void AstPrintVisitor::visit(ArchitectureNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    std::cout << " " << node.getProperty("identifier");
    std::cout << " of";
    std::cout << " " << node.getProperty("entity_name");
    if (!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(AssignNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(CaseNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(EntityDeclarationNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    std::cout << " " << node.getProperty("identifier");
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(GenericNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    std::cout << " " << node.getProperty("identifier");
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(IdentifierNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    std::cout << " " << node.getProperty("identifier");
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(IntegerNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    std::cout << " " << node.getProperty("value");
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(LiteralCharacterNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    std::cout << " " << node.getProperty("value");
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(OperatorBinaryNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    std::cout << " (" << node.getProperty("operator") << ")";
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(OperatorUnaryNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    std::cout << " (" << node.getProperty("operator") << ")";
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(PortNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    std::cout << " " << node.getProperty("identifier");
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(ProcessNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(RangeNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(ReduceBoolNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(SensitivityListNode &node, const AstVisitType &type) {
    checkPasses(type);
    std::cout << indent << node.getString();
    if(!hideLocation)
        std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
    std::cout << std::endl;
}

void AstPrintVisitor::visit(TopNode &node, const AstVisitType &type) {
        checkPasses(type);
        std::cout << indent << node.getString();
        if(!hideLocation)
            std::cout << " at " << node.getLineno() << " (" << node.getFilename() << ")";
        std::cout << std::endl;
}

void AstPrintVisitor::increaseLevel() {
    indent += "  ";
}

void AstPrintVisitor::decreaseLevel() {
    if(!indent.empty())
        indent.pop_back();
    if(!indent.empty())
        indent.pop_back();
}

void AstPrintVisitor::checkPasses(const AstVisitType &type) const {
    if(!(type==AstVisitType::SINGLE))
        throw std::invalid_argument("AstPrintVisitor requires single visit.");
}
