#include "Board.h"

Board::Board() {
    reset();
}

void Board::reset() {
    for (int i = 0; i < 12; i++) {
        if (i == 0 || i == 11)
            oCo[i] = 10;
        else
            oCo[i] = 5;
    }
}

int Board::laySoQuan(int pos) const {
    if (pos >= 0 && pos < 12)
        return oCo[pos];

    return 0;
}

void Board::datSoQuan(int pos, int value) {
    if (pos >= 0 && pos < 12)
        oCo[pos] = value;
}

void Board::tangSoQuan(int pos) {
    if (pos >= 0 && pos < 12)
        oCo[pos]++;
}

bool Board::laOQuan(int pos) const {
    return pos == 0 || pos == 11;
}

bool Board::laOTrong(int pos) const {
    return laySoQuan(pos) == 0;
}

bool Board::isQuan(int pos) const {
    return laOQuan(pos);
}

bool Board::isEmpty(int pos) const {
    return laOTrong(pos);
}

