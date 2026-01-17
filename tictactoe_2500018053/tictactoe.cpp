#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <fstream>
#include <algorithm>
using namespace std;

// Sistem Player dengan Struct
struct Player {
    string nama;
    int TGS = 0; //Total Games
    int TWS = 0; //Total Wins
    int TDS = 0; //Total Draws
    int TLS = 0; //Total Losses
    int SC = 0; //Score
};

// Logic Array Board
void initBoard(char board[3][3]) {
    char num = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = num++;
}

// Fungsi untuk menampilkan board
void displayBoard(char board[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

// Fungsi untuk mengecek apakah posisi valid
bool isValidMove(char board[3][3], int move) {
    if (move < 1 || move > 9) 
        return false;

    int r = (move - 1) / 3;
    int c = (move - 1) % 3;

    return board[r][c] != 'X' && board[r][c] != 'O';
}

// Fungsi untuk menempatkan tanda pada board
void makeMove(char board[3][3], int move, char symbol) {
    int r = (move - 1) / 3;
    int c = (move - 1) % 3;
    board[r][c] = symbol;
}

// Fungsi untuk mengecek kemenangan
bool checkWin(char board[3][3], char s) {
    for (int i = 0; i < 3; i++)
        // Cek baris
        if ((board[i][0] == s && board[i][1] == s && board[i][2] == s) ||
            (board[0][i] == s && board[1][i] == s && board[2][i] == s))
            return true;

    // Cek diagonal
    if ((board[0][0] == s && board[1][1] == s && board[2][2] == s) ||
        (board[0][2] == s && board[1][1] == s && board[2][0] == s))
        return true;

    return false;
}

// Fungsi untuk mengecek apakah board penuh (draw)
bool boardFull(char board[3][3]) {
    for (int i = 1; i <= 9; i++)
        if (isValidMove(board, i)) return false;
    return true;
}

// Fungsi untuk menampilkan panduan posisi
void displayGuide() {
    cout << "\nPanduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

// Menampilkan hasil dan statistik
void tampilkanHasil(Player &p, char result) {
    if (result == 'X') {
        cout << "\n🎉 ANDA MENANG! 🎉\n\n";
    }
    else if (result == 'O') {
        cout << "\n💻 KOMPUTER MENANG! 💻\n\n";
    }
    else {
        cout << "\nSERI! Tidak ada yang menang.\n";
    }

    cout << "================================\n";
    cout << "       HASIL PERTANDINGAN\n";
    cout << "================================\n";

    if (result == 'X') {
        cout << "Hasil: MENANG\n";
        cout << "SC yang didapat: +3 poin\n\n";
    }
    else if (result == 'D') {
        cout << "Hasil: SERI\n";
        cout << "SC yang didapat: +1 poin\n\n";
    }
    else {
        cout << "Hasil: KALAH\n";
        cout << "SC yang didapat: +0 poin\n\n";
    }

    cout << "Statistik " << p.nama << ":\n";
    cout << "- Total Games: " << p.TGS << "\n";
    cout << "- Wins: " << p.TWS << "\n";
    cout << "- Draws: " << p.TDS << "\n";
    cout << "- Losses: " << p.TLS << "\n";
    cout << "- Total SC: " << p.SC << "\n\n";

    cout << "Data telah disimpan ke file players.txt\n\n";
}

// Menyimpan dan memuat data player
void savePlayers(const vector<Player>& players) {
    ofstream file("players.txt");
    for (const auto& p : players) {
        file << p.nama << " "
             << p.TGS << " "
             << p.TWS << " "
             << p.TDS << " "
             << p.TLS << " "
             << p.SC << "\n";
    }
    file.close();
}

// Memuat data player dari file
void loadPlayers(vector<Player>& players) {
    ifstream file("players.txt");
    if (!file.is_open()) return;

    players.clear();

    while (true) {
        Player p;
        if (!(file >> p.nama
                  >> p.TGS
                  >> p.TWS
                  >> p.TDS
                  >> p.TLS
                  >> p.SC)) {
            break;
        }
        if (p.nama.empty()) continue;
        players.push_back(p);
    }

    file.close();
}

// Hasil Menang VS Player
void tampilkanHasilVsPlayer(Player &p, char hasil) {
    if (hasil == 'X' || hasil == 'O') {
        cout << "\n🎉 Player " << hasil << " MENANG! 🎉\n\n";
    } else {
        cout << "\nSERI! Tidak ada yang menang.\n\n";
    }

    cout << "================================\n";
    cout << "       HASIL PERTANDINGAN\n";
    cout << "================================\n";

    if (hasil == 'D') {
        cout << "Hasil: SERI\n";
        cout << "SC yang didapat: +1 poin\n\n";
    } else {
        cout << "Hasil untuk " << p.nama << ": MENANG\n";
        cout << "SC yang didapat: +3 poin\n\n";
    }

    cout << "Statistik " << p.nama << ":\n";
    cout << "- Total Games: " << p.TGS << "\n";
    cout << "- Wins: " << p.TWS << "\n";
    cout << "- Draws: " << p.TDS << "\n";
    cout << "- Losses: " << p.TLS << "\n";
    cout << "- Total SC: " << p.SC << "\n\n";

    cout << "Data telah disimpan ke file players.txt\n\n";
}

// Hasil Seri VS Player
void tampilkanHasilSeriVsPlayer(Player &p1, Player &p2) {
    cout << "SERI! Tidak ada yang menang. \n\n";

    cout << "================================\n";
    cout << "       HASIL PERTANDINGAN\n";
    cout << "================================\n";

    cout << "Hasil: SERI\n";
    cout << "SC yang didapat: +1 poin\n\n";

    cout << "Statistik " << p1.nama << ":\n";
    cout << "- Total Games: " << p1.TGS << "\n";
    cout << "- Wins: " << p1.TWS << "\n";
    cout << "- Draws: " << p1.TDS << "\n";
    cout << "- Losses: " << p1.TLS << "\n";
    cout << "- Total SC: " << p1.SC << "\n\n";

    cout << "Statistik " << p2.nama << ":\n";
    cout << "- Total Games: " << p2.TGS << "\n";
    cout << "- Wins: " << p2.TWS << "\n";
    cout << "- Draws: " << p2.TDS << "\n";
    cout << "- Losses: " << p2.TLS << "\n";
    cout << "- Total SC: " << p2.SC << "\n\n";

    cout << "Data telah disimpan ke file players.txt\n\n";
}

// Menampilkan leaderboard
void tampilkanLeaderboard(vector<Player> players) {

    cout << "================================\n";
    cout << "        LEADERBOARD\n";
    cout << "  Top 10 Players by SC\n";
    cout << "================================\n\n";

    sort(players.begin(), players.end(), [](Player a, Player b) {
        return a.SC > b.SC;
    });

    cout << "Rank | Nama           | SC | Games | W  | D  | L  |\n";
    cout << "-----|----------------|-------|-------|----|----|----|\n";

    int limit = min(10, (int)players.size());
    for (int i = 0; i < limit; i++) {
        cout << setw(4) << i + 1 << " | "
             << left << setw(14) << players[i].nama << " | "
             << right << setw(5) << players[i].SC << " | "
             << setw(5) << players[i].TGS << " | "
             << setw(2) << players[i].TWS << " | "
             << setw(2) << players[i].TDS << " | "
             << setw(2) << players[i].TLS << " |\n";
    }

    cout << "\n================================\n\n";
    cout << "Tekan Enter untuk kembali ke menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Fungsi untuk komputer memilih move (AI sederhana)
int computerMove(char board[3][3]) {
    // Cek apakah komputer bisa menang
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i)) {
            char tempBoard[3][3];
            // Copy board
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    tempBoard[x][y] = board[x][y];

            makeMove(tempBoard, i, 'O');
            if (checkWin(tempBoard, 'O'))
                return i;
        }
    }

    // Cek apakah player bisa menang dan block
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i)) {
            char tempBoard[3][3];
            // Copy board
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    tempBoard[x][y] = board[x][y];

            makeMove(tempBoard, i, 'X');
            if (checkWin(tempBoard, 'X'))
                return i;
        }
    }
    // Coba ambil tengah
    if (isValidMove(board, 5))
        return 5;

    // Coba ambil sudut
    int corners[] = {1, 3, 7, 9};
    for (int i = 0; i < 4; i++)
        if (isValidMove(board, corners[i]))
            return corners[i];
            
    // Ambil posisi kosong pertama
    for (int i = 1; i <= 9; i++)
        if (isValidMove(board, i))
            return i;

    return -1;
}

