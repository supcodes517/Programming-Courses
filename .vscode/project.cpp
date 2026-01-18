#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <ctime>
#include <algorithm>
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
Player* currentPlayer = NULL;
Player* player2 = NULL;

void tekanEnter() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void clearScreen() {
    system("cls||clear");
}

void tampilkanJudul() {
    clearScreen();
    cout << "================================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "================================\n\n";
}

void loadPlayers() {
    players.clear();
    ifstream file("players.txt");
    
    if (!file) {
        cout << "File player tidak ditemukan.  Membuat file baru...\n\n";
        ofstream buat("players.txt");
        buat.close();
        return;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        Player p;
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        size_t pos4 = line.find('|', pos3 + 1);
        size_t pos5 = line.find('|', pos4 + 1);
        
        p.nama = line.substr(0, pos1);
        p.totalGames = atoi(line.substr(pos1 + 1, pos2 - pos1 - 1).c_str());
        p.wins = atoi(line.substr(pos2 + 1, pos3 - pos2 - 1).c_str());
        p.draws = atoi(line.substr(pos3 + 1, pos4 - pos3 - 1).c_str());
        p.losses = atoi(line.substr(pos4 + 1, pos5 - pos4 - 1).c_str());
        p.score = atoi(line.substr(pos5 + 1).c_str());
        
        players.push_back(p);
    }
    
    file.close();
}

void savePlayers() {
    ofstream file("players.txt");
    for (size_t i = 0; i < players.size(); i++) {
        file << players[i].nama << "|"
             << players[i].totalGames << "|"
             << players[i].wins << "|"
             << players[i].draws << "|"
             << players[i].losses << "|"
             << players[i].score << "\n";
    }
    file.close();
}

void tampilkanStatistik(const Player& p) {
    cout << "\nStatistik " << p.nama << ":\n";
    cout << "- Total Games: " << p.totalGames << "\n";
    cout << "- Wins: " << p.wins << "\n";
    cout << "- Draws: " << p.draws << "\n";
    cout << "- Losses: " << p.losses << "\n";
    cout << "- Total Score: " << p.score << "\n";
}

void panduanPosisi() {
    cout << "Panduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void cetakBoard(const vector<char>& board) {
    cout << endl;
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n\n";
}

bool cekMenang(const vector<char>& board, char simbol) {
    // Cek baris
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == simbol && board[i+1] == simbol && board[i+2] == simbol)
            return true;
    }
    // Cek kolom
    for (int i = 0; i < 3; i++) {
        if (board[i] == simbol && board[i+3] == simbol && board[i+6] == simbol)
            return true;
    }
    // Cek diagonal
    if (board[0] == simbol && board[4] == simbol && board[8] == simbol)
        return true;
    if (board[2] == simbol && board[4] == simbol && board[6] == simbol)
        return true;
    
    return false;
}

bool papanPenuh(const vector<char>& board) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') return false;
    }
    return true;
}

int gerakanKomputer(const vector<char>& board) {
    // Coba menang
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            vector<char> temp = board;
            temp[i] = 'O';
            if (cekMenang(temp, 'O')) return i;
        }
    }
    // Coba blokir
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            vector<char> temp = board;
            temp[i] = 'X';
            if (cekMenang(temp, 'X')) return i;
        }
    }
    // Ambil tengah
    if (board[4] == ' ') return 4;
    // Ambil pojok
    int corners[] = {0, 2, 6, 8};
    for (int i = 0; i < 4; i++) {
        if (board[corners[i]] == ' ') return corners[i];
    }
    // Ambil sisi
    int sides[] = {1, 3, 5, 7};
    for (int i = 0; i < 4; i++) {
        if (board[sides[i]] == ' ') return sides[i];
    }
    return -1;
}

