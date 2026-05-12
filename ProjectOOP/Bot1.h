#ifndef BOT1_H
#define BOT1_H

#include "BotBase.h"

class Bot1 : public BotBase {
public:
    Bot1(std::string n);

    int makeMove(OAnQuan &game) override;
};

#endif
