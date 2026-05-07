#pragma once
#include "Botbase.h"
#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Bot1 : public Player {
public:
    Bot1(string n);
    int makeMove(Board &board) override;
};
