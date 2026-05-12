#ifndef BOT2_H
#define BOT2_H

#include "BotBase.h"

class Bot2 : public BotBase {
public:
    Bot2(std::string n);

    int makeMove(OAnQuan &game) override;
};

#endif
