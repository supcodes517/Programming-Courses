#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;


struct Player {
    string nama;
    int totalGames = 0;
    int totalWins = 0;
    int totalDraws = 0;
    int totalLosses = 0;
    int score = 0;
};


vector<Player> players;
char board[3][3];
int p1_idx = -1, p2_idx = -1;


void loadData() {
    players.clear();
    ifstream file("players.txt");
    if (!file) return;
    Player p;
    while (file >> p.nama >> p.totalGames >> p.totalWins >> p.totalDraws >> p.totalLosses >> p.score) {
        players.push_back(p);
    }
    file.close();
}

void saveData() {
    ofstream file("players.txt", ios::trunc);
    for (int i = 0; i < (int)players.size(); i++) {
        file << players[i].nama << " " 
             << players[i].totalGames << " " 
             << players[i].totalWins << " " 
             << players[i].totalDraws << " " 
             << players[i].totalLosses << " " 
             << players[i].score << endl;
    }
    file.close();
}




void displayGuide() {
    cout << "\n SEMOGA SENANG BERMAIN DI GEMES KAMI :\n";
   
}

void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " \n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

void resetBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) board[i][j] = ' ';
}

bool checkWin(char symbol) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;
    return false;
}


void updateStats(int winner) { 
    if (p1_idx != -1) {
        players[p1_idx].totalGames++;
        if (winner == 1) { players[p1_idx].totalWins++; players[p1_idx].score += 3; }
        else if (winner == 2) { players[p1_idx].totalLosses++; }
        else { players[p1_idx].totalDraws++; players[p1_idx].score += 1; }
    }
    if (p2_idx != -1) {
        players[p2_idx].totalGames++;
        if (winner == 2) { players[p2_idx].totalWins++; players[p2_idx].score += 3; }
        else if (winner == 1) { players[p2_idx].totalLosses++; }
        else { players[p2_idx].totalDraws++; players[p2_idx].score += 1; }
    }
    saveData();
}


int choosePlayer(string label) {
    if (players.empty()) return -1;
    cout << "\n--- Pilih " << label << " ---\n";
    for (int i = 0; i < (int)players.size(); i++) cout << i << ". " << players[i].nama << "\n";
    int choice; cout << "Pilihan: "; cin >> choice;
    return (choice >= 0 && choice < (int)players.size()) ? choice : -1;
}

void play(bool vsComputer) {
    p1_idx = choosePlayer("PEMAIN 1 (X)");
    p2_idx = vsComputer ? -1 : choosePlayer("PEMAIN 2 (O)");

    if (p1_idx == -1 || (!vsComputer && p2_idx == -1)) {
        cout << "MAAF KAMI TIDAK BISA MENEMUKAN PEMAIN!\n"; return;
    }

    resetBoard();
    displayGuide();
    int turns = 0;
    char currentSymbol = 'X';

    while (turns < 9) {
        displayBoard();
        int pos;
        if (currentSymbol == 'X') {
            cout << "GILIRAN " << players[p1_idx].nama << " (X)\n";
            cout << "PILILAH ANGKA (1-9): "; cin >> pos;
        } else {
            if (vsComputer) {
                cout << " KOMPUTER SEDANG MEMILIH...\n";
                do { pos = (rand() % 9) + 1; } while (board[(pos-1)/3][(pos-1)%3] != ' ');
                cout << "KOMPUTER MEMILIH ANGKA: " << pos << "\n";
            } else {
                cout << "GILIRAN" << players[p2_idx].nama << " (O)\n";
                cout << "PILILAH ANGKA (1-9): "; cin >> pos;
            }
        }

        int r = (pos-1)/3, c = (pos-1)%3;
        if (pos < 1 || pos > 9 || board[r][c] != ' ') {
            if (!vsComputer || currentSymbol == 'X') cout << "POSISI TIDAK BENAR!\n";
            continue;
        }

        board[r][c] = currentSymbol;
        if (checkWin(currentSymbol)) {
            displayBoard();
            if (currentSymbol == 'X') {
                cout << "?? " << players[p1_idx].nama << " MENANG! ??\n";
                updateStats(1);
            } else {
                cout << vsComputer ? "?? KOMPUTER MENANG! ??" : "?? " + players[p2_idx].nama + " MENANG! ??";
                cout << "\n";
                if (!vsComputer) updateStats(2); else updateStats(2); 
            }
            return;
        }
        currentSymbol = (currentSymbol == 'X') ? 'O' : 'X';
        turns++;
    }
    displayBoard();
    cout << "HASIL SERI!\n";
    updateStats(0);
}

int main() {
    srand(time(0));
    loadData();
    int menu;
    do {
        cout << "\n=================================\n";
        cout << "=   SELAMAT BERMAIN DI GEMES     =\n";
        cout << "=================================\n";
        displayGuide();
        cout << "\n PILIH MODE BERMAIN MU:\n1.  PEMAIN VS  PEMAIN LAIN. \n2.  PEMAIN VS KOMPUTER. \n3. TAMBAHKAN PEMAIN BARU. \n4. HASIL SEKOR PEMAIN.\n5. KELUAR\n PILIHAN MU: ";
        cin >> menu;

        if (menu == 1) play(false);
        else if (menu == 2) play(true);
        else if (menu == 3) {
            Player p; cout << "Nama: "; cin >> p.nama;
            players.push_back(p); saveData();
        }
        else if (menu == 3) {
            cout << "\nNAME\tG\tW\tD\tL\tSCORE\n";
            cout << "--------------------------------------------\n";
            
            for (int i = 0; i < (int)players.size(); i++) {
                cout << players[i].nama << "\t" 
                     << players[i].totalGames << "\t" 
                     << players[i].totalWins << "\t" 
                     << players[i].totalDraws << "\t" 
                     << players[i].totalLosses << "\t" 
                     << players[i].score << "\n";
            }
        }
    } while (menu != 4);
    return 0;
}
