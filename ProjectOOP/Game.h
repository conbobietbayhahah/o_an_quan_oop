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
    
    bool diChuyen(int oBatDau, bool thuancChieu);
    void raiQuan(int pos, bool thuancChieu);
    void anQuan(int pos, bool thuancChieu);
    void vayDanKhiHetQuan();
    
    int tinhDiem(int player) const;
    bool hetQuan() const;
    bool daHetGioiHanLuot() const;
    bool ketThucTroChoi() const;      
    int nguoiThang() const;
    
    int laySoLuotDaChoi() const { return soLuotDaChoi; }
    int nguoiChoiluot() const { return currentPlayer; }
    std::vector<int> danDaAn() const { return captured; }
    
    Board& layBanCo() { return banCo; }
    const Board& layBanCo() const { return banCo; }
};

#endif