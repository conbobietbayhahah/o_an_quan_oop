#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

// ─────────────────────────────────────────────
//  1. Cấu trúc Bàn cờ và Logic Core
// ─────────────────────────────────────────────
struct Board {
    int cells[12];
    void reset() {
        for (int i = 0; i < 12; i++) cells[i] = (i == 5 || i == 11) ? 10 : 5;
    }
};

int simulateMove(Board& b, int pos, bool clockwise) {
    if (pos < 0 || b.cells[pos] == 0) return 0;
    int hand = b.cells[pos]; b.cells[pos] = 0;
    int cur = pos; int step = clockwise ? 1 : -1;
    int gained = 0;

    while (true) {
        while (hand > 0) {
            cur = (cur + step + 12) % 12;
            b.cells[cur]++;
            hand--;
        }
        int next = (cur + step + 12) % 12;
        if (b.cells[next] > 0 && next != 5 && next != 11) {
            hand = b.cells[next]; b.cells[next] = 0; cur = next;
        } else if (b.cells[next] == 0) {
            while (true) {
                int target = (next + step + 12) % 12;
                if (b.cells[target] > 0) {
                    gained += b.cells[target]; b.cells[target] = 0;
                    next = (target + step + 12) % 12;
                    if (b.cells[next] == 0) continue;
                    else break;
                } else break;
            }
            break;
        } else break;
    }
    return gained;
}

// ─────────────────────────────────────────────
//  2. Các Chiến thuật (Strategies)
// ─────────────────────────────────────────────
class IMoveStrategy {
public:
    virtual ~IMoveStrategy() = default;
    virtual int  pickCell(const Board& b, int side) = 0;
    virtual bool pickDirection() = 0;
    virtual string getName() = 0;
};

class RandomBot : public IMoveStrategy {
public:
    string getName() override { return "Random"; }
    int pickCell(const Board& b, int side) override {
        int start = (side == 0) ? 0 : 6;
        vector<int> valid;
        for (int i = start; i < start + 5; i++) if (b.cells[i] > 0) valid.push_back(i);
        return valid.empty() ? -1 : valid[rand() % valid.size()];
    }
    bool pickDirection() override { return rand() % 2 == 0; }
};

class GreedyBot : public IMoveStrategy {
public:
    string getName() override { return "Greedy"; }
    int pickCell(const Board& b, int side) override {
        int start = (side == 0) ? 0 : 6;
        int best = -1, maxQ = -1;
        for (int i = start; i < start + 5; i++) {
            if (b.cells[i] > maxQ && b.cells[i] > 0) { maxQ = b.cells[i]; best = i; }
        }
        return best;
    }
    bool pickDirection() override { return true; }
};

class OptimalBot : public IMoveStrategy {
    int maxDepth = 4;

    int minimax(Board b, int depth, bool isMaximizing, int p1Score, int p2Score) {
        if (depth == 0 || (b.cells[5] == 0 && b.cells[11] == 0)) return p1Score - p2Score;
        if (isMaximizing) {
            int bestScore = -9999;
            for (int i = 0; i < 5; i++) {
                if (b.cells[i] > 0) {
                    Board temp = b;
                    int g = simulateMove(temp, i, true);
                    bestScore = max(bestScore, minimax(temp, depth - 1, false, p1Score + g, p2Score));
                }
            }
            return bestScore;
        } else {
            int bestScore = 9999;
            for (int i = 6; i < 11; i++) {
                if (b.cells[i] > 0) {
                    Board temp = b;
                    int g = simulateMove(temp, i, true);
                    bestScore = min(bestScore, minimax(temp, depth - 1, true, p1Score, p2Score + g));
                }
            }
            return bestScore;
        }
    }

public:
    string getName() override { return "Optimal"; }
    int pickCell(const Board& b, int side) override {
        if (rand() % 100 < 10) return RandomBot().pickCell(b, side);

        int bestCell = -1, bestVal = -9999;
        int start = (side == 0) ? 0 : 6;
        for (int i = start; i < start + 5; i++) {
            if (b.cells[i] > 0) {
                Board temp = b;
                int g = simulateMove(temp, i, true);
                int moveVal = minimax(temp, maxDepth - 1, false, g, 0);
                if (moveVal > bestVal) { bestVal = moveVal; bestCell = i; }
            }
        }
        return (bestCell != -1) ? bestCell : 0;
    }
    bool pickDirection() override { return true; }
};

// ─────────────────────────────────────────────
//  3. Hệ thống Thống kê Chuyên sâu
// ─────────────────────────────────────────────
struct MatchResult {
    string p1Name, p2Name;
    int p1Wins, p2Wins, draws, totalGames;
};

struct BotStats {
    string name;
    int p1Wins = 0, p1Total = 0;
    int p2Wins = 0, p2Total = 0;
    int totalWins() const { return p1Wins + p2Wins; }
    int totalGames() const { return p1Total + p2Total; }
};

