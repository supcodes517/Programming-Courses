#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};

char kotak[10];
vector<Player> list_player;
int index_skrg = -1;

void muat_data() {
    ifstream masukan("tictactoe.txt");
    list_player.clear();
    if (masukan.is_open()) {
        Player p;
        while (masukan >> p.nama >> p.totalGames >> p.totalWins >> p.totalDraws >> p.totalLosses >> p.score) {
            list_player.push_back(p);
        }
        masukan.close();
    }
}

void simpan_data() {
    ofstream keluaran("tictactoe.txt");
    for (int i = 0; i < list_player.size(); i++) {
        keluaran << list_player[i].nama << " " << list_player[i].totalGames << " " 
                 << list_player[i].totalWins << " " << list_player[i].totalDraws << " " 
                 << list_player[i].totalLosses << " " << list_player[i].score << endl;
    }
    keluaran.close();
}

void reset_papan() {
    for (int i = 1; i <= 9; i++) {
        kotak[i] = (char)(i + '0');
    }
}

void tampil_papan() {
    system("cls");
    cout << "Player: " << list_player[index_skrg].nama << " | Skor: " << list_player[index_skrg].score << endl << endl;
    cout << " " << kotak[1] << " | " << kotak[2] << " | " << kotak[3] << endl;
    cout << "-----------" << endl;
    cout << " " << kotak[4] << " | " << kotak[5] << " | " << kotak[6] << endl;
    cout << "-----------" << endl;
    cout << " " << kotak[7] << " | " << kotak[8] << " | " << kotak[9] << endl << endl;
}

int cek_menang() {
    if (kotak[1] == kotak[2] && kotak[2] == kotak[3]) return 1;
    if (kotak[4] == kotak[5] && kotak[5] == kotak[6]) return 1;
    if (kotak[7] == kotak[8] && kotak[8] == kotak[9]) return 1;
    if (kotak[1] == kotak[4] && kotak[4] == kotak[7]) return 1;
    if (kotak[2] == kotak[5] && kotak[5] == kotak[8]) return 1;
    if (kotak[3] == kotak[6] && kotak[6] == kotak[9]) return 1;
    if (kotak[1] == kotak[5] && kotak[5] == kotak[9]) return 1;
    if (kotak[3] == kotak[5] && kotak[5] == kotak[7]) return 1;

    for (int i = 1; i <= 9; i++) {
        if (kotak[i] != 'X' && kotak[i] != 'O') return -1;
    }
    return 0;
}

void main_game() {
    reset_papan();
    int giliran = 1; 
    int status = -1;
    int pilihan;

    while (status == -1) {
        tampil_papan();
        if (giliran == 1) {
            cout << "Giliran " << list_player[index_skrg].nama << " (X): ";
            cin >> pilihan;
            if (pilihan < 1 || pilihan > 9 || kotak[pilihan] == 'X' || kotak[pilihan] == 'O') {
                continue;
            }
            kotak[pilihan] = 'X';
            giliran = 2;
        } else {
            cout << "Komputer mikir...";
            srand(time(0));
            do {
                pilihan = rand() % 9 + 1;
            } while (kotak[pilihan] == 'X' || kotak[pilihan] == 'O');
            kotak[pilihan] = 'O';
            giliran = 1;
        }
        status = cek_menang();
    }

    tampil_papan();
    list_player[index_skrg].totalGames++;
    
    if (status == 1) {
        if (giliran == 2) {
            cout << "MENANG! +3 Poin" << endl;
            list_player[index_skrg].totalWins++;
            list_player[index_skrg].score += 3;
        } else {
            cout << "KALAH! Komputer Menang" << endl;
            list_player[index_skrg].totalLosses++;
        }
    } else {
        cout << "SERI! +1 Poin" << endl;
        list_player[index_skrg].totalDraws++;
        list_player[index_skrg].score += 1;
    }

    simpan_data();
    cout << "Enter buat lanjut...";
    cin.ignore();
    cin.get();
}

int main() {
    muat_data();
    int menu;

    while (true) {
        system("cls");
        cout << "=== TIC TAC TOE MAHASISWA ===" << endl;
        cout << "1. Player Baru" << endl;
        cout << "2. Pilih Player" << endl;
        cout << "3. Leaderboard" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih: ";
        cin >> menu;

        if (menu == 1) {
            Player p;
            cout << "Nama baru: ";
            cin >> p.nama;
            p.totalGames = 0; p.totalWins = 0; p.totalDraws = 0; p.totalLosses = 0; p.score = 0;
            list_player.push_back(p);
            index_skrg = list_player.size() - 1;
            main_game();
        } 
        else if (menu == 2) {
            if (list_player.empty()) {
                cout << "Data kosong!" << endl;
            } else {
                for (int i = 0; i < list_player.size(); i++) {
                    cout << i + 1 << ". " << list_player[i].nama << endl;
                }
                int pilih_p;
                cout << "Nomor player: ";
                cin >> pilih_p;
                index_skrg = pilih_p - 1;
                main_game();
            }
        } 
        else if (menu == 3) {
            system("cls");
            cout << "Nama\tSkor\tM\tS\tK" << endl;
            for (int i = 0; i < list_player.size(); i++) {
                cout << list_player[i].nama << "\t" << list_player[i].score << "\t" 
                     << list_player[i].totalWins << "\t" << list_player[i].totalDraws << "\t" 
                     << list_player[i].totalLosses << endl;
            }
            cout << endl << "Enter buat balik...";
            cin.ignore();
            cin.get();
        } 
        else if (menu == 4) {
            break;
        }
    }
    return 0;
}
