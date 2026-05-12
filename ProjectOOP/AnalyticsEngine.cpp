#include "AnalyticsEngine.h"

#include <iostream>

using namespace std;

AnalyticsEngine::AnalyticsEngine(int n)
    : soTran(n),
      player1Wins(0),
      player2Wins(0),
      draws(0),
      tongLuot(0),
      tongDiemPlayer1(0),
      tongDiemPlayer2(0) {}

int AnalyticsEngine::getPlayer1Wins() const {
    return player1Wins;
}

int AnalyticsEngine::getPlayer2Wins() const {
    return player2Wins;
}

int AnalyticsEngine::getDraws() const {
    return draws;
}

int AnalyticsEngine::getSoTran() const {
    return soTran;
}

void AnalyticsEngine::run(
    BotBase* player1,
    BotBase* player2
) {

    player1Wins = 0;
    player2Wins = 0;
    draws = 0;

    tongLuot = 0;

    tongDiemPlayer1 = 0;
    tongDiemPlayer2 = 0;

    player1->side = 0;
    player2->side = 1;

    for (int i = 0; i < soTran; i++) {

        OAnQuan game;

        while (!game.ketThucTroChoi()) {

            int current = game.nguoiChoiluot();

            int move;

            if (current == 0) {
                move = player1->makeMove(game);
            }
            else {
                move = player2->makeMove(game);
            }

            bool ok = game.diChuyen(move, true);

            if (!ok) {
                break;
            }
        }

        int winner = game.nguoiThang();

        if (winner == 0) {
            player1Wins++;
        }
        else if (winner == 1) {
            player2Wins++;
        }
        else {
            draws++;
        }

        tongLuot += game.laySoLuotDaChoi();

        tongDiemPlayer1 += game.tinhDiem(0);
        tongDiemPlayer2 += game.tinhDiem(1);
    }
}

void AnalyticsEngine::inThongKe(
    string player1Name,
    string player2Name
) const {

    cout << "\n===== THONG KE =====\n";

    cout << player1Name
         << " wins: "
         << player1Wins
         << " ("
         << (double)player1Wins * 100 / soTran
         << "%)\n";

    cout << player2Name
         << " wins: "
         << player2Wins
         << " ("
         << (double)player2Wins * 100 / soTran
         << "%)\n";

    cout << "Draws: "
         << draws
         << " ("
         << (double)draws * 100 / soTran
         << "%)\n";

    cout << "Average turns: "
         << (double)tongLuot / soTran
         << endl;

    cout << "Average score "
         << player1Name
         << ": "
         << (double)tongDiemPlayer1 / soTran
         << endl;

    cout << "Average score "
         << player2Name
         << ": "
         << (double)tongDiemPlayer2 / soTran
         << endl;
}
