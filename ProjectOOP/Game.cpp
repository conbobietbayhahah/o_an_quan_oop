#include "Game.h"

OAnQuan::OAnQuan() : banCo(), quanValue(10), soLuotDaChoi(0), isFirstTurn(true) {
    captured = {0, 0};
    currentPlayer = 0;  
}

bool OAnQuan::diChuyen(int oBatDau, bool thuancChieu) {
    if (daHetGioiHanLuot()) return false;
    
    int startPit = (currentPlayer == 0) ? 1 : 6;
    if (oBatDau < startPit || oBatDau > startPit + 4 || banCo.laOTrong(oBatDau)) {
        return false;
    }
    
    soLuotDaChoi++; 
    raiQuan(oBatDau, thuancChieu);
    
    if (isFirstTurn) isFirstTurn = false;
    vayDanKhiHetQuan(); 
    
    return true;
}

void OAnQuan::raiQuan(int pos, bool thuancChieu) {
    int seeds = banCo.laySoQuan(pos);
    banCo.datSoQuan(pos, 0);
    
    int dir = thuancChieu ? 1 : 11; 
    
    for (int i = 0; i < seeds; i++) {
        pos = (pos + dir + 12) % 12;
        banCo.tangSoQuan(pos);
    }
    
    int tiepTheo = (pos + dir + 12) % 12; 
    if (banCo.laOQuan(tiepTheo)) {
        currentPlayer = 1 - currentPlayer;
        return;
    }

    if (!banCo.laOTrong(tiepTheo)) {
        raiQuan(tiepTheo, thuancChieu); 
    } 
    else {
        anQuan(tiepTheo, thuancChieu); 
    }
}

void OAnQuan::anQuan(int pos, bool thuancChieu) {
    int dir = thuancChieu ? 1 : 11;
    int nextPos = (pos + dir + 12) % 12; 
    
    if (!banCo.laOTrong(nextPos)) {
        if (isFirstTurn && banCo.laOQuan(nextPos)) {
            currentPlayer = 1 - currentPlayer;
            return;
        }
        captured[currentPlayer] += banCo.laySoQuan(nextPos);
        banCo.datSoQuan(nextPos, 0);

        int sauOTrong = (nextPos + dir + 12) % 12; 
        if (banCo.laOTrong(sauOTrong)) {
            anQuan(sauOTrong, thuancChieu); // Ăn chuỗi
        } else {
            currentPlayer = 1 - currentPlayer;
        }
    } else {
        currentPlayer = 1 - currentPlayer;
    }
}

void OAnQuan::vayDanKhiHetQuan() {
    int start = (currentPlayer == 0) ? 1 : 6;
    bool hetDanSanNha = true;
    
    for (int i = 0; i < 5; i++) {
        if (!banCo.laOTrong(start + i)) {
            hetDanSanNha = false;
            break;
        }
    }
    
    if (hetDanSanNha) {
        if (captured[currentPlayer] < 5) {
            int doiThu = 1 - currentPlayer;
            captured[doiThu] -= (5 - captured[currentPlayer]);
            captured[currentPlayer] = 0;
        } else {
            captured[currentPlayer] -= 5;
        }

        for (int i = 0; i < 5; i++) {
            banCo.datSoQuan(start + i, 1);
        }
    }
}

int OAnQuan::tinhDiem(int player) const {
    int diem = captured[player];
    int start = (player == 0) ? 1 : 6;
    for (int i = 0; i < 5; i++) {
        diem += banCo.laySoQuan(start + i);
    }
    return diem;
}

bool OAnQuan::hetQuan() const {
    return banCo.laOTrong(0) && banCo.laOTrong(11);
}

bool OAnQuan::daHetGioiHanLuot() const {
    return soLuotDaChoi >= MAX_LUOT;
}

bool OAnQuan::ketThucTroChoi() const {
    return hetQuan() || daHetGioiHanLuot();
}

int OAnQuan::nguoiThang() const {
    if (!ketThucTroChoi()) return -2;
    int diem1 = tinhDiem(0);
    int diem2 = tinhDiem(1);
    if (diem1 > diem2) return 0;
    if (diem2 > diem1) return 1;
    return -1; 
}

