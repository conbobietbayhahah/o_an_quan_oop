#pragma once
#include "Player.h"
#include "Board.h"
#include <iostream>
using namespace std;

class Bot3 : public Player {
public:
    Bot3(string n);
    int makeMove(Board &board) override;
};
