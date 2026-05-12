#ifndef ANALYTICS_ENGINE_H
#define ANALYTICS_ENGINE_H

#include <string>

#include "BotBase.h"

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

    int getPlayer1Wins() const;
    int getPlayer2Wins() const;
    int getDraws() const;
    int getSoTran() const;

    void run(
        BotBase* player1,
        BotBase* player2
    );

    void inThongKe(
        std::string player1Name,
        std::string player2Name
    ) const;
};

#endif
