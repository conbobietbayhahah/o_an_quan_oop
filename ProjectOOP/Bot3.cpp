#include "Bot3.h"

#include <iostream>
#include <vector>

using namespace std;

extern const bool IN_NUOC_DI;

Bot3::Bot3(string n) : BotBase(n) {}

int Bot3::makeMove(OAnQuan &game) {

    Board &board = game.layBanCo();

    vector<int> validMoves = layNuocDiHopLe(board);

    if (validMoves.empty()) {
        return -1;
    }

    int bestIdx = -1;
    int bestScore = -1000000;

    int mySide = side;
    int oppSide = 1 - side;

    int myDiemHienTai = game.tinhDiem(mySide);

    for (int move : validMoves) {

        OAnQuan temp = game;

        bool ok = temp.diChuyen(move, true);

        if (!ok) {
            continue;
        }

        int myGain = temp.tinhDiem(mySide) - myDiemHienTai;

        int oppBestGain = 0;

        if (!temp.ketThucTroChoi() &&
            temp.nguoiChoiluot() == oppSide) {

            Board &oppBoard = temp.layBanCo();

            int oppStart = (oppSide == 0) ? 1 : 6;

            int oppDiemHienTai =
                temp.tinhDiem(oppSide);

            for (int j = oppStart; j <= oppStart + 4; j++) {

                if (oppBoard.isEmpty(j)) {
                    continue;
                }

                OAnQuan temp2 = temp;

                bool ok2 = temp2.diChuyen(j, true);

                if (!ok2) {
                    continue;
                }

                int oppGain =
                    temp2.tinhDiem(oppSide) -
                    oppDiemHienTai;

                if (oppGain > oppBestGain) {
                    oppBestGain = oppGain;
                }
            }
        }

        int total = myGain - oppBestGain;

        if (total > bestScore) {
            bestScore = total;
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
