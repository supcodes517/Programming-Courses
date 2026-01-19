//===FACHRUL RAZIQ LOTAR===
//===2500018029===
//===KELAS A===
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Player {
    string name;       
    int totalGames;    
    int totalWins;    
    int totalDraws;   
    int totalLosses;   
    int score;         
};

const string FILE_NAME = "players.txt";
vector<Player> players;
int activePlayer = -1;

void loadPlayers() {
    ifstream file(FILE_NAME.c_str());
    Player p;
    players.clear(); 
    
    while (file >> p.name >> p.totalGames >> p.totalWins >> p.totalDraws >> p.totalLosses >> p.score) {
        players.push_back(p);
    }
    file.close();
}

void savePlayers() {
    ofstream file(FILE_NAME.c_str());
    for (int i = 0; i < players.size(); i++) {
        file << players[i].name << " "
             << players[i].totalGames << " "
             << players[i].totalWins << " "
             << players[i].totalDraws << " "
             << players[i].totalLosses << " "
             << players[i].score << endl;
    }
    file.close();
}

void addPlayer() {
    Player p;
    cout << "Nama player: ";
    cin >> p.name;

    p.totalGames = p.totalWins = p.totalDraws = p.totalLosses = p.score = 0;
    players.push_back(p);
    savePlayers();
    cout << "Player berhasil ditambahkan!\n";
}

void resetData() {
    ofstream file(FILE_NAME.c_str(), ofstream::trunc);
    file.close();
    players.clear();
    cout << "Semua data berhasil direset!\n";
}

void choosePlayer() {
    if (players.empty()) {
        cout << "Belum ada data player! Buat dulu.\n";
        return;
    }
    
    for (int i = 0; i < players.size(); i++)
        cout << i + 1 << ". " << players[i].name << endl;

    cout << "Pilih player: ";
    cin >> activePlayer;
    activePlayer--;

    if (activePlayer < 0 || activePlayer >= players.size()) {
        activePlayer = -1;
        cout << "Pilihan salah!\n";
    }
}

bool compareScore(Player a, Player b) {
    return a.score > b.score;
}

void leaderboard() {
    if (players.empty()) {
        cout << "Data kosong.\n";
        return;
    }
    sort(players.begin(), players.end(), compareScore);
    cout << "\n=== LEADERBOARD ===\n";
    for (int i = 0; i < players.size(); i++) {
        cout << players[i].name
             << " | Score: " << players[i].score
             << " | Menang: " << players[i].totalWins
             << " | Seri: " << players[i].totalDraws
             << " | Kalah: " << players[i].totalLosses << endl;
    }
}

void initBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void displayBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        cout << "   "; 
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j] << " ";
            if (j < 2) cout << "|";
        }
        cout << endl;
        if (i < 2) cout << "   ---+---+---\n";
    }
}

void displayGuide() {
    cout << "\nPanduan Posisi:\n";
    cout << " 1 | 2 | 3 \n";
    cout << "---+---+---\n";
    cout << " 4 | 5 | 6 \n";
    cout << "---+---+---\n";
    cout << " 7 | 8 | 9 \n\n";
}

bool win(char b[3][3], char p) {
    for (int i = 0; i < 3; i++)
        if (b[i][0] == p && b[i][1] == p && b[i][2] == p) return true;

    for (int i = 0; i < 3; i++)
        if (b[0][i] == p && b[1][i] == p && b[2][i] == p) return true;

    if (b[0][0] == p && b[1][1] == p && b[2][2] == p) return true;
    if (b[0][2] == p && b[1][1] == p && b[2][0] == p) return true;

    return false;
}

bool full(char b[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[i][j] == ' ') return false;
    return true;
}

int aiMove(char b[3][3]) {
    vector<int> moves;
    for (int i = 1; i <= 9; i++) {
        int r = (i - 1) / 3, c = (i - 1) % 3;
        if (b[r][c] == ' ') moves.push_back(i);
    }
    if (!moves.empty()) {
        int idx = rand() % moves.size();
        return moves[idx];
    }
    return 1;
}

