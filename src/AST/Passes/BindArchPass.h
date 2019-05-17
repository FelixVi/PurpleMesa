#ifndef PURPLEMESA_BINDARCHPASS_H
#define PURPLEMESA_BINDARCHPASS_H

#include <Passes/AstPass.h>

class BindArchPass : public AstPass
{
public:
    void run() override;
};


#endif //PURPLEMESA_BINDARCHPASS_H
