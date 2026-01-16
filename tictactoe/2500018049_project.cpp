#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct Player {
    string nama;
    int totalGames = 0;
    int totalWins = 0;
    int totalDraws = 0;
    int totalLosses = 0;
    int score = 0;
};

vector<Player> playerList;

// --- FUNGSI FILE MANAGEMENT ---

void loadPlayers() {
    playerList.clear();
    ifstream file("players.txt");
    if (file.is_open()) {
        Player p;
        while (file >> p.nama >> p.totalGames >> p.totalWins >> p.totalDraws >> p.totalLosses >> p.score) {
            playerList.push_back(p);
        }
        file.close();
    }
}

void savePlayers() {
    ofstream file("players.txt");
    for (size_t i = 0; i < playerList.size(); i++) {
        file << playerList[i].nama << " " << playerList[i].totalGames << " " << playerList[i].totalWins << " " 
             << playerList[i].totalDraws << " " << playerList[i].totalLosses << " " << playerList[i].score << endl;
    }
    file.close();
}

// --- FUNGSI MANAJEMEN PLAYER ---
int getOrRegisterPlayer(string role, int excludeIdx = -1) {
    while (true) {
        system("cls");
        cout << "\n--- Registrasi/Pilih Player untuk " << role << " ---" << endl;
        if (excludeIdx != -1) {
            cout << "(Pemain sebelumnya: " << playerList[excludeIdx].nama << ")" << endl;
        }
        cout << "1. Player Baru\n2. Pilih Player Terdaftar\n3. Kembali ke Menu Utama\nPilihan: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            Player p;
            cout << "Masukkan Nama Baru (Tanpa Spasi): ";
            cin >> p.nama;
            
            cout << "Konfirmasi Nama: " << p.nama << "? (y/n): ";
            char confirm; cin >> confirm;
            if (confirm == 'n' || confirm == 'N') continue;

            playerList.push_back(p);
            savePlayers();
            return playerList.size() - 1;
        } 
        else if (choice == 2) {
            if (playerList.empty()) {
                cout << "Belum ada player terdaftar.\n";
                system("pause");
                continue;
            }
            system("cls");
            cout << "--- Daftar Player ---\n";
            for (int i = 0; i < playerList.size(); i++) {
                cout << i + 1 << ". " << playerList[i].nama;
                if (i == excludeIdx) cout << " (SUDAH DIPILIH)";
                cout << endl;
            }
            cout << "0. Kembali\nPilih nomor: ";
            int idx; cin >> idx;
            
            if (idx == 0) continue;
            int actualIdx = idx - 1;

            // Validasi agar tidak memilih pemain yang sama
            if (actualIdx == excludeIdx) {
                cout << "Error: Player ini sudah dipilih oleh Player 1! Pilih player lain.\n";
                system("pause");
                continue;
            }
            
            if (actualIdx >= 0 && actualIdx < playerList.size()) {
                return actualIdx;
            }
        } 
        else if (choice == 3) {
            return -2;
        }
    }
}

void updateStats(int pIdx, string result) {
    if (pIdx < 0) return; 
    playerList[pIdx].totalGames++;
    if (result == "win") {
        playerList[pIdx].totalWins++;
        playerList[pIdx].score += 3;
    } else if (result == "draw") {
        playerList[pIdx].totalDraws++;
        playerList[pIdx].score += 1;
    } else {
        playerList[pIdx].totalLosses++;
    }
    savePlayers();
}

// --- LOGIKA PERMAINAN ---


void displayBoard(char board[3][3]) {
    system("cls");
    cout << "\n      KONTROL POSISI\n";
    cout << "  1 | 2 | 3      " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << " ---|---|---    ---|---|---" << endl;
    cout << "  4 | 5 | 6      " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << " ---|---|---    ---|---|---" << endl;
    cout << "  7 | 8 | 9      " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

bool checkWin(char board[3][3], char p) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p) return true;
        if (board[0][i] == p && board[1][i] == p && board[2][i] == p) return true;
    }
    if (board[0][0] == p && board[1][1] == p && board[2][2] == p) return true;
    if (board[0][2] == p && board[1][1] == p && board[2][0] == p) return true;
    return false;
}

bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return false;
    return true;
}

