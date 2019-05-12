#include "AstNode.h"

std::ostream &operator<<(std::ostream &os, const std::shared_ptr<AstNode> &node) {
        return os << node->getString();
}

void AstNode::addChild(std::shared_ptr<AstNode> child) {
    children.push_back(child);
}

void AstNode::deleteChild(std::shared_ptr<AstNode> object) {
    auto it = std::find(children.begin(), children.end(), object);
    if (it != children.end()) { children.erase(it); }
    else { throw std::invalid_argument("Child could not be deleted."); }
}

const std::shared_ptr<AstNode> &AstNode::getParent() const {
    return parent;
}

const std::string &AstNode::getProperty(const std::string name) {
    auto it = properties.find(name);
    if(it != properties.end())
        return it->second;
    else
        throw std::invalid_argument("Property " + name + " not set in " + this->getString() + ".");
}

const std::string AstNode::getFilename() const {
    std::string name = "";
    size_t i = sourcepath.rfind('/', sourcepath.length());
    if (i != std::string::npos) {
        name = sourcepath.substr(i+1, sourcepath.length() - i);
    }
    return name;
}

AstNodeType AstNode::type() const{
    return Nodetype;
}