void gameVsKomputer() {
    char mainLagi;
    
    do {
        tampilkanJudul();
        
        cout << "=== BERMAIN TIC TAC TOE ===\n";
        cout << "Player: " << currentPlayer->nama << "\n";
        cout << "Anda akan bermain melawan komputer.\n";
        cout << "Anda sebagai 'X', komputer sebagai 'O'.\n\n";
        
        panduanPosisi();
        
        vector<char> board(9, ' ');
        bool giliranPlayer = true;
        bool gameSelesai = false;
        string hasil;
        int poin = 0;
        
        cout << "   |   |  \n";
        cout << "---|---|---\n";
        cout << "   |   |  \n";
        cout << "---|---|---\n";
        cout << "   |   |  \n\n";
        
        while (!gameSelesai) {
            if (giliranPlayer) {
                // Giliran player
                int pos;
                bool valid = false;
                
                while (!valid) {
                    cout << "Giliran Anda (X)\nMasukkan posisi (1-9): ";
                    string input;
                    cin >> input;
                    
                    // Cek apakah input angka
                    bool isNumber = true;
                    for (size_t i = 0; i < input.length(); i++) {
                        if (!isdigit(input[i])) {
                            isNumber = false;
                            break;
                        }
                    }
                    
                    if (!isNumber) {
                        cout << "Input harus angka 1-9!\n";
                        continue;
                    }
                    
                    pos = atoi(input.c_str());
                    
                    if (pos < 1 || pos > 9) {
                        cout << "Posisi harus antara 1-9!\n";
                    } else if (board[pos-1] != ' ') {
                        cout << "Posisi sudah terisi! Pilih posisi lain.\n";
                    } else {
                        valid = true;
                    }
                }
                
                board[pos-1] = 'X';
                
                if (cekMenang(board, 'X')) {
                    cetakBoard(board);
                    cout << "?? ANDA MENANG! ??\n";
                    hasil = "MENANG";
                    poin = 3;
                    gameSelesai = true;
                }
            } else {
                // Giliran komputer
                cout << "Komputer sedang berpikir...\n";
                
                int move = gerakanKomputer(board);
                
                if (move != -1) {
                    board[move] = 'O';
                    cout << "Komputer memilih posisi: " << move + 1 << "\n";
                }
                
                if (cekMenang(board, 'O')) {
                    cetakBoard(board);
                    cout << "?? KOMPUTER MENANG! ??\n";
                    hasil = "KALAH";
                    poin = 0;
                    gameSelesai = true;
                }
            }
            
            if (!gameSelesai && papanPenuh(board)) {
                cetakBoard(board);
                cout << "SERI! Tidak ada yang menang.\n";
                hasil = "SERI";
                poin = 1;
                gameSelesai = true;
            }
            
            if (!gameSelesai) {
                cetakBoard(board);
                giliranPlayer = !giliranPlayer;
            }
        }
        
        // Update statistik
        currentPlayer->totalGames++;
        if (hasil == "MENANG") {
            currentPlayer->wins++;
            currentPlayer->score += poin;
        } else if (hasil == "SERI") {
            currentPlayer->draws++;
            currentPlayer->score += poin;
        } else if (hasil == "KALAH") {
            currentPlayer->losses++;
        }
        
        // Update di vector players
        for (size_t i = 0; i < players.size(); i++) {
            if (players[i].nama == currentPlayer->nama) {
                players[i] = *currentPlayer;
                break;
            }
        }
        
        savePlayers();
        
        // Tampilkan hasil
        cout << "\n================================\n";
        cout << "       HASIL PERTANDINGAN\n";
        cout << "================================\n";
        cout << "Hasil: " << hasil << "\n";
        cout << "Score yang didapat: ";
        if (poin > 0) cout << "+";
        cout << poin << " poin\n\n";
        
        tampilkanStatistik(*currentPlayer);
        cout << "\nData telah disimpan ke file players.txt\n";
        
        cout << "\nMain lagi? (y/n): ";
        cin >> mainLagi;
        cin.ignore(1000, '\n');
        
    } while (mainLagi == 'y' || mainLagi == 'Y');
}

