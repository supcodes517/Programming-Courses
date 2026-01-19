#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

/*
=================================================
STRUCT PLAYER
=================================================
*/
struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};

/*
=================================================
FUNGSI FILE I/O
=================================================
*/
void loadPlayers(vector<Player>& players) {
    ifstream file("players.txt");
    if (!file.is_open()) return;

    Player p;
    while (file >> p.nama
                >> p.totalGames
                >> p.totalWins
                >> p.totalDraws
                >> p.totalLosses
                >> p.score) {
        players.push_back(p);
    }
    file.close();
}

void savePlayers(vector<Player>& players) {
    ofstream file("players.txt");
    for (size_t i = 0; i < players.size(); i++) {
        file << players[i].nama << " "
             << players[i].totalGames << " "
             << players[i].totalWins << " "
             << players[i].totalDraws << " "
             << players[i].totalLosses << " "
             << players[i].score << endl;
    }
    file.close();
}

int findPlayer(vector<Player>& players, string nama) {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].nama == nama)
            return i;
    }
    return -1;
}

/*
=================================================
FUNGSI BOARD (ASLI DOSEN)
=================================================
*/
void displayBoard(char board[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j];
            if (j < 2) cout << " |";
        }
        cout << "\n";
        if (i < 2) cout << " ---|---|---\n";
    }
    cout << "\n";
}

void displayGuide() {
    cout << "Panduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

/*
=================================================
LOGIKA GAME (ASLI DOSEN)
=================================================
*/
bool checkWin(char board[3][3], char p) {
    for (int i = 0; i < 3; i++)
        if (board[i][0] == p &&
            board[i][1] == p &&
            board[i][2] == p)
            return true;

    for (int j = 0; j < 3; j++)
        if (board[0][j] == p &&
            board[1][j] == p &&
            board[2][j] == p)
            return true;

    if (board[0][0] == p &&
        board[1][1] == p &&
        board[2][2] == p)
        return true;

    if (board[0][2] == p &&
        board[1][1] == p &&
        board[2][0] == p)
        return true;

    return false;
}

bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

bool isValidMove(char board[3][3], int pos) {
    if (pos < 1 || pos > 9) return false;
    int r = (pos - 1) / 3;
    int c = (pos - 1) % 3;
    return board[r][c] == ' ';
}

void makeMove(char board[3][3], int pos, char p) {
    int r = (pos - 1) / 3;
    int c = (pos - 1) % 3;
    board[r][c] = p;
}

/*
=================================================
AI SEDERHANA (DOSEN + MODIFIKASI)
=================================================
*/
int computerMove(char board[3][3]) {
    for (int i = 1; i <= 9; i++)
        if (isValidMove(board, i))
            return i;
    return -1;
}

/*
=================================================
MODE VS PLAYER
=================================================
*/
void playVsPlayer(Player& p1, Player& p2) {
    char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char current = 'X';
    int pos;

    while (true) {
        displayBoard(board);
        cout << "Giliran " << (current == 'X' ? p1.nama : p2.nama)
             << " (" << current << "): ";
        cin >> pos;

        if (!isValidMove(board, pos)) {
            cout << "Posisi tidak valid!\n";
            continue;
        }

        makeMove(board, pos, current);

        if (checkWin(board, current)) {
            displayBoard(board);
            cout << "MENANG!\n";

            p1.totalGames++;
            p2.totalGames++;

            if (current == 'X') {
                p1.totalWins++;
                p2.totalLosses++;
                p1.score += 3;
            } else {
                p2.totalWins++;
                p1.totalLosses++;
                p2.score += 3;
            }
            break;
        }

        if (isBoardFull(board)) {
            cout << "SERI!\n";
            p1.totalGames++;
            p2.totalGames++;
            p1.totalDraws++;
            p2.totalDraws++;
            p1.score++;
            p2.score++;
            break;
        }

        current = (current == 'X') ? 'O' : 'X';
    }
}

/*
=================================================
MODE VS KOMPUTER
=================================================
*/
void playVsComputer(Player& p) {
    char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    int pos;

    while (true) {
        displayBoard(board);
        cout << "Giliran Anda (X): ";
        cin >> pos;

        if (!isValidMove(board, pos)) continue;
        makeMove(board, pos, 'X');

        if (checkWin(board, 'X')) {
            cout << "ANDA MENANG!\n";
            p.totalWins++;
            p.score += 3;
            break;
        }

        if (isBoardFull(board)) {
            cout << "SERI!\n";
            p.totalDraws++;
            p.score++;
            break;
        }

        int comp = computerMove(board);
        makeMove(board, comp, 'O');

        if (checkWin(board, 'O')) {
            displayBoard(board);
            cout << "KOMPUTER MENANG!\n";
            p.totalLosses++;
            break;
        }
    }
    p.totalGames++;
}

/*
=================================================
PROGRAM UTAMA
=================================================
*/
int main() {
    vector<Player> players;
    loadPlayers(players);

    cout << "================================\n";
    cout << "        TIC TAC TOE GAME\n";
    cout << "================================\n\n";

    displayGuide();

    Player current;
    int menu;

    cout << "1. Player Baru\n";
    cout << "2. Pilih Player\n";
    cout << "Pilihan Anda: ";
    cin >> menu;

    if (menu == 1) {
        cout << "Masukkan nama player: ";
        cin >> current.nama;
        current.totalGames = 0;
        current.totalWins = 0;
        current.totalDraws = 0;
        current.totalLosses = 0;
        current.score = 0;
    } else {
        for (size_t i = 0; i < players.size(); i++)
            cout << i << ". " << players[i].nama << endl;
        int idx;
        cin >> idx;
        current = players[idx];
    }

    int mode;
    cout << "\n1. VS Player\n";
    cout << "2. VS Komputer\n";
    cout << "Pilih mode: ";
    cin >> mode;

    if (mode == 1) {
        Player p2;
        cout << "Masukkan nama player 2: ";
        cin >> p2.nama;
        p2.totalGames = p2.totalWins = p2.totalDraws = p2.totalLosses = p2.score = 0;
        playVsPlayer(current, p2);
    } else {
        playVsComputer(current);
    }

    int idx = findPlayer(players, current.nama);
    if (idx != -1)
        players[idx] = current;
    else
        players.push_back(current);

    savePlayers(players);

    cout << "\nData berhasil disimpan ke players.txt\n";
    return 0;
}
