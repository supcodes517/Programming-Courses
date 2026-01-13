#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream> 

using namespace std;

struct Player {
    string nama;
    int totalMain = 0;
    int menang = 0;
    int seri = 0;
    int kalah = 0;
    int totalSkor = 0;
};


void simpanKeFile(Player daftar[], int jumlah) {
    ofstream fileKeluar("player.txt");
    if (fileKeluar.is_open()) {
        for (int i = 0; i < jumlah; i++) {
            fileKeluar << daftar[i].nama << " " 
                       << daftar[i].totalMain << " "
                       << daftar[i].menang << " " 
                       << daftar[i].seri << " "
                       << daftar[i].kalah << " " 
                       << daftar[i].totalSkor << endl;
        }
        fileKeluar.close();
    }
}

int muatDariFile(Player daftar[]) {
    ifstream fileMasuk("player.txt");
    if (!fileMasuk) {
        cout << "File player tidak ditemukan. Membuat file baru... " << endl;
        return 0;
    }
    
    int i = 0;
    while (fileMasuk >> daftar[i].nama >> daftar[i].totalMain >> daftar[i].menang 
                     >> daftar[i].seri >> daftar[i].kalah >> daftar[i].totalSkor) {
        i++;
    }
    fileMasuk.close();
    return i;
}


void tampilkanPapan(char papan[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << "  " << papan[i][0] << " | " << papan[i][1] << " | " << papan[i][2] << endl;
        if (i < 2) cout << " ---|---|---\n";
    }
    cout << "\n";
}

bool cekMenang(char b[3][3], char p) {
    for (int i = 0; i < 3; i++) {
        if (b[i][0] == p && b[i][1] == p && b[i][2] == p) return true;
        if (b[0][i] == p && b[1][i] == p && b[2][i] == p) return true;
    }
    return (b[0][0] == p && b[1][1] == p && b[2][2] == p) || (b[0][2] == p && b[1][1] == p && b[2][0] == p);
}

int gerakKomputer(char b[3][3]) {
    for (int i = 1; i <= 9; i++) {
        int r = (i-1)/3, c = (i-1)%3;
        if (b[r][c] == ' ') {
            b[r][c] = 'O';
            if (cekMenang(b, 'O')) { b[r][c] = ' '; return i; }
            b[r][c] = ' ';
        }
    }
    for (int i = 1; i <= 9; i++) {
        int r = (i-1)/3, c = (i-1)%3;
        if (b[r][c] == ' ') {
            b[r][c] = 'X';
            if (cekMenang(b, 'X')) { b[r][c] = ' '; return i; }
            b[r][c] = ' ';
        }
    }
    if (b[1][1] == ' ') return 5;
    for (int i = 1; i <= 9; i++) if (b[(i-1)/3][(i-1)%3] == ' ') return i;
    return -1;
}


int main() {
    srand(time(0));
    Player daftarPlayer[100]; 
    int jumlahPlayer = muatDariFile(daftarPlayer);
    int indeksAktif = -1;

    cout << "===================\nGAME TIC TAC TOE\n===================\n";

    while (true) {
        cout << "\n=== MENU UTAMA ===\n1. Player Baru\n2. Pilih Player yang Sudah Ada\n3. Lihat Leaderboard\n4. Keluar\n";
        cout << "\nPilihan Anda: ";
        int menu; cin >> menu;

        if (menu == 1) {
            cout << "\n=== REGISTRASI PLAYER BARU ===\nMasukkan nama : ";
            cin >> daftarPlayer[jumlahPlayer].nama;
            indeksAktif = jumlahPlayer;
            jumlahPlayer++;
            simpanKeFile(daftarPlayer, jumlahPlayer);
            cout << "\nPlayer baru berhasil dibuat!\n";
        } 
        else if (menu == 2) {
            if (jumlahPlayer == 0) { cout << "Belum ada player terdaftar!\n"; continue; }
            for (int i = 0; i < jumlahPlayer; i++) cout << i + 1 << ". " << daftarPlayer[i].nama << endl;
            cout << "Pilih nomor: "; int p; cin >> p;
            indeksAktif = p - 1;
        } 
        else if (menu == 3) {
            cout << "\n=== LEADERBOARD ===\nNama\tSkor\tMenang\n";
            for (int i = 0; i < jumlahPlayer; i++) 
                cout << daftarPlayer[i].nama << "\t" << daftarPlayer[i].totalSkor << "\t" << daftarPlayer[i].menang << endl;
            continue;
        } 
        else break;

        char mainLagi;
        do {
            char papan[3][3] = {{' ',' ',' '}, {' ',' ',' '}, {' ',' ',' '}};
            int langkah = 0; bool gameSelesai = false;
            
            while (!gameSelesai && langkah < 9) {
                tampilkanPapan(papan);
                int pos; cout << "Giliran " << daftarPlayer[indeksAktif].nama << " (X)\nMasukkan posisi (1-9): "; cin >> pos;
                if (pos < 1 || pos > 9 || papan[(pos-1)/3][(pos-1)%3] != ' ') {
                    cout << "Tidak valid!\n"; continue;
                }
                papan[(pos-1)/3][(pos-1)%3] = 'X'; langkah++;
                if (cekMenang(papan, 'X')) {
                    tampilkanPapan(papan); cout << "=== ANDA MENANG! ===\n";
                    daftarPlayer[indeksAktif].menang++; daftarPlayer[indeksAktif].totalSkor += 3;
                    gameSelesai = true;
                } else if (langkah < 9) {
                    int cp = gerakKomputer(papan);
                    papan[(cp-1)/3][(cp-1)%3] = 'O'; langkah++;
                    if (cekMenang(papan, 'O')) {
                        tampilkanPapan(papan); cout << "=== KOMPUTER MENANG! ===\n";
                        daftarPlayer[indeksAktif].kalah++; gameSelesai = true;
                    }
                }
            }
            
            if (!gameSelesai) { tampilkanPapan(papan); cout << "SERI!\n"; daftarPlayer[indeksAktif].seri++; daftarPlayer[indeksAktif].totalSkor += 1; }
            
            daftarPlayer[indeksAktif].totalMain++;
            simpanKeFile(daftarPlayer, jumlahPlayer); 
            
            cout << "\nData telah disimpan ke player.txt\n";
            cout << "Main lagi? (y/n): "; cin >> mainLagi;
        } while (mainLagi == 'y' || mainLagi == 'Y');
    }
    return 0;
}


