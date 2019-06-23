#include "RTILVisitor.h"

#include <iostream>

#include "AssignNode.h"
#include "ArchitectureNode.h"
#include "BinaryOperatorNode.h"
#include "EntityDeclarationNode.h"
#include "GenericNode.h"
#include "PortNode.h"
#include "ProcessNode.h"
#include "SensitivityListNode.h"
#include "SignalNode.h"
#include "TopNode.h"

void RTILVisitor::visit(ArchitectureNode &node, const AstVisitType &type) {

}

void RTILVisitor::visit(AssignNode &node, const AstVisitType &type) {

}

void RTILVisitor::visit(BinaryOperatorNode &node, const AstVisitType &type) {
    if(type==AstVisitType::TRANSLATE_PRE) {
        std::cout << "\n";
        std::cout << indent;
        std::cout << "attribute \\src \"" << node.getFilename() << ":" << node.getLineno() << "\"" << "\n";
        std::cout << indent;
        std::cout << "cell ";
        std::cout << "$";
        std::cout << node.getProperty("operator") << "\n";
        increaseLevel();
    }
    if(type==AstVisitType::TRANSLATE_POST) {
        decreaseLevel();
        std::cout << indent;
        std::cout << "end\n";
    }
}

void RTILVisitor::visit(EntityDeclarationNode &node, const AstVisitType &type) {
    if(type==AstVisitType::TRANSLATE_PRE) {
        std::cout << indent;
        std::cout << "module \\" << node.getProperty("identifier") << "\n";
        increaseLevel();
    }
    if(type==AstVisitType::TRANSLATE_POST) {
        decreaseLevel();
        std::cout << indent;
        std::cout << "end\n";
    }
}

void RTILVisitor::visit(GenericNode &node, const AstVisitType &type) {

}

void RTILVisitor::visit(PortNode &node, const AstVisitType &type) {
    if(type==AstVisitType::TRANSLATE_PRE)
    {
        std::cout << "\n";

        std::cout << indent;
        std::cout << "attribute \\src \"" << node.getFilename() << ":" << node.getLineno() << "\"" << "\n";
        std::cout << indent;
        std::cout << "wire ";

        if (node.getProperty("subtype") == "std_logic_vector")
            std::cout << "width " << node.getProperty("subtype_width")<< " ";
        if (node.getProperty("direction") == "in")
            std::cout << "input ";
        else if (node.getProperty("direction") == "out")
            std::cout << "output ";
        else
            throw std::invalid_argument("Invalid direction.");
        std::cout << "\\" + node.getProperty("identifier") + "\n";
    }
}

void RTILVisitor::visit(ProcessNode &node, const AstVisitType &type) {

}

void RTILVisitor::visit(SensitivityListNode &node, const AstVisitType &type) {

}

void RTILVisitor::visit(SignalNode &node, const AstVisitType &type) {

}

void RTILVisitor::visit(TopNode &node, const AstVisitType &type) {

}