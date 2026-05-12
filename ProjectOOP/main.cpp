#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Bot1.h"
#include "Bot2.h"
#include "Bot3.h"

#include "AnalyticsEngine.h"

using namespace std;

int main() {

    srand((unsigned)time(0));

    const int SO_TRAN_MOI_CAP = 10000;

    AnalyticsEngine engine(SO_TRAN_MOI_CAP);

    Bot1 bot1("Bot1");
    Bot2 bot2("Bot2");
    Bot3 bot3("Bot3");

    int bot1Wins = 0;
    int bot2Wins = 0;
    int bot3Wins = 0;

    int bot1Matches = 0;
    int bot2Matches = 0;
    int bot3Matches = 0;

    int totalDraws = 0;

    cout << "\n========== BOT1 vs BOT2 ==========" << endl;

    engine.run(&bot1, &bot2);
    engine.inThongKe(bot1.name, bot2.name);

    bot1Wins += engine.getPlayer1Wins();
    bot2Wins += engine.getPlayer2Wins();

    bot1Matches += SO_TRAN_MOI_CAP;
    bot2Matches += SO_TRAN_MOI_CAP;

    totalDraws += engine.getDraws();

    cout << "\n========== BOT2 vs BOT3 ==========" << endl;

    engine.run(&bot2, &bot3);
    engine.inThongKe(bot2.name, bot3.name);

    bot2Wins += engine.getPlayer1Wins();
    bot3Wins += engine.getPlayer2Wins();

    bot2Matches += SO_TRAN_MOI_CAP;
    bot3Matches += SO_TRAN_MOI_CAP;

    totalDraws += engine.getDraws();

    cout << "\n========== BOT1 vs BOT3 ==========" << endl;

    engine.run(&bot1, &bot3);
    engine.inThongKe(bot1.name, bot3.name);

    bot1Wins += engine.getPlayer1Wins();
    bot3Wins += engine.getPlayer2Wins();

    bot1Matches += SO_TRAN_MOI_CAP;
    bot3Matches += SO_TRAN_MOI_CAP;

    totalDraws += engine.getDraws();

    cout << "\n========== THONG KE TONG HOP ==========" << endl;

    cout << "Moi bot da dau: "
         << bot1Matches
         << " tran"
         << endl;

    cout << "Bot1 thang: "
         << bot1Wins
         << " / "
         << bot1Matches
         << " ("
         << (double)bot1Wins * 100 / bot1Matches
         << "%)"
         << endl;

    cout << "Bot2 thang: "
         << bot2Wins
         << " / "
         << bot2Matches
         << " ("
         << (double)bot2Wins * 100 / bot2Matches
         << "%)"
         << endl;

    cout << "Bot3 thang: "
         << bot3Wins
         << " / "
         << bot3Matches
         << " ("
         << (double)bot3Wins * 100 / bot3Matches
         << "%)"
         << endl;

    cout << "Tong so tran hoa: "
         << totalDraws
         << endl;

    return 0;
}
