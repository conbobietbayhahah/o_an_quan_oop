#pragma once
#include "Board.h"
#include <string>
using namespace std;

class BotBase {
public:
    string name;
    int score;
    BotBase(string n) { name = n; score = 0; }
    virtual int makeMove(Board &board) = 0; // phải override
    virtual ~BotBase() {}
};
