#ifndef ANALYTICS_ENGINE_H
#define ANALYTICS_ENGINE_H

#include "Game.h"
#include "Botbase.h"
#include <iostream>

using namespace std;

class AnalyticsEngine {
private:
    int soTran;

    int player1Wins;
    int player2Wins;
    int draws;

    int tongLuot;

    int tongDiemPlayer1;
    int tongDiemPlayer2;

public:
    AnalyticsEngine(int n = 10000);

    void run(
        BotBase* player1,
        BotBase* player2
    );

    void inThongKe(
        string player1Name,
        string player2Name
    ) const;
};

#endif
```