// Fungsi untuk bermain vs Player
char playVsPlayer() {
    char board[3][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };

    cout << "\nMode VS Player dipilih!\n";
    cout << "Player 1: X\n";
    cout << "Player 2: O\n\n";
    cout << "Tekan Enter untuk memulai...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    cout << "================================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "================================\n\n";

    displayGuide();
    displayBoard(board);

    char turn = 'X';

    while (true) {
        cout << "Giliran Player " << turn << "\n";
        cout << "Masukkan posisi (1-9): ";

        int move;
        cin >> move;

        if (!isValidMove(board, move)) {
            cout << "Posisi tidak valid!\n";
            continue;
        }

        makeMove(board, move, turn);
        displayBoard(board);

        if (checkWin(board, turn)) {
            return turn;
        }

        if (boardFull(board)) {
            return 'D';
        }

        turn = (turn == 'X') ? 'O' : 'X';
    }
}

// Fungsi untuk bermain vs Komputer
char playVsComputer() {
    char board[3][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };

    cout << "================================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "================================\n\n";

    displayGuide();
    displayBoard(board);

    while (true) {
        // Giliran Player (X)
        int move;
        cout << "Giliran Anda (X)\n";
        cout << "Masukkan posisi (1-9): ";
        cin >> move;

        if (!isValidMove(board, move)) {
        cout << "Posisi tidak valid!\n";
            continue;   
        }
        
        makeMove(board, move, 'X');

        if (checkWin(board, 'X')) {
            displayBoard(board);
            return 'X';
        }

        if (boardFull(board)) {
            displayBoard(board);
            return 'D';
        }

        displayBoard(board);

        // Giliran Komputer (O)
        cout << "\nKomputer sedang berpikir...\n";
        int comp = computerMove(board);
        cout << "Komputer memilih posisi: " << comp << "\n";
        makeMove(board, comp, 'O');

        if (checkWin(board, 'O')) {
            displayBoard(board);
            return 'O';
        }

        if (boardFull(board)) {
            displayBoard(board);
            return 'D';
        }

        displayBoard(board);
    }
}

