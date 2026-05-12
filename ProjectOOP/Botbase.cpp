#include "BotBase.h"

#include <cstdlib>

BotBase::BotBase(std::string n) {

    name = n;

    score = 0;

    side = 0;
}

std::vector<int> BotBase::layNuocDiHopLe(
    const Board &board
) const {

    std::vector<int> validMoves;

    int start = (side == 0) ? 1 : 6;

    for (int i = start; i <= start + 4; i++) {

        if (!board.isEmpty(i))
            validMoves.push_back(i);
    }

    return validMoves;
}

int BotBase::chonNgauNhien(
    const Board &board
) const {

    std::vector<int> validMoves =
        layNuocDiHopLe(board);

    if (validMoves.empty())
        return -1;

    return validMoves[rand() % validMoves.size()];
}