void gameVsPlayer() {
    // Pilih player 2
    tampilkanJudul();
    
    if (players.size() < 2) {
        cout << "Tidak ada player lain yang tersedia.\n";
        cout << "Silakan buat player lain terlebih dahulu.\n";
        tekanEnter();
        return;
    }
    
    cout << "=== PILIH PLAYER 2 ===\n";
    cout << "Daftar Player:\n";
    for (size_t i = 0; i < players.size(); i++) {
        if (&players[i] != currentPlayer) {
            cout << i+1 << ". " << players[i].nama 
                 << " (Score: " << players[i].score 
                 << ", Games: " << players[i].totalGames << ")\n";
        }
    }
    
    cout << "\nPilih Player 2: ";
    
    int pilihan;
    cin >> pilihan;
    cin.ignore(1000, '\n');
    
    if (pilihan < 1 || pilihan > (int)players.size() || 
        &players[pilihan-1] == currentPlayer) {
        cout << "Pilihan tidak valid!\n";
        tekanEnter();
        return;
    }
    
    player2 = &players[pilihan-1];
    
    char mainLagi;
    
    do {
        tampilkanJudul();
        
        cout << "Mode VS Player dipilih!\n";
        cout << "Player 1: X\n";
        cout << "Player 2: O\n\n";
        cout << "Tekan Enter untuk memulai...";
        cin.get();
        
        tampilkanJudul();
        cout << "=== BERMAIN TIC TAC TOE ===\n";
        panduanPosisi();
        
        vector<char> board(9, ' ');
        bool giliranPlayer1 = true;
        bool gameSelesai = false;
        string pemenang;
        int poin = 0;
        
        cout << "   |   |  \n";
        cout << "---|---|---\n";
        cout << "   |   |  \n";
        cout << "---|---|---\n";
        cout << "   |   |  \n\n";
        
        while (!gameSelesai) {
            cetakBoard(board);
            
            if (giliranPlayer1) {
                // Giliran player 1 (X)
                int pos;
                bool valid = false;
                
                while (!valid) {
                    cout << "Giliran Player X\nMasukkan posisi (1-9): ";
                    string input;
                    cin >> input;
                    
                    bool isNumber = true;
                    for (size_t i = 0; i < input.length(); i++) {
                        if (!isdigit(input[i])) {
                            isNumber = false;
                            break;
                        }
                    }
                    
                    if (!isNumber) {
                        cout << "Input harus angka 1-9!\n";
                        continue;
                    }
                    
                    pos = atoi(input.c_str());
                    
                    if (pos < 1 || pos > 9) {
                        cout << "Posisi harus antara 1-9!\n";
                    } else if (board[pos-1] != ' ') {
                        cout << "Posisi sudah terisi! Pilih posisi lain.\n";
                    } else {
                        valid = true;
                    }
                }
                
                board[pos-1] = 'X';
                
                if (cekMenang(board, 'X')) {
                    cetakBoard(board);
                    cout << "?? Player X MENANG! ??\n";
                    pemenang = "PLAYER1";
                    poin = 3;
                    gameSelesai = true;
                }
            } else {
                // Giliran player 2 (O)
                int pos;
                bool valid = false;
                
                while (!valid) {
                    cout << "Giliran Player O\nMasukkan posisi (1-9): ";
                    string input;
                    cin >> input;
                    
                    bool isNumber = true;
                    for (size_t i = 0; i < input.length(); i++) {
                        if (!isdigit(input[i])) {
                            isNumber = false;
                            break;
                        }
                    }
                    
                    if (!isNumber) {
                        cout << "Input harus angka 1-9!\n";
                        continue;
                    }
                    
                    pos = atoi(input.c_str());
                    
                    if (pos < 1 || pos > 9) {
                        cout << "Posisi harus antara 1-9!\n";
                    } else if (board[pos-1] != ' ') {
                        cout << "Posisi sudah terisi! Pilih posisi lain.\n";
                    } else {
                        valid = true;
                    }
                }
                
                board[pos-1] = 'O';
                
                if (cekMenang(board, 'O')) {
                    cetakBoard(board);
                    cout << "?? Player O MENANG! ??\n";
                    pemenang = "PLAYER2";
                    poin = 3;
                    gameSelesai = true;
                }
            }
            
            if (!gameSelesai && papanPenuh(board)) {
                cetakBoard(board);
                cout << "SERI! Tidak ada yang menang.\n";
                pemenang = "SERI";
                poin = 1;
                gameSelesai = true;
            }
            
            if (!gameSelesai) {
                giliranPlayer1 = !giliranPlayer1;
            }
        }
        
        // Update statistik
        currentPlayer->totalGames++;
        player2->totalGames++;
        
        if (pemenang == "PLAYER1") {
            currentPlayer->wins++;
            currentPlayer->score += 3;
            player2->losses++;
        } else if (pemenang == "PLAYER2") {
            player2->wins++;
            player2->score += 3;
            currentPlayer->losses++;
        } else if (pemenang == "SERI") {
            currentPlayer->draws++;
            currentPlayer->score += 1;
            player2->draws++;
            player2->score += 1;
        }
        
        // Update di vector players
        for (size_t i = 0; i < players.size(); i++) {
            if (players[i].nama == currentPlayer->nama) {
                players[i] = *currentPlayer;
            }
            if (players[i].nama == player2->nama) {
                players[i] = *player2;
            }
        }
        
        savePlayers();
        
        // Tampilkan hasil
        cout << "\n================================\n";
        cout << "       HASIL PERTANDINGAN\n";
        cout << "================================\n";
        
        if (pemenang == "PLAYER1") {
            cout << "Hasil untuk " << currentPlayer->nama << ": MENANG\n";
            cout << "Score yang didapat: +3 poin\n";
        } else if (pemenang == "PLAYER2") {
            cout << "Hasil untuk " << currentPlayer->nama << ": KALAH\n";
            cout << "Score yang didapat: +0 poin\n";
        } else {
            cout << "Hasil: SERI\n";
            cout << "Score yang didapat: +1 poin untuk " << currentPlayer->nama << " dan " << player2->nama << "\n";
        }
        
        cout << "\nStatistik " << currentPlayer->nama << ":\n";
        cout << "- Total Games: " << currentPlayer->totalGames << "\n";
        cout << "- Wins: " << currentPlayer->wins << "\n";
        cout << "- Draws: " << currentPlayer->draws << "\n";
        cout << "- Losses: " << currentPlayer->losses << "\n";
        cout << "- Total Score: " << currentPlayer->score << "\n";
        
        cout << "\nData telah disimpan ke file players.txt\n";
        
        cout << "\nMain lagi? (y/n): ";
        cin >> mainLagi;
        cin.ignore(1000, '\n');
        
    } while (mainLagi == 'y' || mainLagi == 'Y');
}

