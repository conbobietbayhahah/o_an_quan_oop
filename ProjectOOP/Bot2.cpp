#include "Bot2.h"

#include <iostream>
#include <vector>

using namespace std;

extern const bool IN_NUOC_DI;

Bot2::Bot2(string n) : BotBase(n) {}

int Bot2::makeMove(OAnQuan &game) {

    Board &board = game.layBanCo();

    vector<int> validMoves = layNuocDiHopLe(board);

    if (validMoves.empty()) {
        return -1;
    }

    int bestIdx = -1;
    int bestScore = -1000000;

    int diemHienTai = game.tinhDiem(side);

    for (int move : validMoves) {

        OAnQuan temp = game;

        bool ok = temp.diChuyen(move, true);

        if (!ok) {
            continue;
        }

        int score = temp.tinhDiem(side) - diemHienTai;

        if (score > bestScore) {
            bestScore = score;
            bestIdx = move;
        }
    }

    if (bestIdx == -1) {
        bestIdx = chonNgauNhien(board);
    }

    if (IN_NUOC_DI && bestIdx != -1) {
        cout << name << " chon o " << bestIdx << endl;
    }

    return bestIdx;
}
