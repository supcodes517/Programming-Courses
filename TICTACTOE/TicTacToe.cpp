#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <fstream>

using namespace std;
struct Player {
    string nama;
    int main;
    int menang;
    int seri;
    int kalah;
    int skor;

    Player() {
        main = menang = seri = kalah = skor = 0;
    }
};


vector<Player> players;
char papan[9];


void simpanKeFile() {
    ofstream file("player.txt");
    for (int i = 0; i < players.size(); i++) {
        file << players[i].nama << endl;
        file << players[i].main << " "
             << players[i].menang << " "
             << players[i].seri << " "
             << players[i].kalah << " "
             << players[i].skor << endl;
    }
    file.close();
    cout << "?? Data berhasil disimpan ke player.txt\n";
}


void resetPapan() {
    for (int i = 0; i < 9; i++)
        papan[i] = '1' + i;
}

void panduanPosisi() {
    cout << "\n=== PANDUAN POSISI ===\n";
    cout << " 1 | 2 | 3\n";
    cout << "---+---+---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---+---+---\n";
    cout << " 7 | 8 | 9\n\n";
}

void tampilPapan() {
    cout << "\n";
    cout << " " << papan[0] << " | " << papan[1] << " | " << papan[2] << "\n";
    cout << "---+---+---\n";
    cout << " " << papan[3] << " | " << papan[4] << " | " << papan[5] << "\n";
    cout << "---+---+---\n";
    cout << " " << papan[6] << " | " << papan[7] << " | " << papan[8] << "\n\n";
}

bool cekMenang(char t) {
    int w[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for (int i = 0; i < 8; i++) {
        if (papan[w[i][0]] == t &&
            papan[w[i][1]] == t &&
            papan[w[i][2]] == t)
            return true;
    }
    return false;
}

bool papanPenuh() {
    for (int i = 0; i < 9; i++)
        if (papan[i] != 'X' && papan[i] != 'O')
            return false;
    return true;
}


void daftarPlayer() {
    Player p;
    cout << "Masukkan nama player: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, p.nama);
    players.push_back(p);
    simpanKeFile();
}

int pilihPlayer() {
    if (players.empty()) {
        cout << "? Belum ada player terdaftar!\n";
        return -1;
    }

    cout << "\n=== DAFTAR PLAYER ===\n";
    for (int i = 0; i < players.size(); i++)
        cout << i + 1 << ". " << players[i].nama << endl;

    int p;
    cout << "Pilih player: ";
    cin >> p;

    if (p < 1 || p > players.size()) {
        cout << "? Pilihan tidak valid!\n";
        return -1;
    }
    return p - 1;
}

void statistik(Player &p) {
    cout << "\n=== STATISTIK PLAYER ===\n";
    cout << "Nama   : " << p.nama << endl;
    cout << "Main   : " << p.main << endl;
    cout << "Menang : " << p.menang << endl;
    cout << "Seri   : " << p.seri << endl;
    cout << "Kalah  : " << p.kalah << endl;
    cout << "Skor   : " << p.skor << endl;
}


void leaderboard() {
    vector<Player> temp = players;

    for (int i = 0; i < temp.size() - 1; i++) {
        for (int j = i + 1; j < temp.size(); j++) {
            if (temp[j].skor > temp[i].skor) {
                Player t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    cout << "\n=== LEADERBOARD TOP 10 ===\n";
    for (int i = 0; i < temp.size() && i < 10; i++) {
        cout << i + 1 << ". " << temp[i].nama
             << " | Skor: " << temp[i].skor << endl;
    }
}


void vsKomputer(Player &p) {
    resetPapan();
    panduanPosisi();

    while (true) {
        tampilPapan();
        int m;
        cout << p.nama << " (X) pilih posisi: ";
        cin >> m;

        if (m < 1 || m > 9 || papan[m-1] == 'X' || papan[m-1] == 'O') {
            cout << "? Input tidak valid!\n";
            continue;
        }

        papan[m-1] = 'X';

        if (cekMenang('X')) {
            tampilPapan();
            cout << "?? ANDA MENANG!\n";
            p.menang++; p.skor += 10;
            break;
        }

        if (papanPenuh()) {
            tampilPapan();
            cout << "?? HASIL SERI!\n";
            p.seri++; p.skor += 5;
            break;
        }

        cout << "?? Komputer sedang berpikir...\n";
        int c;
        do { c = rand() % 9; }
        while (papan[c] == 'X' || papan[c] == 'O');

        papan[c] = 'O';

        if (cekMenang('O')) {
            tampilPapan();
            cout << "?? ANDA KALAH!\n";
            p.kalah++;
            break;
        }
    }

    p.main++;
    statistik(p);
    simpanKeFile();
}

void vsPlayer(Player &p1, Player &p2) {
    resetPapan();
    panduanPosisi();
    int giliran = 0;

    while (true) {
        tampilPapan();
        Player &p = (giliran % 2 == 0) ? p1 : p2;
        char tanda = (giliran % 2 == 0) ? 'X' : 'O';

        int m;
        cout << p.nama << " (" << tanda << ") pilih posisi: ";
        cin >> m;

        if (m < 1 || m > 9 || papan[m-1] == 'X' || papan[m-1] == 'O') {
            cout << "? Input tidak valid!\n";
            continue;
        }

        papan[m-1] = tanda;

        if (cekMenang(tanda)) {
            tampilPapan();
            cout << "?? " << p.nama << " MENANG!\n";
            p.menang++; p.skor += 10;
            if (giliran % 2 == 0) p2.kalah++;
            else p1.kalah++;
            break;
        }

        if (papanPenuh()) {
            tampilPapan();
            cout << "?? HASIL SERI!\n";
            p1.seri++; p2.seri++;
            p1.skor += 5; p2.skor += 5;
            break;
        }
        giliran++;
    }

    p1.main++; p2.main++;
    statistik(p1);
    statistik(p2);
    simpanKeFile();
}


int main() {
    srand(time(0));
    int menu;

    do {
        cout << "\n=== MENU TIC TAC TOE ===\n";
        cout << "1. Registrasi Player Baru\n";
        cout << "2. Main Game\n";
        cout << "3. Leaderboard\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu: ";
        cin >> menu;

        if (menu == 1) daftarPlayer();

        else if (menu == 2) {
            int p1 = pilihPlayer();
            if (p1 == -1) continue;

            cout << "1. VS Player\n2. VS Komputer\nPilih mode: ";
            int mode;
            cin >> mode;

            if (mode == 1) {
                int p2 = pilihPlayer();
                if (p2 == -1 || p1 == p2) continue;
                vsPlayer(players[p1], players[p2]);
            }
            else if (mode == 2) {
                vsKomputer(players[p1]);
            }
        }
        else if (menu == 3) leaderboard();

        else if (menu == 4)
            cout << "?? Terima kasih telah bermain Tic Tac Toe!\n";

    } while (menu != 4);

    return 0;
}
