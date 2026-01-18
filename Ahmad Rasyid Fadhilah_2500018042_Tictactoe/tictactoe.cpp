#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player {
    string nama;
    int score, games, win, draw, loss;
};

vector<Player> players;
Player current;
bool activePlayer = false;

/* ================= UTIL ================= */

void pause() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void header() {
    cout << "================================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "================================\n\n";
}

/* ================= FILE ================= */

void loadPlayers() {
    ifstream file("players.txt");
    if (!file) {
        cout << "File player tidak ditemukan.  Membuat file baru...\n\n";
        return;
    }
    Player p;
    while (file >> p.nama >> p.score >> p.games >> p.win >> p.draw >> p.loss)
        players.push_back(p);
    file.close();
}

void savePlayers() {
    ofstream file("players.txt");
    for (size_t i = 0; i < players.size(); i++)
        file << players[i].nama << " "
             << players[i].score << " "
             << players[i].games << " "
             << players[i].win << " "
             << players[i].draw << " "
             << players[i].loss << endl;
    file.close();
    cout << "\nData telah disimpan ke file players.txt\n";
}

/* ================= DISPLAY ================= */

void guide() {
    cout << "Panduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void board(char b[]) {
    cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n\n";
}

/* ================= GAME LOGIC ================= */

bool win(char b[], char c) {
    int w[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for (int i=0;i<8;i++)
        if (b[w[i][0]]==c && b[w[i][1]]==c && b[w[i][2]]==c)
            return true;
    return false;
}

bool draw(char b[]) {
    for (int i=0;i<9;i++) if (b[i]==' ') return false;
    return true;
}

int cpuMove(char b[]) {
    int p;
    do { p = rand()%9; } while (b[p]!=' ');
    return p;
}

/* ================= PLAYER ================= */

void registerPlayer() {
    header();
    cout << "=== REGISTRASI PLAYER BARU ===\n";
    cout << "Masukkan nama Anda: ";
    cin >> current.nama;

    current.score=0; current.games=0;
    current.win=0; current.draw=0; current.loss=0;

    players.push_back(current);
    activePlayer = true;

    cout << "\nPlayer baru berhasil dibuat!\n";
    cout << "Selamat datang, " << current.nama << "!\n";
    pause();
}

void choosePlayer() {
    if (players.empty()) {
        cout << "Belum ada player!\n";
        pause();
        return;
    }

    header();
    cout << "=== DAFTAR PLAYER ===\n";
    for (size_t i=0;i<players.size();i++)
        cout << i+1 << ". " << players[i].nama << " (Score: " << players[i].score << ")\n";

    int p;
    do {
        cout << "\nPilih player: ";
        cin >> p;
    } while (p<1 || p>(int)players.size());

    current = players[p-1];
    activePlayer = true;
    pause();
}

/* ================= LEADERBOARD ================= */

bool sortScore(Player a, Player b) {
    return a.score > b.score;
}

void leaderboard() {
    header();
    cout << "LEADERBOARD - TOP 10\n\n";

    sort(players.begin(), players.end(), sortScore);

    cout <<"Rank | Nama | Score | Games | W | D | L\n";
    for (size_t i=0;i<players.size() && i<10;i++)
        cout << i+1 << "              | "
             << players[i].nama << "  | "
             << players[i].score << " | "
             << players[i].games << " | "
             << players[i].win << "   | "
             << players[i].draw << "  | "
             << players[i].loss << endl;
    pause();
}

/* ================= GAME MODE ================= */

void vsComputer() {
    char b[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
    int pos;

    while (true) {
        header(); guide(); board(b);

        do {
            cout << "Giliran Anda (X)\nMasukkan posisi (1-9): ";
            cin >> pos;
        } while (pos<1||pos>9||b[pos-1]!=' ');

        b[pos-1]='X';

        if (win(b,'X')) {
            cout << "?? ANDA MENANG! ??\n";
            current.win++; current.score+=3;
            break;
        }
        if (draw(b)) {
            cout << "SERI!\n";
            current.draw++; current.score+=1;
            break;
        }

        cout << "\nKomputer sedang berpikir...\n";
        int c=cpuMove(b);
        cout << "Komputer memilih posisi: " << c+1 << endl;
        b[c]='O';

        if (win(b,'O')) {
            cout << "?? KOMPUTER MENANG! ??\n";
            current.loss++;
            break;
        }
    }
    current.games++;
}

/* ================= MAIN ================= */

int main() {
    srand(time(0));
    loadPlayers();

    int menu;
    do {
        header();
        cout << "=== MENU UTAMA ===\n";
        cout << "1. Player Baru\n";
        cout << "2. Pilih Player\n";
        cout << "3. Leaderboard\n";
        cout << "4. Keluar\n\n";
        cout << "Pilihan Anda: ";
        cin >> menu;

        if (menu==1) registerPlayer();
        else if (menu==2) choosePlayer();
        else if (menu==3) leaderboard();

        if ((menu==1||menu==2) && activePlayer) {
            int mode;
            do {
                cout << "\n=== PILIH MODE PERMAINAN ===\n";
                cout << "1. VS Player\n";
                cout << "2. VS Komputer\n";
                cout << "Pilihan: ";
                cin >> mode;
            } while (mode!=2); // VS Player bisa dikembangkan

            char lagi;
            do {
                vsComputer();
                cout << "\nMain lagi? (y/n): ";
                cin >> lagi;
            } while (lagi=='y');

            for (size_t i=0;i<players.size();i++)
                if (players[i].nama==current.nama)
                    players[i]=current;

            savePlayers();
        }

    } while (menu!=4);

    cout << "\nTerima kasih telah bermain Tic Tac Toe! ??\n";
    return 0;
}

