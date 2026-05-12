#include "Bot1.h"

#include <iostream>

using namespace std;

extern const bool IN_NUOC_DI;

Bot1::Bot1(string n) : BotBase(n) {}

int Bot1::makeMove(OAnQuan &game) {

    int idx = chonNgauNhien(game.layBanCo());

    if (IN_NUOC_DI && idx != -1) {
        cout << name << " chon o " << idx << endl;
    }

    return idx;
}
