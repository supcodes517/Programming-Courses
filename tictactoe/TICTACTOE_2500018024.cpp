#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};


vector<Player> players;
char board[3][3];
const string FILE_PLAYER = "player.txt";

// ================= PRESS ENTER UNTUK MELANJUTKAN =================
void pressEnter() {
    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

// ================= FILE.TXT =================
void loadPlayers() {
    players.clear();
    ifstream file(FILE_PLAYER.c_str());

    if (!file) {
        cout << "File player tidak ditemukan.\n";
        return;
    }

    Player p;
    while (file >> p.nama >> p.totalGames >> p.totalWins
                >> p.totalDraws >> p.totalLosses >> p.score) {
        players.push_back(p);
    }
    file.close();
}

void savePlayers() {
    ofstream file(FILE_PLAYER.c_str());

    for (int i = 0; i < players.size(); i++) {
        file << players[i].nama << " "
             << players[i].totalGames << " "
             << players[i].totalWins << " "
             << players[i].totalDraws << " "
             << players[i].totalLosses << " "
             << players[i].score << endl;
    }

    file.close();
    cout << "\nData telah disimpan ke file player\n";
}

// ================= BOARD TICTACTOE =================
void resetBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void displayGuide() {
    cout << "\nPanduan Posisi :\n";
    cout << "1 | 2 | 3\n";
    cout << "--+---+--\n";
    cout << "4 | 5 | 6\n";
    cout << "--+---+--\n";
    cout << "7 | 8 | 9\n\n";
}

void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        if (i < 2) cout << "\n---+---+---\n";
    }
    cout << "\n";
}

bool placeMove(int pos, char mark) {
    if (pos < 1 || pos > 9) return false;

    int r = (pos - 1) / 3;
    int c = (pos - 1) % 3;

    if (board[r][c] == 'X' || board[r][c] == 'O')
        return false;

    board[r][c] = mark;
    return true;
}

bool checkWin(char m) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == m && board[i][1] == m && board[i][2] == m) ||
            (board[0][i] == m && board[1][i] == m && board[2][i] == m))
            return true;
    }

    if ((board[0][0] == m && board[1][1] == m && board[2][2] == m) ||
        (board[0][2] == m && board[1][1] == m && board[2][0] == m))
        return true;

    return false;
}

bool isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return false;

    return true;
}

void computerMove() {
    cout << "\nKomputer sedang berpikir...\n";
    int pos;

    do {
        pos = rand() % 9 + 1;
    } while (!placeMove(pos, 'O'));

    cout << "Komputer memilih posisi : " << pos << endl;
}

bool compareScore(Player a, Player b) {
    return a.score > b.score;
}


// (1 = MENANG, 2 = SERI, 3 = KALAH)
void showMatchResult(int result) {
    cout << "\n============================\n";
    cout << "     HASIL PERTANDINGAN\n";
    cout << "============================\n";

    if (result == 1)
        cout << "Hasil : MENANG\nScore yang didapat : +3\n";
    else if (result == 2)
        cout << "Hasil : SERI\nScore yang didapat : +1\n";
    else if (result == 3)
        cout << "Hasil : KALAH\nScore yang didapat : +0\n";
}

// ================= STATISTIK PLAYER  =================
void showStatistics(Player p) {
    cout << "\nStatistik " << p.nama << " :\n";
    cout << "- Total Games : " << p.totalGames << endl;
    cout << "- Wins        : " << p.totalWins << endl;
    cout << "- Draws       : " << p.totalDraws << endl;
    cout << "- Losses      : " << p.totalLosses << endl;
    cout << "- Total Score : " << p.score << endl;
}

// ================= REGISTRASI PLAYER =================
void registerPlayer() {
    Player p;
    cout << "\n--- REGISTRASI PLAYER BARU ---\n";
    cout << "Masukkan Nama Anda : ";
    cin.ignore();
    getline(cin, p.nama);

    p.totalGames = 0;
    p.totalWins = 0;
    p.totalDraws = 0;
    p.totalLosses = 0;
    p.score = 0;

    players.push_back(p);

    cout << "\nPlayer baru berhasil dibuat!\n";
    cout << "Selamat datang, " << p.nama << "!\n";
    showStatistics(players.back());

    savePlayers();
}

int choosePlayer() {
    if (players.empty()) {
        cout << "Belum ada player.\n";
        return -1;
    }

    cout << "\n================== | DAFTAR PLAYER | ==================\n";

    cout << left << setw(3) << "\n No" << " | "
         << setw(16) << "Nama" << " | "
         << setw(6) << "Score" << " | "
         << setw(6) << "Games" << " | "
         << setw(2) << "W" << " | "
         << setw(2) << "D" << " | "
         << "L" << endl;

    cout << "----|------------------|--------|--------|----|----|---" << endl;

    for (int i = 0; i < players.size(); i++) {
        cout << left << setw(3) << i + 1 << " | "
             << setw(16) << players[i].nama << " | "
             << setw(6) << players[i].score << " | "
             << setw(6) << players[i].totalGames << " | "
             << setw(2) << players[i].totalWins << " | "
             << setw(2) << players[i].totalDraws << " | "
             << players[i].totalLosses << endl;
    }

    int p;
    cout << "\nPilih player (1-" << players.size() << ") atau 0 untuk kembali : ";
    cin >> p;

    if (p == 0) return -1;
    if (p < 1 || p > players.size()) {
        cout << "Pilihan tidak valid!\n";
        return -1;
    }

    cout << "\nPlayer dipilih : " << players[p-1].nama << endl;
    cout << "\nSelamat datang kembali, " << players[p-1].nama << "!\n";

    cout << "\nStatistik Anda :" << endl;
    cout << "- Total Games : " << players[p-1].totalGames << endl;
    cout << "- Wins        : " << players[p-1].totalWins << endl;
    cout << "- Draws       : " << players[p-1].totalDraws << endl;
    cout << "- Losses      : " << players[p-1].totalLosses << endl;
    cout << "- Total Score : " << players[p-1].score << endl;

    pressEnter();
    return p - 1;
}

