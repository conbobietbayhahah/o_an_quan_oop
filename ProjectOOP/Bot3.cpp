#include "Bot3.h"

Bot3::Bot3(string n) : Player(n) {}

int Bot3::makeMove(Board &board){
    int bestIdx=-1;
    int bestScore=-1000;

    // heuristic: myScore - oppScore
    for(int i=6;i<=10;i++){
        if(board.isEmpty(i)) continue;

        Board temp = board;
        int lastIdx = temp.sow(i);
        int myScore = temp.capture(lastIdx);

        int nextIdx = (lastIdx + 1) % 12;
        if(temp.isQuan(nextIdx)) myScore += 10;

        // giả lập bot greedy đối phương
        Board opp = temp;
        int oppScore=-1;
        for(int j=6;j<=10;j++){
            if(opp.isEmpty(j)) continue;
            Board t = opp;
            int last = t.sow(j);
            int s = t.capture(last);
            if(t.isQuan((last+1)%12)) s += 10;
            if(s>oppScore) oppScore=s;
        }

        int total = myScore - oppScore;
        if(total > bestScore){
            bestScore = total;
            bestIdx = i;
        }
    }

    if(bestIdx==-1){
        for(int i=6;i<=10;i++){
            if(board.cells[i]>0){ bestIdx=i; break; }
        }
    }

    cout << name << " chon o " << bestIdx - 5 << endl;
    return bestIdx;
}