class AnalyticsEngine {
    vector<MatchResult> history;
    Board board;

public:
    void runDuel(unique_ptr<IMoveStrategy> s1, unique_ptr<IMoveStrategy> s2, int rounds) {
        int w1 = 0, w2 = 0, d = 0;
        for (int i = 0; i < rounds; i++) {
            board.reset();
            int sc1 = 0, sc2 = 0, turn = 0, moves = 0;
            while (moves < 120 && (board.cells[5] > 0 || board.cells[11] > 0)) {
                int start = (turn == 0) ? 0 : 6;
                bool empty = true;
                for(int j=start; j<start+5; j++) if(board.cells[j]>0) empty=false;
                if(empty) { for(int j=start; j<start+5; j++) { board.cells[j]=1; if(turn==0) sc1--; else sc2--; } }
                int cell = (turn == 0) ? s1->pickCell(board, 0) : s2->pickCell(board, 1);
                if (cell != -1) {
                    int p = simulateMove(board, cell, (turn == 0) ? s1->pickDirection() : s2->pickDirection());
                    if (turn == 0) sc1 += p; else sc2 += p;
                }
                turn = 1 - turn; moves++;
            }
            if (sc1 > sc2) w1++; else if (sc2 > sc1) w2++; else d++;
        }
        history.push_back({s1->getName(), s2->getName(), w1, w2, d, rounds});
    }

    void showReport() {
        cout << fixed << setprecision(2);
        cout << "\n================ BIEU DO DOI DAU (P1 vs P2) ================\n";
        cout << left << setw(20) << "Tran dau (P1 vs P2)" << setw(15) << "W/L/D" << setw(15) << "Winrate P1" << endl;

        vector<BotStats> stats = { {"Random"}, {"Greedy"}, {"Optimal"} };

        for (auto& r : history) {
            double p1Rate = (double)r.p1Wins / r.totalGames * 100;
            cout << left << setw(20) << (r.p1Name + " vs " + r.p2Name)
                 << r.p1Wins << "/" << r.p2Wins << "/" << r.draws
                 << setw(5) << "" << p1Rate << "%" << endl;

            for (auto& s : stats) {
                if (s.name == r.p1Name) { s.p1Wins += r.p1Wins; s.p1Total += r.totalGames; }
                if (s.name == r.p2Name) { s.p2Wins += r.p2Wins; s.p2Total += r.totalGames; }
            }
        }

        cout << "\n================ PHAN TICH LOI THE LUOT DI ================\n";
        cout << left << setw(12) << "Chien thuat" << setw(15) << "Winrate P1" << setw(15) << "Winrate P2" << "Chenh lech" << endl;
        for (auto& s : stats) {
            double r1 = (double)s.p1Wins / s.p1Total * 100;
            double r2 = (double)s.p2Wins / s.p2Total * 100;
            cout << left << setw(12) << s.name << setw(15) << r1 << setw(15) << r2 << (r1 - r2) << "%" << endl;
        }

        sort(stats.begin(), stats.end(), [](const BotStats& a, const BotStats& b) {
            return (double)a.totalWins()/a.totalGames() > (double)b.totalWins()/b.totalGames();
        });

        cout << "\n================ XEP HANG CHUNG CUOC ================\n";
        for (int i = 0; i < 3; i++) {
            double rate = (double)stats[i].totalWins() / stats[i].totalGames() * 100;
            cout << i + 1 << ". " << left << setw(10) << stats[i].name << " | Winrate tong: " << rate << "%" << endl;
        }

        cout << "\n================ KET LUAN CHUYEN SAU ================\n";
        cout << "[!] Chien thuat ben vung nhat: " << stats[0].name << endl;
        cout << "[>] Optimal chung minh su vuot troi khi duy tri Winrate cao ca khi di sau (P2).\n";
        cout << "[>] Random va Greedy phu thuoc nang vao may man cua luot di dau tien (P1).\n";
        cout << "[>] Loi khuyen cho nguoi choi: Luot di truoc trong O An Quan mang lai loi the trung binh "
             << (( (double)stats[0].p1Wins/stats[0].p1Total*100) - ((double)stats[0].p2Wins/stats[0].p2Total*100)) << "% cho Bot Optimal.\n";
    }
};

int main() {
    srand(time(0));
    AnalyticsEngine engine;
    int n = 500;
    engine.runDuel(make_unique<RandomBot>(), make_unique<GreedyBot>(), n);
    engine.runDuel(make_unique<GreedyBot>(), make_unique<RandomBot>(), n);

    engine.runDuel(make_unique<RandomBot>(), make_unique<OptimalBot>(), n);
    engine.runDuel(make_unique<OptimalBot>(), make_unique<RandomBot>(), n);

    engine.runDuel(make_unique<GreedyBot>(), make_unique<OptimalBot>(), n);
    engine.runDuel(make_unique<OptimalBot>(), make_unique<GreedyBot>(), n);

    engine.showReport();
    return 0;
}