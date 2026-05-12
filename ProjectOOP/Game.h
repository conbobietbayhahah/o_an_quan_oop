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

    bool daHetGioiHanLuot() const;

    bool ketThucTroChoi() const;

    int nguoiThang() const;

    int laySoLuotDaChoi() const;

    int nguoiChoiluot() const;

    std::vector<int> danDaAn() const;

    Board& layBanCo();

    const Board& layBanCo() const;
};

#endif
