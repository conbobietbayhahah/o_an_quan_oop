#pragma once
#ifndef ANALYTICS_ENGINE_H
#define ANALYTICS_ENGINE_H

#include "Game.h"
#include "Botbase.h"
#include <iostream>
using namespace std;

class AnalyticsEngine {
private:
    int soTran;
    int bot1Wins;
    int bot2Wins;
    int draws;

    int tongLuot;
    int tongDiemBot1;
    int tongDiemBot2;

public:
    AnalyticsEngine(int n = 10000);

    void run(BotBase* bot1, BotBase* bot2);

    void inThongKe(
        string tenBot1,
        string tenBot2
    ) const;
};

#endif
