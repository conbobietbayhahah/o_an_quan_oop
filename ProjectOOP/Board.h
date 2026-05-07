#pragma once
#pragma once
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
    bool laOQuan(int pos) const { return (pos == 0 || pos == 11); }
    bool laOTrong(int pos) const { return laySoQuan(pos) == 0; }
};

#endif