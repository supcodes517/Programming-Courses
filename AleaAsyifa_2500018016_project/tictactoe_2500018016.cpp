#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

#define FILE_NAME "players.txt"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

struct Player {
    string name;
    int games = 0;
    int wins = 0;
    int draws = 0;
    int losses = 0;
    int score = 0;
};

Player currentPlayer;

void clearScreen() {
    system(CLEAR);
}

void header() {
    cout << "==========================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "==========================\n\n";
}

void pressEnter() {
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void savePlayers(const vector<Player>& players) {
    ofstream file(FILE_NAME);
    for (const Player &p : players) {
        file << p.name << " "
             << p.games << " "
             << p.wins << " "
             << p.draws << " "
             << p.losses << " "
             << p.score << endl;
    }
    file.close();
}

void savePlayer(const Player &current, vector<Player> &players) {
    bool found = false;
    for (Player &p : players) {
        if (p.name == current.name) {
            p = current;
            found = true;
            break;
        }
    }
    if (!found) {
        players.push_back(current);
    }
    savePlayers(players);
}

void guide() {
    cout << "Panduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void showBoard(char b[]) {
    cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n\n";
}

bool checkWin(char b[], char s) {
    int w[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (auto &x : w)
        if (b[x[0]] == s && b[x[1]] == s && b[x[2]] == s)
            return true;
    return false;
}

bool draw(char b[]) {
    for (int i = 0; i < 9; i++)
        if (b[i] == ' ') return false;
    return true;
}

void vsComputer(Player& current, vector<Player>& players) {
    clearScreen();
    header();
    guide();

    char board[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    showBoard(board);

    bool menang = false, kalah = false, seri = false;

    while (true) {
        // PLAYER (X)
        int pos;
        cout << "Giliran Anda (X)\n";
        cout << "Masukkan posisi (1-9): ";
        cin >> pos;
        if (pos < 1 || pos > 9 || board[pos-1] != ' ') continue;
        board[pos-1] = 'X';
        showBoard(board);

        if (checkWin(board, 'X')) { menang = true; break; }
        if (draw(board)) { seri = true; break; }

        // KOMPUTER (O)
        cout << "Komputer sedang berpikir...\n";
        if (rand() % 2 == 0) {
            do { pos = rand() % 9; } while (board[pos] != ' ');
        } else {
            for (pos = 0; pos < 9; pos++)
                if (board[pos] == ' ') break;
        }
        board[pos] = 'O';
        showBoard(board);

        if (checkWin(board, 'O')) { kalah = true; break; }
        if (draw(board)) { seri = true; break; }
    }

    // HASIL
    cout << "================================\n";
    cout << "     HASIL PERTANDINGAN\n";
    cout << "================================\n";

    current.games++;
    if (menang) {
        current.wins++;
        current.score += 3;
        cout << "Hasil: MENANG\n";
        cout << "Score yang didapat: +3 poin\n";
    }
    else if (kalah) {
        current.losses++;
        cout << "Hasil: KALAH\n";
        cout << "Score yang didapat: +0 poin\n";
    }
    else if (seri) {
        current.draws++;
        current.score += 1;
        cout << "Hasil: SERI\n";
        cout << "Score yang didapat: +1 poin\n";
    }

    cout << "\nStatistik " << current.name << ":\n";
    cout << "- Total Games: " << current.games << "\n";
    cout << "- Wins: " << current.wins << "\n";
    cout << "- Draws: " << current.draws << "\n";
    cout << "- Losses: " << current.losses << "\n";
    cout << "- Total Score: " << current.score << "\n\n";

    savePlayer(current, players);

    char ulang;
    cout << "Main lagi? (y/n): ";
    cin >> ulang;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (ulang == 'y' || ulang == 'Y') vsComputer(current, players);
}

void vsPlayer(vector<Player>& players) {
    clearScreen();
    header();

    cout << "=== PILIH MODE PERMAINAN ===\n";
    cout << "1. VS Player\n";
    cout << "2. VS Komputer\n\n";
    cout << "Pilihan Anda: ";
    int mode;
    cin >> mode;
    cin.ignore();

    if (mode == 2) {
        vsComputer(currentPlayer, players);
        return;
    }

    cout << "\nMode VS Player dipilih!\n";
    cout << "Player 1: X\n";
    cout << "Player 2: O\n\n";
    cout << "Tekan Enter untuk memulai... ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "==========================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "==========================\n\n";


    guide();

    char board[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    showBoard(board);

    bool menangX = false, menangO = false, seri = false;
    int turn = 0;

    while (true) {
        int pos;
        if (turn % 2 == 0) {
            cout << "Giliran Player X\n";
            cout << "Masukkan posisi (1-9): ";
            cin >> pos;
            if (pos < 1 || pos > 9 || board[pos-1] != ' ') continue;
            board[pos-1] = 'X';
        } else {
            cout << "Giliran Player O\n";
            cout << "Masukkan posisi (1-9): ";
            cin >> pos;
            if (pos < 1 || pos > 9 || board[pos-1] != ' ') continue;
            board[pos-1] = 'O';
        }

        showBoard(board);

        if (checkWin(board, 'X')) { menangX = true; break; }
        if (checkWin(board, 'O')) { menangO = true; break; }
        if (draw(board)) { seri = true; break; }

        turn++;
    }

    if (menangX) cout << "Player X MENANG! \n";
    else if (menangO) cout << "Player O MENANG! \n";
    else cout << "SERI! \n";

    cout << "\n================================\n";
    cout << "       HASIL PERTANDINGAN\n";
    cout << "================================\n";

    if (menangX) {
        currentPlayer.games++;
        currentPlayer.wins++;
        currentPlayer.score += 3;
        cout << "Hasil untuk " << currentPlayer.name << ": MENANG\n";
        cout << "Score yang didapat: +3 poin\n";
    }
    else if (menangO) {
        currentPlayer.games++;
        currentPlayer.losses++;
        cout << "Hasil untuk " << currentPlayer.name << ": KALAH\n";
        cout << "Score yang didapat: +0 poin\n";
    }
    else {
        currentPlayer.games++;
        currentPlayer.draws++;
        currentPlayer.score += 1;
        cout << "Hasil untuk " << currentPlayer.name << ": SERI\n";
        cout << "Score yang didapat: +1 poin\n";
    }

    cout << "\nStatistik " << currentPlayer.name << ":\n";
    cout << "- Total Games: " << currentPlayer.games << "\n";
    cout << "- Wins: " << currentPlayer.wins << "\n";
    cout << "- Draws: " << currentPlayer.draws << "\n";
    cout << "- Losses: " << currentPlayer.losses << "\n";
    cout << "- Total Score: " << currentPlayer.score << "\n\n";

    savePlayer(currentPlayer, players);

    cout << "Data telah disimpan ke file players.txt\n";

    char ulang;
    cout << "Main lagi? (y/n): ";
    cin >> ulang;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (ulang == 'y' || ulang == 'Y') {
        vsPlayer(players);
    }
}

void leaderboard(const vector<Player>& players) {
    if (players.empty()) {
        cout << "Belum ada data leaderboard.\n";
        pressEnter();
        return;
    }

    vector<Player> sortedPlayers = players;
    sort(sortedPlayers.begin(), sortedPlayers.end(), [](const Player& a, const Player& b) {
        return a.score > b.score;
    });

    cout << "================================\n";
    cout << "        LEADERBOARD\n";
    cout << "  Top 10 Players by Score\n";
    cout << "================================\n\n";
    cout << "Rank | Nama           | Score | Games | W  | D  | L\n";
    cout << "-----|----------------|-------|-------|----|----|----\n";

    for (size_t i = 0; i < min(static_cast<size_t>(10), sortedPlayers.size()); i++) {
        const auto& p = sortedPlayers[i];
        cout << setw(4) << i+1 << " | "
             << setw(14) << left << p.name << " | "
             << setw(5) << p.score << " | "
             << setw(5) << p.games << " | "
             << setw(2) << p.wins << " | "
             << setw(2) << p.draws << " | "
             << setw(2) << p.losses << " |\n";
    }
    cout << "\n================================\n";
    pressEnter();
}

int main() {
    srand(time(nullptr));
    clearScreen();
    header();

    vector<Player> players;

    // Baca file
    ifstream infile(FILE_NAME);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            Player p;
            if (ss >> p.name >> p.games >> p.wins >> p.draws >> p.losses >> p.score) {
                players.push_back(p);
            }
        }
        infile.close();
    }

    bool exitProgram = false;
    while (!exitProgram) {
        clearScreen();
        header();

        cout << "=== MENU UTAMA ===\n";
        cout << "1. Player Baru\n";
        cout << "2. Pilih Player yang Sudah Ada\n";
        cout << "3. Lihat Leaderboard\n";
        cout << "4. Keluar\n\n";
        cout << "Pilihan Anda: ";
        int c;
        cin >> c;
        if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
        cin.ignore();

        if (c == 1) {
            cout << "\n=== REGISTRASI PLAYER BARU ===\n";
            cout << "Masukkan nama Anda: ";
            string name;
            getline(cin, name);

            currentPlayer.name = name;
            currentPlayer.games = 0;
            currentPlayer.wins = 0;
            currentPlayer.draws = 0;
            currentPlayer.losses = 0;
            currentPlayer.score = 0;

            cout << "\nPlayer baru berhasil dibuat!\n";
            cout << "Selamat datang, " << currentPlayer.name << "!\n\n";
            cout << "Statistik Anda:\n";
            cout << "- Total Games: 0\n";
            cout << "- Wins: 0\n";
            cout << "- Draws: 0\n";
            cout << "- Losses: 0\n";
            cout << "- Total Score: 0\n\n";
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            savePlayer(currentPlayer, players);
            vsPlayer(players);
        }
        else if (c == 2) {
            clearScreen();
            header();

            ifstream infile2(FILE_NAME);
            vector<Player> listPlayers;
            string line;

            while (getline(infile2, line)) {
                stringstream ss(line);
                Player p;
                if (ss >> p.name >> p.games >> p.wins >> p.draws >> p.losses >> p.score) {
                    listPlayers.push_back(p);
                }
            }
            infile2.close();

            if (listPlayers.empty()) {
                cout << "=== DAFTAR PLAYER ===\n";
                cout << "Belum ada player yang terdaftar.\n";
                pressEnter();
                continue;
            }

            cout << "=== DAFTAR PLAYER ===\n";
            cout << "No | Nama           | Score | Games | W  | D  | L\n";
            cout << "---|----------------|-------|-------|----|----|---\n";

            for (size_t i = 0; i < listPlayers.size(); i++) {
                auto& p = listPlayers[i];
                cout << setw(2) << i + 1 << " | "
                     << setw(14) << left << p.name << " | "
                     << setw(5) << p.score << " | "
                     << setw(5) << p.games << " | "
                     << setw(2) << p.wins << " | "
                     << setw(2) << p.draws << " | "
                     << setw(2) << p.losses << "\n";
            }

            cout << "\nPilih player (1-" << listPlayers.size() << ") atau 0 untuk kembali: ";
            int pilih;
            cin >> pilih;

            if (cin.fail() || pilih < 0 || pilih > static_cast<int>(listPlayers.size())) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Input tidak valid!\n";
                pressEnter();
                continue;
            }

            if (pilih == 0) continue;

            currentPlayer = listPlayers[pilih - 1];
            cout << "\nPlayer dipilih: " << currentPlayer.name << "\n\n";
            cout << "Selamat datang kembali, " << currentPlayer.name << "!\n\n";
            cout << "Statistik Anda:\n";
            cout << "- Total Games: " << currentPlayer.games << "\n";
            cout << "- Wins: " << currentPlayer.wins << "\n";
            cout << "- Draws: " << currentPlayer.draws << "\n";
            cout << "- Losses: " << currentPlayer.losses << "\n";
            cout << "- Total Score: " << currentPlayer.score << "\n\n";
            pressEnter();

            vsPlayer(players);
        }
        else if (c == 3) {
            leaderboard(players);
        }
        else if (c == 4) {
            exitProgram = true;
        }
        else {
            cout << "Pilihan tidak valid!\n";
            pressEnter();
        }
    }

    cout << "\nTerima kasih telah bermain!\n";
    return 0;
}