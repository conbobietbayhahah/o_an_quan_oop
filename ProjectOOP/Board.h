# Board.h

```cpp
#ifndef BOARD_H
#define BOARD_H

class Board {
private:
    int oCo[12];

public:
    Board();

    void reset();

    int laySoQuan(int pos) const;
    void datSoQuan(int pos, int value);
    void tangSoQuan(int pos);

    bool laOQuan(int pos) const;
    bool laOTrong(int pos) const;

    bool isQuan(int pos) const;
    bool isEmpty(int pos) const;

    int sow(int pos);
    int capture(int lastIdx);
};

#endif
```

---

# Board.cpp

```cpp
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
    return (pos == 0 || pos == 11);
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

int Board::sow(int pos) {
    int seeds = laySoQuan(pos);
    datSoQuan(pos, 0);

    for (int i = 0; i < seeds; i++) {
        pos = (pos + 1) % 12;
        tangSoQuan(pos);
    }

    return pos;
}

int Board::capture(int lastIdx) {
    int score = 0;

    int emptyPos = (lastIdx + 1) % 12;
    int capturePos = (emptyPos + 1) % 12;

    if (laOTrong(emptyPos) && !laOTrong(capturePos)) {
        score = laySoQuan(capturePos);
        datSoQuan(capturePos, 0);
    }

    return score;
}
```

---

# Game.h

```cpp
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Board.h"

class OAnQuan {
private:
    Board banCo;
    std::vector<int> captured;

    int currentPlayer;
    int quanValue;
    int soLuotDaChoi;

    bool isFirstTurn;

    static const int MAX_LUOT = 200;

public:
    OAnQuan();

    bool diChuyen(int oBatDau, bool thuanChieu);

    void raiQuan(int pos, bool thuanChieu);
    void anQuan(int pos, bool thuanChieu);
    void vayDanKhiHetQuan();

    int tinhDiem(int player) const;

    bool hetQuan() const;
    bool daHetGioiHanL
```
