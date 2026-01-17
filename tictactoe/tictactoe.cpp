#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>

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
Player *currentPlayer = nullptr;
const string FILE_NAME = "players.txt";


void loadPlayers() {
    ifstream file(FILE_NAME);
    if (!file) {
        cout << "File player tidak ditemukan. Membuat file baru...\n\n";
        ofstream newFile(FILE_NAME);
        newFile.close();
        return;
    }

    players.clear();
    Player p;
    char h;
    while (file >> p.nama >> h >> p.totalGames >> h >> p.totalWins >> h >> p.totalDraws >> h >> p.totalLosses >> h >> p.score) {
        players.push_back(p);
    }
    file.close();
}

void savePlayers() {
    ofstream file(FILE_NAME);
    for (auto &p : players) {
        file << p.nama << ";"
             << p.totalGames << ";"
             << p.totalWins << ";"
             << p.totalDraws << ";"
             << p.totalLosses << ";"
             << p.score << endl;
    }
    file.close();
    cout << "\nData telah disimpan ke file players.txt\n";
}

/* ================= UI ================= */

void header() {
    cout << "================================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "================================\n\n";
}

void pause() {
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

/* ================= PLAYER ================= */

void showStats(Player &p) {
    cout << "\nStatistik " << p.nama << ":\n";
    cout << "- Total Games : " << p.totalGames << endl;
    cout << "- Wins        : " << p.totalWins << endl;
    cout << "- Draws       : " << p.totalDraws << endl;
    cout << "- Losses      : " << p.totalLosses << endl;
    cout << "- Total Score : " << p.score << endl;
}

void registerPlayer() {
    Player p;
    cout << "\n=== REGISTRASI PLAYER BARU ===\n";
    cout << "\nMasukkan nama Anda: ";
    cin >> p.nama;

    p.totalGames = p.totalWins = p.totalDraws = p.totalLosses = p.score = 0;
    players.push_back(p);
    currentPlayer = &players.back();

    cout << "\nPlayer baru berhasil dibuat!\n";
    cout << "Selamat datang, " << p.nama << "!\n";

    showStats(*currentPlayer);
    pause();
}

void selectPlayer() {
    if (players.empty()) {
        cout << "\nBelum ada player.\n";
        pause();
        return;
    }
    
    cout << "=== DAFTAR PLAYER ===\n";

    cout << left
         << setw(4)  << "No"  << "| "
         << setw(10) << "Nama"  << "| "
         << setw(6)  << "Score" << "| "
         << setw(6)  << "Games" << "| "
         << setw(2)  << "W"     << "| "
         << setw(2)  << "D"     << "| "
         << setw(2)  << "L"     << endl;

    cout << "---------------------------------------------\n";

    for (size_t i = 0; i < players.size() && i < 10; i++) {
        cout << left
             << setw(4)  << i + 1               << "| "
             << setw(10) << players[i].nama     << "| "
             << setw(6)  << players[i].score    << "| "
             << setw(6)  << players[i].totalGames << "| "
             << setw(2)  << players[i].totalWins  << "| "
             << setw(2)  << players[i].totalDraws << "| "
             << setw(2)  << players[i].totalLosses
             << endl;
        }


    int pilih;
    cout << "\nPilih player (0 batal) ";
    cin >> pilih;

    if (pilih > 0 && pilih <= players.size()) {
        currentPlayer = &players[pilih - 1];
        showStats(*currentPlayer);
        pause();
    }
}

/* ================= LEADERBOARD ================= */

void showLeaderboard() {
    sort(players.begin(), players.end(), [](Player a, Player b) {
        return a.score > b.score;
    });

    cout << "\n================================\n";
    cout << "        LEADERBOARD\n";
    cout << "  Top 10 Players by Score\n";
    cout << "================================\n\n";

    cout << left
         << setw(5)  << "Rank"  << "| "
         << setw(10) << "Nama"  << "| "
         << setw(6)  << "Score" << "| "
         << setw(6)  << "Games" << "| "
         << setw(2)  << "W"     << "| "
         << setw(2)  << "D"     << "| "
         << setw(2)  << "L"     << endl;

    cout << "--------------------------------------------------------\n";

    for (size_t i = 0; i < players.size() && i < 10; i++) {
        cout << left
             << setw(5)  << i + 1               << "| "
             << setw(10) << players[i].nama     << "| "
             << setw(6)  << players[i].score    << "| "
             << setw(6)  << players[i].totalGames << "| "
             << setw(2)  << players[i].totalWins  << "| "
             << setw(2)  << players[i].totalDraws << "| "
             << setw(2)  << players[i].totalLosses
             << endl;
        }

    pause();
}

/* ================= GAME LOGIC ================= */

char board[9];

void resetBoard() {
    for (int i = 0; i < 9; i++)
        board[i] = ' ';
}

void showGuide() {
    cout << "Panduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void drawBoard() {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << board[i] << " ";
        if (i % 3 != 2) cout << "|";
        if (i % 3 == 2 && i != 8)
            cout << "\n---|---|---\n";
    }
    cout << "\n\n";
}