// Cek file players.txt
bool fplayer() {
    ifstream file("players.txt");
    return file.good();
}

int main() {
    vector<Player> players;
    loadPlayers(players);

    cout << "================================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "================================\n\n";

    if (!fplayer()) {
    cout << "File player tidak ditemukan.  Membuat file baru...\n\n";
    ofstream file("players.txt"); // Membuat file baru kalau engga ada filenya
    file.close();

}

    while (true) {
        cout << "=== MENU UTAMA ===\n";
        cout << "1. Player Baru\n";
        cout << "2. Pilih Player yang Sudah Ada\n";
        cout << "3. Lihat Leaderboard\n";
        cout << "4. Keluar\n\n";
        cout << "Pilihan Anda: ";

        int menu;
        cin >> menu;

        if (menu == 1) {
            Player p;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\n=== REGISTRASI PLAYER BARU ===\n";
            cout << "Masukkan nama Anda: ";
            getline(cin, p.nama);

            players.push_back(p);

            cout << "\nPlayer baru berhasil dibuat!\n";
            cout << "Selamat datang, " << p.nama << "!\n\n";

            cout << "Statistik Anda:\n";
            cout << "- Total Games: 0\n";
            cout << "- Wins: 0\n";
            cout << "- Draws: 0\n";
            cout << "- Losses: 0\n";
            cout << "- Total SC: 0\n\n";

            cout << "Tekan Enter untuk melanjutkan...";
            cin.get();
            cout << "\n\n";
        }

        else if (menu == 2) {
            if (players.empty()) {
                cout << "\nBelum ada player terdaftar.\n\n";
                continue;
            }
        
            cout << "\n=== DAFTAR PLAYER ===\n";
            cout << "No | Nama            | SC | Games | W  | D  | L\n";
            cout << "---+-----------------+-------+-------+----+----+---\n";

            for (size_t i = 0; i < players.size(); i++) {
                cout << setw(2) << i + 1 << " | "
                     << left << setw(15) << players[i].nama << " | "
                     << right << setw(5) << players[i].SC << " | "
                     << setw(5) << players[i].TGS << " | "
                     << setw(2) << players[i].TWS << " | "
                     << setw(2) << players[i].TDS << " | "
                     << setw(2) << players[i].TLS
                     << "\n";
            }

            int pilih;
            cout << "\nPilih player (1-" << players.size() << ") atau 0 untuk kembali: ";
            cin >> pilih;

            if (pilih == 0) continue;
            if (pilih < 1 || pilih > players.size()) continue;
            Player* player1 = &players[pilih - 1];
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nPlayer dipilih:  " << player1->nama << "\n\n";
            cout << "Selamat datang kembali, " << player1->nama << "!\n\n";

            cout << "Statistik Anda:\n";
            cout << "- Total Games: " << player1->TGS << "\n";
            cout << "- Wins: " << player1->TWS << "\n";
            cout << "- Draws: " << player1->TDS << "\n";
            cout << "- Losses: " << player1->TLS << "\n";
            cout << "- Total SC: " << player1->SC << "\n\n";

            cout << "Tekan Enter untuk melanjutkan...";
            cin.get();

            int mode;
            cout << "\nMode Permainan:\n";
            cout << "1. VS Player\n";
            cout << "2. VS Komputer\n";
            cout << "Pilih: ";
            cin >> mode;

            char result;

            if (mode == 1) {
                cout << "\n=== PILIH PLAYER 2 ===\n";
                for (size_t i = 0; i < players.size(); i++)
                    cout << i + 1 << ". " << players[i].nama << "\n";
            
                int pilih2;
                cout << "\nPilih player 2: ";
                cin >> pilih2;
            
                if (pilih2 < 1 || pilih2 > players.size() ||
                    &players[pilih2 - 1] == player1)
                    continue;
            
                Player* player2 = &players[pilih2 - 1];
            
                result = playVsPlayer();

                player1->TGS++;
                player2->TGS++;

                if (result == 'D') {
                    player1->TDS++;
                    player2->TDS++;
                    player1->SC++;
                    player2->SC++;
                
                    tampilkanHasilSeriVsPlayer(*player1, *player2);
                    savePlayers(players);
                }
                else if (result == 'X') {
                    player1->TWS++;
                    player2->TLS++;
                    player1->SC += 3;
                
                    tampilkanHasilVsPlayer(*player1, 'X');
                    savePlayers(players);
                }
                else {
                    player2->TWS++;
                    player1->TLS++;
                    player2->SC += 3;
                
                    tampilkanHasilVsPlayer(*player2, 'O');
                    savePlayers(players);
                }
            }

            else if (mode == 2) {
                result = playVsComputer();
            
                player1->TGS++;
            
                if (result == 'X') {
                    player1->TWS++;
                    player1->SC += 3;
                }
                else if (result == 'D') {
                    player1->TDS++;
                    player1->SC += 1;
                }
                else {
                    player1->TLS++;
                }
            
                tampilkanHasil(*player1, result);
                savePlayers(players);
            }

            char ulang;
            cout << "Main lagi? (y/n): ";
            cin >> ulang;

            if (ulang == 'n' || ulang == 'N') {
                savePlayers(players);
                cout << "\nKeluar dari game...";
                return 0;
            }
        }

            else if (menu == 3) {
                loadPlayers(players);
                tampilkanLeaderboard(players);
            }

            else if (menu == 4) {
                savePlayers(players);
                cout << "\nKeluar dari game...\n";
                return 0;
            }
    }
    return 0;
}
