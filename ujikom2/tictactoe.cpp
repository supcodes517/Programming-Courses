#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


struct Player {
    string nama;
    int totalGames;
    int wins;
    int draws;
    int losses;
    int score;
};

vector<Player> players;


void loadPlayers() {
    ifstream file("players.txt");
    if (!file) {
        cout << "File player tidak ditemukan.  Membuat file baru...\n\n";
        ofstream newFile("players.txt");
        newFile.close();
        return;
    }

    Player p;
    while (file >> p.nama >> p.totalGames >> p.wins >> p.draws >> p.losses >> p.score) {
        players.push_back(p);
    }
    file.close();
}

void savePlayers() {
    ofstream file("players.txt");
    for (int i = 0; i < players.size(); i++) {
        file << players[i].nama << " "
             << players[i].totalGames << " "
             << players[i].wins << " "
             << players[i].draws << " "
             << players[i].losses << " "
             << players[i].score << endl;
    }
    file.close();
}


int getPlayerIndex(string name) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i].nama == name)
            return i;
    }

    Player p;
    p.nama = name;
    p.totalGames = p.wins = p.draws = p.losses = p.score = 0;
    players.push_back(p);
    return players.size() - 1;
}


void resetBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void displayBoard(char board[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
}

bool validMove(char board[3][3], int pos) {
    if (pos < 1 || pos > 9) return false;
    int r = (pos - 1) / 3;
    int c = (pos - 1) % 3;
    return board[r][c] == ' ';
}

void makeMove(char board[3][3], int pos, char mark) {
    board[(pos - 1) / 3][(pos - 1) % 3] = mark;
}

bool checkWin(char board[3][3], char m) {
    for (int i = 0; i < 3; i++)
        if (board[i][0] == m && board[i][1] == m && board[i][2] == m)
            return true;

    for (int j = 0; j < 3; j++)
        if (board[0][j] == m && board[1][j] == m && board[2][j] == m)
            return true;

    if (board[0][0] == m && board[1][1] == m && board[2][2] == m) return true;
    if (board[0][2] == m && board[1][1] == m && board[2][0] == m) return true;

    return false;
}

bool isDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return false;
    return true;
}


int computerMove(char board[3][3]) {
    for (int i = 1; i <= 9; i++)
        if (validMove(board, i)) return i;
    return -1;
}


void playVsComputer(Player &p) {
    char board[3][3];
    resetBoard(board);

    while (true) {
        int pos;
        displayBoard(board);
        cout << "\nGiliran " << p.nama << " (X): ";
        cin >> pos;

        if (!validMove(board, pos)) continue;
        makeMove(board, pos, 'X');

        if (checkWin(board, 'X')) {
            cout << "\nANDA MENANG!\n";
            p.wins++; p.score += 3;
            break;
        }

        if (isDraw(board)) {
            cout << "\nSERI!\n";
            p.draws++; p.score++;
            break;
        }

        int c = computerMove(board);
        makeMove(board, c, 'O');

        if (checkWin(board, 'O')) {
            cout << "\nKOMPUTER MENANG!\n";
            p.losses++;
            break;
        }
    }
    p.totalGames++;
}

void playVsPlayer(Player &p1, Player &p2) {
    char board[3][3];
    resetBoard(board);
    char turn = 'X';

    while (true) {
        displayBoard(board);
        cout << "\nGiliran "
             << (turn == 'X' ? p1.nama : p2.nama)
             << " (" << turn << "): ";

        int pos;
        cin >> pos;

        if (!validMove(board, pos)) continue;
        makeMove(board, pos, turn);

        if (checkWin(board, turn)) {
            cout << "\nPEMENANG: "
                 << (turn == 'X' ? p1.nama : p2.nama) << endl;

            if (turn == 'X') {
                p1.wins++; p1.score += 3; p2.losses++;
            } else {
                p2.wins++; p2.score += 3; p1.losses++;
            }
            break;
        }

        if (isDraw(board)) {
            cout << "\nSERI!\n";
            p1.draws++; p2.draws++;
            p1.score++; p2.score++;
            break;
        }

        turn = (turn == 'X') ? 'O' : 'X';
    }

    p1.totalGames++;
    p2.totalGames++;
}


void showLeaderboard() {
    cout << "\n=== LEADERBOARD ===\n";
    if (players.empty()) {
        cout << "Belum ada player yang pernah bermain.\n";
        return;
    }

    for (int i = 0; i < players.size(); i++) {
        cout << players[i].nama
             << " | Score: " << players[i].score
             << " | Win: " << players[i].wins
             << " | Draw: " << players[i].draws
             << " | Loss: " << players[i].losses << endl;
    }
}


int main() {
    loadPlayers();
    int menu;

    do {
        cout << "\n================================\n";
        cout << "     TIC TAC TOE GAME\n";
        cout << "================================\n\n";
        cout << "1. Player Baru\n";
        cout << "2. Pilih Player yang Sudah Ada\n";
        cout << "3. Lihat Leaderboard\n";
        cout << "4. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> menu;

        if (menu == 1) {
            string name;
            cout << "\nMasukkan nama Player: ";
            cin >> name;
            int pIndex = getPlayerIndex(name);

            cout << "\n=== PILIH MODE GAME ===\n";
            cout << "1. Player vs Player\n";
            cout << "2. Player vs Komputer\n";
            cout << "Pilihan: ";
            int mode;
            cin >> mode;

            if (mode == 1) {
                string p2name;
                cout << "Masukkan nama Player 2 (O): ";
                cin >> p2name;
                int p2Index = getPlayerIndex(p2name);
                playVsPlayer(players[pIndex], players[p2Index]);
            }
            else if (mode == 2) {
                playVsComputer(players[pIndex]);
            }

            savePlayers();
        }
        else if (menu == 2) {
            if (players.empty()) {
                cout << "\nBelum ada player yang pernah bermain.\n";
                continue;
            }

            string name;
            cout << "\nMasukkan nama Player: ";
            cin >> name;

            int pIndex = getPlayerIndex(name);

            cout << "\n=== PILIH MODE GAME ===\n";
            cout << "1. Player vs Player\n";
            cout << "2. Player vs Komputer\n";
            cout << "Pilihan: ";
            int mode;
            cin >> mode;

            if (mode == 1) {
                string p2name;
                cout << "Masukkan nama Player 2 (O): ";
                cin >> p2name;
                int p2Index = getPlayerIndex(p2name);
                playVsPlayer(players[pIndex], players[p2Index]);
            }
            else if (mode == 2) {
                playVsComputer(players[pIndex]);
            }

            savePlayers();
        }
        else if (menu == 3) {
            showLeaderboard();
        }

    } while (menu != 4);

    cout << "\nTerima kasih telah bermain!\n";
    return 0;
}