void menuPlayerBaru() {
    tampilkanJudul();
    
    cout << "=== REGISTRASI PLAYER BARU ===\n";
    cout << "Masukkan nama Anda: ";
    
    string nama;
    getline(cin, nama);
    
    if (nama.empty()) {
        cout << "\nNama tidak boleh kosong!\n";
        tekanEnter();
        return;
    }
    
    // Cek apakah nama sudah ada
    bool sudahAda = false;
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].nama == nama) {
            sudahAda = true;
            break;
        }
    }
    
    if (sudahAda) {
        cout << "\nPlayer dengan nama '" << nama << "' sudah ada!\n";
        tekanEnter();
        return;
    }
    
    Player p;
    p.nama = nama;
    p.totalGames = 0;
    p.wins = 0;
    p.draws = 0;
    p.losses = 0;
    p.score = 0;
    
    players.push_back(p);
    currentPlayer = &players.back();
    savePlayers();
    
    cout << "\nPlayer baru berhasil dibuat!\n";
    cout << "Selamat datang, " << p.nama << "!\n";
    
    cout << "\nStatistik Anda:\n";
    cout << "- Total Games: " << p.totalGames << "\n";
    cout << "- Wins: " << p.wins << "\n";
    cout << "- Draws: " << p.draws << "\n";
    cout << "- Losses: " << p.losses << "\n";
    cout << "- Total Score: " << p.score << "\n";

    // Tawarkan untuk langsung bermain
    cout << "\nIngin langsung bermain? (y/n): ";
    char jawab;
    cin >> jawab;
    cin.ignore(1000, '\n');
    
    if (jawab == 'y' || jawab == 'Y') {
        cout << "\n=== PILIH MODE PERMAINAN ===\n";
        cout << "1. VS Player\n";
        cout << "2. VS Komputer\n\n";
        cout << "Pilihan Anda: ";
        
        int mode;
        cin >> mode;
        cin.ignore(1000, '\n');
        
        if (mode == 1) {
            if (players.size() < 2) {
                cout << "\nTidak ada player lain yang tersedia.\n";
                cout << "Silakan pilih VS Komputer atau buat player lain terlebih dahulu.\n";
                tekanEnter();
            } else {
                gameVsPlayer();
            }
        } else if (mode == 2) {
            gameVsKomputer();
        } else {
            cout << "Pilihan tidak valid!\n";
            tekanEnter();
        }
    } else {
        tekanEnter();
    }
}

