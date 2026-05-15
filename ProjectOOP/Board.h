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

    
};

#endif