// ================= PILIHAN GAME =================
void playVsComputer(Player &p) {
    int result = 0;
    char ulang;

    do {
        resetBoard();
        displayGuide();

        while (true) {
            displayBoard();
            int pos;
            cout << "Giliran " << p.nama << " (X): ";
            cin >> pos;

            if (!placeMove(pos, 'X')) {
                cout << "Input tidak valid!\n";
                continue;
            }

            if (checkWin('X')) {
                displayBoard();
                cout << "\nANDA MENANG!\n";
                result = 1;
                p.totalWins++;
                p.score += 3;
                break;
            }

            if (isDraw()) {
                displayBoard();
                cout << "\nSERI! Tidak ada yang menang.\n";
                result = 2;
                p.totalDraws++;
                p.score += 1;
                break;
            }

            computerMove();

            if (checkWin('O')) {
                displayBoard();
                cout << "\nANDA KALAH!\n";
                result = 3;
                p.totalLosses++;
                break;
            }

            if (isDraw()) {
                displayBoard();
                cout << "\nSERI! Tidak ada yang menang.\n";
                result = 2;
                p.totalDraws++;
                p.score += 1;
                break;
            }
        }

        p.totalGames++;
        showMatchResult(result);
        showStatistics(p);
        savePlayers();
        pressEnter();

        cout << "\nMain lagi? (y/n): ";
        cin >> ulang;

    } while (ulang == 'y' || ulang == 'Y');
}

void playVsPlayer(Player &p1, Player &p2) {
    char ulang;

    do {
        resetBoard();
        displayGuide();
        char turn = 'X';

        while (true) {
            displayBoard();
            Player &current = (turn == 'X') ? p1 : p2;

            cout << "Giliran " << current.nama << " (" << turn << "): ";
            int pos;
            cin >> pos;

            if (!placeMove(pos, turn)) {
                cout << "Input tidak valid!!\n";
                continue;
            }

            if (checkWin(turn)) {
                displayBoard();
                cout << " " << current.nama << " MENANG!\n";

                current.totalWins++;
                current.score += 3;

                if (&current == &p1) p2.totalLosses++;
                else p1.totalLosses++;

                break;
            }

            if (isDraw()) {
                displayBoard();
                cout << "SERI!\n";
                p1.totalDraws++; p2.totalDraws++;
                p1.score++; p2.score++;
                break;
            }

            turn = (turn == 'X') ? 'O' : 'X';
        }

        p1.totalGames++;
        p2.totalGames++;

        showStatistics(p1);
        showStatistics(p2);
        savePlayers();

        cout << "\nMain lagi? (y/n): ";
        cin >> ulang;

    } while (ulang == 'y' || ulang == 'Y');
}

// ================= PILIHAN MENU =================
int main() {
    srand(time(0));
    loadPlayers();

    int menu;
    do {
        cout << "\n==============================\n";
        cout << "      TIC TAC TOE GAME        \n";
        cout << "==============================\n";
        cout << "1. Player Baru\n";
        cout << "2. Pilih Player yang Sudah Ada\n";
        cout << "3. Lihat Leaderboard\n";
        cout << "4. Keluar\n";
        cout << "\nPilihan Anda : ";
        cin >> menu;

        if (menu == 1) registerPlayer();
        else if (menu == 2) {
            int p1 = choosePlayer();
            if (p1 == -1) continue;

            cout << "\n--- PILIH MODE GAME ---\n";
            cout << "1. VS Player\n";
            cout << "2. VS Komputer\n";
            cout << "\nPilih Mode : ";
            int mode;
            cin >> mode;

            if (mode == 2)
                playVsComputer(players[p1]);
            else if (mode == 1) {
                cout << "\nPilih Player ke-2 : ";
                int p2 = choosePlayer();
                if (p2 != -1 && p2 != p1)
                    playVsPlayer(players[p1], players[p2]);
            }
        }
        else if (menu == 3) {
            vector<Player> temp = players;
            sort(temp.begin(), temp.end(), compareScore);

            cout << "\n=================== | LEADERBOARD | ===================\n";

            cout << left << setw(3) << "\n No" << " | "
                 << setw(16) << "Nama" << " | "
                 << setw(6) << "Score" << " | "
                 << setw(6) << "Games" << " | "
                 << setw(2) << "W" << " | "
                 << setw(2) << "D" << " | "
                 << "L" << endl;

            cout << "----|------------------|--------|--------|----|----|---" << endl;

            for (int i = 0; i < temp.size() && i < 10; i++) {
                cout << left << setw(3) << i + 1 << " | "
                     << setw(16) << temp[i].nama << " | "
                     << setw(6) << temp[i].score << " | "
                     << setw(6) << temp[i].totalGames << " | "
                     << setw(2) << temp[i].totalWins << " | "
                     << setw(2) << temp[i].totalDraws << " | "
                     << temp[i].totalLosses << endl;
            }
        }
        else if (menu == 4)
            cout << "Terima kasih telah bermain.\n";
        else
            cout << "Pilihan tidak valid!\n";

    } while (menu != 4);

    return 0;
}