int computerMove(char board[3][3]) {
    for (int i = 1; i <= 9; i++) {
        int r = (i-1)/3, c = (i-1)%3;
        if (board[r][c] == ' ') {
            board[r][c] = 'O';
            if (checkWin(board, 'O')) { board[r][c] = ' '; return i; }
            board[r][c] = ' ';
        }
    }
    for (int i = 1; i <= 9; i++) {
        int r = (i-1)/3, c = (i-1)%3;
        if (board[r][c] == ' ') {
            board[r][c] = 'X';
            if (checkWin(board, 'X')) { board[r][c] = ' '; return i; }
            board[r][c] = ' ';
        }
    }
    if (board[1][1] == ' ') return 5;
    for(int i=1; i<=9; i++) if(board[(i-1)/3][(i-1)%3] == ' ') return i;
    return -1;
}

void showLeaderboard() {
    system("cls");
    loadPlayers();
    cout << "\n" << setfill('=') << setw(45) << "" << endl;
    cout << left << setw(15) << "Nama" << setw(7) << "W" << setw(7) << "D" << setw(7) << "L" << "Score" << endl;
    cout << setfill('-') << setw(45) << "" << setfill(' ') << endl;
    for (size_t i = 0; i < playerList.size(); i++) {
        cout << left << setw(15) << playerList[i].nama << setw(7) << playerList[i].totalWins << setw(7) 
             << playerList[i].totalDraws << setw(7) << playerList[i].totalLosses << playerList[i].score << endl;
    }
    cout << setfill('=') << setw(45) << "" << setfill(' ') << endl;
    system("pause");
}
void loadingScreen() {
    system("cls");
    cout << "\n\n\n\n\t\t\t   MEMUAT GAME...\n";
    cout << "\t\t\t[";
    
    for (int i = 0; i < 30; i++) {
        Sleep(80);
        cout << char(219);
    }
    
    cout << "]\n";
    cout << "\t\t\t   SELESAI!";
    Sleep(500);
}

int main() {
    srand(time(0));
    loadPlayers();
    
    loadingScreen();
    
    int menu;
    do {
        system("cls");
        cout << "\n=== TIC TAC TOE PRO ===\n";
        cout << "1. Player vs Player\n2. Player vs Komputer\n3. Leaderboard\n4. Keluar\nPilihan: ";
        cin >> menu;

        if (menu == 1 || menu == 2) {
            int p1Idx = getOrRegisterPlayer("Player 1 (X)");
            if (p1Idx == -2) continue;

            int p2Idx = -1;
            if (menu == 1) {
                p2Idx = getOrRegisterPlayer("Player 2 (O)", p1Idx);
                if (p2Idx == -2) continue;
            }

            char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
            char turn = 'X';
            bool running = true;

            while (running) {
                displayBoard(board);
                int move;
                
                if (turn == 'X') {
                    cout << playerList[p1Idx].nama << " (X), pilih (1-9): "; cin >> move;
                } else {
                    if (menu == 1) {
                        cout << playerList[p2Idx].nama << " (O), pilih (1-9): "; cin >> move;
                    } else {
                        cout << "Komputer sedang berpikir...\n";
                        move = computerMove(board);
                        _sleep(800);
                    }
                }

                int r = (move-1)/3, c = (move-1)%3;
                if (move < 1 || move > 9 || board[r][c] != ' ') {
                    cout << "Langkah tidak valid!\n"; 
                    system("pause");
                    continue;
                }

                board[r][c] = turn;

                if (checkWin(board, turn)) {
                    displayBoard(board);
                    if (turn == 'X') {
                        cout << "\n?? " << playerList[p1Idx].nama << " MENANG!\n";
                        updateStats(p1Idx, "win");
                        if (menu == 1) updateStats(p2Idx, "loss");
                    } else {
                        if (menu == 1) {
                            cout << "\n?? " << playerList[p2Idx].nama << " MENANG!\n";
                            updateStats(p2Idx, "win");
                            updateStats(p1Idx, "loss");
                        } else {
                            cout << "\n?? KOMPUTER MENANG!\n";
                            updateStats(p1Idx, "loss");
                        }
                    }
                    system("pause");
                    running = false;
                } else if (isBoardFull(board)) {
                    displayBoard(board);
                    cout << "\n?? HASIL SERI!\n";
                    updateStats(p1Idx, "draw");
                    if (menu == 1) updateStats(p2Idx, "draw");
                    system("pause");
                    running = false;
                }
                turn = (turn == 'X') ? 'O' : 'X';
            }
        } else if (menu == 3) showLeaderboard();
    } while (menu != 4);

    cout << "\nTerimakasih telah bermain!";
    return 0;
}
