#include "AnalyticsEngine.h"

AnalyticsEngine::AnalyticsEngine(int n) {

    soTran = n;

    player1Wins = 0;
    player2Wins = 0;
    draws = 0;

    tongLuot = 0;

    tongDiemPlayer1 = 0;
    tongDiemPlayer2 = 0;
}

void AnalyticsEngine::run(
    BotBase* player1,
    BotBase* player2
) {

    for (int gameIndex = 0; gameIndex < soTran; gameIndex++) {

        OAnQuan game;

        while (!game.ketThucTroChoi()) {

            int current = game.nguoiChoiluot();

            BotBase* currentPlayer;

            if (current == 0)
                currentPlayer = player1;
            else
                currentPlayer = player2;

            bool hopLe = false;

            while (!hopLe) {

                int move =
                    currentPlayer->makeMove(
                        game.layBanCo()
                    );

                bool direction =
                    rand() % 2;

                hopLe =
                    game.diChuyen(
                        move,
                        direction
                    );
            }
        }

        int winner = game.nguoiThang();

        if (winner == 0)
            player1Wins++;
        else if (winner == 1)
            player2Wins++;
        else
            draws++;

        tongLuot +=
            game.laySoLuotDaChoi();

        tongDiemPlayer1 +=
            game.tinhDiem(0);

        tongDiemPlayer2 +=
            game.tinhDiem(1);
    }
}

void AnalyticsEngine::inThongKe(
    string player1Name,
    string player2Name
) const {

    cout << "\n========== THONG KE ==========\n";

    cout << "\nTong so tran: "
         << soTran
         << endl;

    cout << "\n"
         << player1Name
         << " thang: "
         << player1Wins
         << " ("
         << (100.0 * player1Wins / soTran)
         << "%)\n";

    cout << player2Name
         << " thang: "
         << player2Wins
         << " ("
         << (100.0 * player2Wins / soTran)
         << "%)\n";

    cout << "Hoa: "
         << draws
         << " ("
         << (100.0 * draws / soTran)
         << "%)\n";

    cout << "\nSo luot trung binh: "
         << (double)tongLuot / soTran
         << endl;

    cout << player1Name
         << " diem trung binh: "
         << (double)tongDiemPlayer1 / soTran
         << endl;

    cout << player2Name
         << " diem trung binh: "
         << (double)tongDiemPlayer2 / soTran
         << endl;

    cout << "\n===============================\n";
}
```
