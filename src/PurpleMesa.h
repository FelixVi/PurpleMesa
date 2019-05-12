#ifndef PURPLEMESA_PURPLEMESA_H
#define PURPLEMESA_PURPLEMESA_H

#include <string>
#include <memory>

class TopNode;

class PurpleMesa {
public:
    std::shared_ptr<TopNode> parseFile(const std::string &filename);

    void printAST(TopNode &node);
};


#endif //PURPLEMESA_PURPLEMESA_H
