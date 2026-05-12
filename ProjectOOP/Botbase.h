#ifndef BOTBASE_H
#define BOTBASE_H

#include <vector>
#include <string>

#include "Game.h"

class BotBase {
public:
    std::string name;

    int score;

    int side;

    BotBase(std::string n);

    virtual int makeMove(OAnQuan &game) = 0;

    virtual ~BotBase() {}

protected:
    std::vector<int> layNuocDiHopLe(
        const Board &board
    ) const;

    int chonNgauNhien(
        const Board &board
    ) const;
};

#endif
