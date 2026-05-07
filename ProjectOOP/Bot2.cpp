#include "Bot2.h"

Bot2::Bot2(string n) : Player(n) {}

int Bot2::makeMove(Board &board){
    int bestIdx=-1;
    int maxScore=-1;

    // chọn ô 7->11 (6->10)
    for(int i=6;i<=10;i++){
        if(board.isEmpty(i)) continue;

        Board temp = board;
        int lastIdx = temp.sow(i);
        int score = temp.capture(lastIdx);

        int nextIdx = (lastIdx + 1) % 12;
        if(temp.isQuan(nextIdx)) score += 10;

        if(score > maxScore){
            maxScore = score;
            bestIdx = i;
        }
    }

    if(bestIdx == -1){ // fallback
        for(int i=6;i<=10;i++){
            if(board.cells[i]>0){ bestIdx=i; break; }
        }
    }

    cout << name << " chon o " << bestIdx - 5 << endl;
    return bestIdx;
}
