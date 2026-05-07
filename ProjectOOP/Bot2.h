#pragma once
#include "Botbase.h"
#include "Board.h"
#include <iostream>
using namespace std;

class Bot2 : public Player {
public:
    Bot2(string n);
    int makeMove(Board &board) override;
};
