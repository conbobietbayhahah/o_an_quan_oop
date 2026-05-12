#ifndef BOT3_H
#define BOT3_H

#include "BotBase.h"

class Bot3 : public BotBase {
public:
    Bot3(std::string n);

    int makeMove(OAnQuan &game) override;
};

#endif