bool checkWin(char p) {
    int w[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for (auto &x : w)
        if (board[x[0]] == p && board[x[1]] == p && board[x[2]] == p)
            return true;

    return false;
}

bool boardFull() {
    for (char c : board)
        if (c == ' ') return false;
    return true;
}

/* ================= VS COMPUTER ================= */

void playVsComputer() {
    resetBoard();
    showGuide();
    drawBoard();

    while (true) {
        int pos;
        cout << "Giliran Anda (X)\nMasukkan posisi (1-9): ";
        cin >> pos;
        pos--;

        if (pos < 0 || pos >= 9 || board[pos] != ' ') continue;
        board[pos] = 'X';
        drawBoard();

        if (checkWin('X')) {
            cout << " \nANDA MENANG! \n";
            cout << "================================\n";
            cout << "      HASIL PERTANDINGAN\n";
            cout << "================================\n";
            cout << "Hasil " << currentPlayer->nama<< " : Menang\n";
            cout << "Score yang di dapatkan : +3 poin\n ";
            currentPlayer->totalWins++;
            currentPlayer->score += 3;
            break;
        }

        if (boardFull()) {
            cout << "SERI! Tidak ada yang menang.\n";
            cout << "================================\n";
            cout << "      HASIL PERTANDINGAN\n";
            cout << "================================\n";
            cout << "Hasil " << currentPlayer->nama<< " : SERI\n";
            cout << "Score yang di dapatkan : +1 poin\n ";
            currentPlayer->totalDraws++;
            currentPlayer->score += 1;
            break;
        }

        cout << "Komputer sedang berpikir...\n";
        int c;
        do {
            c = rand() % 9;
        } while (board[c] != ' ');

        cout << "Komputer memilih posisi: " << c + 1 << endl;
        board[c] = 'O';
        drawBoard();

        if (checkWin('O')) {
            cout << "KOMPUTER MENANG!\n";
            cout << "================================\n";
            cout << "      HASIL PERTANDINGAN\n";
            cout << "================================\n";
            cout << "Hasil KOMPUTER : Menang\n";
            cout << "Score yang di dapatkan : +3 poin\n ";
            currentPlayer->totalLosses++;
            break;
        }
    }

    currentPlayer->totalGames++;
    showStats(*currentPlayer);
    savePlayers();
}
void playVsPlayer() {
    resetBoard();
    char player = 'X';
    string ply1,ply2;
        
    cout << "\nMode Vs Player dipilih!\n";
    cout << "Player 1 : ";
	cin>>ply1;
    cout << "Player 2 : ";
    cin>>ply2;

    while (true) {
        drawBoard();
        int pos;
        
        
        cout << "Player " << player << " pilih posisi (1-9): ";
        cin >> pos;
        pos--;

        if (pos < 0 || pos > 8 || board[pos] != ' ')
            continue;

        board[pos] = player;

        if (checkWin(player)) {
            drawBoard();
            cout << "Player " << player << " MENANG!\n";
            cout << "================================\n";
            cout << "      HASIL PERTANDINGAN\n";
            cout << "================================\n";
            cout << "Hasil " << currentPlayer->nama<< " : Menang\n";
            cout << "Score yang di dapatkan : +3 poin\n ";
            if (player == 'ply1') currentPlayer->totalWins++;
            else currentPlayer->totalLosses++;
            break;
        }

        if (boardFull()) {
            drawBoard();
            cout << "SERI!\n";
            cout << "================================\n";
            cout << "      HASIL PERTANDINGAN\n";
            cout << "================================\n";
            cout << "Hasil " << currentPlayer->nama << " : SERI\n";
            cout << "Score yang di dapatkan : +1 poin\n ";
            currentPlayer->totalDraws++;
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }

    currentPlayer->totalGames++;
    savePlayers();
    pause();
}


/* ================= MAIN ================= */

int main() {
    srand(time(0));
    loadPlayers();
    char mainlagi;

    int menu;
    do {
        header();
        cout << "=== MENU UTAMA ===\n";
        cout << "1. Player Baru\n";
        cout << "2. Pilih Player yang Sudah Ada\n";
        cout << "3. Lihat Leaderboard\n";
        cout << "4. Keluar\n";
        cout << "\nPilihan Anda: ";
        cin >> menu;

         switch (menu) {
            case 1: registerPlayer(); break;
            case 2: selectPlayer(); break;
            case 3: showLeaderboard(); break;
            case 4: cout << "\nTerima kasih telah bermain! \n"; break;
        }

        if (currentPlayer && menu != 4) {
            int mode;
            cout << "\n=== PILIH MODE PERMAINAN ===\n";
            cout << "1. VS Player\n";
            cout << "2. VS Komputer\n";
            cout << "Pilihan Anda: ";
            cin >> mode;

            if (mode==1) playVsPlayer(); 
            else if (mode == 2) playVsComputer();
            
            cout << "Main lagi? (y/n): ";
		cin >> mainlagi;
		fflush(stdin);
	}
		
		if(mainlagi == 'n'|| mainlagi == 'N'){
			cout <<"\nTerima kasih telah bermain, " << currentPlayer->nama << "!" <<endl;
			pause();			            
        }

    } while (menu != 4);
    

    return 0;
}
