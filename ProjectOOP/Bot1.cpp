#include "Bot1.h"

Bot1::Bot1(string n) : Player(n){
    srand(time(0));
}

int Bot1::makeMove(Board &board){
    // chọn ngẫu nhiên ô 7->11 (chỉ số 6->10)
    int idx;
    do{
        idx = 6 + rand() % 5; // 6,7,8,9,10
    } while(board.isEmpty(idx));

    cout << name << " chon o " << idx - 5 << endl;
    return idx;
}
