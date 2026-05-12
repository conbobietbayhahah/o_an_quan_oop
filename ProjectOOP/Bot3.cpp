#include "Bot3.h"
#include <vector>
#include <iostream>
using namespace std;
const bool IN_NUOC_DI = false;
Bot3::Bot3(std::string n) : BotBase(n) {}

int Bot3::makeMove(OAnQuan& game) {

    Board& board = game.layBanCo();
    vector<int> validMoves = layNuocDiHopLe(board);

    if (validMoves.empty()) {
        return -1;
    }

    int mySide = side;
    int oppSide = 1 - side;

    int myCurrentScore = game.tinhDiem(mySide);
    int oppCurrentScore = game.tinhDiem(oppSide);

    int bestAttackMove = -1;
    int bestAttackGain = 0;

    int bestBlockMove = -1;
    int bestBlockScore = -1000000;

    bool foundEatingMove = false;
    bool foundOpponentThreat = false;

    for (int move : validMoves) {

        OAnQuan temp = game;

        bool ok = temp.diChuyen(move, true);

        if (!ok) {
            continue;
        }

        int myGain = temp.tinhDiem(mySide) - myCurrentScore;

        int oppBestGain = 0;

        if (!temp.ketThucTroChoi() &&
            temp.nguoiChoiluot() == oppSide) {

            Board& oppBoard = temp.layBanCo();

            int oppStart = (oppSide == 0) ? 1 : 6;

            for (int oppMove = oppStart; oppMove <= oppStart + 4; oppMove++) {

                if (oppBoard.isEmpty(oppMove)) {
                    continue;
                }

                OAnQuan temp2 = temp;

                bool ok2 = temp2.diChuyen(oppMove, true);

                if (!ok2) {
                    continue;
                }

                int oppGain =
                    temp2.tinhDiem(oppSide) -
                    temp.tinhDiem(oppSide);

                if (oppGain > oppBestGain) {
                    oppBestGain = oppGain;
                }
            }
        }

        if (myGain > 0) {
            foundEatingMove = true;

            if (myGain > bestAttackGain) {
                bestAttackGain = myGain;
                bestAttackMove = move;
            }
        }

        if (oppBestGain > 0) {
            foundOpponentThreat = true;
        }

        int blockScore = myGain - oppBestGain;

        if (blockScore > bestBlockScore) {
            bestBlockScore = blockScore;
            bestBlockMove = move;
        }
    }

    int chosenMove = -1;

    /*
        Logic:
        - Nếu Bot3 ăn được nhiều hơn hoặc bằng đối thủ có thể ăn:
            => ưu tiên ăn quân.
        - Nếu Bot3 ăn ít hơn đối thủ:
            => ưu tiên chặn đối thủ.
        - Nếu cả hai đều không ăn được:
            => random.
    */

    if (foundEatingMove && bestAttackGain >= 1) {

        if (!foundOpponentThreat) {
            chosenMove = bestAttackMove;
        }
        else {
            /*
                Nếu có nguy cơ đối thủ ăn,
                so sánh nước ăn tốt nhất của mình với điểm chặn tốt nhất.
            */

            OAnQuan tempAttack = game;
            tempAttack.diChuyen(bestAttackMove, true);

            int oppGainAfterAttack = 0;

            if (!tempAttack.ketThucTroChoi() &&
                tempAttack.nguoiChoiluot() == oppSide) {

                Board& oppBoard = tempAttack.layBanCo();
                int oppStart = (oppSide == 0) ? 1 : 6;

                for (int oppMove = oppStart; oppMove <= oppStart + 4; oppMove++) {

                    if (oppBoard.isEmpty(oppMove)) {
                        continue;
                    }

                    OAnQuan temp2 = tempAttack;
                    temp2.diChuyen(oppMove, true);

                    int gain =
                        temp2.tinhDiem(oppSide) -
                        tempAttack.tinhDiem(oppSide);

                    if (gain > oppGainAfterAttack) {
                        oppGainAfterAttack = gain;
                    }
                }
            }

            if (bestAttackGain >= oppGainAfterAttack) {
                chosenMove = bestAttackMove;
            }
            else {
                chosenMove = bestBlockMove;
            }
        }
    }
    else {
        if (foundOpponentThreat) {
            chosenMove = bestBlockMove;
        }
        else {
            chosenMove = chonNgauNhien(board);
        }
    }

    if (chosenMove == -1) {
        chosenMove = chonNgauNhien(board);
    }

    //cout << name << " chon o " << chosenMove << endl;

    return chosenMove;
}