void menuPilihPlayer() {
    tampilkanJudul();
    
    if (players.empty()) {
        cout << "Belum ada player terdaftar.\n";
        tekanEnter();
        return;
    }
    
    cout << "=== DAFTAR PLAYER ===\n";
    cout << "No | Nama           | Score | Games | W  | D  | L\n";
    cout << "---|----------------|-------|-------|----|----|---\n";
    
    for (size_t i = 0; i < players.size(); i++) {
        cout << setw(2) << i+1 << "  | " 
             << left << setw(14) << players[i].nama << "|"
             << setw(6) << players[i].score << " |"
             << setw(6) << players[i].totalGames << " |"
             << setw(3) << players[i].wins << " |"
             << setw(3) << players[i].draws << " |"
             << setw(3) << players[i].losses << "\n";
    }
    
    cout << "\nPilih player (1-" << players.size() << ") atau 0 untuk kembali: ";
    
    int idx;
    cin >> idx;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (idx == 0) {
        return;
    }
    
    if (idx < 1 || idx > (int)players.size()) {
        cout << "\nPilihan tidak valid!\n";
        tekanEnter();
        return;
    }
    
    currentPlayer = &players[idx-1];
    cout << "\nPlayer dipilih: " << currentPlayer->nama << "\n";
    cout << "Selamat datang kembali, " << currentPlayer->nama << "!\n";
    
    cout << "\nStatistik Anda:\n";
    cout << "- Total Games: " << currentPlayer->totalGames << "\n";
    cout << "- Wins: " << currentPlayer->wins << "\n";
    cout << "- Draws: " << currentPlayer->draws << "\n";
    cout << "- Losses: " << currentPlayer->losses << "\n";
    cout << "- Total Score: " << currentPlayer->score << "\n";
    
    // Tawarkan untuk langsung bermain
    cout << "\nIngin langsung bermain? (y/n): ";
    char jawab;
    cin >> jawab;
    cin.ignore(1000, '\n');
    
    if (jawab == 'y' || jawab == 'Y') {
        cout << "\n=== PILIH MODE PERMAINAN ===\n";
        cout << "1. VS Player\n";
        cout << "2. VS Komputer\n\n";
        cout << "Pilihan Anda: ";
        
        int mode;
        cin >> mode;
        cin.ignore(1000, '\n');
        
        if (mode == 1) {
            if (players.size() < 2) {
                cout << "\nTidak ada player lain yang tersedia.\n";
                cout << "Silakan pilih VS Komputer atau buat player lain terlebih dahulu.\n";
                tekanEnter();
            } else {
                gameVsPlayer();
            }
        } else if (mode == 2) {
            gameVsKomputer();
        } else {
            cout << "Pilihan tidak valid!\n";
            tekanEnter();
        }
    } else {
        tekanEnter();
    }
}

void tampilkanLeaderboard() {
    tampilkanJudul();
    
    if (players.empty()) {
        cout << "Belum ada data player.\n";
        tekanEnter();
        return;
    }
    
    // Sorting manual untuk C++98
    vector<Player> sortedPlayers = players;
    for (size_t i = 0; i < sortedPlayers.size() - 1; i++) {
        for (size_t j = i + 1; j < sortedPlayers.size(); j++) {
            if (sortedPlayers[i].score < sortedPlayers[j].score) {
                Player temp = sortedPlayers[i];
                sortedPlayers[i] = sortedPlayers[j];
                sortedPlayers[j] = temp;
            }
        }
    }
    
    cout << "================================\n";
    cout << "        LEADERBOARD\n";
    cout << "  Top 10 Players by Score\n";
    cout << "================================\n\n";
    
    cout << "Rank | Nama           | Score | Games | W  | D  | L\n";
    cout << "-----|----------------|-------|-------|----|----|---\n";
    
    int limit = sortedPlayers.size();
    if (limit > 10) limit = 10;
    
    for (int i = 0; i < limit; i++) {
        cout << " " << setw(3) << i+1 << "  | " 
             << left << setw(14) << sortedPlayers[i].nama << "|"
             << setw(6) << sortedPlayers[i].score << " |"
             << setw(6) << sortedPlayers[i].totalGames << " |"
             << setw(3) << sortedPlayers[i].wins << " |"
             << setw(3) << sortedPlayers[i].draws << " |"
             << setw(3) << sortedPlayers[i].losses << "\n";
    }
    
    cout << "\n================================\n\n";
    tekanEnter();
}

int main() {
    srand(time(0));
    loadPlayers();
    
    while (true) {
        tampilkanJudul();
        
        cout << "=== MENU UTAMA ===\n";
        cout << "1. Player Baru\n";
        cout << "2. Pilih Player yang Sudah Ada\n";
        cout << "3. Lihat Leaderboard\n";
        cout << "4. Keluar\n\n";
        cout << "Pilihan Anda: ";
        
        int pilih;
        cin >> pilih;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (pilih) {
            case 1:
                menuPlayerBaru();
                break;
            case 2:
                menuPilihPlayer();
                break;
            case 3:
                tampilkanLeaderboard();
                break;
            case 4:
                savePlayers();
                tampilkanJudul();
                cout << "Terima kasih telah bermain!\n";
                return 0;
            default:
                cout << "\nPilihan tidak valid!\n";
                tekanEnter();
                break;
        }
    }   
    return 0;
}