void updateScore(int result) {
    players[activePlayer].totalGames++;
    if (result == 1) { 
        players[activePlayer].totalWins++;
        players[activePlayer].score += 3;
    } else if (result == 0) { 
        players[activePlayer].totalDraws++;
        players[activePlayer].score += 1;
    } else {
        players[activePlayer].totalLosses++;
    }
    savePlayers();
}

void showMatchStats() {
    cout << "\n===========================\n";
    cout << "     HASIL PERTANDINGAN    \n";
    cout << "===========================\n\n";
    cout << "Nama Player : " << players[activePlayer].name << endl;
    cout << "Total Main  : " << players[activePlayer].totalGames << endl;
    cout << "Menang      : " << players[activePlayer].totalWins << endl;
    cout << "Seri        : " << players[activePlayer].totalDraws << endl;
    cout << "Kalah       : " << players[activePlayer].totalLosses << endl;
    cout << "Score       : " << players[activePlayer].score << endl;
    cout << endl;
}

void playGame() {
    if (activePlayer == -1) {
        cout << "Pilih player dulu!\n";
        return;
    }

    int mode = 2;
    int pilihanMenuLagi;
    
    do {
        char board[3][3];
        initBoard(board);
        char turn = 'X';
        int pos;
        
        displayGuide();
        cout << players[activePlayer].name << " (X) vs " << (mode == 2 ? "Komputer" : "Lawan") << " (O)\n";

        while (true) {
            displayBoard(board);

            if (mode == 2 && turn == 'O') {
                pos = aiMove(board);
                cout << "Giliran Komputer : " << pos << endl;
            } else {
                cout << "Giliran " << (turn == 'X' ? players[activePlayer].name : "Lawan") << " : ";
                cin >> pos;
            }

            int r = (pos - 1) / 3;
            int c = (pos - 1) % 3;
            
            if (pos < 1 || pos > 9 || board[r][c] != ' ') {
                cout << "Gerakan tidak valid!\n";
                continue;
            }

            board[r][c] = turn;

            if (win(board, turn)) {
                displayBoard(board);
                if (turn == 'X') {
                    cout << "\n" << players[activePlayer].name << " MENANG!\n";
                    updateScore(1);
                } else {
                    cout << "\nKomputer MENANG!\n";
                    updateScore(-1);
                }
                break;
            }

            if (full(board)) {
                displayBoard(board);
                cout << "\nSERI!\n";
                updateScore(0);
                break;
            }

            turn = (turn == 'X') ? 'O' : 'X';
        }

        showMatchStats();

        cout << "1. Bermain lagi\n";
        cout << "2. Kembali ke menu utama\n";
        cout << "Pilih: ";
        cin >> pilihanMenuLagi;
        cout << "\n";

    } while (pilihanMenuLagi == 1);
}

int main() {
    srand(time(0));
    loadPlayers();
    
    int menu;
    do {
        cout << "+===========================+\n";
        cout << "|    MENU TIC TAC TOE GAME  |\n";
        cout << "+===========================+\n";
        cout << "1. Player Baru\n";
        cout << "2. Pilih Player\n";
        cout << "3. Leaderboard\n";
        cout << "4. Reset Data\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> menu;

        switch (menu) {
        case 1: 
            addPlayer(); 
            break;
        case 2: 
            choosePlayer(); 
            if(activePlayer != -1) {
                playGame(); 
            }
            break;
        case 3: 
            leaderboard(); 
            break;
        case 4:
            resetData();
            break;
        case 5:
            cout << "Terima kasih telah bermain!\n";
            break;
        default:
            cout << "Pilihan tidak ada.\n";
        }
        cout << endl;
    } while (menu != 5);
    
    return 0;
}
